//============================================================
//
//	�F�B���� [friend.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "friend.h"
#include "manager.h"
#include "sceneGame.h"
#include "gameManager.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "collision.h"
#include "fade.h"

#include "multiModel.h"
#include "objectBillboard.h"
#include "shadow.h"
#include "stage.h"
#include "player.h"
#include "field.h"
#include "building.h"
#include "obstacle.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* SETUP_TXT = "data\\TXT\\friend.txt";	// �F�B�Z�b�g�A�b�v�e�L�X�g

	const int PRIORITY = 3;		// �F�B�̗D�揇��

	// �F�B��{���
	namespace basic
	{
		const float	GRAVITY		= 1.0f;		// �d��
		const float	RADIUS		= 20.0f;	// ���a
		const float	HEIGHT		= 100.0f;	// �c��
		const float	REV_ROTA	= 0.03f;	// �����ύX�̕␳�W��
		const float	MIN_VARY	= 0.2f;		// �����ƖڕW�����̈Ⴄ�ʂ̋��e�l

		const float	NOR_JUMP_REV	= 0.16f;	// �ʏ��Ԏ��̋󒆂̈ړ��ʂ̌����W��
		const float	NOR_LAND_REV	= 0.16f;	// �ʏ��Ԏ��̒n��̈ړ��ʂ̌����W��

		
	}

	// �F�B���N���X���
	namespace other
	{
		const D3DXVECTOR3 EMOTION_PLUSPOS = D3DXVECTOR3(0.0f, 160.0f, 0.0f);	// ������o���̈ʒu���Z��
		const D3DXVECTOR3 EMOTION_SIZE = D3DXVECTOR3(120.0f, 120.0f, 0.0f);		// ������o���̑傫��
		const D3DXVECTOR3 SHADOW_SIZE = D3DXVECTOR3(80.0f, 0.0f, 80.0f);		// �e�̑傫��
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CFriend::mc_apTextureFile[] =	// �e�N�X�`���萔
{
	"data\\TEXTURE\\emotion000.png",	// ����������e�N�X�`��
};
const char *CFriend::mc_apModelFile[] =	// ���f���萔
{
	"data\\MODEL\\FRIEND\\00_waist.x",	// ��
	"data\\MODEL\\FRIEND\\01_body.x",	// ��
	"data\\MODEL\\FRIEND\\02_head.x",	// ��
	"data\\MODEL\\FRIEND\\03_armUL.x",	// ����r
	"data\\MODEL\\FRIEND\\04_armUR.x",	// �E��r
	"data\\MODEL\\FRIEND\\05_armDL.x",	// �����r
	"data\\MODEL\\FRIEND\\06_armDR.x",	// �E���r
	"data\\MODEL\\FRIEND\\07_handL.x",	// ����
	"data\\MODEL\\FRIEND\\08_handR.x",	// �E��
	"data\\MODEL\\FRIEND\\09_legUL.x",	// ��������
	"data\\MODEL\\FRIEND\\10_legUR.x",	// �E������
	"data\\MODEL\\FRIEND\\11_legDL.x",	// ����
	"data\\MODEL\\FRIEND\\12_legDR.x",	// �E��
	"data\\MODEL\\FRIEND\\13_footL.x",	// ����
	"data\\MODEL\\FRIEND\\14_footR.x",	// �E��
};

//************************************************************
//	�q�N���X [CFriend] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFriend::CFriend() : CObjectChara(CObject::LABEL_FRIEND, PRIORITY)
{
	// �����o�ϐ����N���A
	m_pEmotion		= NULL;			// ������o���̏��
	m_pShadow		= NULL;			// �e�̏��
	m_oldPos		= VEC3_ZERO;	// �ߋ��ʒu
	m_move			= VEC3_ZERO;	// �ړ���
	m_destRot		= VEC3_ZERO;	// �ڕW����
	m_state			= STATE_NONE;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_bJump			= false;		// �W�����v��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CFriend::~CFriend()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFriend::Init(void)
{
	// �����o�ϐ���������
	m_pEmotion		= NULL;			// ������o���̏��
	m_pShadow		= NULL;			// �e�̏��
	m_oldPos		= VEC3_ZERO;	// �ߋ��ʒu
	m_move			= VEC3_ZERO;	// �ړ���
	m_destRot		= VEC3_ZERO;	// �ڕW����
	m_state			= STATE_NORMAL;	// ���
	m_nCounterState	= 0;			// ��ԊǗ��J�E���^�[
	m_bJump			= false;		// �W�����v��

	// �I�u�W�F�N�g�L�����N�^�[�̏�����
	if (FAILED(CObjectChara::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �Z�b�g�A�b�v�̓ǂݍ���
	LoadSetup();

	// ���f�����̐ݒ�
	SetModelInfo();

	// ������o���̐���
	m_pEmotion = CObjectBillboard::Create(VEC3_ZERO, other::EMOTION_SIZE);
	if (m_pEmotion == NULL)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����Ǎ��E����
	m_pEmotion->BindTexture(mc_apTextureFile[TEXTURE_HAPPY]);

	// �����`���OFF�ɂ���
	m_pEmotion->SetEnableDraw(false);

	// �e�̐���
	m_pShadow = CShadow::Create(CShadow::TEXTURE_NORMAL, other::SHADOW_SIZE, this);
	if (m_pShadow == NULL)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFriend::Uninit(void)
{
	// ������o���̏I��
	m_pEmotion->Uninit();

	// �e�̏I��
	m_pShadow->Uninit();

	// �I�u�W�F�N�g�L�����N�^�[�̏I��
	CObjectChara::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFriend::Update(void)
{
	// �ϐ���錾
	EMotion currentMotion = MOTION_IDOL;	// ���݂̃��[�V����

	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:
		break;

	case STATE_NORMAL:

		// �ʏ��Ԃ̍X�V
		currentMotion = UpdateNormal();

		break;

	case STATE_UNION:

		// ������Ԏ��̍X�V
		currentMotion = UpdateUnion();

		break;

	default:
		assert(false);
		break;
	}

	// ������o���̍X�V
	m_pEmotion->Update();

	// �e�̍X�V
	m_pShadow->Update();

	// ���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V
	UpdateMotion(currentMotion);
}

//============================================================
//	�`�揈��
//============================================================
void CFriend::Draw(void)
{
	// �I�u�W�F�N�g�L�����N�^�[�̕`��
	CObjectChara::Draw();
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CFriend::SetState(const int nState)
{
	// �����̏�Ԃ�ݒ�
	m_state = (EState)nState;
}

//============================================================
//	��Ԏ擾����
//============================================================
int CFriend::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	���a�擾����
//============================================================
float CFriend::GetRadius(void) const
{
	// ���a��Ԃ�
	return basic::RADIUS;
}

//============================================================
//	�c���擾����
//============================================================
float CFriend::GetHeight(void) const
{
	// �c����Ԃ�
	return basic::HEIGHT;
}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CFriend::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	CObjectChara::SetVec3Position(rPos);	// ���g
	m_pEmotion->SetVec3Position(rPos + other::EMOTION_PLUSPOS);	// ������o��
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CFriend::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);		// ���g
	m_pShadow->SetEnableUpdate(bUpdate);	// �e
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CFriend::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);		// ���g
	m_pShadow->SetEnableDraw(bDraw);	// �e
}

//============================================================
//	�}�g���b�N�X�擾����
//============================================================
D3DXMATRIX CFriend::GetMtxWorld(void) const
{
	// �ϐ���錾
	D3DXMATRIX  mtxRot, mtxTrans, mtxWorld;		// �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 posFriend = GetVec3Position();	// �F�B�ʒu
	D3DXVECTOR3 rotFriend = GetVec3Rotation();	// �F�B����

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotFriend.y, rotFriend.x, rotFriend.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posFriend.x, posFriend.y, posFriend.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X��Ԃ�
	return mtxWorld;
}

//============================================================
//	��������
//============================================================
CFriend *CFriend::Create(void)
{
	// �|�C���^��錾
	CFriend *pFriend = NULL;	// �F�B�����p

	if (pFriend == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pFriend = new CFriend;	// �F�B
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pFriend != NULL)
	{ // �g�p����Ă���ꍇ

		// �F�B�̏�����
		if (FAILED(pFriend->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pFriend;
			pFriend = NULL;

			// ���s��Ԃ�
			return NULL;
		}
	}

	// �m�ۂ����A�h���X��Ԃ�
	return pFriend;
}

//============================================================
//	�ʏ��Ԏ��̍X�V����
//============================================================
CFriend::EMotion CFriend::UpdateNormal(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posFriend = GetVec3Position();	// �F�B�ʒu
	D3DXVECTOR3 rotFriend = GetVec3Rotation();	// �F�B����

	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W���
	if (pStage == NULL)
	{ // �X�e�[�W���g�p����Ă��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return MOTION_IDOL;
	}

	// �d�͂̍X�V
	UpdateGravity();

	// ���n����
	UpdateLanding(posFriend);

	// �����X�V
	UpdateRotation(rotFriend);

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posFriend, basic::RADIUS);

	// �ʒu�𔽉f
	SetVec3Position(posFriend);

	// �����𔽉f
	SetVec3Rotation(rotFriend);

	// �ҋ@���[�V������Ԃ�
	return MOTION_IDOL;
}

//============================================================
//	������Ԏ��̍X�V����
//============================================================
CFriend::EMotion CFriend::UpdateUnion(void)
{
	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W���
	if (pStage == NULL)
	{ // �X�e�[�W���g�p����Ă��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return MOTION_WAVEHAND;
	}

	CPlayer *pPlayer = CScene::GetPlayer();	// �v���C���[���
	if (pPlayer == NULL)
	{ // �v���C���[���g�p����Ă��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return MOTION_WAVEHAND;
	}

	// �ϐ���錾
	D3DXVECTOR3 posPlayer = pPlayer->GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 posFriend = GetVec3Position();			// �F�B�ʒu
	D3DXVECTOR3 rotFriend = GetVec3Rotation();			// �F�B����

	// �ڕW������ݒ�
	m_destRot.y = atan2f(posFriend.x - posPlayer.x, posFriend.z - posPlayer.z);

	if (fabsf(rotFriend.y - m_destRot.y) <= basic::MIN_VARY)
	{ // ������������x��v�����ꍇ

		// �����`���ON�ɂ���
		m_pEmotion->SetEnableDraw(true);
	}

	// �d�͂̍X�V
	UpdateGravity();

	// ���n����
	UpdateLanding(posFriend);

	// �����X�V
	UpdateRotation(rotFriend);

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posFriend, basic::RADIUS);

	// �ʒu�𔽉f
	SetVec3Position(posFriend);

	// �����𔽉f
	SetVec3Rotation(rotFriend);

	// ��U�胂�[�V������Ԃ�
	return MOTION_WAVEHAND;
}

//============================================================
//	�ߋ��ʒu�̍X�V����
//============================================================
void CFriend::UpdateOldPosition(void)
{
	// �ߋ��ʒu���X�V
	m_oldPos = GetVec3Position();
}

//============================================================
//	�d�͂̍X�V����
//============================================================
void CFriend::UpdateGravity(void)
{
	// �d�͂����Z
	m_move.y -= basic::GRAVITY;
}

//============================================================
//	���n�󋵂̍X�V����
//============================================================
bool CFriend::UpdateLanding(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	bool bLand = false;	// ���n��

	// �W�����v���Ă����Ԃɂ���
	m_bJump = true;

	// �ʒu�̍X�V
	// �r���̓����蔻��E���n����
	if (CollisionBuilding(rPos))
	{ // �r���ɒ��n���Ă����ꍇ

		// ���n���Ă����Ԃɂ���
		bLand = true;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;
	}

	// ��Q���̓����蔻��E���n����
	if (LandObstacle(rPos))
	{ // ��Q���ɒ��n���Ă����ꍇ

		// ���n���Ă����Ԃɂ���
		bLand = true;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;
	}

	// �n�ʁE�����ʒu�̒��n����
	if (CScene::GetStage()->LandFieldPosition(rPos, m_move)
	||  CScene::GetStage()->LandLimitPosition(rPos, m_move, 0.0f))
	{ // �F�B�����n���Ă����ꍇ

		// ���n���Ă����Ԃɂ���
		bLand = true;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;
	}

	// ���n�󋵂�Ԃ�
	return bLand;
}

//============================================================
//	�����̍X�V����
//============================================================
void CFriend::UpdateRotation(D3DXVECTOR3& rRot)
{
	// �ϐ���錾
	float fDiffRot = 0.0f;	// ��������

	// �ڕW�����̐��K��
	useful::NormalizeRot(m_destRot.y);

	// �ڕW�����܂ł̍������v�Z
	fDiffRot = m_destRot.y - rRot.y;

	// ���������̐��K��
	useful::NormalizeRot(fDiffRot);

	// �����̍X�V
	rRot.y += fDiffRot * basic::REV_ROTA;

	// �����̐��K��
	useful::NormalizeRot(rRot.y);
}

//============================================================
//	���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V����
//============================================================
void CFriend::UpdateMotion(int nMotion)
{
	// �ϐ���錾
	int nAnimMotion = GetMotionType();	// ���ݍĐ����̃��[�V����

	if (nMotion != NONE_IDX)
	{ // ���[�V�������ݒ肳��Ă���ꍇ

		if (IsMotionLoop(nAnimMotion))
		{ // ���[�v���郂�[�V�����������ꍇ

			if (nAnimMotion != nMotion)
			{ // ���݂̃��[�V�������Đ����̃��[�V�����ƈ�v���Ȃ��ꍇ

				// ���݂̃��[�V�����̐ݒ�
				SetMotion(nMotion);
			}
		}
	}

	// �I�u�W�F�N�g�L�����N�^�[�̍X�V
	CObjectChara::Update();
}

//============================================================
//	�r���Ƃ̈ꎲ���Ƃ̓����蔻��
//============================================================
bool CFriend::ResponseSingleBuilding(const EAxis axis, D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinFriend = D3DXVECTOR3(basic::RADIUS, 0.0f, basic::RADIUS);			// �F�B�ŏ��傫��
	D3DXVECTOR3 sizeMaxFriend = D3DXVECTOR3(basic::RADIUS, basic::HEIGHT, basic::RADIUS);	// �F�B�ő�傫��
	bool bMin = false;	// �s�̕����̔����
	bool bMax = false;	// ���̕����̔����
	bool bHit = false;	// �e���̔�����

	for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
	{ // �D�揇�ʂ̑������J��Ԃ�

		// �|�C���^��錾
		CObject *pObjectTop = CObject::GetTop(nCntPri);	// �擪�I�u�W�F�N�g

		if (pObjectTop != NULL)
		{ // �擪�����݂���ꍇ

			// �|�C���^��錾
			CObject *pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

			while (pObjCheck != NULL)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// �ϐ���錾
				D3DXVECTOR3 posBuild = VEC3_ZERO;		// �r���ʒu
				D3DXVECTOR3 rotBuild = VEC3_ZERO;		// �r������
				D3DXVECTOR3 sizeMinBuild = VEC3_ZERO;	// �r���ŏ��傫��
				D3DXVECTOR3 sizeMaxBuild = VEC3_ZERO;	// �r���ő�傫��

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_BUILDING)
				{ // �I�u�W�F�N�g���x�����r���ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �r���̈ʒu��ݒ�
				posBuild = pObjCheck->GetVec3Position();

				// �r���̌�����ݒ�
				rotBuild = pObjCheck->GetVec3Rotation();

				// �r���̍ŏ��̑傫����ݒ�
				sizeMinBuild = pObjCheck->GetVec3Sizing();
				sizeMinBuild.y = 0.0f;	// �c�̑傫����������

				// �r���̍ő�̑傫����ݒ�
				sizeMaxBuild = pObjCheck->GetVec3Sizing();
				sizeMaxBuild.y *= 2.0f;	// �c�̑傫����{�ɂ���

				switch (axis)
				{ // ���莲���Ƃ̏���
				case AXIS_X:	// X��

					// X���̏Փ˔���
					collision::ResponseSingleX
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posBuild,		// ����ڕW�ʒu
						sizeMaxFriend,	// ����T�C�Y(�E�E��E��)
						sizeMinFriend,	// ����T�C�Y(���E���E�O)
						sizeMaxBuild,	// ����ڕW�T�C�Y(�E�E��E��)
						sizeMinBuild,	// ����ڕW�T�C�Y(���E���E�O)
						&m_move,		// �ړ���
						&bMin,			// ������̔���
						&bMax			// �E����̔���
					);

					if (bMin || bMax)
					{ // �����瓖�����Ă����ꍇ

						// �Ԃ���󋵂ɂ���
						bHit = true;
					}

					break;

				case AXIS_Y:	// Y��

					// Y���̏Փ˔���
					collision::ResponseSingleY
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posBuild,		// ����ڕW�ʒu
						sizeMaxFriend,	// ����T�C�Y(�E�E��E��)
						sizeMinFriend,	// ����T�C�Y(���E���E�O)
						sizeMaxBuild,	// ����ڕW�T�C�Y(�E�E��E��)
						sizeMinBuild,	// ����ڕW�T�C�Y(���E���E�O)
						&m_move,		// �ړ���
						&bMin,			// ������̔���
						&bMax			// �ォ��̔���
					);

					if (bMax)
					{ // �ォ�瓖�����Ă����ꍇ

						// ���n���Ă���󋵂ɂ���
						bHit = true;
					}

					break;

				case AXIS_Z:	// Z��

					// Z���̏Փ˔���
					collision::ResponseSingleZ
					( // ����
						rPos,			// ����ʒu
						m_oldPos,		// ����ߋ��ʒu
						posBuild,		// ����ڕW�ʒu
						sizeMaxFriend,	// ����T�C�Y(�E�E��E��)
						sizeMinFriend,	// ����T�C�Y(���E���E�O)
						sizeMaxBuild,	// ����ڕW�T�C�Y(�E�E��E��)
						sizeMinBuild,	// ����ڕW�T�C�Y(���E���E�O)
						&m_move,		// �ړ���
						&bMin,			// �O����̔���
						&bMax			// �ォ��̔���
					);

					if (bMin || bMax)
					{ // �����瓖�����Ă����ꍇ

						// �Ԃ���󋵂ɂ���
						bHit = true;
					}

					break;

				default:	// ��O����
					assert(false);
					break;
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	// �e���̔������Ԃ�
	return bHit;
}

//============================================================
//	��Q���Ƃ̒��n����
//============================================================
bool CFriend::LandObstacle(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinFriend = D3DXVECTOR3(basic::RADIUS, 0.0f, basic::RADIUS);			// �F�B�ŏ��傫��
	D3DXVECTOR3 sizeMaxFriend = D3DXVECTOR3(basic::RADIUS, basic::HEIGHT, basic::RADIUS);	// �F�B�ő�傫��
	bool bLand = false;	// ���n��

	for (int nCntPri = 0; nCntPri < MAX_PRIO; nCntPri++)
	{ // �D�揇�ʂ̑������J��Ԃ�

		// �|�C���^��錾
		CObject *pObjectTop = CObject::GetTop(nCntPri);	// �擪�I�u�W�F�N�g

		if (pObjectTop != NULL)
		{ // �擪�����݂���ꍇ

			// �|�C���^��錾
			CObject *pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

			while (pObjCheck != NULL)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// �ϐ���錾
				D3DXVECTOR3 pos0, pos1, pos2, pos3;	// ���_���W����p
				D3DXVECTOR3 posObs  = VEC3_ZERO;	// ��Q���ʒu
				D3DXVECTOR3 rotObs  = VEC3_ZERO;	// ��Q������
				D3DXVECTOR3 sizeObs = VEC3_ZERO;	// ��Q���傫��
				float fAngle  = 0.0f;	// �Ίp���̊p�x
				float fLength = 0.0f;	// �Ίp���̒���
				bool  bHit = false;		// ������

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_OBSTACLE)
				{ // �I�u�W�F�N�g���x������Q���ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck->GetState() != CObstacle::STATE_LAND)
				{ // ���n�ł�������Ԃł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// ��Q���̏����擾
				posObs  = pObjCheck->GetVec3Position();	// �ʒu
				rotObs  = pObjCheck->GetVec3Rotation();	// ����
				sizeObs = pObjCheck->GetVec3Sizing();	// �傫��
				fAngle  = pObjCheck->GetAngle();		// �Ίp���p�x
				fLength = pObjCheck->GetLength();		// �Ίp������

				// ���_���W���v�Z
				pos0.x = posObs.x + sinf(rotObs.y + (D3DX_PI + fAngle)) * fLength;
				pos0.y = 0.0f;
				pos0.z = posObs.z + cosf(rotObs.y + (D3DX_PI + fAngle)) * fLength;
				pos1.x = posObs.x + sinf(rotObs.y + (D3DX_PI - fAngle)) * fLength;
				pos1.y = 0.0f;
				pos1.z = posObs.z + cosf(rotObs.y + (D3DX_PI - fAngle)) * fLength;
				pos3.x = posObs.x + sinf(rotObs.y - fAngle) * fLength;
				pos3.y = 0.0f;
				pos3.z = posObs.z + cosf(rotObs.y - fAngle) * fLength;
				pos2.x = posObs.x + sinf(rotObs.y + fAngle) * fLength;
				pos2.y = 0.0f;
				pos2.z = posObs.z + cosf(rotObs.y + fAngle) * fLength;

				// ��Q���Ƃ̔���
				if (rPos.y + basic::HEIGHT > posObs.y
				&&  rPos.y < posObs.y + sizeObs.y)
				{ // Y���W���͈͓��̏ꍇ

					// �񎲂̋�`�̏Փ˔���
					bHit = collision::BoxOuterPillar
					( // ����
						pos0,	// �l�p�̊e���_
						pos1,	// �l�p�̊e���_
						pos2,	// �l�p�̊e���_
						pos3,	// �l�p�̊e���_
						rPos	// ����ʒu
					);
				}

				if (bHit)
				{ // �������Ă����ꍇ

					if (m_oldPos.y >= posObs.y + sizeObs.y)
					{ // �O��̈ʒu�����n�_�ȏ�̏ꍇ

						// �F�B�ʒu����Q���̏�ɂ���
						rPos.y = posObs.y + sizeObs.y;

						// ���n���Ă���󋵂ɂ���
						bLand = true;

						// �c�ړ��ʂ�������
						m_move.y = 0.0f;
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	// ���n�󋵂�Ԃ�
	return bLand;
}

//============================================================
//	�r���Ƃ̓����蔻��
//============================================================
bool CFriend::CollisionBuilding(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	bool bLand = false;	// ���n��

	// �ړ��ʂ����Z
	rPos.x += m_move.x;

	// X���̓����蔻��
	if (ResponseSingleBuilding(AXIS_X, rPos))
	{ // ���ɓ������Ă����ꍇ

		// �q�b�g
		Hit();
	}

	// �ړ��ʂ����Z
	rPos.y += m_move.y;

	// Y���̓����蔻��
	if (ResponseSingleBuilding(AXIS_Y, rPos))
	{ // ��ɓ������Ă����ꍇ

		// ���n���Ă���󋵂ɂ���
		bLand = true;
	}

	// �ړ��ʂ����Z
	rPos.z += m_move.z;

	// Z���̓����蔻��
	if (ResponseSingleBuilding(AXIS_Z, rPos))
	{ // ���ɓ������Ă����ꍇ

		// �q�b�g
		Hit();
	}

	// �ړ��ʂ�����
	if (m_bJump)
	{ // �󒆂̏ꍇ

		m_move.x += (0.0f - m_move.x) * basic::NOR_JUMP_REV;
		m_move.z += (0.0f - m_move.z) * basic::NOR_JUMP_REV;
	}
	else
	{ // �n��̏ꍇ

		m_move.x += (0.0f - m_move.x) * basic::NOR_LAND_REV;
		m_move.z += (0.0f - m_move.z) * basic::NOR_LAND_REV;
	}

	// ���n�󋵂�Ԃ�
	return bLand;
}

//============================================================
//	�Z�b�g�A�b�v����
//============================================================
void CFriend::LoadSetup(void)
{
	// �ϐ���錾
	CMotion::SMotionInfo info;		// �|�[�Y�̑���p
	D3DXVECTOR3 pos = VEC3_ZERO;	// �ʒu�̑���p
	D3DXVECTOR3 rot = VEC3_ZERO;	// �����̑���p
	int nID			= 0;	// �C���f�b�N�X�̑���p
	int nParentID	= 0;	// �e�C���f�b�N�X�̑���p
	int nNowPose	= 0;	// ���݂̃|�[�Y�ԍ�
	int nNowKey		= 0;	// ���݂̃L�[�ԍ�
	int nLoop		= 0;	// ���[�v��ON/OFF�̕ϊ��p
	int nEnd		= 0;	// �e�L�X�g�ǂݍ��ݏI���̊m�F�p

	// �ϐ��z���錾
	char aString[MAX_STRING];	// �e�L�X�g�̕�����̑���p

	// �|�C���^��錾
	FILE *pFile;	// �t�@�C���|�C���^

	// �|�[�Y����p�̕ϐ���������
	memset(&info, 0, sizeof(info));

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(SETUP_TXT, "r");

	if (pFile != NULL)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			// �L�����N�^�[�̐ݒ�
			if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{ // �ǂݍ��񂾕����� CHARACTERSET �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_CHARACTERSET �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "PARTSSET") == 0)
					{ // �ǂݍ��񂾕����� PARTSSET �̏ꍇ

						do
						{ // �ǂݍ��񂾕����� END_PARTSSET �ł͂Ȃ��ꍇ���[�v

							// �t�@�C�����當�����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "INDEX") == 0)
							{ // �ǂݍ��񂾕����� INDEX �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &nID);			// ���f���̃C���f�b�N�X��ǂݍ���
							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{ // �ǂݍ��񂾕����� PARENT �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &nParentID);	// ���f���̐e�̃C���f�b�N�X��ǂݍ���
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{ // �ǂݍ��񂾕����� POS �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%f", &pos.x);		// X���W��ǂݍ���
								fscanf(pFile, "%f", &pos.y);		// Y���W��ǂݍ���
								fscanf(pFile, "%f", &pos.z);		// Z���W��ǂݍ���
							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{ // �ǂݍ��񂾕����� ROT �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%f", &rot.x);		// X������ǂݍ���
								fscanf(pFile, "%f", &rot.y);		// Y������ǂݍ���
								fscanf(pFile, "%f", &rot.z);		// Z������ǂݍ���
							}
						} while (strcmp(&aString[0], "END_PARTSSET") != 0);	// �ǂݍ��񂾕����� END_PARTSSET �ł͂Ȃ��ꍇ���[�v

						// �p�[�c���̐ݒ�
						CObjectChara::SetPartsInfo(nID, nParentID, pos, rot, mc_apModelFile[nID]);
					}
				} while (strcmp(&aString[0], "END_CHARACTERSET") != 0);		// �ǂݍ��񂾕����� END_CHARACTERSET �ł͂Ȃ��ꍇ���[�v
			}

			// ���[�V�����̐ݒ�
			else if (strcmp(&aString[0], "MOTIONSET") == 0)
			{ // �ǂݍ��񂾕����� MOTIONSET �̏ꍇ

				// ���݂̃|�[�Y�ԍ���������
				nNowPose = 0;

				do
				{ // �ǂݍ��񂾕����� END_MOTIONSET �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "LOOP") == 0)
					{ // �ǂݍ��񂾕����� LOOP �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &nLoop);		// ���[�v��ON/OFF��ǂݍ���

						// �ǂݍ��񂾒l��bool�^�ɕϊ�
						info.bLoop = (nLoop == 0) ? false : true;
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)
					{ // �ǂݍ��񂾕����� NUM_KEY �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);	// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &info.nNumKey);	// �L�[�̑�����ǂݍ���
					}
					else if (strcmp(&aString[0], "KEYSET") == 0)
					{ // �ǂݍ��񂾕����� KEYSET �̏ꍇ

						// ���݂̃L�[�ԍ���������
						nNowKey = 0;

						do
						{ // �ǂݍ��񂾕����� END_KEYSET �ł͂Ȃ��ꍇ���[�v

							// �t�@�C�����當�����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "FRAME") == 0)
							{ // �ǂݍ��񂾕����� FRAME �̏ꍇ

								fscanf(pFile, "%s", &aString[0]);						// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &info.aKeyInfo[nNowPose].nFrame);	// �L�[���؂�ւ��܂ł̃t���[������ǂݍ���
							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{ // �ǂݍ��񂾕����� KEY �̏ꍇ

								do
								{ // �ǂݍ��񂾕����� END_KEY �ł͂Ȃ��ꍇ���[�v

									// �t�@�C�����當�����ǂݍ���
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "POS") == 0)
									{ // �ǂݍ��񂾕����� POS �̏ꍇ

										fscanf(pFile, "%s", &aString[0]);									// = ��ǂݍ��� (�s�v)
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].pos.x);	// X�ʒu��ǂݍ���
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].pos.y);	// Y�ʒu��ǂݍ���
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].pos.z);	// Z�ʒu��ǂݍ���

										// �ǂݍ��񂾈ʒu�Ƀp�[�c�̏����ʒu�����Z
										info.aKeyInfo[nNowPose].aKey[nNowKey].pos += GetPartsPosition(nNowKey);
									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{ // �ǂݍ��񂾕����� ROT �̏ꍇ

										fscanf(pFile, "%s", &aString[0]);									// = ��ǂݍ��� (�s�v)
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].rot.x);	// X������ǂݍ���
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].rot.y);	// Y������ǂݍ���
										fscanf(pFile, "%f", &info.aKeyInfo[nNowPose].aKey[nNowKey].rot.z);	// Z������ǂݍ���

										// �ǂݍ��񂾌����Ƀp�[�c�̏������������Z
										info.aKeyInfo[nNowPose].aKey[nNowKey].rot += GetPartsRotation(nNowKey);

										// ���������𐳋K��
										useful::NormalizeRot(info.aKeyInfo[nNowPose].aKey[nNowKey].rot.x);
										useful::NormalizeRot(info.aKeyInfo[nNowPose].aKey[nNowKey].rot.y);
										useful::NormalizeRot(info.aKeyInfo[nNowPose].aKey[nNowKey].rot.z);
									}

								} while (strcmp(&aString[0], "END_KEY") != 0);	// �ǂݍ��񂾕����� END_KEY �ł͂Ȃ��ꍇ���[�v

								// ���݂̃L�[�ԍ������Z
								nNowKey++;
							}
						} while (strcmp(&aString[0], "END_KEYSET") != 0);	// �ǂݍ��񂾕����� END_KEYSET �ł͂Ȃ��ꍇ���[�v

						// ���݂̃|�[�Y�ԍ������Z
						nNowPose++;
					}
				} while (strcmp(&aString[0], "END_MOTIONSET") != 0);	// �ǂݍ��񂾕����� END_MOTIONSET �ł͂Ȃ��ꍇ���[�v

				// ���[�V�������̐ݒ�
				CObjectChara::SetMotionInfo(info);
			}
		} while (nEnd != EOF);	// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v
		
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "�F�B�Z�b�g�A�b�v�t�@�C���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}
}

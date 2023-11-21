//============================================================
//
//	�v���C���[���� [player.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "player.h"
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
#include "objectOrbit.h"
#include "shadow.h"
#include "object2D.h"
#include "timerManager.h"
#include "rankingManager.h"
#include "stage.h"
#include "field.h"
#include "building.h"
#include "obstacle.h"
#include "savePoint.h"
#include "goalPoint.h"
#include "friend.h"

#include "effect3D.h"
#include "particle3D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* SETUP_TXT = "data\\TXT\\player.txt";	// �v���C���[�Z�b�g�A�b�v�e�L�X�g

	const int PRIORITY = 3;	// �v���C���[�̗D�揇��
	const int CNT_WAIT[CRetentionManager::RESULT_MAX] = { 0, 40, 220 };	// ���U���g�J�ڎ��̗]�C�t���[��

	// �v���C���[��{���
	namespace basic
	{
		const float	MOVE		= 2.8f;		// �ړ���
		const float	JUMP		= 21.0f;	// �W�����v�㏸��
		const float	GRAVITY		= 1.0f;		// �d��
		const float	RADIUS		= 20.0f;	// ���a
		const float	HEIGHT		= 100.0f;	// �c��
		const float	REV_ROTA	= 0.15f;	// �����ύX�̕␳�W��
		const float	BLOW_SIDE	= 10.0f;	// ������ю��̉��ړ���
		const float	BLOW_UP		= 30.0f;	// ������ю��̏c�ړ���
		const float	ADD_MOVE	= 0.08f;	// ��A�N�V�������̑��x���Z��
		const float	MIN_VARY	= 0.001f;	// �����ƖڕW�����̈Ⴄ�ʂ̋��e�l

		const int	LAND_SE_CNT = 10;			// ���n����SE��炷�ϋ�t���[��
		const int	JUMP_SAVECONTROL_CNT = 10;	// �W�����v�����ێ�����t���[��

		const float	JUMPPAD_MOVE	= 50.0f;	// �W�����v�p�b�h�̏�ړ���
		const float	NOR_JUMP_REV	= 0.16f;	// �ʏ��Ԏ��̋󒆂̈ړ��ʂ̌����W��
		const float	NOR_LAND_REV	= 0.16f;	// �ʏ��Ԏ��̒n��̈ړ��ʂ̌����W��
		const float	DMG_JUMP_REV	= 0.015f;	// �_���[�W��Ԏ��̋󒆂̈ړ��ʂ̌����W��
		const float	DMG_LAND_REV	= 0.25f;	// �_���[�W��Ԏ��̒n��̈ړ��ʂ̌����W��
		const float DMG_SUB_ALPHA	= 0.025f;	// �_���[�W��Ԏ��̓����x�̌��Z��
		const float	SPAWN_ADD_ALPHA	= 0.03f;	// �X�|�[����Ԏ��̓����x�̉��Z��

		const D3DXVECTOR3 DMG_ADDROT = D3DXVECTOR3(0.04f, 0.0f, -0.02f);	// �_���[�W��Ԏ��̃v���C���[��]��
	}

	// �X���C�f�B���O���
	namespace slide
	{
		const float	CONTROL_MIN		= 2.4f;		// �X���C�f�B���O���\�ɂȂ�ړ���
		const float	PLUS_SUB_MOVE	= 0.0035f;	// �ړ��ʂ̍ő�ǉ����Z��

		const int	MIN_END_CNT	= 30;		// �X���C�f�B���O�̉������삪�ł���悤�ɂȂ�J�E���g
		const int	MAX_END_CNT	= 80;		// �X���C�f�B���O�������I������J�E���g
		const float	MIN_MOVE	= 1.25f;	// �ړ��ʂ̍Œᑬ�x
		const float	SUB_MOVE	= 0.01f;	// �X���C�f�B���O���̑��x���Z��
	}

	// �Ǒ�����
	namespace walldash
	{
		const float	CONTROL_MIN		= 2.0f;		// �Ǒ��肪�\�ɂȂ�ړ���
		const float	PLUS_SUB_MOVE	= 0.0f;		// �ړ��ʂ̍ő�ǉ����Z��
		const float	PLUS_COLL_SIZE	= 90.0f;	// ����̊g����
		const float	MAX_GRAVITY		= -8.2f;	// �d�͂̍ő�l
		const float	GRAVITY_LOW		= 0.28f;	// �㏸�ʂ��Ȃ��ꍇ�̏d��
		const float	GRAVITY_HIGH	= 1.3f;		// �㏸�ʂ�����ꍇ�̏d��
		const float	PLUSMOVE_UP		= 22.0f;	// �ǃ_�b�V���������̏㏸��
		const float	PLUSMOVE_SIDE	= 3.0f;		// �ǃ_�b�V���������̉�����
		const float	REV_PLUSMOVE	= 0.1f;		// �v���X�ړ��ʂ̌����W��

		const int	MIN_END_CNT	= 16;		// �Ǒ���̉������삪�ł���悤�ɂȂ�J�E���g
		const float	MIN_MOVE	= 1.5f;		// �ړ��ʂ̍Œᑬ�x
		const float	SUB_MOVE	= 0.004f;	// �Ǒ��莞�̑��x���Z��
		const float	COLL_SIZE	= 100.0f;	// �Ǒ���̔���傫��
		const float	BOOST_RATE	= 0.0f;		// �����ł���ʒu����
	}

	// �N���A�\�����
	namespace clear
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(-420.0f, 620.0f, 0.0f);	// �N���A�\���̈ʒu
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(823.0f, 200.0f, 0.0f);	// �N���A�\���̑傫��

		const float MOVE_POS = 82.0f;	// �ړ���
		const float STOP_POS = 450.0f;	// ��~�ʒu
	}

	// �G�t�F�N�g���
	namespace effect
	{
		const float	SMOKE_RADIUS	= 30.0f;	// ���̔��a
		const int	SMOKE_LIFE		= 20;		// ���̎���
	}

	// �p�[�e�B�N�����
	namespace particle
	{
		const D3DXCOLOR	COL_HEAL = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);	// �񕜃p�[�e�B�N���̐F
	}

	// �v���C���[���N���X���
	namespace other
	{
		const int ORBIT_PARTS[]		= { CPlayer::MODEL_ARMDL, CPlayer::MODEL_ARMDR, CPlayer::MODEL_LEGDL, CPlayer::MODEL_LEGDR };	// �O�Ղ��o���p�[�c�̃C���f�b�N�X
		const int ORBIT_PART		= 20;	// �O�Ղ̕�����
		const D3DXCOLOR ORBIT_COL	= D3DXCOLOR(0.0f, 0.9f, 1.0f, 0.8f);	// �O�Ղ̐F

		const D3DXVECTOR3 SHADOW_SIZE = D3DXVECTOR3(80.0f, 0.0f, 80.0f);	// �e�̑傫��
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CPlayer::mc_apTextureFile[] =	// �e�N�X�`���萔
{
	"data\\TEXTURE\\clear000.png",	// �N���A�\���e�N�X�`��
};
const char *CPlayer::mc_apModelFile[] =	// ���f���萔
{
	"data\\MODEL\\PLAYER\\00_waist.x",	// ��
	"data\\MODEL\\PLAYER\\01_body.x",	// ��
	"data\\MODEL\\PLAYER\\02_head.x",	// ��
	"data\\MODEL\\PLAYER\\03_armUL.x",	// ����r
	"data\\MODEL\\PLAYER\\04_armUR.x",	// �E��r
	"data\\MODEL\\PLAYER\\05_armDL.x",	// �����r
	"data\\MODEL\\PLAYER\\06_armDR.x",	// �E���r
	"data\\MODEL\\PLAYER\\07_handL.x",	// ����
	"data\\MODEL\\PLAYER\\08_handR.x",	// �E��
	"data\\MODEL\\PLAYER\\09_legUL.x",	// ��������
	"data\\MODEL\\PLAYER\\10_legUR.x",	// �E������
	"data\\MODEL\\PLAYER\\11_legDL.x",	// ����
	"data\\MODEL\\PLAYER\\12_legDR.x",	// �E��
	"data\\MODEL\\PLAYER\\13_footL.x",	// ����
	"data\\MODEL\\PLAYER\\14_footR.x",	// �E��
};

//************************************************************
//	�q�N���X [CPlayer] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPlayer::CPlayer() : CObjectChara(CObject::LABEL_PLAYER, PRIORITY)
{
	// �����o�ϐ����N���A
	memset(&m_apOrbit[0], 0, sizeof(m_apOrbit));	// �O�Ղ̏��
	m_pShadow			= NULL;			// �e�̏��
	m_pGoal				= NULL;			// �S�[���̏��
	m_pClear			= NULL;			// �N���A�\���̏��
	m_oldPos			= VEC3_ZERO;	// �ߋ��ʒu
	m_move				= VEC3_ZERO;	// �ړ���
	m_destRot			= VEC3_ZERO;	// �ڕW����
	m_land				= LAND_NONE;	// ���n��
	m_state				= STATE_NONE;	// ���
	m_nCounterState		= 0;			// ��ԊǗ��J�E���^�[
	m_nCounterSlide		= 0;			// �X���C�f�B���O�Ǘ��J�E���^�[
	m_nCounterWallDash	= 0;			// �Ǒ���Ǘ��J�E���^�[
	m_nCounterLand		= 0;			// ���n�Ǘ��J�E���^�[
	m_nCounterJump		= 0;			// �W�����v�Ǘ��J�E���^�[
	m_fMove				= 0.0f;			// �ړ���
	m_fPlusMove			= 0.0f;			// �v���X�ړ���
	m_bJump				= false;		// �W�����v��
	m_bJumpControl		= false;		// �W�����v�����
	m_bSlide			= false;		// �X���C�f�B���O��
	m_bSlideControl		= false;		// �X���C�f�B���O�����
	m_bWallDash			= false;		// �Ǒ����
	m_bWallDashControl	= false;		// �Ǒ��葀���
}

//============================================================
//	�f�X�g���N�^
//============================================================
CPlayer::~CPlayer()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPlayer::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apOrbit[0], 0, sizeof(m_apOrbit));	// �O�Ղ̏��
	m_pShadow			= NULL;			// �e�̏��
	m_pGoal				= NULL;			// �S�[���̏��
	m_pClear			= NULL;			// �N���A�\���̏��
	m_oldPos			= VEC3_ZERO;	// �ߋ��ʒu
	m_move				= VEC3_ZERO;	// �ړ���
	m_destRot			= VEC3_ZERO;	// �ڕW����
	m_land				= LAND_NONE;	// ���n��
	m_state				= STATE_NONE;	// ���
	m_nCounterState		= 0;			// ��ԊǗ��J�E���^�[
	m_nCounterSlide		= 0;			// �X���C�f�B���O�Ǘ��J�E���^�[
	m_nCounterWallDash	= 0;			// �Ǒ���Ǘ��J�E���^�[
	m_nCounterLand		= 0;			// ���n�Ǘ��J�E���^�[
	m_nCounterJump		= 0;			// �W�����v�Ǘ��J�E���^�[
	m_fMove				= basic::MOVE;	// �ړ���
	m_fPlusMove			= 0.0f;			// �v���X�ړ���
	m_bJump				= true;			// �W�����v��
	m_bJumpControl		= false;		// �W�����v�����
	m_bSlide			= false;		// �X���C�f�B���O��
	m_bSlideControl		= false;		// �X���C�f�B���O�����
	m_bWallDash			= false;		// �Ǒ����
	m_bWallDashControl	= false;		// �Ǒ��葀���

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

	for (int nCntPlayer = 0; nCntPlayer < NUM_ORBIT; nCntPlayer++)
	{ // �O�Ղ̐��������J��Ԃ�

		// �O�Ղ̐���
		m_apOrbit[nCntPlayer] = CObjectOrbit::Create
		( // ����
			GetMultiModel(other::ORBIT_PARTS[nCntPlayer])->GetPtrMtxWorld(),	// �e�}�g���b�N�X	
			other::ORBIT_COL,	// �F
			(CObjectOrbit::EOffset)nCntPlayer,	// �I�t�Z�b�g
			other::ORBIT_PART	// ������
		);
		if (m_apOrbit[nCntPlayer] == NULL)
		{ // ��g�p���̏ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �����`���OFF�ɐݒ�
		m_apOrbit[nCntPlayer]->SetEnableDraw(false);
	}

	// �e�̐���
	m_pShadow = CShadow::Create(CShadow::TEXTURE_NORMAL, other::SHADOW_SIZE, this);
	if (m_pShadow == NULL)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �N���A�\���̐���
	m_pClear = CObject2D::Create(clear::POS, clear::SIZE);
	if (m_pClear == NULL)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����Ǎ��E����
	m_pClear->BindTexture(mc_apTextureFile[TEXTURE_CLEAR]);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CPlayer::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < NUM_ORBIT; nCntPlayer++)
	{ // �O�Ղ̐��������J��Ԃ�

		// �O�Ղ̏I��
		m_apOrbit[nCntPlayer]->Uninit();
	}

	// �e�̏I��
	m_pShadow->Uninit();

	// �N���A�\���̏I��
	m_pClear->Uninit();

	// �I�u�W�F�N�g�L�����N�^�[�̏I��
	CObjectChara::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CPlayer::Update(void)
{
	// �ϐ���錾
	EMotion currentMotion = MOTION_WAVEHAND;	// ���݂̃��[�V����

	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:
		break;

	case STATE_SPAWN:

		// �X�|�[����Ԏ��̍X�V
		currentMotion = UpdateSpawn();

		break;

	case STATE_NORMAL:

		// �ʏ��Ԃ̍X�V
		currentMotion = UpdateNormal();

		break;

	case STATE_DAMAGE:

		// �_���[�W��Ԏ��̍X�V
		currentMotion = UpdateDamage();

		break;

	case STATE_UNION:

		// ������Ԏ��̍X�V
		currentMotion = UpdateUnion();

		break;

	case STATE_CLEAR:

		// �Q�[���N���A��Ԏ��̍X�V
		UpdateClear();

		break;

	case STATE_OVER:
		break;

	default:
		assert(false);
		break;
	}

	for (int nCntPlayer = 0; nCntPlayer < NUM_ORBIT; nCntPlayer++)
	{ // �O�Ղ̐��������J��Ԃ�

		// �O�Ղ̍X�V
		m_apOrbit[nCntPlayer]->Update();
	}

	// �e�̍X�V
	m_pShadow->Update();

	// �N���A�\���̍X�V
	m_pClear->Update();

	// ���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V
	UpdateMotion(currentMotion);
}

//============================================================
//	�`�揈��
//============================================================
void CPlayer::Draw(void)
{
	// �I�u�W�F�N�g�L�����N�^�[�̕`��
	CObjectChara::Draw();

	for (int nCntPlayer = 0; nCntPlayer < NUM_ORBIT; nCntPlayer++)
	{ // �O�Ղ̐��������J��Ԃ�

		// �O�Ղ̕`��
		m_apOrbit[nCntPlayer]->Draw();
	}
}

//============================================================
//	�q�b�g����
//============================================================
void CPlayer::Hit(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// �v���C���[����

	if (IsDeath() != true)
	{ // ���S�t���O�������Ă��Ȃ��ꍇ

		if (m_state == STATE_NORMAL)
		{ // �ʏ��Ԃ̏ꍇ

			// �J�E���^�[��������
			m_nCounterState = 0;

			// ������уx�N�g����ݒ�
			m_move.x = sinf(rotPlayer.y) * basic::BLOW_SIDE;
			m_move.y = basic::BLOW_UP;
			m_move.z = cosf(rotPlayer.y) * basic::BLOW_SIDE;

			// ��Ԃ�ύX
			SetState(STATE_DAMAGE);	// �_���[�W���

			// �ҋ@���[�V������ݒ�
			SetMotion(MOTION_IDOL);

			// �����p�[�e�B�N���𐶐�
			CParticle3D::Create(CParticle3D::TYPE_SMALL_EXPLOSION, D3DXVECTOR3(posPlayer.x, posPlayer.y + basic::HEIGHT * 0.5f, posPlayer.z));

			// �T�E���h�̍Đ�
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_HIT);	// �q�b�g��
		}
	}
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CPlayer::SetState(const int nState)
{
	if (m_state != CPlayer::STATE_CLEAR
	&&  m_state != CPlayer::STATE_OVER)
	{ // �Q�[���I���Ɋւ����Ԃł͂Ȃ��ꍇ

		// �����̏�Ԃ�ݒ�
		m_state = (EState)nState;

		if (m_state == CPlayer::STATE_CLEAR)
		{ // �Q�[���N���A��ԂɂȂ����ꍇ

			// �|�C���^��錾
			CTimerManager *pTimer = CSceneGame::GetTimerManager();	// �^�C�}�[�}�l�[�W���[
			assert(pTimer != NULL);

			// �^�C���̌v�����I��
			pTimer->End();

			// �����L���O�ɐݒ�
			CRankingManager::Set(pTimer->GetLimit() - pTimer->Get());

			// �����Ń��U���g�J��
			ResultTransition(CRetentionManager::RESULT_CLEAR);
		}
		else if (m_state == CPlayer::STATE_OVER)
		{ // �Q�[���I�[�o�[��ԂɂȂ����ꍇ

			// ���s�Ń��U���g�J��
			ResultTransition(CRetentionManager::RESULT_FAILED);
		}
		else if (m_state == CPlayer::STATE_UNION)
		{ // ������ԂɂȂ����ꍇ

			for (int nCntPlayer = 0; nCntPlayer < NUM_ORBIT; nCntPlayer++)
			{ // �O�Ղ̐��������J��Ԃ�

				// �O�Ղ�������Ԃɐݒ�
				m_apOrbit[nCntPlayer]->SetState(CObjectOrbit::STATE_VANISH);
			}
		}
	}
}

//============================================================
//	��Ԏ擾����
//============================================================
int CPlayer::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	���a�擾����
//============================================================
float CPlayer::GetRadius(void) const
{
	// ���a��Ԃ�
	return basic::RADIUS;
}

//============================================================
//	�c���擾����
//============================================================
float CPlayer::GetHeight(void) const
{
	// �c����Ԃ�
	return basic::HEIGHT;
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CPlayer::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);		// ���g
	m_pShadow->SetEnableUpdate(bUpdate);	// �e
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CPlayer::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);		// ���g
	m_pShadow->SetEnableDraw(bDraw);	// �e
}

//============================================================
//	�}�g���b�N�X�擾����
//============================================================
D3DXMATRIX CPlayer::GetMtxWorld(void) const
{
	// �ϐ���錾
	D3DXMATRIX  mtxRot, mtxTrans, mtxWorld;		// �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// �v���C���[����

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotPlayer.y, rotPlayer.x, rotPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posPlayer.x, posPlayer.y, posPlayer.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X��Ԃ�
	return mtxWorld;
}

//============================================================
//	��������
//============================================================
CPlayer *CPlayer::Create(CScene::EMode mode)
{
	// �|�C���^��錾
	CPlayer *pPlayer = NULL;	// �v���C���[�����p

	if (pPlayer == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		switch (mode)
		{ // ���[�h���Ƃ̏���
		case CScene::MODE_TITLE:

			// ����

			break;

		case CScene::MODE_TUTORIAL:

			// �������m��
			pPlayer = new CPlayer;	// �v���C���[

			break;

		case CScene::MODE_GAME:

			// �������m��
			pPlayer = new CPlayer;	// �v���C���[

			break;

		case CScene::MODE_RESULT:

			// ����

			break;

		case CScene::MODE_RANKING:

			// ����

			break;

		default:	// ��O����
			assert(false);
			break;
		}
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pPlayer != NULL)
	{ // �g�p����Ă���ꍇ

		// �v���C���[�̏�����
		if (FAILED(pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pPlayer;
			pPlayer = NULL;

			// ���s��Ԃ�
			return NULL;
		}
	}

	// �m�ۂ����A�h���X��Ԃ�
	return pPlayer;
}

//============================================================
//	�o���̐ݒ菈��
//============================================================
void CPlayer::SetSpawn(void)
{
	if (CSavePoint::GetNumAll() <= 0)
	{ // �Z�[�u�|�C���g������Ȃ��ꍇ

		// �����𔲂���
		return;
	}

	// �ϐ���錾
	CSavePoint::SInfo SavePointInfo = CSavePoint::GetSavePointInfo();	// �Z�[�u�|�C���g�̏��

	// ����������
	SetState(STATE_SPAWN);		// �X�|�[����Ԃ̐ݒ�
	SetMotion(MOTION_IDOL);		// �ҋ@���[�V������ݒ�

	// �J�E���^�[��������
	m_nCounterState = 0;	// ��ԊǗ��J�E���^�[
	m_nCounterSlide = 0;	// �X���C�f�B���O�Ǘ��J�E���^�[
	m_nCounterWallDash = 0;	// �Ǒ���Ǘ��J�E���^�[
	m_nCounterLand = 0;		// ���n�Ǘ��J�E���^�[
	m_nCounterJump = 0;		// �W�����v�Ǘ��J�E���^�[

	// �^�U��������
	m_bJumpControl = false;		// �W�����v�����������
	m_bSlideControl = false;	// �X���C�f�B���O�����������
	m_bWallDashControl = false;	// �Ǒ��葀���������

	// �ʒu��ݒ�
	SetVec3Position(SavePointInfo.pos);

	// ������ݒ�
	SetVec3Rotation(SavePointInfo.rot);
	m_destRot = SavePointInfo.rot;

	// �ړ��ʂ�������
	m_move = VEC3_ZERO;

	// �}�e���A�����Đݒ�
	ResetMaterial();

	// �����x�𓧖��ɍĐݒ�
	SetAlpha(0.0f);

	for (int nCntPlayer = 0; nCntPlayer < NUM_ORBIT; nCntPlayer++)
	{ // �O�Ղ̐��������J��Ԃ�

		// �O�Ղ�ʏ��ԂɍĐݒ�
		m_apOrbit[nCntPlayer]->SetState(CObjectOrbit::STATE_NORMAL);
	}

	// �v���C���[���g�̕`����ĊJ
	CObject::SetEnableDraw(true);

	// �񕜃p�[�e�B�N���𐶐�
	CParticle3D::Create(CParticle3D::TYPE_HEAL, SavePointInfo.pos, particle::COL_HEAL);

	// �Ǐ]�J�����̖ڕW�ʒu�̐ݒ�
	CManager::GetInstance()->GetCamera()->SetDestFollow();

	// �T�E���h�̍Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_SPAWN);	// ������
}

//============================================================
//	�S�[���̐ݒ菈��
//============================================================
void CPlayer::SetGoal(CGoalPoint *pGoal)
{
	// �����̃S�[����ݒ�
	m_pGoal = pGoal;
}

//============================================================
//	�X�|�[����Ԏ��̍X�V����
//============================================================
CPlayer::EMotion CPlayer::UpdateSpawn(void)
{
	// �ϐ���錾
	EMotion currentMotion = MOTION_IDOL;	// ���݂̃��[�V����

	// �t�F�[�h�A�E�g��Ԏ��̍X�V
	if (UpdateFadeOut(basic::SPAWN_ADD_ALPHA))
	{ // �s�����ɂȂ�؂����ꍇ

		// ��Ԃ�ݒ�
		SetState(STATE_NORMAL);
	}

	// ���݂̃��[�V������Ԃ�
	return currentMotion;
}

//============================================================
//	�ʏ��Ԏ��̍X�V����
//============================================================
CPlayer::EMotion CPlayer::UpdateNormal(void)
{
	// �ϐ���錾
	EMotion currentMotion = MOTION_IDOL;		// ���݂̃��[�V����
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// �v���C���[����

	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W���
	if (pStage == NULL)
	{ // �X�e�[�W���g�p����Ă��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return MOTION_IDOL;
	}

	// �ړ�����
	currentMotion = UpdateMove(posPlayer);

	// �d�͂̍X�V
	UpdateGravity();

	// ���n����
	UpdateLanding(posPlayer);

	// �W�����v����
	UpdateJump();

	// �X���C�f�B���O����
	UpdateSliding();

	// �����X�V
	UpdateRotation(rotPlayer);

	// �����ύX�̓����蔻��
	CollisionRotationBuilding(posPlayer);

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posPlayer, basic::RADIUS);

	// ��Q���̓����蔻��
	CollisionObstacle(posPlayer);

	// �ʒu�𔽉f
	SetVec3Position(posPlayer);

	// �����𔽉f
	SetVec3Rotation(rotPlayer);

	// �G�t�F�N�g�̍X�V
	UpdateEffect(posPlayer);

	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�v���C���[�ړ����x]�F%f\n", m_fMove);
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�v���C���[�ړ���]�F%f %f %f\n", m_move.x, m_move.y, m_move.z);
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, (m_bJump) ? "[�W�����v]�FON\n" : "[�W�����v]�FOFF\n");
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, (m_bSlide) ? "[�X���C�f�B���O]�FON\n" : "[�X���C�f�B���O]�FOFF\n");
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, (m_bWallDash) ? "[�Ǒ���]�FON\n" : "[�Ǒ���]�FOFF\n");

	// ���݂̃��[�V������Ԃ�
	return currentMotion;
}

//============================================================
//	�_���[�W��Ԏ��̍X�V����
//============================================================
CPlayer::EMotion CPlayer::UpdateDamage(void)
{
	// �ϐ���錾
	EMotion currentMotion = MOTION_IDOL;		// ���݂̃��[�V����
	D3DXVECTOR3 posPlayer = GetVec3Position();	// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();	// �v���C���[����

	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W���
	if (pStage == NULL)
	{ // �X�e�[�W���g�p����Ă��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return MOTION_IDOL;
	}

	// ���������Z
	rotPlayer += basic::DMG_ADDROT;

	// �d�͂̍X�V
	UpdateGravity();

	// ���n����
	UpdateLanding(posPlayer);

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posPlayer, basic::RADIUS);

	// �ʒu�𔽉f
	SetVec3Position(posPlayer);

	// �����𔽉f
	SetVec3Rotation(rotPlayer);

	// �t�F�[�h�C����Ԏ��̍X�V
	if (UpdateFadeIn(basic::DMG_SUB_ALPHA))
	{ // �����ɂȂ�؂����ꍇ

		// �o���̐ݒ�
		SetSpawn();
	}

	// ���݂̃��[�V������Ԃ�
	return currentMotion;
}

//============================================================
//	������Ԏ��̍X�V����
//============================================================
CPlayer::EMotion CPlayer::UpdateUnion(void)
{
	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W���
	if (pStage == NULL)
	{ // �X�e�[�W���g�p����Ă��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return MOTION_IDOL;
	}

	if (m_pGoal == NULL)
	{ // �S�[�����ݒ肳��Ă��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return MOTION_IDOL;
	}

	// �ϐ���錾
	D3DXVECTOR3 sizePlayer = VEC3_ZERO;							// �v���C���[�傫��
	D3DXVECTOR3 posPlayer = GetVec3Position();					// �v���C���[�ʒu
	D3DXVECTOR3 rotPlayer = GetVec3Rotation();					// �v���C���[����
	D3DXVECTOR3 sizeGoal = m_pGoal->GetVec3Sizing();			// �S�[���傫��
	D3DXVECTOR3 posGoal = m_pGoal->GetVec3Position();			// �S�[���ʒu
	D3DXVECTOR3 posFriend = m_pGoal->GetVec3FriendPosition();	// �F�B�ʒu
	EMotion currentMotion = MOTION_WAVEHAND;					// ���݂̃��[�V����

	if (m_bJump)
	{ // �W�����v���̏ꍇ

		// �ړ�����
		currentMotion = UpdateMove(posPlayer);
	}
	else
	{ // �W�����v���ł͂Ȃ��ꍇ

		// �ڕW������ݒ�
		m_destRot.y = atan2f(posPlayer.x - posFriend.x, posPlayer.z - posFriend.z);

		// �J�������Y�[����Ԃɐݒ�
		CManager::GetInstance()->GetCamera()->SetState(CCamera::STATE_ZOOM);

		if (fabsf(rotPlayer.y - m_destRot.y) <= basic::MIN_VARY)
		{ // ������������x��v�����ꍇ

			// �Q�[���N���A��Ԃɂ���
			SetState(STATE_CLEAR);
		}
	}

	// �d�͂̍X�V
	UpdateGravity();

	// ���n����
	UpdateLanding(posPlayer);

	// �����X�V
	UpdateRotation(rotPlayer);

	// �S�[���͈͓��̕␳
	collision::InBoxPillar(posPlayer, posGoal, sizePlayer, sizePlayer, sizeGoal, sizeGoal);

	// �X�e�[�W�͈͊O�̕␳
	pStage->LimitPosition(posPlayer, basic::RADIUS);

	// �ʒu�𔽉f
	SetVec3Position(posPlayer);

	// �����𔽉f
	SetVec3Rotation(rotPlayer);

	// �f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�v���C���[�ړ����x]�F%f\n", m_fMove);
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, "[�v���C���[�ړ���]�F%f %f %f\n", m_move.x, m_move.y, m_move.z);
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, (m_bJump) ? "[�W�����v]�FON\n" : "[�W�����v]�FOFF\n");
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, (m_bSlide) ? "[�X���C�f�B���O]�FON\n" : "[�X���C�f�B���O]�FOFF\n");
	CManager::GetInstance()->GetDebugProc()->Print(CDebugProc::POINT_LEFT, (m_bWallDash) ? "[�Ǒ���]�FON\n" : "[�Ǒ���]�FOFF\n");

	// ���݂̃��[�V������Ԃ�
	return currentMotion;
}

//============================================================
//	�Q�[���N���A��Ԏ��̍X�V����
//============================================================
void CPlayer::UpdateClear(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posClear = m_pClear->GetVec3Position();	// �N���A�\���ʒu

	if (posClear.x < clear::STOP_POS)
	{ // �ʒu����~�ʒu�𖢖��̏ꍇ

		// ���ʒu���E�Ɉړ�
		posClear.x += clear::MOVE_POS;

		if (posClear.x > clear::STOP_POS)
		{ // �ʒu����~�ʒu�𒴂����ꍇ

			// ��~�ʒu�ɕ␳
			posClear.x = clear::STOP_POS;

			// �T�E���h�̍Đ�
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// ���艹01
		}
	}

	// �N���A�\���ʒu�𔽉f
	m_pClear->SetVec3Position(posClear);
}

//============================================================
//	�ߋ��ʒu�̍X�V����
//============================================================
void CPlayer::UpdateOldPosition(void)
{
	// �ߋ��ʒu���X�V
	m_oldPos = GetVec3Position();
}

//============================================================
//	�ړ��ʁE�Ǒ���̍X�V����
//============================================================
CPlayer::EMotion CPlayer::UpdateMove(D3DXVECTOR3& rPos)
{
	// �Ǒ���̍X�V
	UpdateWallDash(rPos);

	// �ړ��ʂ��X�V
	m_move.x += sinf(m_destRot.y + D3DX_PI) * (m_fMove + m_fPlusMove);
	m_move.z += cosf(m_destRot.y + D3DX_PI) * (m_fMove + m_fPlusMove);

	if (!m_bSlide && !m_bWallDash)
	{ // �X���C�f�B���O���ł͂Ȃ��ꍇ

		if (m_fMove < basic::MOVE)
		{ // �ړ��ʂ��ō����x�ł͂Ȃ��ꍇ

			// �ړ��ʂ����Z
			m_fMove += basic::ADD_MOVE;

			if (m_fMove > basic::MOVE)
			{ // �ړ��ʂ��ō����x�𒴂����ꍇ

				// �ړ��ʂ�␳
				m_fMove = basic::MOVE;
			}
		}
	}

	// �v���X�ړ��ʂ����Z
	m_fPlusMove += (0.0f - m_fPlusMove) * walldash::REV_PLUSMOVE;

	// �ړ����[�V������Ԃ�
	return MOTION_MOVE;
}

//============================================================
//	�Ǒ���̍X�V����
//============================================================
void CPlayer::UpdateWallDash(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	float fRate = 0.0f;	// ����
	bool bHit = false;	// �Ǒ���\��

	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h
	CInputPad		*pPad		= CManager::GetInstance()->GetPad();		// �p�b�h
	CInputMouse		*pMouse		= CManager::GetInstance()->GetMouse();		// �}�E�X

	// �ŔƂ̓����蔻��
	bHit = CollisionSignboard(rPos, &fRate);	// �Ǒ���\�󋵂�ݒ�

	if (!m_bWallDash)
	{ // �Ǒ��肵�Ă��Ȃ��ꍇ

		if (bHit)
		{ // �Ǒ���\�ȏꍇ

			if (pKeyboard->IsTrigger(DIK_S)
			||  pPad->IsTrigger(CInputPad::KEY_A)
			||  pMouse->IsTrigger(CInputMouse::KEY_RIGHT))
			{ // �Ǒ���̑��삪�s��ꂽ�ꍇ

				// �Ǒ��葀�삪�s��ꂽ����ۑ�
				m_bWallDashControl = true;
			}
		}

		if (m_fMove >= walldash::CONTROL_MIN)
		{ // �Ǒ��肪�\�Ȉړ����x�̏ꍇ

			if (bHit && m_bWallDashControl)
			{ // �Ǒ���\���A�Ǒ���̑��삪�s��ꂽ�ꍇ

				// �Ǒ��葀�삪�s��ꂽ����������
				m_bWallDashControl = false;

				// �Ǒ��肵�Ă����Ԃɂ���
				m_bWallDash = true;

				// �Ǒ��胂�[�V������ݒ�
				SetMotion(MOTION_WALLDASH);

				// �T�E���h�̍Đ�
				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_SLIDE);	// �X���C�f�B���O��
			}
		}
	}
	else
	{ // �Ǒ��肵�Ă���ꍇ

		// �ϐ���錾
		float fPlusSubMove = walldash::PLUS_SUB_MOVE * m_nCounterWallDash;	// �ړ��ʂ̒ǉ����Z��

		// �J�E���^�[�����Z
		m_nCounterWallDash++;

		if (m_fMove > walldash::MIN_MOVE)
		{ // �ړ��ʂ��Œᑬ�x�ł͂Ȃ��ꍇ

			// �ړ��ʂ����Z
			m_fMove -= walldash::SUB_MOVE + fPlusSubMove;

			if (m_fMove < walldash::MIN_MOVE)
			{ // �ړ��ʂ��Œᑬ�x�𒴂����ꍇ

				// �ړ��ʂ�␳
				m_fMove = walldash::MIN_MOVE;
			}
		}

		if (bHit)
		{ // �Ǒ���\�ȏꍇ

			if (m_nCounterWallDash > walldash::MIN_END_CNT)
			{ // �Ǒ���̉������삪�ł���J�E���g�ɓ��B�����ꍇ

				if (!(pKeyboard->IsPress(DIK_S) || pPad->IsPress(CInputPad::KEY_A) || pMouse->IsPress(CInputMouse::KEY_RIGHT)))
				{ // �Ǒ�������̑��삪�s��ꂽ�ꍇ

					// �J�E���^�[��������
					m_nCounterWallDash = 0;

					// �Ǒ��肵�Ă��Ȃ���Ԃɂ���
					m_bWallDash = false;

					// �Ǒ��葀�삪�s��ꂽ����������
					m_bWallDashControl = false;

					if (fRate >= walldash::BOOST_RATE)
					{ // �����ł���v���C���[�̈ʒu�����ȏゾ�����ꍇ

						// �c�ړ��ʂ����Z
						m_move.y += walldash::PLUSMOVE_UP;

						// �v���X�ړ��ʂ�ݒ�
						m_fPlusMove = walldash::PLUSMOVE_SIDE;

						// �W�����v���[�V������ݒ�
						SetMotion(MOTION_JUMP);

						// �T�E���h�̍Đ�
						CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_JUMP);	// �W�����v��
					}
				}
			}
		}
		else
		{ // �Ǒ���s�\�̏ꍇ

			// �J�E���^�[��������
			m_nCounterWallDash = 0;

			// �Ǒ��肵�Ă��Ȃ���Ԃɂ���
			m_bWallDash = false;

			// �Ǒ��葀�삪�s��ꂽ����������
			m_bWallDashControl = false;
		}

		// �o�C�u�̐ݒ�
		pPad->SetVibration(CInputPad::TYPE_WALLDASH);
	}
}

//============================================================
//	�W�����v�̍X�V����
//============================================================
void CPlayer::UpdateJump(void)
{
	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h
	CInputPad		*pPad		= CManager::GetInstance()->GetPad();		// �p�b�h
	CInputMouse		*pMouse		= CManager::GetInstance()->GetMouse();		// �}�E�X

	if (m_bJumpControl)
	{ // �W�����v���삪�s���Ă���ꍇ

		// �W�����v�Ǘ��J�E���^�[�����Z
		m_nCounterJump++;

		if (m_nCounterJump >= basic::JUMP_SAVECONTROL_CNT)
		{ // ��������폜����t���[�������o�߂����ꍇ

			// �W�����v�Ǘ��J�E���^�[��������
			m_nCounterJump = 0;

			// �W�����v���삪�s��ꂽ����������
			m_bJumpControl = false;
		}
	}

	if (pKeyboard->IsTrigger(DIK_W)
	||  pPad->IsTrigger(CInputPad::KEY_B)
	||  pMouse->IsTrigger(CInputMouse::KEY_LEFT))
	{ // �W�����v�̑��삪�s��ꂽ�ꍇ

		// �W�����v���삪�s��ꂽ����ۑ�
		m_bJumpControl = true;
	}

	if (!m_bJump && !m_bWallDash)
	{ // �W�����v�ƕǑ�������Ă��Ȃ��ꍇ

		if (m_bJumpControl)
		{ // �W�����v�̑��삪�s��ꂽ�ꍇ

			// �W�����v�Ǘ��J�E���^�[��������
			m_nCounterJump = 0;

			// �W�����v���삪�s��ꂽ����������
			m_bJumpControl = false;

			// �J�E���^�[��������
			m_nCounterSlide = 0;

			// �X���C�f�B���O���Ă��Ȃ���Ԃɂ���
			m_bSlide = false;

			// ��ړ���
			m_move.y += basic::JUMP;

			// �W�����v���Ă����Ԃɂ���
			m_bJump = true;

			// �W�����v���[�V������ݒ�
			SetMotion(MOTION_JUMP);

			// �T�E���h�̍Đ�
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_JUMP);	// �W�����v��
		}
	}
}

//============================================================
//	�X���C�f�B���O�̍X�V����
//============================================================
void CPlayer::UpdateSliding(void)
{
	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h
	CInputPad		*pPad		= CManager::GetInstance()->GetPad();		// �p�b�h
	CInputMouse		*pMouse		= CManager::GetInstance()->GetMouse();		// �}�E�X

	if (!m_bSlide)
	{ // �X���C�f�B���O���Ă��Ȃ��ꍇ

		if (pKeyboard->IsTrigger(DIK_S)
		||  pPad->IsTrigger(CInputPad::KEY_A)
		||  pMouse->IsTrigger(CInputMouse::KEY_RIGHT))
		{ // �X���C�f�B���O�̑��삪�s��ꂽ�ꍇ

			if (!m_bWallDash)
			{ // �Ǒ�������Ă��Ȃ��ꍇ

				// �X���C�f�B���O���삪�s��ꂽ����ۑ�
				m_bSlideControl = true;
			}
		}

		if (!m_bJump && !m_bWallDash)
		{ // �W�����v�E�Ǒ�������Ă��Ȃ��ꍇ

			if (m_fMove >= slide::CONTROL_MIN)
			{ // �X���C�f�B���O���\�Ȉړ����x�̏ꍇ

				if (m_bSlideControl)
				{ // �X���C�f�B���O�̑��삪�s��ꂽ�ꍇ

					// �X���C�f�B���O���삪�s��ꂽ����������
					m_bSlideControl = false;

					// �X���C�f�B���O���Ă����Ԃɂ���
					m_bSlide = true;

					// �X���C�f�B���O���[�V������ݒ�
					SetMotion(MOTION_SLIDE);

					// �T�E���h�̍Đ�
					CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_SLIDE);	// �X���C�f�B���O��
				}
			}
		}
	}
	else
	{ // �X���C�f�B���O���Ă���ꍇ

		// �ϐ���錾
		float fPlusSubMove = (slide::PLUS_SUB_MOVE / (float)slide::MAX_END_CNT) * (float)(slide::MAX_END_CNT - m_nCounterSlide);	// �ړ��ʂ̒ǉ����Z��

		// �J�E���^�[�����Z
		m_nCounterSlide++;

		if (m_fMove > slide::MIN_MOVE)
		{ // �ړ��ʂ��Œᑬ�x�ł͂Ȃ��ꍇ

			// �ړ��ʂ����Z
			m_fMove -= slide::SUB_MOVE + fPlusSubMove;

			if (m_fMove < slide::MIN_MOVE)
			{ // �ړ��ʂ��Œᑬ�x�𒴂����ꍇ

				// �ړ��ʂ�␳
				m_fMove = slide::MIN_MOVE;
			}
		}

		if (m_nCounterSlide > slide::MIN_END_CNT)
		{ // �X���C�f�B���O�̉������삪�ł���J�E���g�ɓ��B�����ꍇ

			if (!(pKeyboard->IsPress(DIK_S) || pPad->IsPress(CInputPad::KEY_A) || pMouse->IsPress(CInputMouse::KEY_RIGHT)))
			{ // �X���C�f�B���O�����̑��삪�s��ꂽ�ꍇ

				// �J�E���^�[��������
				m_nCounterSlide = 0;

				// �X���C�f�B���O���Ă��Ȃ���Ԃɂ���
				m_bSlide = false;
			}
		}

		if (m_nCounterSlide > slide::MAX_END_CNT)
		{ // �X���C�f�B���O�������I������J�E���g�ɓ��B�����ꍇ

			// �J�E���^�[��������
			m_nCounterSlide = 0;

			// �X���C�f�B���O���Ă��Ȃ���Ԃɂ���
			m_bSlide = false;
		}
	}
}

//============================================================
//	�d�͂̍X�V����
//============================================================
void CPlayer::UpdateGravity(void)
{
	if (m_bWallDash)
	{ // �Ǒ��蒆�̏ꍇ

		if (m_move.y > 0.0f)
		{ // �㏸�ʂ�����ꍇ

			// �d�͂����Z
			m_move.y -= walldash::GRAVITY_HIGH;

			if (m_move.y < 0.0f)
			{ // �ړ��ʂ�������؂����ꍇ

				// �ړ��ʂ�������
				m_move.y = 0.0f;
			}
		}
		else
		{ // �㏸�ʂ��Ȃ��ꍇ

			// �d�͂����Z
			m_move.y -= walldash::GRAVITY_LOW;

			if (m_move.y < walldash::MAX_GRAVITY)
			{ // �ړ��ʂ������肷�����ꍇ

				// �ړ��ʂ�������
				m_move.y = walldash::MAX_GRAVITY;
			}
		}
	}
	else
	{ // �Ǒ��蒆�ł͂Ȃ��ꍇ

		// �d�͂����Z
		m_move.y -= basic::GRAVITY;
	}
}

//============================================================
//	���n�󋵂̍X�V����
//============================================================
bool CPlayer::UpdateLanding(D3DXVECTOR3& rPos)
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

		// ���n�����r���ɐݒ�
		m_land = LAND_BUILDING;
	}

	// ��Q���̓����蔻��E���n����
	if (LandObstacle(rPos))
	{ // ��Q���ɒ��n���Ă����ꍇ

		// ���n���Ă����Ԃɂ���
		bLand = true;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;

		// ���n������Q���ɐݒ�
		m_land = LAND_OBSTACLE;
	}

	// �n�ʁE�����ʒu�̒��n����
	if (CScene::GetStage()->LandFieldPosition(rPos, m_move)
	||  CScene::GetStage()->LandLimitPosition(rPos, m_move, 0.0f))
	{ // �v���C���[�����n���Ă����ꍇ

		// ���n���Ă����Ԃɂ���
		bLand = true;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;

		// ���n�������̑��ɐݒ�
		m_land = LAND_OTHER;
	}

	if (!bLand)
	{ // ���n���Ă��Ȃ������ꍇ

		if (m_state == STATE_NORMAL
		&&  GetMotionType() == MOTION_MOVE)
		{ // �ʏ��Ԋ��A�ړ����[�V�����������ꍇ

			// �������[�V������ݒ�
			SetMotion(MOTION_FALL);
		}

		// ���n�J�E���^�[�����Z
		m_nCounterLand++;

		// ���n�������Ă��Ȃ��ɐݒ�
		m_land = LAND_NONE;
	}
	else
	{ // ���n�����ꍇ

		if (m_nCounterLand >= basic::LAND_SE_CNT)
		{ // ���n�J�E���^�[�����l�ȏ�̏ꍇ

			switch (m_land)
			{ // ���n�����Ƃ̏���
			case LAND_OBSTACLE:

				// �T�E���h�̍Đ�
				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_WALK_OBS);	// ���s���i��Q���j

				break;

			default:

				// �T�E���h�̍Đ�
				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_WALK_BUILD);	// ���s���i�r���j

				break;
			}
		}

		// ���n�J�E���^�[��������
		m_nCounterLand = 0;
	}

	// ���n�󋵂�Ԃ�
	return bLand;
}

//============================================================
//	�����̍X�V����
//============================================================
void CPlayer::UpdateRotation(D3DXVECTOR3& rRot)
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
//	�G�t�F�N�g�̍X�V����
//============================================================
void CPlayer::UpdateEffect(D3DXVECTOR3& rPos)
{
	if (m_bSlide || m_bWallDash)
	{ // �X���C�f�B���O�܂��͕Ǒ���̏ꍇ

		// ���𐶐�
		CEffect3D::Create(rPos, effect::SMOKE_RADIUS, CEffect3D::TYPE_SMOKE, effect::SMOKE_LIFE, D3DXVECTOR3((float)(rand() % 2), (float)(rand() % 4), (float)(rand() % 2)), VEC3_ZERO, XCOL_WHITE, -(float)(rand() % 12), false);
	}
}

//============================================================
//	���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V����
//============================================================
void CPlayer::UpdateMotion(int nMotion)
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

	switch (GetMotionType())
	{ // ���[�V�����̎�ނ��Ƃ̏���
	case MOTION_MOVE:		// �ړ����[�V����

		if (GetMotionPose() % 4 == 0 && GetMotionCounter() == 0)
		{ // ���������^�C�~���O�̏ꍇ

			switch (m_land)
			{ // ���n�����Ƃ̏���
			case LAND_OBSTACLE:

				// �T�E���h�̍Đ�
				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_WALK_OBS);	// ���s���i��Q���j

				break;

			default:

				// �T�E���h�̍Đ�
				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_WALK_BUILD);	// ���s���i�r���j

				break;
			}
		}

		break;

	case MOTION_JUMP:		// �W�����v���[�V����

		if (!m_bJump)
		{ // �W�����v���ł͂Ȃ��ꍇ

			// ���݂̃��[�V�����̐ݒ�
			SetMotion(nMotion);
		}

		// �����𔲂���
		break;

	case MOTION_SLIDE:		// �X���C�f�B���O���[�V����

		if (!m_bSlide)
		{ // �X���C�f�B���O���ł͂Ȃ��ꍇ

			// ���݂̃��[�V�����̐ݒ�
			SetMotion(nMotion);
		}

		// �����𔲂���
		break;

	case MOTION_WALLDASH:	// �Ǒ��胂�[�V����

		if (!m_bWallDash)
		{ // �Ǒ��蒆�ł͂Ȃ��ꍇ

			if (m_bJump)
			{ // �W�����v���̏ꍇ

				// ���݂̃��[�V�����̐ݒ�
				SetMotion(MOTION_FALL);
			}
			else
			{ // �W�����v���ł͂Ȃ��ꍇ

				// ���݂̃��[�V�����̐ݒ�
				SetMotion(nMotion);
			}
		}

		// �����𔲂���
		break;

	case MOTION_FALL:		// �������[�V����

		if (!m_bJump)
		{ // �W�����v���ł͂Ȃ��ꍇ

			// ���݂̃��[�V�����̐ݒ�
			SetMotion(nMotion);
		}

		// �����𔲂���
		break;
	}
}

//============================================================
//	�t�F�[�h�A�E�g��Ԏ��̍X�V����
//============================================================
bool CPlayer::UpdateFadeOut(const float fAdd)
{
	// �ϐ���錾
	bool bAlpha = false;		// ������
	float fAlpha = GetAlpha();	// �����x

	// �v���C���[���g�̕`����ĊJ
	CObject::SetEnableDraw(true);

	// �����x���グ��
	fAlpha += fAdd;

	if (fAlpha >= GetMaxAlpha())
	{ // �����x���オ��؂����ꍇ

		// �����x��␳
		fAlpha = GetMaxAlpha();

		// �s�����ɂȂ�؂�����Ԃɂ���
		bAlpha = true;
	}

	// �����x��ݒ�
	SetAlpha(fAlpha);

	// �����󋵂�Ԃ�
	return bAlpha;
}

//============================================================
//	�t�F�[�h�C����Ԏ��̍X�V����
//============================================================
bool CPlayer::UpdateFadeIn(const float fSub)
{
	// �ϐ���錾
	bool bAlpha = false;		// ������
	float fAlpha = GetAlpha();	// �����x

	// �����x��������
	fAlpha -= fSub;

	if (fAlpha <= 0.0f)
	{ // �����x��������؂����ꍇ

		// �����x��␳
		fAlpha = 0.0f;

		// �����ɂȂ�؂�����Ԃɂ���
		bAlpha = true;

		// �v���C���[���g�̕`����~
		CObject::SetEnableDraw(false);
	}

	// �����x��ݒ�
	SetAlpha(fAlpha);

	// �����󋵂�Ԃ�
	return bAlpha;
}

//============================================================
//	���U���g�J�ڏ���
//============================================================
void CPlayer::ResultTransition(const CRetentionManager::EResult result)
{
	if (CManager::GetInstance()->GetFade()->GetState() == CFade::FADE_NONE)
	{ // �t�F�[�h���Ă��Ȃ��ꍇ

		// �|�C���^��錾
		CRetentionManager *m_pRetention = CManager::GetInstance()->GetRetentionManager();	// �f�[�^�ۑ��}�l�[�W���[
		assert(m_pRetention != NULL);

		CTimerManager *pTimer = CSceneGame::GetTimerManager();	// �^�C�}�[�}�l�[�W���[
		assert(pTimer != NULL);

		// �N���A�󋵂�ݒ�
		m_pRetention->SetResult(result);

		// �o�ߎ��Ԃ�ݒ�
		m_pRetention->SetTime(pTimer->GetLimit() - pTimer->Get());

		// �V�[���̐ݒ�
		CManager::GetInstance()->SetScene(CScene::MODE_RESULT, CNT_WAIT[result]);	// ���U���g���
	}
}

//============================================================
//	�l�����ϊ�����
//============================================================
CPlayer::EDirection CPlayer::FourDirection
(
	const float fRot,		// ����
	const float fTolerance	// ���e�l
)
{
	if (fabsf(fRot) <= fTolerance)
	{ // ���e�l�ȉ��̌덷�̏ꍇ

		// �����F0����Ԃ�
		return DIRECTION_DOWN;
	}
	else if (fabsf(fRot - HALF_PI_TWO_DP) <= fTolerance)
	{ // ���e�l�ȉ��̌덷�̏ꍇ

		// �����F90����Ԃ�
		return DIRECTION_RIGHT;
	}
	else if (fabsf(fRot - PI_TWO_DP) <= fTolerance)
	{ // ���e�l�ȉ��̌덷�̏ꍇ

		// �����F180����Ԃ�
		return DIRECTION_UP;
	}
	else if (fabsf(fRot - -HALF_PI_TWO_DP) <= fTolerance)
	{ // ���e�l�ȉ��̌덷�̏ꍇ

		// �����F270����Ԃ�
		return DIRECTION_LEFT;
	}

	// �����Ȃ���Ԃ�
	return DIRECTION_NONE;
}

//============================================================
//	�����ύX�̓����蔻��
//============================================================
void CPlayer::CollisionRotationBuilding(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(basic::RADIUS, 0.0f, basic::RADIUS);			// �v���C���[�ŏ��傫��
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(basic::RADIUS, basic::HEIGHT, basic::RADIUS);	// �v���C���[�ő�傫��
	float fDisPosY = 0.0f;	// �v���C���[�ƃr����Y����
	bool bInitDis = false;	// Y�����̏�������

	// �|�C���^��錾
	CObject *pCurrentRotObj = NULL;	// ���݂̌����ݒ�I�u�W�F�N�g

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

				if (pObjCheck->GetState() != CBuilding::COLLISION_GROUND)
				{ // ��Ԃ��n�ʂł͂Ȃ��ꍇ

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

				// �����ύX�̓����蔻��
				if (collision::Box2D
				( // ����
					rPos,			// ����ʒu
					posBuild,		// ����ڕW�ʒu
					sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
					sizeMinPlayer,	// ����T�C�Y(���E���E�O)
					sizeMaxBuild,	// ����ڕW�T�C�Y(�E�E��E��)
					sizeMinBuild	// ����ڕW�T�C�Y(���E���E�O)
				))
				{ // ������������ꍇ

					// �ϐ���錾
					float fDis = rPos.y - (posBuild.y + sizeMaxBuild.y);	// �v���C���[�ƃr����Y����

					if (fDis >= 0.0f)
					{ // �v���C���[�ƃr����Y�������v���X�̏ꍇ

						if (!bInitDis)
						{ // ���������Ă��Ȃ��ꍇ

							// ���݂̋�������
							fDisPosY = fDis;

							// ���݂̌����ݒ�I�u�W�F�N�g����
							pCurrentRotObj = pObjCheck;

							// �������ς݂ɂ���
							bInitDis = true;
						}
						else
						{ // ���������Ă���ꍇ

							if (fDis < fDisPosY)
							{ // ���߂��r���̏ꍇ

								// ���݂̋�������
								fDisPosY = fDis;

								// ���݂̌����ݒ�I�u�W�F�N�g����
								pCurrentRotObj = pObjCheck;
							}
						}
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	if (pCurrentRotObj != NULL)
	{ // �r�����������ꍇ

		// �ϐ���錾
		D3DXVECTOR3 posBuild = VEC3_ZERO;	// �r���ʒu
		D3DXVECTOR3 rotBuild = VEC3_ZERO;	// �r������
		D3DXVECTOR3 sizeBuild = VEC3_ZERO;	// �r���傫��
		D3DXVECTOR3 posLeft = VEC3_ZERO;	// �v���C���[���猩���r���̍��ʒu
		D3DXVECTOR3 posRight = VEC3_ZERO;	// �v���C���[���猩���r���̉E�ʒu
		
		// �r���̈ʒu��ݒ�
		posBuild = pCurrentRotObj->GetVec3Position();

		// �r���̌�����ݒ�
		rotBuild = pCurrentRotObj->GetVec3Rotation();

		// �r���̑傫����ݒ�
		sizeBuild = pCurrentRotObj->GetVec3Sizing();
		sizeBuild.y *= 2.0f;	// �c�̑傫����{�ɂ���

		float fRotLeft = m_destRot.y - HALF_PI;		// �v���C���[��90�x������
		useful::NormalizeRot(fRotLeft);				// ���������K��
		float fRotRight = m_destRot.y + HALF_PI;	// �v���C���[��90�x�E����
		useful::NormalizeRot(fRotRight);			// �E�������K��

		if (FourDirection(m_destRot.y, QRTR_PI * 0.5f) == FourDirection(rotBuild.y, QRTR_PI * 0.5f))
		{ // �������Ⴄ�ꍇ

			// �֐��𔲂���
			return;
		}

		// �r���̍��ʒu���v�Z
		posLeft.x = posBuild.x - sinf(fRotLeft) * sizeBuild.x;
		posLeft.y = posBuild.y + sizeBuild.y;
		posLeft.z = posBuild.z - cosf(fRotLeft) * sizeBuild.z;

		// �r���̉E�ʒu���v�Z
		posRight.x = posBuild.x - sinf(fRotRight) * sizeBuild.x;
		posRight.y = posBuild.y + sizeBuild.y;
		posRight.z = posBuild.z - cosf(fRotRight) * sizeBuild.z;

		if (collision::LineOuterProduct(posLeft, posRight, rPos) <= 0.0f)
		{ // �v���C���[�̐i�s�������猩�ăr���̒��S��艜���̏ꍇ

			// �v���C���[�̈ʒu�Ƀr���̒��S�ʒu��ݒ�
			rPos.x = posBuild.x;
			rPos.z = posBuild.z;

			// �v���C���[�̈ړ��ʂ�������
			m_move.x = 0.0f;
			m_move.z = 0.0f;

			// �v���C���[�̖ڕW�����Ƀr���̌�����ݒ�
			m_destRot.y = rotBuild.y;
		}
	}
}

//============================================================
//	�r���Ƃ̈ꎲ���Ƃ̓����蔻��
//============================================================
bool CPlayer::ResponseSingleBuilding(const EAxis axis, D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(basic::RADIUS, 0.0f, basic::RADIUS);			// �v���C���[�ŏ��傫��
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(basic::RADIUS, basic::HEIGHT, basic::RADIUS);	// �v���C���[�ő�傫��
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
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
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
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
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
						sizeMaxPlayer,	// ����T�C�Y(�E�E��E��)
						sizeMinPlayer,	// ����T�C�Y(���E���E�O)
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
//	�ŔƂ̓����蔻��
//============================================================
bool CPlayer::CollisionSignboard(D3DXVECTOR3& rPos, float *pRate)
{
	// �ϐ���錾
	D3DXVECTOR3 posPlayer = D3DXVECTOR3(rPos.x, rPos.y + basic::HEIGHT * 0.5f, rPos.z);	// �v���C���[����ʒu

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

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_SIGNBOARD)
				{ // �I�u�W�F�N�g���x�����Ŕł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �ϐ���錾
				D3DXMATRIX mtxSign;		// �Ŕ}�g���b�N�X
				D3DXVECTOR3 posSign;	// �Ŕʒu
				D3DXVECTOR3 sizeSign;	// �Ŕ傫��
				bool bHit = false;		// ������

				// �ϐ��z���錾
				D3DXVECTOR3 aGap[4];	// �����
				D3DXVECTOR3 aPos[4];	// ���_�ʒu

				// �Ŕ̏����擾
				mtxSign = *pObjCheck->GetPtrMtxWorld();	// �}�g���b�N�X
				posSign = pObjCheck->GetVec3Position();	// �ʒu
				sizeSign = pObjCheck->GetVec3Sizing();	// �傫��

				// ����ʂ�ݒ�
				aGap[0] = D3DXVECTOR3(-sizeSign.x - walldash::PLUS_COLL_SIZE, 0.0f, 0.0f);
				aGap[1] = D3DXVECTOR3(-sizeSign.x - walldash::PLUS_COLL_SIZE, 0.0f, -walldash::COLL_SIZE);
				aGap[2] = D3DXVECTOR3( sizeSign.x + walldash::PLUS_COLL_SIZE, 0.0f, -walldash::COLL_SIZE);
				aGap[3] = D3DXVECTOR3( sizeSign.x + walldash::PLUS_COLL_SIZE, 0.0f, 0.0f);

				for (int nCntSign = 0; nCntSign < 4; nCntSign++)
				{ // ����p�̒��_�����J��Ԃ�

					// �ϐ���錾
					D3DXMATRIX mtxGap;		// ���_�̂���ʃ}�g���b�N�X
					D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X

					// ���[���h�}�g���b�N�X�̏�����
					D3DXMatrixIdentity(&mtxGap);

					// �ʒu�𔽉f
					D3DXMatrixTranslation(&mtxTrans, aGap[nCntSign].x, aGap[nCntSign].y, aGap[nCntSign].z);
					D3DXMatrixMultiply(&mtxGap, &mtxGap, &mtxTrans);

					// �}�g���b�N�X���|�����킹��
					D3DXMatrixMultiply(&mtxGap, &mtxGap, &mtxSign);

					// �ʒu��ݒ�
					aPos[nCntSign] = D3DXVECTOR3(mtxGap._41, mtxGap._42, mtxGap._43);
				}

				if (posPlayer.y < posSign.y + sizeSign.y
				&&  posPlayer.y > posSign.y - sizeSign.y)
				{ // �v���C���[�̏c���W���Ŕ��̏ꍇ

					// �Ǒ���͈͂̔���
					bHit = collision::BoxOuterPillar
					( // ����
						aPos[0],	// �l�p�̊e���_
						aPos[1],	// �l�p�̊e���_
						aPos[2],	// �l�p�̊e���_
						aPos[3],	// �l�p�̊e���_
						posPlayer	// ����ʒu
					);
					if (bHit)
					{ // �͈͓��̏ꍇ

						// �ϐ���錾
						float fWidth	= sqrtf((aPos[1].x - aPos[2].x) * (aPos[1].x - aPos[2].x) + (aPos[1].z - aPos[2].z) * (aPos[1].z - aPos[2].z)) * 0.5f;			// �Ŕ̉���
						float fPlayer	= sqrtf((aPos[1].x - posPlayer.x) * (aPos[1].x - posPlayer.x) + (aPos[1].z - posPlayer.z) * (aPos[1].z - posPlayer.z)) * 0.5f;	// ���[���猩���v���C���[�ʒu

						if (pRate != NULL)
						{ // �����̊i�[�|�C���g�����݂���ꍇ

							// �v���C���[�ʒu�̊�������
							*pRate = (1.0f / fWidth) * fPlayer;
						}

						// �Ǒ���͈͓���Ԃ�
						return true;
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	// �Ǒ���͈͊O��Ԃ�
	return false;
}

//============================================================
//	��Q���Ƃ̓����蔻��
//============================================================
void CPlayer::CollisionObstacle(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(basic::RADIUS, 0.0f, basic::RADIUS);			// �v���C���[�ŏ��傫��
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(basic::RADIUS, basic::HEIGHT, basic::RADIUS);	// �v���C���[�ő�傫��

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

				if (pObjCheck->GetState() == CObstacle::STATE_LAND)
				{ // ���n�ł�������Ԃ̏ꍇ

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

					switch (pObjCheck->GetState())
					{ // �����Ԃ��Ƃ̏���
					case CObstacle::STATE_NONE:	// �����Ԗ���

						switch (pObjCheck->GetDodge())
						{ // ���@���Ƃ̏���
						case CObstacle::DODGE_NONE:		// �����@�Ȃ�

							// ����

							break;

						case CObstacle::DODGE_JUMP:		// �W�����v���

							if (!m_bJump)
							{ // �W�����v���ł͂Ȃ��ꍇ

								// �q�b�g
								Hit();
							}

							break;

						case CObstacle::DODGE_SLIDE:	// �X���C�f�B���O���

							if (!m_bSlide)
							{ // �X���C�f�B���O���ł͂Ȃ��ꍇ

								// �q�b�g
								Hit();
							}

							break;

						default:	// ��O����
							assert(false);
							break;
						}

						break;

					case CObstacle::STATE_JUMP:	// �G���ƃW�����v���������

						if (!m_bJump)
						{ // �W�����v���ł͂Ȃ��ꍇ

							// �ړ��ʂ�ǉ�
							m_move.y += basic::JUMPPAD_MOVE;

							// �W�����v���[�V������ݒ�
							SetMotion(MOTION_JUMP);

							// �W�����v���Ă����Ԃɂ���
							m_bJump = true;

							// �T�E���h�̍Đ�
							CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_JUMPPAD);	// �W�����v�p�b�h��
						}

						break;

					
					default:	// ��O����
						assert(false);
						break;
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}
}

//============================================================
//	��Q���Ƃ̒��n����
//============================================================
bool CPlayer::LandObstacle(D3DXVECTOR3& rPos)
{
	// �ϐ���錾
	D3DXVECTOR3 sizeMinPlayer = D3DXVECTOR3(basic::RADIUS, 0.0f, basic::RADIUS);			// �v���C���[�ŏ��傫��
	D3DXVECTOR3 sizeMaxPlayer = D3DXVECTOR3(basic::RADIUS, basic::HEIGHT, basic::RADIUS);	// �v���C���[�ő�傫��
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

						// �v���C���[�ʒu����Q���̏�ɂ���
						rPos.y = posObs.y + sizeObs.y;

						// ���n���Ă���󋵂ɂ���
						bLand = true;

						// �c�ړ��ʂ�������
						m_move.y = 0.0f;
					}
					else if (m_oldPos.y + basic::HEIGHT <= posObs.y)
					{ // �O��̈ʒu�����_�ȉ��̏ꍇ

						// �v���C���[�ʒu����Q���̏�ɂ���
						rPos.y = posObs.y - basic::HEIGHT;

						// �c�ړ��ʂ�������
						m_move.y = 0.0f;
					}
					else
					{ // �O��̈ʒu�����n�_��菬�����ꍇ

						switch (pObjCheck->GetDodge())
						{ // ���@���Ƃ̏���
						case CObstacle::DODGE_NONE:		// �����@�Ȃ�

							// ����
			
							break;

						case CObstacle::DODGE_JUMP:		// �W�����v���

							// �q�b�g
							Hit();

							break;

						case CObstacle::DODGE_SLIDE:	// �X���C�f�B���O���

							if (!m_bSlide)
							{ // �X���C�f�B���O���ł͂Ȃ��ꍇ

								// �q�b�g
								Hit();
							}

							break;

						default:	// ��O����
							assert(false);
							break;
						}
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
bool CPlayer::CollisionBuilding(D3DXVECTOR3& rPos)
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

	if (m_state == STATE_DAMAGE)
	{ // �_���[�W��Ԃ̏ꍇ

		// �ړ��ʂ�����
		if (m_bJump)
		{ // �󒆂̏ꍇ
//			m_move.x *= (1.0f - basic::DMG_JUMP_REV);
			m_move.x += (0.0f - m_move.x) * basic::DMG_JUMP_REV;
//			m_move.z -= m_move.z * basic::DMG_JUMP_REV;
			m_move.z += (0.0f - m_move.z) * basic::DMG_JUMP_REV;
		}
		else
		{ // �n��̏ꍇ

			m_move.x += (0.0f - m_move.x) * basic::DMG_LAND_REV;
			m_move.z += (0.0f - m_move.z) * basic::DMG_LAND_REV;
		}
	}
	else
	{ // �_���[�W��Ԃł͂Ȃ��ꍇ

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
	}

	// ���n�󋵂�Ԃ�
	return bLand;
}

//============================================================
//	�Z�b�g�A�b�v����
//============================================================
void CPlayer::LoadSetup(void)
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
		MessageBox(NULL, "�v���C���[�Z�b�g�A�b�v�t�@�C���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}
}

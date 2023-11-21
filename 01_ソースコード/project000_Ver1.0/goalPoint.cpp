//============================================================
//
//	�S�[���|�C���g���� [goalPoint.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "goalPoint.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "collision.h"
#include "scene.h"
#include "friend.h"
#include "player.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int PRIORITY = 1;	// �S�[���|�C���g�̗D�揇��
	const D3DXVECTOR3 ADDPOS_FRIEND = D3DXVECTOR3(320.0f, 0.0f, -120.0f);	// �F�B�ʒu�̃S�[���ʒu����̉��Z��
}

//************************************************************
//	�q�N���X [CGoalPoint] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGoalPoint::CGoalPoint() : CObject(CObject::LABEL_GOALPOINT, PRIORITY)
{
	// �����o�ϐ����N���A
	m_pFriend = NULL;	// �F�B�̏��
	m_pos = VEC3_ZERO;	// �ʒu
	m_size = VEC3_ZERO;	// �傫��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CGoalPoint::~CGoalPoint()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGoalPoint::Init(void)
{
	// �����o�ϐ���������
	m_pFriend = NULL;	// �F�B�̏��
	m_pos = VEC3_ZERO;	// �ʒu
	m_size = VEC3_ZERO;	// �傫��

	// �F�B�̐���
	m_pFriend = CFriend::Create();
	if (m_pFriend == NULL)
	{ // �����Ɏ��s�����ꍇ

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
void CGoalPoint::Uninit(void)
{
	// �F�B�̏I��
	m_pFriend->Uninit();

	// �S�[���|�C���g��j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CGoalPoint::Update(void)
{
	// �v���C���[�Ƃ̓����蔻��
	CollisionPlayer();
}

//============================================================
//	�`�揈��
//============================================================
void CGoalPoint::Draw(void)
{

}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CGoalPoint::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// �F�B�̈ʒu��ݒ�
	m_pFriend->SetVec3Position(m_pos + ADDPOS_FRIEND);
}

//============================================================
//	�ʒu�擾����
//============================================================
D3DXVECTOR3 CGoalPoint::GetVec3Position(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//============================================================
//	����傫���ݒ�̐ݒ菈��
//============================================================
void CGoalPoint::SetVec3Sizing(const D3DXVECTOR3& rSize)
{
	// �����̑傫����ݒ�
	m_size = rSize;
}

//============================================================
//	����傫���擾����
//============================================================
D3DXVECTOR3 CGoalPoint::GetVec3Sizing(void) const
{
	// �傫����Ԃ�
	return m_size;
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CGoalPoint::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableDraw(bUpdate);	// ���g
	m_pFriend->SetEnableDraw(bUpdate);	// �F�B
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CGoalPoint::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);		// ���g
	m_pFriend->SetEnableDraw(bDraw);	// �F�B
}

//============================================================
//	��������
//============================================================
CGoalPoint *CGoalPoint::Create	// ����
(
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rSize	// �傫��
)
{
	// �|�C���^��錾
	CGoalPoint *pGoalPoint = NULL;	// �S�[���|�C���g�����p

	if (pGoalPoint == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pGoalPoint = new CGoalPoint;	// �S�[���|�C���g
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pGoalPoint != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// �S�[���|�C���g�̏�����
		if (FAILED(pGoalPoint->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pGoalPoint;
			pGoalPoint = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �ʒu��ݒ�
		pGoalPoint->SetVec3Position(rPos);

		// �傫����ݒ�
		pGoalPoint->SetVec3Sizing(rSize);

		// �m�ۂ����A�h���X��Ԃ�
		return pGoalPoint;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�F�B�ʒu�擾����
//============================================================
D3DXVECTOR3 CGoalPoint::GetVec3FriendPosition(void) const
{
	// �F�B�̈ʒu��Ԃ�
	return m_pFriend->GetVec3Position();
}

//============================================================
//	�v���C���[�Ƃ̓����蔻��
//============================================================
void CGoalPoint::CollisionPlayer(void)
{
	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME)
	{ // �Q�[�����[�h�̏ꍇ

		// �|�C���^��錾
		CPlayer *pPlayer = CScene::GetPlayer();	// �v���C���[���
		if (pPlayer == NULL)
		{ // �v���C���[�����݂��Ȃ��ꍇ

			// �����𔲂���
			assert(false);
			return;
		}

		// �ϐ���錾
		bool  bHit = false;	// �����
		float fPlayerRadius    = pPlayer->GetRadius();			// �v���C���[���a
		D3DXVECTOR3 posPlayer  = pPlayer->GetVec3Position();	// �v���C���[�ʒu
		D3DXVECTOR3 posGoal    = GetVec3Position();				// �S�[���ʒu
		D3DXVECTOR3 sizePlayer = D3DXVECTOR3(fPlayerRadius, 0.0f, fPlayerRadius);	// �v���C���[�傫��

		if (pPlayer->GetState() != CPlayer::STATE_CLEAR
		&&  pPlayer->GetState() != CPlayer::STATE_OVER)
		{ // �Q�[���I���Ɋւ����Ԃł͂Ȃ��ꍇ

			// �v���C���[�Ƃ̔���
			bHit = collision::Box2D
			( // ����
				posPlayer,	// ����ʒu
				posGoal,	// ����ڕW�ʒu
				sizePlayer,	// ����T�C�Y(�E�E��E��)
				sizePlayer,	// ����T�C�Y(���E���E�O)
				m_size,		// ����ڕW�T�C�Y(�E�E��E��)
				m_size		// ����ڕW�T�C�Y(���E���E�O)
			);
			if (bHit)
			{ // �v���C���[��������̏ꍇ

				// �v���C���[��������Ԃɂ���
				pPlayer->SetState(CPlayer::STATE_UNION);

				// �v���C���[�̃S�[�������g�ɐݒ�
				pPlayer->SetGoal(this);

				// �F�B�̏�Ԃ�������Ԃɐݒ�
				m_pFriend->SetState(CFriend::STATE_UNION);
			}
		}
	}
}


//============================================================
//
//	�Q�[���}�l�[�W���[���� [gameManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "gameManager.h"
#include "manager.h"
#include "scene.h"
#include "sceneGame.h"
#include "camera.h"
#include "player.h"
#include "timerManager.h"
#include "phoneManager.h"
#include "editStageManager.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CPhoneManager *CGameManager::m_pPhone = NULL;			// �X�}�z�}�l�[�W���[�̏��
CEditStageManager *CGameManager::m_pEditStage = NULL;	// �G�f�B�b�g�X�e�[�W�̏��

//************************************************************
//	�e�N���X [CGameManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGameManager::CGameManager()
{
	// �����o�ϐ����N���A
	m_state = STATE_NONE;	// ���
}

//============================================================
//	�f�X�g���N�^
//============================================================
CGameManager::~CGameManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGameManager::Init(void)
{
	// �����o�ϐ���������
	m_state = STATE_INIT_PHONE;	// ���

	if (m_pPhone == NULL)
	{ // �X�}�z�}�l�[�W���[���g�p����Ă��Ȃ��ꍇ

		// �X�}�z�}�l�[�W���[�̐���
		m_pPhone = CPhoneManager::Create();
		if (m_pPhone == NULL)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else { assert(false); }	// �g�p�ς�

#if _DEBUG

	if (m_pEditStage == NULL)
	{ // �G�f�B�b�g�X�e�[�W���g�p����Ă��Ȃ��ꍇ

		// �G�f�B�b�g�X�e�[�W�̐���
		m_pEditStage = CEditStageManager::Create();
		if (m_pEditStage == NULL)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else { assert(false); }	// �g�p�ς�

#endif	// _DEBUG

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGameManager::Uninit(void)
{
	if (m_pPhone != NULL)
	{ // �X�}�z�}�l�[�W���[���g�p����Ă���ꍇ

		// �X�}�z�}�l�[�W���[�̔j��
		CPhoneManager::Release(m_pPhone);
	}
	else { assert(false); }	// ��g�p��

	if (m_pEditStage != NULL)
	{ // �G�f�B�b�g�X�e�[�W���g�p����Ă���ꍇ

		// �G�f�B�b�g�X�e�[�W�̔j��
		CEditStageManager::Release(m_pEditStage);
	}
}

//============================================================
//	�X�V����
//============================================================
void CGameManager::Update(void)
{
	// �|�C���^��錾
	CTimerManager *pTimer = CSceneGame::GetTimerManager();	// �^�C�}�[�}�l�[�W���[
	assert(pTimer != NULL);
	CPlayer *pPlayer = CScene::GetPlayer();	// �v���C���[
	assert(pPlayer != NULL);

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:

		// ����

		break;

	case STATE_INIT_PHONE:

		// �X�}�z�����n�߂�悤�ɐݒ�
		m_pPhone->SetLook(CPhoneManager::TYPE_START);

		// �X�}�z�\����Ԃ�ݒ�
		m_state = STATE_PHONE;

		// �����𔲂����ɂ��̂܂ܒx���\����Ԃֈڍs

	case STATE_PHONE:

		if (m_pPhone != NULL)
		{ // �X�}�z�}�l�[�W���[���g�p����Ă���ꍇ

			// �X�}�z�}�l�[�W���[�̍X�V
			m_pPhone->Update();
		}
		else { assert(false); }	// ��g�p��

		if (m_pPhone->GetState() == CPhoneManager::STATE_END)
		{ // �x���̕\�����I�������ꍇ

			// �ʏ평������Ԃ�ݒ�
			m_state = STATE_INIT_NORMAL;
		}

		break;

	case STATE_INIT_NORMAL:

		// �`��̕`���ON�ɂ���
		CScene::GetPlayer()->SetEnableDraw(true);

		// �^�C�����v���J�n
		CSceneGame::GetTimerManager()->Start();	// �v�����J�n

		// �ʏ��Ԃ�ݒ�
		m_state = STATE_NORMAL;

		// �����𔲂����ɂ��̂܂ܒʏ��Ԃֈڍs

	case STATE_NORMAL:

		if (pTimer->GetState() == CTimerManager::STATE_END && pTimer->Get() <= 0)
		{ // �v���I�����Ă��銎�A�c�莞�Ԃ� 0�ȉ��̏ꍇ

			// �N���A���s�\���̏�������Ԃ�ݒ�
			m_state = STATE_INIT_END;
		}

		break;

	case STATE_INIT_END:

		// �X�}�z�����n�߂�悤�ɐݒ�
		m_pPhone->SetLook(CPhoneManager::TYPE_END);

		// �N���A���s�̕\����Ԃ�ݒ�
		m_state = STATE_END;

		// �����𔲂����ɂ��̂܂܃N���A���s�̕\����Ԃֈڍs

	case STATE_END:

		if (m_pPhone != NULL)
		{ // �X�}�z�}�l�[�W���[���g�p����Ă���ꍇ

			// �X�}�z�}�l�[�W���[�̍X�V
			m_pPhone->Update();
		}
		else { assert(false); }	// ��g�p��

		if (m_pPhone->GetState() == CPhoneManager::STATE_END)
		{ // �N���A���s�̕\�����I�������ꍇ

			// �v���C���[���N���A���s��Ԃɂ���
			pPlayer->SetState(CPlayer::STATE_OVER);
		}

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	if (m_pEditStage != NULL)
	{ // �G�f�B�b�g�X�e�[�W���g�p����Ă���ꍇ

		// �G�f�B�b�g�X�e�[�W�̍X�V
		m_pEditStage->Update();
	}
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CGameManager::SetState(const EState state)
{
	if (state == STATE_INIT_PHONE
	||  state == STATE_INIT_NORMAL
	||  state == STATE_INIT_END)
	{ // ��������Ԃ̏ꍇ

		// ��Ԃ�ݒ�
		m_state = state;
	}
	else { assert(false); }	// ��������ԈȊO
}

//============================================================
//	��Ԏ擾����
//============================================================
CGameManager::EState CGameManager::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	��������
//============================================================
CGameManager *CGameManager::Create(void)
{
	// �|�C���^��錾
	CGameManager *pGameManager = NULL;	// �Q�[���}�l�[�W���[�����p

	if (pGameManager == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pGameManager = new CGameManager;	// �Q�[���}�l�[�W���[
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pGameManager != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �Q�[���}�l�[�W���[�̏�����
		if (FAILED(pGameManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pGameManager;
			pGameManager = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pGameManager;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CGameManager::Release(CGameManager *&prGameManager)
{
	if (prGameManager != NULL)
	{ // �g�p���̏ꍇ

		// �Q�[���}�l�[�W���[�̏I��
		prGameManager->Uninit();

		// �������J��
		delete prGameManager;
		prGameManager = NULL;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	�X�}�z�}�l�[�W���[�擾����
//============================================================
CPhoneManager *CGameManager::GetPhone(void)
{
	// �X�}�z�}�l�[�W���[�̏���Ԃ�
	return m_pPhone;
}

//============================================================
//	�G�f�B�b�g�X�e�[�W�擾����
//============================================================
CEditStageManager *CGameManager::GetEditStage(void)
{
	// �G�f�B�b�g�X�e�[�W�̏���Ԃ�
	return m_pEditStage;
}

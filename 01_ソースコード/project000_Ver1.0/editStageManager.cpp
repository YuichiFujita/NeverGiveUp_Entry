//============================================================
//
//	�G�f�B�b�g�X�e�[�W�}�l�[�W���[���� [editStageManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "editStageManager.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "editBuilding.h"
#include "editWindow.h"
#include "editSignboard.h"
#include "editObstacle.h"
#include "editSavePoint.h"
#include "editGoalPoint.h"

//************************************************************
//	�}�N����`
//************************************************************
#define KEY_DOUBLE		(DIK_LCONTROL)	// ��d���L�[
#define NAME_DOUBLE		("LCTRL")		// ��d���\��
#define KEY_TRIGGER		(DIK_LSHIFT)	// �g���K�[���L�[
#define NAME_TRIGGER	("LSHIFT")		// �g���K�[���\��

#define KEY_SAVE	(DIK_F9)	// �ۑ��L�[
#define NAME_SAVE	("F9")		// �ۑ��\��

#define KEY_CHANGE_THING	(DIK_1)	// �z�u���ύX�L�[
#define NAME_CHANGE_THING	("1")	// �z�u���ύX�\��

#define KEY_CAMERA	(DIK_1)	// �J�����ʒu�ύX�L�[
#define NAME_CAMERA	("1")	// �J�����ʒu�ύX�\��

#define KEY_MOVE_UP		(DIK_UP)	// �ړ��ʏ㏸�L�[
#define NAME_MOVE_UP	("��")		// �ړ��ʏ㏸�\��
#define KEY_MOVE_DOWN	(DIK_DOWN)	// �ړ��ʉ��~�L�[
#define NAME_MOVE_DOWN	("��")		// �ړ��ʉ��~�\��

#define KEY_FAR		(DIK_W)	// ���ړ��L�[
#define NAME_FAR	("W")	// ���ړ��\��
#define KEY_NEAR	(DIK_S)	// ��O�ړ��L�[
#define NAME_NEAR	("S")	// ��O�ړ��\��
#define KEY_RIGHT	(DIK_D)	// �E�ړ��L�[
#define NAME_RIGHT	("D")	// �E�ړ��\��
#define KEY_LEFT	(DIK_A)	// ���ړ��L�[
#define NAME_LEFT	("A")	// ���ړ��\��
#define KEY_UP		(DIK_E)	// ��ړ��L�[
#define NAME_UP		("E")	// ��ړ��\��
#define KEY_DOWN	(DIK_Q)	// ���ړ��L�[
#define NAME_DOWN	("Q")	// ���ړ��\��

#define KEY_ROTA_RIGHT	(DIK_Z)	// �E��]�L�[
#define NAME_ROTA_RIGHT	("Z")	// �E��]�\��
#define KEY_ROTA_LEFT	(DIK_C)	// ����]�L�[
#define NAME_ROTA_LEFT	("C")	// ����]�\��

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* SAVE_TXT	= "data\\TXT\\save_stage.txt";	// �X�e�[�W�Z�[�u�e�L�X�g
	const float INIT_MOVE	= 40.0f;	// �z�u���̏����ړ���
	const float CHANGE_MOVE = 10.0f;	// �z�u���̈ړ��ʂ̕ϓ���
	const float MIN_MOVE	= 10.0f;	// �z�u���̍ŏ��ړ���
	const float MAX_MOVE	= 200.0f;	// �z�u���̍ő�ړ���
}

//************************************************************
//	�e�N���X [CEditStageManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEditStageManager::CEditStageManager()
{
#if _DEBUG

	// �����o�ϐ����N���A
	m_pBuilding		= NULL;		// �G�f�B�b�g�r���̏��
	m_pWindow		= NULL;		// �G�f�B�b�g���̏��
	m_pSignboard	= NULL;		// �G�f�B�b�g�Ŕ̏��
	m_pObstacle		= NULL;		// �G�f�B�b�g��Q���̏��
	m_pSavePoint	= NULL;		// �G�f�B�b�g�Z�[�u�|�C���g�̏��
	m_pGoalPoint	= NULL;		// �G�f�B�b�g�S�[���|�C���g�̏��
	m_pos	= VEC3_ZERO;		// �ʒu
	m_rot	= VEC3_ZERO;		// ����
	m_fMove	= 0.0f;				// �ʒu�ړ���
	m_thing	= THING_BUILDING;	// �z�u��
	m_bSave	= false;			// �ۑ���
	m_bEdit	= false;			// �G�f�B�b�g��

#endif	// _DEBUG
}

//============================================================
//	�f�X�g���N�^
//============================================================
CEditStageManager::~CEditStageManager()
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	����������
//============================================================
HRESULT CEditStageManager::Init(void)
{
#if _DEBUG

	// �����o�ϐ���������
	m_pBuilding		= NULL;		// �G�f�B�b�g�r���̏��
	m_pWindow		= NULL;		// �G�f�B�b�g���̏��
	m_pSignboard	= NULL;		// �G�f�B�b�g�Ŕ̏��
	m_pObstacle		= NULL;		// �G�f�B�b�g��Q���̏��
	m_pSavePoint	= NULL;		// �G�f�B�b�g�Z�[�u�|�C���g�̏��
	m_pGoalPoint	= NULL;		// �G�f�B�b�g�S�[���|�C���g�̏��
	m_pos	= VEC3_ZERO;		// �ʒu
	m_rot	= VEC3_ZERO;		// ����
	m_fMove	= INIT_MOVE;		// �ʒu�ړ���
	m_thing	= THING_BUILDING;	// �z�u��
	m_bSave = false;			// �ۑ���
	m_bEdit	= false;			// �G�f�B�b�g��

#if 1	// TODO�F��Q�����ؗp�̏�����

	m_pos = D3DXVECTOR3(-2880.0f, 1120.0f, -4000.0f);		// �ʒu
	m_thing = THING_OBSTACLE;	// �z�u��

#endif

	// �G�f�B�b�g�r���̐���
	m_pBuilding = CEditBuilding::Create(this);
	if (m_pBuilding == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �G�f�B�b�g���̐���
	m_pWindow = CEditWindow::Create(this);
	if (m_pWindow == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �G�f�B�b�g�Ŕ̐���
	m_pSignboard = CEditSignboard::Create(this);
	if (m_pSignboard == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �G�f�B�b�g��Q���̐���
	m_pObstacle = CEditObstacle::Create(this);
	if (m_pObstacle == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �G�f�B�b�g�Z�[�u�|�C���g�̐���
	m_pSavePoint = CEditSavePoint::Create(this);
	if (m_pSavePoint == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �G�f�B�b�g�S�[���|�C���g�̐���
	m_pGoalPoint = CEditGoalPoint::Create(this);
	if (m_pGoalPoint == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;

#else	// NDEBUG

	// ������Ԃ�
	return S_OK;

#endif	// _DEBUG
}

//============================================================
//	�I������
//============================================================
void CEditStageManager::Uninit(void)
{
#if _DEBUG

	if (m_pBuilding != NULL)
	{ // �G�f�B�b�g�r�����g�p����Ă���ꍇ

		// �G�f�B�b�g�r���̔j��
		CEditBuilding::Release(m_pBuilding);
	}
	else { assert(false); }	// ��g�p��

	if (m_pWindow != NULL)
	{ // �G�f�B�b�g�����g�p����Ă���ꍇ

		// �G�f�B�b�g���̔j��
		CEditWindow::Release(m_pWindow);
	}
	else { assert(false); }	// ��g�p��

	if (m_pSignboard != NULL)
	{ // �G�f�B�b�g�Ŕ��g�p����Ă���ꍇ

		// �G�f�B�b�g�Ŕ̔j��
		CEditSignboard::Release(m_pSignboard);
	}
	else { assert(false); }	// ��g�p��

	if (m_pObstacle != NULL)
	{ // �G�f�B�b�g��Q�����g�p����Ă���ꍇ

		// �G�f�B�b�g��Q���̔j��
		CEditObstacle::Release(m_pObstacle);
	}
	else { assert(false); }	// ��g�p��

	if (m_pSavePoint != NULL)
	{ // �G�f�B�b�g�Z�[�u�|�C���g���g�p����Ă���ꍇ

		// �G�f�B�b�g�Z�[�u�|�C���g�̔j��
		CEditSavePoint::Release(m_pSavePoint);
	}
	else { assert(false); }	// ��g�p��

	if (m_pGoalPoint != NULL)
	{ // �G�f�B�b�g�S�[���|�C���g���g�p����Ă���ꍇ

		// �G�f�B�b�g�S�[���|�C���g�̔j��
		CEditGoalPoint::Release(m_pGoalPoint);
	}
	else { assert(false); }	// ��g�p��

#endif	// _DEBUG
}

//============================================================
//	�X�V����
//============================================================
void CEditStageManager::Update(void)
{
#if _DEBUG

	if (!m_bEdit)
	{ // �G�f�B�b�g���[�h�ł͂Ȃ��ꍇ

		// �����𔲂���
		return;
	}

	// �z�u���ύX�̍X�V
	UpdateChangeThing();

	// �ړ��ʕύX�̍X�V
	UpdateChangeMove();

	// �ʒu�̍X�V
	UpdatePosition();

	// �����̍X�V
	UpdateRotation();

	// �J�����ʒu�ύX�̍X�V
	UpdatePosCamera();

	switch (m_thing)
	{ // �z�u�����Ƃ̏���
	case THING_BUILDING:	// �r��

		if (m_pBuilding != NULL)
		{ // �G�f�B�b�g�r�����g�p����Ă���ꍇ

			// �G�f�B�b�g�r���̍X�V
			m_pBuilding->Update();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_WINDOW:		// ��

		if (m_pWindow != NULL)
		{ // �G�f�B�b�g�����g�p����Ă���ꍇ

			// �G�f�B�b�g���̍X�V
			m_pWindow->Update();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_SIGNBOARD:	// �Ŕ�

		if (m_pSignboard != NULL)
		{ // �G�f�B�b�g�Ŕ��g�p����Ă���ꍇ

			// �G�f�B�b�g�Ŕ̍X�V
			m_pSignboard->Update();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_OBSTACLE:	// ��Q��

		if (m_pObstacle != NULL)
		{ // �G�f�B�b�g��Q�����g�p����Ă���ꍇ

			// �G�f�B�b�g��Q���̍X�V
			m_pObstacle->Update();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_SAVEPOINT:	// �Z�[�u�|�C���g

		if (m_pSavePoint != NULL)
		{ // �G�f�B�b�g�Z�[�u�|�C���g���g�p����Ă���ꍇ

			// �G�f�B�b�g�Z�[�u�|�C���g�̍X�V
			m_pSavePoint->Update();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_GOALPOINT:	// �S�[���|�C���g

		if (m_pGoalPoint != NULL)
		{ // �G�f�B�b�g�S�[���|�C���g���g�p����Ă���ꍇ

			// �G�f�B�b�g�S�[���|�C���g�̍X�V
			m_pGoalPoint->Update();
		}
		else { assert(false); }	// ��g�p��

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	// �X�e�[�W�ۑ�
	SaveStage();

	// ����\���̕`��
	DrawDebugControl();

	// ���\���̕`��
	DrawDebugInfo();

#endif	// _DEBUG
}

//============================================================
//	���ۑ��̐ݒ菈��
//============================================================
void CEditStageManager::UnSave(void)
{
	// �ۑ����Ă��Ȃ��󋵂ɂ���
	m_bSave = false;
}

//============================================================
//	�G�f�B�b�g�󋵂̐ݒ菈��
//============================================================
void CEditStageManager::SetEnableEdit(const bool bEdit)
{
	// �����̃G�f�B�b�g�󋵂ɂ���
	m_bEdit = bEdit;

	switch (m_thing)
	{ // �z�u�����Ƃ̏���
	case THING_BUILDING:	// �r��

		if (m_pBuilding != NULL)
		{ // �G�f�B�b�g�r�����g�p����Ă���ꍇ

			// �G�f�B�b�g�r���̕\���̐ݒ�
			m_pBuilding->SetDisp(m_bEdit);
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_WINDOW:		// ��

		if (m_pWindow != NULL)
		{ // �G�f�B�b�g�����g�p����Ă���ꍇ

			// �G�f�B�b�g���̕\���̐ݒ�
			m_pWindow->SetDisp(m_bEdit);
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_SIGNBOARD:	// �Ŕ�

		if (m_pSignboard != NULL)
		{ // �G�f�B�b�g�Ŕ��g�p����Ă���ꍇ

			// �G�f�B�b�g�Ŕ̕\���̐ݒ�
			m_pSignboard->SetDisp(m_bEdit);
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_OBSTACLE:	// ��Q��

		if (m_pObstacle != NULL)
		{ // �G�f�B�b�g��Q�����g�p����Ă���ꍇ

			// �G�f�B�b�g��Q���̕\���̐ݒ�
			m_pObstacle->SetDisp(m_bEdit);
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_SAVEPOINT:	// �Z�[�u�|�C���g

		if (m_pSavePoint != NULL)
		{ // �G�f�B�b�g�Z�[�u�|�C���g���g�p����Ă���ꍇ

			// �G�f�B�b�g�Z�[�u�|�C���g�̕\���̐ݒ�
			m_pSavePoint->SetDisp(m_bEdit);
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_GOALPOINT:	// �S�[���|�C���g

		if (m_pGoalPoint != NULL)
		{ // �G�f�B�b�g�S�[���|�C���g���g�p����Ă���ꍇ

			// �G�f�B�b�g�S�[���|�C���g�̕\���̐ݒ�
			m_pGoalPoint->SetDisp(m_bEdit);
		}
		else { assert(false); }	// ��g�p��

		break;

	default:	// ��O����
		assert(false);
		break;
	}
}

//============================================================
//	�G�f�B�b�g�󋵎擾����
//============================================================
bool CEditStageManager::IsEdit(void) const
{
	// �G�f�B�b�g�󋵂�Ԃ�
	return m_bEdit;
}

//============================================================
//	�ʒu�擾����
//============================================================
D3DXVECTOR3 CEditStageManager::GetVec3Position(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//============================================================
//	�����擾����
//============================================================
D3DXVECTOR3 CEditStageManager::GetVec3Rotation(void) const
{
	// ������Ԃ�
	return m_rot;
}

//============================================================
//	��������
//============================================================
CEditStageManager *CEditStageManager::Create(void)
{
#if _DEBUG

	// �|�C���^��錾
	CEditStageManager *pEditStageManager = NULL;	// �G�f�B�b�g�X�e�[�W�}�l�[�W���[�����p

	if (pEditStageManager == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pEditStageManager = new CEditStageManager;	// �G�f�B�b�g�X�e�[�W�}�l�[�W���[
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pEditStageManager != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �G�f�B�b�g�X�e�[�W�}�l�[�W���[�̏�����
		if (FAILED(pEditStageManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pEditStageManager;
			pEditStageManager = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pEditStageManager;
	}
	else { assert(false); return NULL; }	// �m�ێ��s

#else	// NDEBUG

	// NULL��Ԃ�
	return NULL;

#endif	// _DEBUG
}

//============================================================
//	�j������
//============================================================
HRESULT CEditStageManager::Release(CEditStageManager *&prEditStageManager)
{
#if _DEBUG

	if (prEditStageManager != NULL)
	{ // �g�p���̏ꍇ

		// �G�f�B�b�g�X�e�[�W�}�l�[�W���[�̏I��
		prEditStageManager->Uninit();

		// �������J��
		delete prEditStageManager;
		prEditStageManager = NULL;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��

#else	// NDEBUG

	// ������Ԃ�
	return S_OK;

#endif	// _DEBUG
}

//============================================================
//	�z�u���ύX�̍X�V����
//============================================================
void CEditStageManager::UpdateChangeThing(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �z�u����ύX
	if (!m_pKeyboard->IsPress(KEY_DOUBLE))
	{
		if (m_pKeyboard->IsTrigger(KEY_CHANGE_THING))
		{
			switch (m_thing)
			{ // �z�u�����Ƃ̏���
			case THING_BUILDING:	// �r��

				if (m_pBuilding != NULL)
				{ // �G�f�B�b�g�r�����g�p����Ă���ꍇ

					// �G�f�B�b�g�r���̕\���̐ݒ�
					m_pBuilding->SetDisp(false);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_WINDOW:		// ��

				if (m_pWindow != NULL)
				{ // �G�f�B�b�g�����g�p����Ă���ꍇ

					// �G�f�B�b�g���̕\���̐ݒ�
					m_pWindow->SetDisp(false);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_SIGNBOARD:	// �Ŕ�

				if (m_pSignboard != NULL)
				{ // �G�f�B�b�g�Ŕ��g�p����Ă���ꍇ

					// �G�f�B�b�g�Ŕ̕\���̐ݒ�
					m_pSignboard->SetDisp(false);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_OBSTACLE:	// ��Q��

				if (m_pObstacle != NULL)
				{ // �G�f�B�b�g��Q�����g�p����Ă���ꍇ

					// �G�f�B�b�g��Q���̕\���̐ݒ�
					m_pObstacle->SetDisp(false);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_SAVEPOINT:	// �Z�[�u�|�C���g

				if (m_pSavePoint != NULL)
				{ // �G�f�B�b�g�Z�[�u�|�C���g���g�p����Ă���ꍇ

					// �G�f�B�b�g�Z�[�u�|�C���g�̕\���̐ݒ�
					m_pSavePoint->SetDisp(false);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_GOALPOINT:	// �S�[���|�C���g

				if (m_pGoalPoint != NULL)
				{ // �G�f�B�b�g�S�[���|�C���g���g�p����Ă���ꍇ

					// �G�f�B�b�g�S�[���|�C���g�̕\���̐ݒ�
					m_pGoalPoint->SetDisp(false);
				}
				else { assert(false); }	// ��g�p��

				break;

			default:	// ��O����
				assert(false);
				break;
			}

			// �z�u���̕ύX
			m_thing = (EThing)((m_thing + 1) % THING_MAX);

			switch (m_thing)
			{ // �z�u�����Ƃ̏���
			case THING_BUILDING:	// �r��

				if (m_pBuilding != NULL)
				{ // �G�f�B�b�g�r�����g�p����Ă���ꍇ

					// �G�f�B�b�g�r���̕\���̐ݒ�
					m_pBuilding->SetDisp(true);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_WINDOW:		// ��

				if (m_pWindow != NULL)
				{ // �G�f�B�b�g�����g�p����Ă���ꍇ

					// �G�f�B�b�g���̕\���̐ݒ�
					m_pWindow->SetDisp(true);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_SIGNBOARD:	// �Ŕ�

				if (m_pSignboard != NULL)
				{ // �G�f�B�b�g�Ŕ��g�p����Ă���ꍇ

					// �G�f�B�b�g�Ŕ̕\���̐ݒ�
					m_pSignboard->SetDisp(true);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_OBSTACLE:	// ��Q��

				if (m_pObstacle != NULL)
				{ // �G�f�B�b�g��Q�����g�p����Ă���ꍇ

					// �G�f�B�b�g��Q���̕\���̐ݒ�
					m_pObstacle->SetDisp(true);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_SAVEPOINT:	// �Z�[�u�|�C���g

				if (m_pSavePoint != NULL)
				{ // �G�f�B�b�g�Z�[�u�|�C���g���g�p����Ă���ꍇ

					// �G�f�B�b�g�Z�[�u�|�C���g�̕\���̐ݒ�
					m_pSavePoint->SetDisp(true);
				}
				else { assert(false); }	// ��g�p��

				break;

			case THING_GOALPOINT:	// �S�[���|�C���g

				if (m_pGoalPoint != NULL)
				{ // �G�f�B�b�g�S�[���|�C���g���g�p����Ă���ꍇ

					// �G�f�B�b�g�S�[���|�C���g�̕\���̐ݒ�
					m_pGoalPoint->SetDisp(true);
				}
				else { assert(false); }	// ��g�p��

				break;

			default:	// ��O����
				assert(false);
				break;
			}
		}
	}
}

//============================================================
//	�ړ��ʕύX�̍X�V����
//============================================================
void CEditStageManager::UpdateChangeMove(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �ړ��ʂ�ύX
	if (!m_pKeyboard->IsPress(KEY_TRIGGER))
	{
		if (m_pKeyboard->IsPress(KEY_MOVE_UP))
		{
			m_fMove += CHANGE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_MOVE_DOWN))
		{
			m_fMove -= CHANGE_MOVE;
		}
	}
	else
	{
		if (m_pKeyboard->IsTrigger(KEY_MOVE_UP))
		{
			m_fMove += CHANGE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_MOVE_DOWN))
		{
			m_fMove -= CHANGE_MOVE;
		}
	}

	// �ړ��ʂ�␳
	useful::LimitNum(m_fMove, MIN_MOVE, MAX_MOVE);
}

//============================================================
//	�ʒu�̍X�V����
//============================================================
void CEditStageManager::UpdatePosition(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �ʒu��ύX
	if (!m_pKeyboard->IsPress(KEY_TRIGGER))
	{
		if (m_pKeyboard->IsPress(KEY_FAR))
		{
			m_pos.z += m_fMove;
		}
		if (m_pKeyboard->IsPress(KEY_NEAR))
		{
			m_pos.z -= m_fMove;
		}
		if (m_pKeyboard->IsPress(KEY_RIGHT))
		{
			m_pos.x += m_fMove;
		}
		if (m_pKeyboard->IsPress(KEY_LEFT))
		{
			m_pos.x -= m_fMove;
		}
		if (m_pKeyboard->IsPress(KEY_UP))
		{
			m_pos.y += m_fMove;
		}
		if (m_pKeyboard->IsPress(KEY_DOWN))
		{
			m_pos.y -= m_fMove;
		}
	}
	else
	{
		if (m_pKeyboard->IsTrigger(KEY_FAR))
		{
			m_pos.z += m_fMove;
		}
		if (m_pKeyboard->IsTrigger(KEY_NEAR))
		{
			m_pos.z -= m_fMove;
		}
		if (m_pKeyboard->IsTrigger(KEY_RIGHT))
		{
			m_pos.x += m_fMove;
		}
		if (m_pKeyboard->IsTrigger(KEY_LEFT))
		{
			m_pos.x -= m_fMove;
		}
		if (m_pKeyboard->IsTrigger(KEY_UP))
		{
			m_pos.y += m_fMove;
		}
		if (m_pKeyboard->IsTrigger(KEY_DOWN))
		{
			m_pos.y -= m_fMove;
		}
	}
}

//============================================================
//	�����̍X�V����
//============================================================
void CEditStageManager::UpdateRotation(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ������ύX
	if (m_pKeyboard->IsTrigger(KEY_ROTA_RIGHT))
	{
		m_rot.y += HALF_PI;
	}
	if (m_pKeyboard->IsTrigger(KEY_ROTA_LEFT))
	{
		m_rot.y -= HALF_PI;
	}

	// �����𐳋K��
	useful::Vec3NormalizeRot(m_rot);
}

//============================================================
//	�J�����ʒu�ύX�̍X�V����
//============================================================
void CEditStageManager::UpdatePosCamera(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �J�����ʒu��ύX
	if (m_pKeyboard->IsPress(KEY_DOUBLE))
	{
		if (m_pKeyboard->IsTrigger(KEY_CAMERA))
		{
			// �|�C���^��錾
			CCamera *pCamera = CManager::GetInstance()->GetCamera();	// �J�������

#if _DEBUG

			// �z�u���̈ʒu�ɒ����_��ݒ�
			pCamera->SetThingLook();

#endif	// _DEBUG

		}
	}
}

//============================================================
//	����\���̕`�揈��
//============================================================
void CEditStageManager::DrawDebugControl(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��

	pDebug->Print(CDebugProc::POINT_RIGHT, "======================================\n");
	pDebug->Print(CDebugProc::POINT_RIGHT, "[�G�f�B�b�g����]�@\n");
	pDebug->Print(CDebugProc::POINT_RIGHT, "======================================\n");
	pDebug->Print(CDebugProc::POINT_RIGHT, "�X�e�[�W�ۑ��F[%s+%s]\n", NAME_DOUBLE, NAME_SAVE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�ړ��F[%s/%s/%s/%s/%s/%s+%s]\n", NAME_FAR, NAME_LEFT, NAME_NEAR, NAME_RIGHT, NAME_UP, NAME_DOWN, NAME_TRIGGER);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�ړ��ʕύX�F[%s/%s]\n", NAME_MOVE_UP, NAME_MOVE_DOWN);
	pDebug->Print(CDebugProc::POINT_RIGHT, "��]�F[%s/%s]\n", NAME_ROTA_RIGHT, NAME_ROTA_LEFT);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�z�u���J�����F[%s+%s]\n", NAME_DOUBLE, NAME_CAMERA);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�z�u���ύX�F[%s]\n", NAME_CHANGE_THING);

	switch (m_thing)
	{ // �z�u�����Ƃ̏���
	case THING_BUILDING:	// �r��

		if (m_pBuilding != NULL)
		{ // �G�f�B�b�g�r�����g�p����Ă���ꍇ

			// �G�f�B�b�g�r���̑���\��
			m_pBuilding->DrawDebugControl();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_WINDOW:		// ��

		if (m_pWindow != NULL)
		{ // �G�f�B�b�g�����g�p����Ă���ꍇ

			// �G�f�B�b�g���̑���\��
			m_pWindow->DrawDebugControl();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_SIGNBOARD:	// �Ŕ�

		if (m_pSignboard != NULL)
		{ // �G�f�B�b�g�Ŕ��g�p����Ă���ꍇ

			// �G�f�B�b�g�Ŕ̑���\��
			m_pSignboard->DrawDebugControl();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_OBSTACLE:	// ��Q��

		if (m_pObstacle != NULL)
		{ // �G�f�B�b�g��Q�����g�p����Ă���ꍇ

			// �G�f�B�b�g��Q���̑���\��
			m_pObstacle->DrawDebugControl();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_SAVEPOINT:	// �Z�[�u�|�C���g

		if (m_pSavePoint != NULL)
		{ // �G�f�B�b�g�Z�[�u�|�C���g���g�p����Ă���ꍇ

			// �G�f�B�b�g�Z�[�u�|�C���g�̑���\��
			m_pSavePoint->DrawDebugControl();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_GOALPOINT:	// �S�[���|�C���g

		if (m_pGoalPoint != NULL)
		{ // �G�f�B�b�g�S�[���|�C���g���g�p����Ă���ꍇ

			// �G�f�B�b�g�S�[���|�C���g�̑���\��
			m_pGoalPoint->DrawDebugControl();
		}
		else { assert(false); }	// ��g�p��

		break;

	default:	// ��O����
		assert(false);
		break;
	}
}

//============================================================
//	���\���̕`�揈��
//============================================================
void CEditStageManager::DrawDebugInfo(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��
	static char* apThing[] = { "�r��", "��", "�Ŕ�", "��Q��", "�Z�[�u�|�C���g", "�S�[���|�C���g" };	// �z�u��

	// �z�u�����̕s��v
	assert((sizeof(apThing) / sizeof(apThing[0])) == THING_MAX);

	pDebug->Print(CDebugProc::POINT_RIGHT, "======================================\n");
	pDebug->Print(CDebugProc::POINT_RIGHT, "[�G�f�B�b�g���]�@\n");
	pDebug->Print(CDebugProc::POINT_RIGHT, "======================================\n");
	pDebug->Print(CDebugProc::POINT_RIGHT, (m_bSave) ? "�ۑ��ρF[�ۑ���]\n" : "���ۑ��F[�ۑ���]\n");
	pDebug->Print(CDebugProc::POINT_RIGHT, "%s�F[�z�u��]\n", apThing[m_thing]);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%f %f %f�F[�ʒu]\n", m_pos.x, m_pos.y, m_pos.z);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%f %f %f�F[����]\n", m_rot.x, m_rot.y, m_rot.z);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%f�F[�ړ���]\n", m_fMove);

	switch (m_thing)
	{ // �z�u�����Ƃ̏���
	case THING_BUILDING:	// �r��

		if (m_pBuilding != NULL)
		{ // �G�f�B�b�g�r�����g�p����Ă���ꍇ

			// �G�f�B�b�g�r���̏��\��
			m_pBuilding->DrawDebugInfo();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_WINDOW:		// ��

		if (m_pWindow != NULL)
		{ // �G�f�B�b�g�����g�p����Ă���ꍇ

			// �G�f�B�b�g���̏��\��
			m_pWindow->DrawDebugInfo();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_SIGNBOARD:	// �Ŕ�

		if (m_pSignboard != NULL)
		{ // �G�f�B�b�g�Ŕ��g�p����Ă���ꍇ

			// �G�f�B�b�g�Ŕ̏��\��
			m_pSignboard->DrawDebugInfo();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_OBSTACLE:	// ��Q��

		if (m_pObstacle != NULL)
		{ // �G�f�B�b�g��Q�����g�p����Ă���ꍇ

			// �G�f�B�b�g��Q���̏��\��
			m_pObstacle->DrawDebugInfo();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_SAVEPOINT:	// �Z�[�u�|�C���g

		if (m_pSavePoint != NULL)
		{ // �G�f�B�b�g�Z�[�u�|�C���g���g�p����Ă���ꍇ

			// �G�f�B�b�g�Z�[�u�|�C���g�̏��\��
			m_pSavePoint->DrawDebugInfo();
		}
		else { assert(false); }	// ��g�p��

		break;

	case THING_GOALPOINT:	// �S�[���|�C���g

		if (m_pGoalPoint != NULL)
		{ // �G�f�B�b�g�S�[���|�C���g���g�p����Ă���ꍇ

			// �G�f�B�b�g�S�[���|�C���g�̏��\��
			m_pGoalPoint->DrawDebugInfo();
		}
		else { assert(false); }	// ��g�p��

		break;

	default:	// ��O����
		assert(false);
		break;
	}
}

//============================================================
//	�X�e�[�W�ۑ�����
//============================================================
void CEditStageManager::SaveStage(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �X�e�[�W��ۑ�
	if (m_pKeyboard->IsPress(KEY_DOUBLE))
	{
		if (m_pKeyboard->IsTrigger(KEY_SAVE))
		{
			// �ۑ�����
			Save();

			// �ۑ�������Ԃɂ���
			m_bSave = true;
		}
	}
}

//============================================================
//	�ۑ�����
//============================================================
void CEditStageManager::Save(void)
{
	// �|�C���^��錾
	FILE *pFile = NULL;	// �t�@�C���|�C���^

	// �t�@�C���������o���`���ŊJ��
	pFile = fopen(SAVE_TXT, "w");

	if (pFile != NULL)
	{ // �t�@�C�����J�����ꍇ

		// ���o���������o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	�X�e�[�W�Z�[�u�e�L�X�g [save_stage.txt]\n");
		fprintf(pFile, "#	Author : you\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "---------->--<---------- �������牺�� �R�s�[���\��t�� ---------->--<----------\n\n");

		// �r���̕ۑ�
		m_pBuilding->Save(pFile);

		// ���̕ۑ�
		m_pWindow->Save(pFile);

		// �Ŕ̕ۑ�
		m_pSignboard->Save(pFile);

		// ��Q���̕ۑ�
		m_pObstacle->Save(pFile);

		// �Z�[�u�|�C���g�̕ۑ�
		m_pSavePoint->Save(pFile);

		// �S�[���|�C���g�̕ۑ�
		m_pGoalPoint->Save(pFile);

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "�X�e�|�W�Z�[�u�t�@�C���̏����o���Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}
}

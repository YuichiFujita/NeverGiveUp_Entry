//============================================================
//
//	�G�f�B�b�g������ [editWindow.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "editWindow.h"
#include "manager.h"
#include "input.h"
#include "collision.h"
#include "editStageManager.h"
#include "stage.h"

//************************************************************
//	�}�N����`
//************************************************************
#define KEY_TRIGGER		(DIK_LSHIFT)	// �g���K�[���L�[
#define NAME_TRIGGER	("LSHIFT")		// �g���K�[���\��

#define KEY_CREATE		(DIK_0)	// �����L�[
#define NAME_CREATE		("0")	// �����\��
#define KEY_RELEASE		(DIK_9)	// �j���L�[
#define NAME_RELEASE	("9")	// �j���\��
#define KEY_TYPE		(DIK_2)	// ��ޕύX�L�[
#define NAME_TYPE		("2")	// ��ޕύX�\��
#define KEY_SCALE_UP	(DIK_3)	// �g�嗦�㏸�L�[
#define NAME_SCALE_UP	("3")	// �g�嗦�㏸�\��
#define KEY_SCALE_DOWN	(DIK_4)	// �g�嗦���~�L�[
#define NAME_SCALE_DOWN	("4")	// �g�嗦���~�\��

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const D3DXCOLOR	INIT_COL	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// �z�u�O�̐F
	const float CHANGE_SCALE	= 0.05f;	// �g�嗦�ύX��
}

//************************************************************
//	�e�N���X [CEditWindow] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEditWindow::CEditWindow()
{
#if _DEBUG

	// �����o�ϐ����N���A
	m_pEdit = NULL;	// �G�f�B�b�g�X�e�[�W�̏��
	memset(&m_window, 0, sizeof(m_window));	// ���z�u���

#endif	// _DEBUG
}

//============================================================
//	�f�X�g���N�^
//============================================================
CEditWindow::~CEditWindow()
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	����������
//============================================================
HRESULT CEditWindow::Init(void)
{
#if _DEBUG

	// �����o�ϐ���������
	m_pEdit = NULL;	// �G�f�B�b�g�X�e�[�W�̏��
	m_window.pWindow = NULL;	// �����
	m_window.type = CWindow::TYPE_NORMAL;	// �����

	// ���̐���
	m_window.pWindow = CWindow::Create(m_window.type, VEC3_ZERO, VEC3_ZERO);
	if (m_window.pWindow == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �F��ݒ�
	m_window.pWindow->SetColor(INIT_COL);

	// �\����OFF�ɂ���
	SetDisp(false);

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
void CEditWindow::Uninit(void)
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	�X�V����
//============================================================
void CEditWindow::Update(void)
{
#if _DEBUG

	if (m_pEdit == NULL)
	{ // �G�f�B�b�g�X�e�[�W�����݂��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return;
	}

	// ��ޕύX�̍X�V
	UpdateChangeType();

	// �g�嗦�ύX�̍X�V
	UpdateChangeScale();

	// ���̐���
	MyCreateWindow();

	// ���̔j��
	ReleaseWindow();

	// �ʒu�𔽉f
	m_window.pWindow->SetVec3Position(m_pEdit->GetVec3Position());

	// �����𔽉f
	m_window.pWindow->SetVec3Rotation(m_pEdit->GetVec3Rotation());

	// ��ނ𔽉f
	m_window.pWindow->SetType(m_window.type);

#endif	// _DEBUG
}

//============================================================
//	�\���̐ݒ菈��
//============================================================
void CEditWindow::SetDisp(const bool bDisp)
{
	// �����X�V�E�����`���\���󋵂ɍ��킹��
	m_window.pWindow->SetEnableUpdate(bDisp);	// �X�V
	m_window.pWindow->SetEnableDraw(bDisp);		// �`��

	if (bDisp)
	{ // �\��ON�̏ꍇ

		// �ʒu�𔽉f
		m_window.pWindow->SetVec3Position(m_pEdit->GetVec3Position());
	}
	else
	{ // �\��OFF�̏ꍇ

		// ���̐F�̑S������
		InitAllColorWindow();

		// �ʒu���X�e�[�W�͈̔͊O�ɐݒ�
		D3DXVECTOR3 outLimit = D3DXVECTOR3(0.0f, 0.0f, CScene::GetStage()->GetStageLimit().fNear - m_window.pWindow->GetVec3Sizing().z);
		m_window.pWindow->SetVec3Position(outLimit);
	}
}

//============================================================
//	����\���̕`�揈��
//============================================================
void CEditWindow::DrawDebugControl(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��

	pDebug->Print(CDebugProc::POINT_RIGHT, "��ޕύX�F[%s]\n", NAME_TYPE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�g�嗦�㏸�F[%s]\n", NAME_SCALE_UP);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�g�嗦���~�F[%s]\n", NAME_SCALE_DOWN);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�폜�F[%s]\n", NAME_RELEASE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�ݒu�F[%s]\n", NAME_CREATE);
}

//============================================================
//	���\���̕`�揈��
//============================================================
void CEditWindow::DrawDebugInfo(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��

	pDebug->Print(CDebugProc::POINT_RIGHT, "%d�F[���]\n", m_window.type);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%f�F[�g�嗦]\n", m_window.pWindow->GetScale());
}

//============================================================
//	�ۑ�����
//============================================================
void CEditWindow::Save(FILE *pFile)
{
#if _DEBUG

	if (pFile != NULL)
	{ // �t�@�C�������݂���ꍇ

		// ���o���������o��
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#	���̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		// ���J�n�n�_�������o��
		fprintf(pFile, "STAGE_WINDOWSET\n\n");

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
	
					if (pObjCheck->GetLabel() != CObject::LABEL_WINDOW)
					{ // �I�u�W�F�N�g���x�������ł͂Ȃ��ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}
	
					if (pObjCheck == (CObject*)m_window.pWindow)
					{ // �����A�h���X�������ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}

					// ���̏����擾
					D3DXVECTOR3 posBuild = pObjCheck->GetVec3Position();	// �ʒu
					D3DXVECTOR3 rotBuild = pObjCheck->GetVec3Rotation();	// ����
					int nType = pObjCheck->GetType();		// ���
					float fScale = pObjCheck->GetScale();	// �g�嗦
	
					// ���������o��
					fprintf(pFile, "	WINDOWSET\n");
					fprintf(pFile, "		TYPE = %d\n", nType);
					fprintf(pFile, "		POS = %.2f %.2f %.2f\n", posBuild.x, posBuild.y, posBuild.z);
					fprintf(pFile, "		ROT = %.2f %.2f %.2f\n", rotBuild.x, rotBuild.y, rotBuild.z);
					fprintf(pFile, "		SCALE = %.2f\n", fScale);
					fprintf(pFile, "	END_WINDOWSET\n\n");

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;
				}
			}
		}

		// ���I���n�_�������o��
		fprintf(pFile, "END_STAGE_WINDOWSET\n\n");
	}

#endif	// _DEBUG
}

//============================================================
//	��������
//============================================================
CEditWindow *CEditWindow::Create(CEditStageManager *pEdit)
{
#if _DEBUG

	// �|�C���^��錾
	CEditWindow *pEditWindow = NULL;	// �G�f�B�b�g�������p

	if (pEditWindow == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pEditWindow = new CEditWindow;	// �G�f�B�b�g��
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pEditWindow != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �G�f�B�b�g���̏�����
		if (FAILED(pEditWindow->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pEditWindow;
			pEditWindow = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �G�f�B�b�g�X�e�[�W�̏���ݒ�
		pEditWindow->m_pEdit = pEdit;

		// �m�ۂ����A�h���X��Ԃ�
		return pEditWindow;
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
HRESULT CEditWindow::Release(CEditWindow *&prEditWindow)
{
#if _DEBUG

	if (prEditWindow != NULL)
	{ // �g�p���̏ꍇ

		// �G�f�B�b�g���̏I��
		prEditWindow->Uninit();

		// �������J��
		delete prEditWindow;
		prEditWindow = NULL;

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
//	��ޕύX�̍X�V����
//============================================================
void CEditWindow::UpdateChangeType(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ��ނ�ύX
	if (m_pKeyboard->IsTrigger(KEY_TYPE))
	{
		m_window.type = (CWindow::EType)((m_window.type + 1) % CWindow::TYPE_MAX);
	}
}

//============================================================
//	�g�嗦�ύX�̍X�V����
//============================================================
void CEditWindow::UpdateChangeScale(void)
{
	// �ϐ���錾
	float fScale = m_window.pWindow->GetScale();	// ���g�嗦

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �g�嗦��ύX
	if (!m_pKeyboard->IsPress(KEY_TRIGGER))
	{
		if (m_pKeyboard->IsPress(KEY_SCALE_UP))
		{
			fScale += CHANGE_SCALE;
		}
		if (m_pKeyboard->IsPress(KEY_SCALE_DOWN))
		{
			fScale -= CHANGE_SCALE;
		}
	}
	else
	{
		if (m_pKeyboard->IsTrigger(KEY_SCALE_UP))
		{
			fScale += CHANGE_SCALE;
		}
		if (m_pKeyboard->IsTrigger(KEY_SCALE_DOWN))
		{
			fScale -= CHANGE_SCALE;
		}
	}

	// ���g�嗦�𔽉f
	m_window.pWindow->SetScale(fScale);
}

//============================================================
//	���̐�������
//============================================================
void CEditWindow::MyCreateWindow(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();	// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 rotEdit = m_pEdit->GetVec3Rotation();	// �G�f�B�b�g�̌���
	D3DXCOLOR colBuild = XCOL_WHITE;	// �F�ۑ��p
	float fScale = 0.0f;	// �g�嗦

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ����z�u
	if (m_pKeyboard->IsTrigger(KEY_CREATE))
	{
		//----------------------------------------------------
		//	���̏���z�u�p�ɕύX
		//----------------------------------------------------
		// �����X�V�E�����`���ON�ɂ���
		m_window.pWindow->SetEnableUpdate(true);
		m_window.pWindow->SetEnableDraw(true);

		// �F��ݒ�
		m_window.pWindow->SetColor(XCOL_WHITE);

		// �g�嗦��ۑ�
		fScale = m_window.pWindow->GetScale();

		// ���ۑ���ݒ�
		m_pEdit->UnSave();

		//----------------------------------------------------
		//	�V�������̐���
		//----------------------------------------------------
		// ���̐���
		m_window.pWindow = CWindow::Create(m_window.type, posEdit, rotEdit);
		assert(m_window.pWindow != NULL);

		// �F��ݒ�
		m_window.pWindow->SetColor(INIT_COL);

		// �g�嗦��ݒ�
		m_window.pWindow->SetScale(fScale);
	}
}

//============================================================
//	���̔j������
//============================================================
void CEditWindow::ReleaseWindow(void)
{
	// �ϐ���錾
	bool bRelease = false;	// �j����

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �����폜
	if (m_pKeyboard->IsTrigger(KEY_RELEASE))
	{
		// �j�������Ԃ�ݒ�
		bRelease = true;
	}

	// ���̍폜����
	DeleteCollisionWindow(bRelease);
}

//============================================================
//	���̍폜����
//============================================================
void CEditWindow::DeleteCollisionWindow(const bool bRelase)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();				// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 sizeEdit = m_window.pWindow->GetVec3Sizing();	// �G�f�B�b�g���̑傫��

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
				D3DXVECTOR3 posBuild = VEC3_ZERO;	// ���ʒu
				D3DXVECTOR3 sizeBuild = VEC3_ZERO;	// ���傫��

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_WINDOW)
				{ // �I�u�W�F�N�g���x�������ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_window.pWindow)
				{ // �����A�h���X�������ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// ���̈ʒu���擾
				posBuild = pObjCheck->GetVec3Position();

				// ���̑傫�����擾
				sizeBuild = pObjCheck->GetVec3Sizing();

				// ���̂̓����蔻��
				if (collision::Circle3D
				( // ����
					posEdit,							// ����ʒu
					posBuild,							// ����ڕW�ʒu
					(sizeBuild.x + sizeBuild.z) * 0.5f,	// ���蔼�a
					(sizeEdit.x + sizeEdit.z) * 0.5f	// ����ڕW���a
				))
				{ // ������������ꍇ

					if (bRelase)
					{ // �j������ꍇ

						// �I������
						pObjCheck->Uninit();

						// ���ۑ���ݒ�
						m_pEdit->UnSave();
					}
					else
					{ // �j�����Ȃ��ꍇ

						// �Ԃ�ݒ�
						pObjCheck->SetColor(XCOL_RED);
					}
				}
				else
				{ // ����O�������ꍇ

					// �ʏ�F��ݒ�
					pObjCheck->SetColor(XCOL_WHITE);
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}
}

//============================================================
//	���̐F�̑S����������
//============================================================
void CEditWindow::InitAllColorWindow(void)
{
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

				if (pObjCheck->GetLabel() != CObject::LABEL_WINDOW)
				{ // �I�u�W�F�N�g���x�������ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_window.pWindow)
				{ // �����A�h���X�������ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �ʏ�F��ݒ�
				pObjCheck->SetColor(XCOL_WHITE);

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}
}

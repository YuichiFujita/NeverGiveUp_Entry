//============================================================
//
//	�G�f�B�b�g�Z�[�u�|�C���g���� [editSavePoint.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "editSavePoint.h"
#include "manager.h"
#include "input.h"
#include "collision.h"
#include "editStageManager.h"
#include "stage.h"
#include "effect3D.h"

//************************************************************
//	�}�N����`
//************************************************************
#define KEY_CREATE		(DIK_0)	// �����L�[
#define NAME_CREATE		("0")	// �����\��
#define KEY_RELEASE		(DIK_9)	// �j���L�[
#define NAME_RELEASE	("9")	// �j���\��

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const float	INIT_ALPHA		= 0.5f;		// �z�u�O�̃��l
	const float	EFFECT_RADIUS	= 30.0f;	// �����\���G�t�F�N�g�̔��a
	const int	EFFECT_LIFE		= 10;		// �����\���G�t�F�N�g�̎���
}

//************************************************************
//	�e�N���X [CEditSavePoint] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEditSavePoint::CEditSavePoint()
{
#if _DEBUG

	// �����o�ϐ����N���A
	m_pEdit = NULL;	// �G�f�B�b�g�X�e�[�W�̏��
	memset(&m_savePoint, 0, sizeof(m_savePoint));	// �Z�[�u�|�C���g�z�u���

#endif	// _DEBUG
}

//============================================================
//	�f�X�g���N�^
//============================================================
CEditSavePoint::~CEditSavePoint()
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	����������
//============================================================
HRESULT CEditSavePoint::Init(void)
{
#if _DEBUG

	// �����o�ϐ���������
	m_pEdit = NULL;	// �G�f�B�b�g�X�e�[�W�̏��
	m_savePoint.pSavePoint = NULL;	// �Z�[�u�|�C���g���

	// �Z�[�u�|�C���g�̐���
	m_savePoint.pSavePoint = CSavePoint::Create(VEC3_ZERO, VEC3_ZERO);
	if (m_savePoint.pSavePoint == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����x��ݒ�
	m_savePoint.pSavePoint->SetAlpha(INIT_ALPHA);

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
void CEditSavePoint::Uninit(void)
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	�X�V����
//============================================================
void CEditSavePoint::Update(void)
{
#if _DEBUG

	if (m_pEdit == NULL)
	{ // �G�f�B�b�g�X�e�[�W�����݂��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return;
	}

	// �����\���G�t�F�N�g�̐���
	CreateRotaEffect();

	// �Z�[�u�|�C���g�̐���
	CreateSavePoint();

	// �Z�[�u�|�C���g�̔j��
	ReleaseSavePoint();

	// �ʒu�𔽉f
	m_savePoint.pSavePoint->SetVec3Position(m_pEdit->GetVec3Position());

	// �����𔽉f
	m_savePoint.pSavePoint->SetVec3Rotation(m_pEdit->GetVec3Rotation());

#endif
}

//============================================================
//	�\���̐ݒ菈��
//============================================================
void CEditSavePoint::SetDisp(const bool bDisp)
{
	// �����X�V�E�����`���\���󋵂ɍ��킹��
	m_savePoint.pSavePoint->SetEnableUpdate(bDisp);	// �X�V
	m_savePoint.pSavePoint->SetEnableDraw(bDisp);	// �`��

	if (bDisp)
	{ // �\��ON�̏ꍇ

		// �ʒu�𔽉f
		m_savePoint.pSavePoint->SetVec3Position(m_pEdit->GetVec3Position());
	}
	else
	{ // �\��OFF�̏ꍇ

		// �Z�[�u�|�C���g�̐F�̑S������
		InitAllColorSavePoint();
	}
}

//============================================================
//	����\���̕`�揈��
//============================================================
void CEditSavePoint::DrawDebugControl(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��

	pDebug->Print(CDebugProc::POINT_RIGHT, "�폜�F[%s]\n", NAME_RELEASE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�ݒu�F[%s]\n", NAME_CREATE);
}

//============================================================
//	���\���̕`�揈��
//============================================================
void CEditSavePoint::DrawDebugInfo(void)
{
	// �|�C���^��錾
	//CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��
}

//============================================================
//	�ۑ�����
//============================================================
void CEditSavePoint::Save(FILE *pFile)
{
#if _DEBUG

	if (pFile != NULL)
	{ // �t�@�C�������݂���ꍇ

		// ���o���������o��
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#	�Z�[�u�|�C���g�̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		// ���J�n�n�_�������o��
		fprintf(pFile, "STAGE_SAVEPOINTSET\n\n");

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
	
					if (pObjCheck->GetLabel() != CObject::LABEL_SAVEPOINT)
					{ // �I�u�W�F�N�g���x�����Z�[�u�|�C���g�ł͂Ȃ��ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}
	
					if (pObjCheck == (CObject*)m_savePoint.pSavePoint)
					{ // �����A�h���X�������ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}

					// �Z�[�u�|�C���g�̏����擾
					D3DXVECTOR3 posSave = pObjCheck->GetVec3Position();	// �ʒu
					D3DXVECTOR3 rotSave = pObjCheck->GetVec3Rotation();	// ����
	
					// ���������o��
					fprintf(pFile, "	SAVEPOINTSET\n");
					fprintf(pFile, "		POS = %.2f %.2f %.2f\n", posSave.x, posSave.y, posSave.z);
					fprintf(pFile, "		ROT = %.2f %.2f %.2f\n", rotSave.x, rotSave.y, rotSave.z);
					fprintf(pFile, "	END_SAVEPOINTSET\n\n");

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;
				}
			}
		}

		// ���I���n�_�������o��
		fprintf(pFile, "END_STAGE_SAVEPOINTSET\n\n");
	}

#endif	// _DEBUG
}

//============================================================
//	��������
//============================================================
CEditSavePoint *CEditSavePoint::Create(CEditStageManager *pEdit)
{
#if _DEBUG

	// �|�C���^��錾
	CEditSavePoint *pEditSavePoint = NULL;	// �G�f�B�b�g�Z�[�u�|�C���g�����p

	if (pEditSavePoint == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pEditSavePoint = new CEditSavePoint;	// �G�f�B�b�g�Z�[�u�|�C���g
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pEditSavePoint != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �G�f�B�b�g�Z�[�u�|�C���g�̏�����
		if (FAILED(pEditSavePoint->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pEditSavePoint;
			pEditSavePoint = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �G�f�B�b�g�X�e�[�W�̏���ݒ�
		pEditSavePoint->m_pEdit = pEdit;

		// �m�ۂ����A�h���X��Ԃ�
		return pEditSavePoint;
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
HRESULT CEditSavePoint::Release(CEditSavePoint *&prEditSavePoint)
{
#if _DEBUG

	if (prEditSavePoint != NULL)
	{ // �g�p���̏ꍇ

		// �G�f�B�b�g�Z�[�u�|�C���g�̏I��
		prEditSavePoint->Uninit();

		// �������J��
		delete prEditSavePoint;
		prEditSavePoint = NULL;

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
//	�Z�[�u�|�C���g�̐�������
//============================================================
void CEditSavePoint::CreateSavePoint(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();	// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 rotEdit = m_pEdit->GetVec3Rotation();	// �G�f�B�b�g�̌���
	D3DXCOLOR colSave = XCOL_WHITE;	// �F�ۑ��p

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �Z�[�u�|�C���g��z�u
	if (m_pKeyboard->IsTrigger(KEY_CREATE))
	{
		//----------------------------------------------------
		//	�Z�[�u�|�C���g�̏���z�u�p�ɕύX
		//----------------------------------------------------
		// �����X�V�E�����`���ON�ɂ���
		m_savePoint.pSavePoint->SetEnableUpdate(true);
		m_savePoint.pSavePoint->SetEnableDraw(true);

		// �}�e���A�����Đݒ�
		m_savePoint.pSavePoint->ResetMaterial();

		// ���ۑ���ݒ�
		m_pEdit->UnSave();

		//----------------------------------------------------
		//	�V�����Z�[�u�|�C���g�̐���
		//----------------------------------------------------
		// �Z�[�u�|�C���g�̐���
		m_savePoint.pSavePoint = CSavePoint::Create(VEC3_ZERO, VEC3_ZERO);
		assert(m_savePoint.pSavePoint != NULL);

		// �����x��ݒ�
		m_savePoint.pSavePoint->SetAlpha(INIT_ALPHA);
	}
}

//============================================================
//	�Z�[�u�|�C���g�̔j������
//============================================================
void CEditSavePoint::ReleaseSavePoint(void)
{
	// �ϐ���錾
	bool bRelease = false;	// �j����

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �Z�[�u�|�C���g���폜
	if (m_pKeyboard->IsTrigger(KEY_RELEASE))
	{
		// �j�������Ԃ�ݒ�
		bRelease = true;
	}

	// �Z�[�u�|�C���g�̍폜����
	DeleteCollisionSavePoint(bRelease);
}

//============================================================
//	�����\���G�t�F�N�g�̐�������
//============================================================
void CEditSavePoint::CreateRotaEffect(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posEffect = VEC3_ZERO;							// �G�t�F�N�g�ʒu
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();			// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 rotEdit = m_pEdit->GetVec3Rotation();			// �G�f�B�b�g�̌���
	float fRadiusSave = m_savePoint.pSavePoint->GetRadius();	// �Z�[�u���a

	// �G�t�F�N�g�ʒu���v�Z
	posEffect.x = posEdit.x + sinf(rotEdit.y + D3DX_PI) * fRadiusSave;
	posEffect.y = posEdit.y;
	posEffect.z = posEdit.z + cosf(rotEdit.y + D3DX_PI) * fRadiusSave;

	// �����\���G�t�F�N�g�𐶐�
	CEffect3D::Create(posEffect, EFFECT_RADIUS, CEffect3D::TYPE_NORMAL, EFFECT_LIFE);
}

//============================================================
//	�Z�[�u�|�C���g�̍폜����
//============================================================
void CEditSavePoint::DeleteCollisionSavePoint(const bool bRelase)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();			// �G�f�B�b�g�̈ʒu
	float fRadiusEdit = m_savePoint.pSavePoint->GetRadius();	// �G�f�B�b�g�Z�[�u�|�C���g�̔��a

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
				D3DXVECTOR3 posSave = VEC3_ZERO;	// �Z�[�u�|�C���g�ʒu
				float fRadiusSave = 0.0f;			// �Z�[�u�|�C���g���a

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_SAVEPOINT)
				{ // �I�u�W�F�N�g���x�����Z�[�u�|�C���g�ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_savePoint.pSavePoint)
				{ // �����A�h���X�������ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �Z�[�u�|�C���g�̈ʒu���擾
				posSave = pObjCheck->GetVec3Position();

				// �Z�[�u�|�C���g�̔��a���擾
				fRadiusSave = pObjCheck->GetRadius();

				// ���̂̓����蔻��
				if (collision::Circle3D
				( // ����
					posEdit,		// ����ʒu
					posSave,		// ����ڕW�ʒu
					fRadiusEdit,	// ���蔼�a
					fRadiusSave		// ����ڕW���a
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

						// �ԃ}�e���A����S�ݒ�
						pObjCheck->SetAllMaterial(material::Red());
					}
				}
				else
				{ // ����O�������ꍇ

					// �}�e���A�����Đݒ�
					pObjCheck->ResetMaterial();
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}
}


//============================================================
//	�Z�[�u�|�C���g�̐F�̑S����������
//============================================================
void CEditSavePoint::InitAllColorSavePoint(void)
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

				if (pObjCheck->GetLabel() != CObject::LABEL_SAVEPOINT)
				{ // �I�u�W�F�N�g���x�����Z�[�u�|�C���g�ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_savePoint.pSavePoint)
				{ // �����A�h���X�������ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �}�e���A�����Đݒ�
				pObjCheck->ResetMaterial();

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}
}

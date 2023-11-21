//============================================================
//
//	�G�f�B�b�g�Ŕ��� [editSignboard.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "editSignboard.h"
#include "manager.h"
#include "input.h"
#include "collision.h"
#include "editStageManager.h"
#include "objectMeshCube.h"
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

#define KEY_SCALE_UP	(DIK_RIGHT)	// �g�嗦�㏸�L�[
#define NAME_SCALE_UP	("��")		// �g�嗦�㏸�\��
#define KEY_SCALE_DOWN	(DIK_LEFT)	// �g�嗦���~�L�[
#define NAME_SCALE_DOWN	("��")		// �g�嗦���~�\��

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const float	INIT_ALPHA		= 0.5f;		// �z�u�O�̃��l
	const float CHANGE_SCALE	= 0.05f;	// �g�嗦�ύX��
	const float	EFFECT_RADIUS	= 30.0f;	// �����\���G�t�F�N�g�̔��a
	const int	EFFECT_LIFE		= 10;		// �����\���G�t�F�N�g�̎���

	namespace center
	{
		const D3DXVECTOR3	SIZE	= D3DXVECTOR3(280.0f, 20.0f, 280.0f);	// ���S�\���̑傫��
		const D3DXCOLOR		COL		= D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f);	// ���S�\���̐F

		const float ADD_SIDE	= 50.0f;	// ���S�ʒu�܂ł̉����Z��
		const float SUB_DOWN	= 240.0f;	// ���S�ʒu�܂ł̏c���Z��
	}
}

//************************************************************
//	�e�N���X [CEditSignboard] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEditSignboard::CEditSignboard()
{
#if _DEBUG

	// �����o�ϐ����N���A
	m_pEdit = NULL;		// �G�f�B�b�g�X�e�[�W�̏��
	m_pCenter = NULL;	// ���S�̏��
	memset(&m_signboard, 0, sizeof(m_signboard));	// �Ŕz�u���

#endif	// _DEBUG
}

//============================================================
//	�f�X�g���N�^
//============================================================
CEditSignboard::~CEditSignboard()
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	����������
//============================================================
HRESULT CEditSignboard::Init(void)
{
#if _DEBUG

	// �����o�ϐ���������
	m_pEdit = NULL;		// �G�f�B�b�g�X�e�[�W�̏��
	m_pCenter = NULL;	// ���S�̏��
	m_signboard.pSignboard = NULL;				// �Ŕ��
	m_signboard.type = CSignboard::TYPE_LEFT;	// �Ŕ��

	// ���S���̐���
	m_pCenter = CObjectMeshCube::Create
	( // ����
		VEC3_ZERO,								// �ʒu
		VEC3_ZERO,								// ����
		center::SIZE,							// �傫��
		center::COL,							// �L���[�u�F
		XCOL_WHITE,								// �����F
		CObjectMeshCube::BORDER_OFF,			// �������
		0.0f,									// ����葾��
		CObjectMeshCube::TEXSTATE_ONE,			// �e�N�X�`�����
		CObjectMeshCube::ETexState(NONE_IDX),	// �e�N�X�`�����
		CObjectMeshCube::ORIGIN_DOWN			// ���_
	);
	if (m_pCenter == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �Ŕ̐���
	m_signboard.pSignboard = CSignboard::Create(m_signboard.type, VEC3_ZERO, VEC3_ZERO);
	if (m_signboard.pSignboard == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �F��ݒ�
	D3DXCOLOR col = m_signboard.pSignboard->GetColor();	// ���̐F���擾
	m_signboard.pSignboard->SetColor(D3DXCOLOR(col.r, col.g, col.b, INIT_ALPHA));

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
void CEditSignboard::Uninit(void)
{
#if _DEBUG

	if (m_pCenter != NULL)
	{ // ���S��񂪎g�p����Ă���ꍇ

		// ���S���̏I��
		m_pCenter->Uninit();
	}
	else { assert(false); }	// ��g�p��

#endif	// _DEBUG
}

//============================================================
//	�X�V����
//============================================================
void CEditSignboard::Update(void)
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

	// ���S�\���̍X�V
	UpdateCenter();

	// �Ŕ̐���
	CreateSignboard();

	// �Ŕ̔j��
	ReleaseSignboard();

	// �ʒu�𔽉f
	m_signboard.pSignboard->SetVec3Position(m_pEdit->GetVec3Position());

	// �����𔽉f
	m_signboard.pSignboard->SetVec3Rotation(m_pEdit->GetVec3Rotation());

	// ��ނ𔽉f
	m_signboard.pSignboard->SetType(m_signboard.type);

#endif	// _DEBUG
}

//============================================================
//	�\���̐ݒ菈��
//============================================================
void CEditSignboard::SetDisp(const bool bDisp)
{
	// �Ŕ̎����X�V�E�����`���\���󋵂ɍ��킹��
	m_signboard.pSignboard->SetEnableUpdate(bDisp);	// �X�V
	m_signboard.pSignboard->SetEnableDraw(bDisp);	// �`��

	// ���S�\���̎����X�V�E�����`���\���󋵂ɍ��킹��
	m_pCenter->SetEnableUpdate(bDisp);	// �X�V
	m_pCenter->SetEnableDraw(bDisp);	// �`��

	if (bDisp)
	{ // �\��ON�̏ꍇ

		// �ʒu�𔽉f
		m_signboard.pSignboard->SetVec3Position(m_pEdit->GetVec3Position());
	}
	else
	{ // �\��OFF�̏ꍇ

		// �Ŕ̐F�̑S������
		InitAllColorSignboard();

		// �ʒu���X�e�[�W�͈̔͊O�ɐݒ�
		D3DXVECTOR3 outLimit = D3DXVECTOR3(0.0f, 0.0f, CScene::GetStage()->GetStageLimit().fNear - m_signboard.pSignboard->GetVec3Sizing().z);
		m_signboard.pSignboard->SetVec3Position(outLimit);
	}
}

//============================================================
//	����\���̕`�揈��
//============================================================
void CEditSignboard::DrawDebugControl(void)
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
void CEditSignboard::DrawDebugInfo(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��

	pDebug->Print(CDebugProc::POINT_RIGHT, "%d�F[���]\n", m_signboard.type);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%f�F[�g�嗦]\n", m_signboard.pSignboard->GetScale());
}

//============================================================
//	�ۑ�����
//============================================================
void CEditSignboard::Save(FILE *pFile)
{
#if _DEBUG

	if (pFile != NULL)
	{ // �t�@�C�������݂���ꍇ

		// ���o���������o��
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#	�Ŕ̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		// ���J�n�n�_�������o��
		fprintf(pFile, "STAGE_SIGNBOARDSET\n\n");

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
	
					if (pObjCheck == (CObject*)m_signboard.pSignboard)
					{ // �����A�h���X�������ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}

					// �Ŕ̏����擾
					D3DXVECTOR3 posSign = pObjCheck->GetVec3Position();	// �ʒu
					D3DXVECTOR3 rotSign = pObjCheck->GetVec3Rotation();	// ����
					D3DXCOLOR colSign = pObjCheck->GetColor();	// �F
					int nType = pObjCheck->GetType();			// ���
					float fScale = pObjCheck->GetScale();		// �g�嗦
	
					// ���������o��
					fprintf(pFile, "	SIGNBOARDSET\n");
					fprintf(pFile, "		TYPE = %d\n", nType);
					fprintf(pFile, "		POS = %.2f %.2f %.2f\n", posSign.x, posSign.y, posSign.z);
					fprintf(pFile, "		ROT = %.2f %.2f %.2f\n", rotSign.x, rotSign.y, rotSign.z);
					fprintf(pFile, "		COL = %.2f %.2f %.2f %.2f\n", colSign.r, colSign.g, colSign.b, colSign.a);
					fprintf(pFile, "		SCALE = %.2f\n", fScale);
					fprintf(pFile, "	END_SIGNBOARDSET\n\n");

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;
				}
			}
		}

		// ���I���n�_�������o��
		fprintf(pFile, "END_STAGE_SIGNBOARDSET\n\n");
	}

#endif	// _DEBUG
}

//============================================================
//	��������
//============================================================
CEditSignboard *CEditSignboard::Create(CEditStageManager *pEdit)
{
#if _DEBUG

	// �|�C���^��錾
	CEditSignboard *pEditSignboard = NULL;	// �G�f�B�b�g�Ŕ����p

	if (pEditSignboard == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pEditSignboard = new CEditSignboard;	// �G�f�B�b�g�Ŕ�
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pEditSignboard != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �G�f�B�b�g�Ŕ̏�����
		if (FAILED(pEditSignboard->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pEditSignboard;
			pEditSignboard = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �G�f�B�b�g�X�e�[�W�̏���ݒ�
		pEditSignboard->m_pEdit = pEdit;

		// �m�ۂ����A�h���X��Ԃ�
		return pEditSignboard;
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
HRESULT CEditSignboard::Release(CEditSignboard *&prEditSignboard)
{
#if _DEBUG

	if (prEditSignboard != NULL)
	{ // �g�p���̏ꍇ

		// �G�f�B�b�g�Ŕ̏I��
		prEditSignboard->Uninit();

		// �������J��
		delete prEditSignboard;
		prEditSignboard = NULL;

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
void CEditSignboard::UpdateChangeType(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ��ނ�ύX
	if (m_pKeyboard->IsTrigger(KEY_TYPE))
	{
		m_signboard.type = (CSignboard::EType)((m_signboard.type + 1) % CSignboard::TYPE_MAX);
	}
}

//============================================================
//	�g�嗦�ύX�̍X�V����
//============================================================
void CEditSignboard::UpdateChangeScale(void)
{
	// �ϐ���錾
	float fScale = m_signboard.pSignboard->GetScale();	// �Ŕg�嗦

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

	// �Ŕg�嗦�𔽉f
	m_signboard.pSignboard->SetScale(fScale);
}

//============================================================
//	���S�\���̍X�V����
//============================================================
void CEditSignboard::UpdateCenter(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posCenter = VEC3_ZERO;					// ���S�ʒu
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();	// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 rotEdit = m_pEdit->GetVec3Rotation();	// �G�f�B�b�g�̌���

	// ���S�ʒu���v�Z
	posCenter.x = posEdit.x + sinf(rotEdit.y + D3DX_PI) * center::ADD_SIDE;
	posCenter.y = posEdit.y - center::SUB_DOWN;
	posCenter.z = posEdit.z + cosf(rotEdit.y + D3DX_PI) * center::ADD_SIDE;

	// ���S�ʒu���w��
	m_pCenter->SetVec3Position(posCenter);
}

//============================================================
//	�Ŕ̐�������
//============================================================
void CEditSignboard::CreateSignboard(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();	// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 rotEdit = m_pEdit->GetVec3Rotation();	// �G�f�B�b�g�̌���
	D3DXCOLOR colSign = XCOL_WHITE;	// �F�ۑ��p
	float fScale = 0.0f;	// �g�嗦

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �Ŕ�z�u
	if (m_pKeyboard->IsTrigger(KEY_CREATE))
	{
		//----------------------------------------------------
		//	�Ŕ̏���z�u�p�ɕύX
		//----------------------------------------------------
		// �����X�V�E�����`���ON�ɂ���
		m_signboard.pSignboard->SetEnableUpdate(true);
		m_signboard.pSignboard->SetEnableDraw(true);

		// �F��ݒ�
		colSign = m_signboard.pSignboard->GetColor();	// ���̐F���擾
		m_signboard.pSignboard->SetColor(D3DXCOLOR(colSign.r, colSign.g, colSign.b, 1.0f));

		// �g�嗦��ۑ�
		fScale = m_signboard.pSignboard->GetScale();

		// ���ۑ���ݒ�
		m_pEdit->UnSave();

		//----------------------------------------------------
		//	�V�����Ŕ̐���
		//----------------------------------------------------
		// �Ŕ̐���
		m_signboard.pSignboard = CSignboard::Create(m_signboard.type, posEdit, rotEdit);
		assert(m_signboard.pSignboard != NULL);

		// �F��ݒ�
		colSign = m_signboard.pSignboard->GetColor();	// ���̐F���擾
		m_signboard.pSignboard->SetColor(D3DXCOLOR(colSign.r, colSign.g, colSign.b, INIT_ALPHA));

		// �g�嗦��ݒ�
		m_signboard.pSignboard->SetScale(fScale);
	}
}

//============================================================
//	�Ŕ̔j������
//============================================================
void CEditSignboard::ReleaseSignboard(void)
{
	// �ϐ���錾
	bool bRelease = false;	// �j����

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �Ŕ��폜
	if (m_pKeyboard->IsTrigger(KEY_RELEASE))
	{
		// �j�������Ԃ�ݒ�
		bRelease = true;
	}

	// �Ŕ̍폜����
	DeleteCollisionSignboard(bRelease);
}

//============================================================
//	�Ŕ̍폜����
//============================================================
void CEditSignboard::DeleteCollisionSignboard(const bool bRelase)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();				// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 sizeEdit = m_signboard.pSignboard->GetVec3Sizing();	// �G�f�B�b�g�Ŕ̑傫��

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
				D3DXVECTOR3 posSign = VEC3_ZERO;	// �Ŕʒu
				D3DXVECTOR3 sizeSign = VEC3_ZERO;	// �Ŕ傫��

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_SIGNBOARD)
				{ // �I�u�W�F�N�g���x�����Ŕł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_signboard.pSignboard)
				{ // �����A�h���X�������ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �Ŕ̈ʒu���擾
				posSign = pObjCheck->GetVec3Position();

				// �Ŕ̑傫�����擾
				sizeSign = pObjCheck->GetVec3Sizing();

				// ���̂̓����蔻��
				if (collision::Circle3D
				( // ����
					posEdit,							// ����ʒu
					posSign,							// ����ڕW�ʒu
					(sizeSign.x + sizeSign.z) * 0.5f,	// ���蔼�a
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
//	�Ŕ̐F�̑S����������
//============================================================
void CEditSignboard::InitAllColorSignboard(void)
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

				if (pObjCheck->GetLabel() != CObject::LABEL_SIGNBOARD)
				{ // �I�u�W�F�N�g���x�����Ŕł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_signboard.pSignboard)
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

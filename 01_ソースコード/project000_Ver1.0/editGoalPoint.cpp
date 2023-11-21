//============================================================
//
//	�G�f�B�b�g�S�[���|�C���g���� [editGoalPoint.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "editGoalPoint.h"
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

#define KEY_XSIZE_UP	(DIK_T)	// X�g��L�[
#define NAME_XSIZE_UP	("T")	// X�g��\��
#define KEY_YSIZE_UP	(DIK_Y)	// Y�g��L�[
#define NAME_YSIZE_UP	("Y")	// Y�g��\��
#define KEY_ZSIZE_UP	(DIK_U)	// Z�g��L�[
#define NAME_ZSIZE_UP	("U")	// Z�g��\��

#define KEY_XSIZE_DOWN	(DIK_G)	// X�k���L�[
#define NAME_XSIZE_DOWN	("G")	// X�k���\��
#define KEY_YSIZE_DOWN	(DIK_H)	// Y�k���L�[
#define NAME_YSIZE_DOWN	("H")	// Y�k���\��
#define KEY_ZSIZE_DOWN	(DIK_J)	// Z�k���L�[
#define NAME_ZSIZE_DOWN	("J")	// Z�k���\��

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const D3DXVECTOR3 INIT_COLL_SIZE = D3DXVECTOR3(60.0f, 60.0f, 60.0f);	// �S�[������̑傫��

	namespace coll
	{
		const int	PRIORITY	= 2;	// �����蔻��̗D�揇��
		const float	SIZE_MOVE	= 2.0f;	// �����蔻��̑傫���ύX��

		const D3DXCOLOR COLL_COL = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f);	// �����蔻��̐F
		const D3DXCOLOR DRAW_COL = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);	// �ݒu�ʒu�̐F
	}
}

//************************************************************
//	�e�N���X [CEditGoalPoint] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEditGoalPoint::CEditGoalPoint()
{
#if _DEBUG

	// �����o�ϐ����N���A
	m_pEdit = NULL;	// �G�f�B�b�g�X�e�[�W�̏��
	m_pSet = NULL;	// �ݒu�\��ʒu�̏��
	memset(&m_goalPoint, 0, sizeof(m_goalPoint));	// �S�[���|�C���g�z�u���

#endif	// _DEBUG
}

//============================================================
//	�f�X�g���N�^
//============================================================
CEditGoalPoint::~CEditGoalPoint()
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	����������
//============================================================
HRESULT CEditGoalPoint::Init(void)
{
#if _DEBUG

	// �����o�ϐ���������
	m_pEdit = NULL;	// �G�f�B�b�g�X�e�[�W�̏��
	m_pSet = NULL;	// �ݒu�\��ʒu�̏��
	m_goalPoint.pGoalPoint = NULL;	// �S�[���|�C���g���
	m_goalPoint.pCollision = NULL;	// �����蔻��̏��
	m_goalPoint.bSet = false;		// �z�u��

	//--------------------------------------------------------
	//	�S�[���|�C���g�̐����E�ݒ�
	//--------------------------------------------------------
	// �S�[���|�C���g�̐���
	m_goalPoint.pGoalPoint = CGoalPoint::Create(VEC3_ZERO, INIT_COLL_SIZE);
	if (m_goalPoint.pGoalPoint == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	�ݒu�\��ʒu�̐����E�ݒ�
	//--------------------------------------------------------
	// �ݒu�\��ʒu�̐���
	m_pSet = CObjectMeshCube::Create
	( // ����
		VEC3_ZERO,									// �ʒu
		VEC3_ZERO,									// ����
		m_goalPoint.pGoalPoint->GetVec3Sizing(),	// �傫��
		coll::COLL_COL,								// �L���[�u�F
		XCOL_WHITE,									// �����F
		CObjectMeshCube::BORDER_OFF,				// �������
		0.0f,										// ����葾��
		CObjectMeshCube::TEXSTATE_ONE,				// �e�N�X�`�����
		CObjectMeshCube::ETexState(NONE_IDX),		// �e�N�X�`�����
		CObjectMeshCube::ORIGIN_DOWN				// ���_
	);
	if (m_pSet == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pSet->SetPriority(coll::PRIORITY);

	//--------------------------------------------------------
	//	�����蔻��̐����E�ݒ�
	//--------------------------------------------------------
	// �����蔻��̐���
	m_goalPoint.pCollision = CObjectMeshCube::Create
	( // ����
		VEC3_ZERO,									// �ʒu
		VEC3_ZERO,									// ����
		m_goalPoint.pGoalPoint->GetVec3Sizing(),	// �傫��
		coll::DRAW_COL,								// �L���[�u�F
		XCOL_WHITE,									// �����F
		CObjectMeshCube::BORDER_OFF,				// �������
		0.0f,										// ����葾��
		CObjectMeshCube::TEXSTATE_ONE,				// �e�N�X�`�����
		CObjectMeshCube::ETexState(NONE_IDX),		// �e�N�X�`�����
		CObjectMeshCube::ORIGIN_DOWN				// ���_
	);
	if (m_goalPoint.pCollision == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_goalPoint.pCollision->SetPriority(coll::PRIORITY);

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
void CEditGoalPoint::Uninit(void)
{
#if _DEBUG

	if (m_pSet != NULL)
	{ // �ݒu�\��ʒu�̏�񂪎g�p����Ă���ꍇ

		// �ݒu�\��ʒu�̏��̏I��
		m_pSet->Uninit();
	}
	else { assert(false); }	// ��g�p��

	if (m_goalPoint.pCollision != NULL)
	{ // �����蔻��̏�񂪎g�p����Ă���ꍇ

		// �����蔻��̏��̏I��
		m_goalPoint.pCollision->Uninit();
	}
	else { assert(false); }	// ��g�p��

#endif	// _DEBUG
}

//============================================================
//	�X�V����
//============================================================
void CEditGoalPoint::Update(void)
{
#if _DEBUG

	if (m_pEdit == NULL)
	{ // �G�f�B�b�g�X�e�[�W�����݂��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return;
	}

	// ����傫���̍X�V
	UpdateCollSize();

	// �S�[���|�C���g�̐����E�ʒu�ύX
	CreateGoalPoint();

	// �ݒu�\��ʒu�̍X�V
	UpdateSet();
	
	// �����蔻��̍X�V
	UpdateColl();

#endif	// _DEBUG
}

//============================================================
//	�\���̐ݒ菈��
//============================================================
void CEditGoalPoint::SetDisp(const bool bDisp)
{
	// �ϐ���錾
	bool bDispGoal = (m_goalPoint.bSet) ? bDisp : false;	// �S�[���|�C���g�̕`���

	// �ݒu�\��ʒu�̎����X�V�E�����`���\���󋵂ɍ��킹��
	m_pSet->SetEnableUpdate(bDisp);
	m_pSet->SetEnableDraw(bDisp);

	// �S�[���|�C���g�̎����X�V�E�����`���OFF�ɂ���
	m_goalPoint.pGoalPoint->SetEnableUpdate(bDispGoal);
	m_goalPoint.pGoalPoint->SetEnableDraw(bDispGoal);

	// �����蔻��̎����X�V�E�����`���OFF�ɂ���
	m_goalPoint.pCollision->SetEnableUpdate(bDispGoal);
	m_goalPoint.pCollision->SetEnableDraw(bDispGoal);
}

//============================================================
//	����\���̕`�揈��
//============================================================
void CEditGoalPoint::DrawDebugControl(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��

	pDebug->Print(CDebugProc::POINT_RIGHT, "����g��F[%s/%s/%s+%s]\n", NAME_XSIZE_UP, NAME_YSIZE_UP, NAME_ZSIZE_UP, NAME_TRIGGER);
	pDebug->Print(CDebugProc::POINT_RIGHT, "����k���F[%s/%s/%s+%s]\n", NAME_XSIZE_DOWN, NAME_YSIZE_DOWN, NAME_ZSIZE_DOWN, NAME_TRIGGER);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�ݒu�F[%s]\n", NAME_CREATE);
}

//============================================================
//	���\���̕`�揈��
//============================================================
void CEditGoalPoint::DrawDebugInfo(void)
{
	// �|�C���^��錾
	//CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��
}

//============================================================
//	�ۑ�����
//============================================================
void CEditGoalPoint::Save(FILE *pFile)
{
#if _DEBUG

	if (pFile != NULL)
	{ // �t�@�C�������݂���ꍇ

		// ���o���������o��
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#	�S�[���|�C���g�̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		// ���J�n�n�_�������o��
		fprintf(pFile, "STAGE_GOALPOINTSET\n\n");

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
	
					if (pObjCheck->GetLabel() != CObject::LABEL_GOALPOINT)
					{ // �I�u�W�F�N�g���x�����S�[���|�C���g�ł͂Ȃ��ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}

					// �S�[���|�C���g�̏����擾
					D3DXVECTOR3 posGoal = pObjCheck->GetVec3Position();	// �ʒu
					D3DXVECTOR3 sizeGoal = pObjCheck->GetVec3Sizing();	// �傫��
	
					// ���������o��
					fprintf(pFile, "	GOALPOINTSET\n");
					fprintf(pFile, "		POS = %.2f %.2f %.2f\n", posGoal.x, posGoal.y, posGoal.z);
					fprintf(pFile, "		SIZE = %.2f %.2f %.2f\n", sizeGoal.x, sizeGoal.y, sizeGoal.z);
					fprintf(pFile, "	END_GOALPOINTSET\n\n");

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;
				}
			}
		}

		// ���I���n�_�������o��
		fprintf(pFile, "END_STAGE_GOALPOINTSET\n\n");
	}

#endif	// _DEBUG
}

//============================================================
//	��������
//============================================================
CEditGoalPoint *CEditGoalPoint::Create(CEditStageManager *pEdit)
{
#if _DEBUG

	// �|�C���^��錾
	CEditGoalPoint *pEditGoalPoint = NULL;	// �G�f�B�b�g�S�[���|�C���g�����p

	if (pEditGoalPoint == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pEditGoalPoint = new CEditGoalPoint;	// �G�f�B�b�g�S�[���|�C���g
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pEditGoalPoint != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �G�f�B�b�g�S�[���|�C���g�̏�����
		if (FAILED(pEditGoalPoint->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pEditGoalPoint;
			pEditGoalPoint = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �G�f�B�b�g�X�e�[�W�̏���ݒ�
		pEditGoalPoint->m_pEdit = pEdit;

		// �m�ۂ����A�h���X��Ԃ�
		return pEditGoalPoint;
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
HRESULT CEditGoalPoint::Release(CEditGoalPoint *&prEditGoalPoint)
{
#if _DEBUG

	if (prEditGoalPoint != NULL)
	{ // �g�p���̏ꍇ

		// �G�f�B�b�g�S�[���|�C���g�̏I��
		prEditGoalPoint->Uninit();

		// �������J��
		delete prEditGoalPoint;
		prEditGoalPoint = NULL;

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
//	����傫���̍X�V����
//============================================================
void CEditGoalPoint::UpdateCollSize(void)
{
	// �ϐ���錾
	D3DXVECTOR3 size = m_pSet->GetVec3Sizing();	// �傫��

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ����T�C�Y��ύX
	if (!m_pKeyboard->IsPress(KEY_TRIGGER))
	{
		if (m_pKeyboard->IsPress(KEY_ZSIZE_UP))
		{
			size.z += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_ZSIZE_DOWN))
		{
			size.z -= coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_XSIZE_UP))
		{
			size.x += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_XSIZE_DOWN))
		{
			size.x -= coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_YSIZE_UP))
		{
			size.y += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_YSIZE_DOWN))
		{
			size.y -= coll::SIZE_MOVE;
		}
	}
	else
	{
		if (m_pKeyboard->IsTrigger(KEY_ZSIZE_UP))
		{
			size.z += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_ZSIZE_DOWN))
		{
			size.z -= coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_XSIZE_UP))
		{
			size.x += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_XSIZE_DOWN))
		{
			size.x -= coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_YSIZE_UP))
		{
			size.y += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_YSIZE_DOWN))
		{
			size.y -= coll::SIZE_MOVE;
		}
	}

	// �傫���𔽉f
	m_pSet->SetVec3Sizing(size);
}

//============================================================
//	�S�[���|�C���g�̐�������
//============================================================
void CEditGoalPoint::CreateGoalPoint(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �S�[���|�C���g��z�u
	if (m_pKeyboard->IsTrigger(KEY_CREATE))
	{
		// �ϐ���錾
		D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();	// �G�f�B�b�g�̈ʒu
		D3DXVECTOR3 sizeGoal = m_pSet->GetVec3Sizing();		// �S�[���̑傫��

		// �S�[���|�C���g�̈ʒu�𔽉f
		m_goalPoint.pGoalPoint->SetVec3Position(posEdit);

		// �S�[���|�C���g�̑傫���𔽉f
		m_goalPoint.pGoalPoint->SetVec3Sizing(sizeGoal);

		// �����蔻��̈ʒu�𔽉f
		m_goalPoint.pCollision->SetVec3Position(posEdit);

		// �����蔻��̑傫���𔽉f
		m_goalPoint.pCollision->SetVec3Sizing(sizeGoal);

		// �z�u������Ԃɂ���
		m_goalPoint.bSet = true;

		// �\����ON�ɂ���
		SetDisp(true);

		// ���ۑ���ݒ�
		m_pEdit->UnSave();
	}
}

//============================================================
//	�ݒu�\��ʒu�̍X�V����
//============================================================
void CEditGoalPoint::UpdateSet(void)
{
	// �ݒu�\��̈ʒu�𔽉f
	m_pSet->SetVec3Position(m_pEdit->GetVec3Position());

	// �ݒu�\��̑傫���𔽉f
	m_pSet->SetVec3Sizing(m_pSet->GetVec3Sizing());
}

//============================================================
//	�����蔻��̍X�V����
//============================================================
void CEditGoalPoint::UpdateColl(void)
{
	// �����蔻��̈ʒu�𔽉f
	m_goalPoint.pCollision->SetVec3Position(m_goalPoint.pGoalPoint->GetVec3Position());

	// �����蔻��̑傫���𔽉f
	m_goalPoint.pCollision->SetVec3Sizing(m_goalPoint.pGoalPoint->GetVec3Sizing());
}

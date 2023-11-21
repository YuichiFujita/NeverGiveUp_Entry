//============================================================
//
//	�G�f�B�b�g��Q������ [editObstacle.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "editObstacle.h"
#include "manager.h"
#include "input.h"
#include "collision.h"
#include "editStageManager.h"
#include "objectMeshCube.h"
#include "stage.h"

//************************************************************
//	�}�N����`
//************************************************************
#define KEY_DOUBLE		(DIK_LCONTROL)	// ��d���L�[
#define NAME_DOUBLE		("LCTRL")		// ��d���\��
#define KEY_REVERSE		(DIK_LCONTROL)	// �t�]�L�[
#define NAME_REVERSE	("LCTRL")		// �t�]�\��
#define KEY_TRIGGER		(DIK_LSHIFT)	// �g���K�[���L�[
#define NAME_TRIGGER	("LSHIFT")		// �g���K�[���\��

#define KEY_SAVE	(DIK_F8)	// �ۑ��L�[
#define NAME_SAVE	("F8")		// �ۑ��\��

#define KEY_CREATE		(DIK_0)	// �����L�[
#define NAME_CREATE		("0")	// �����\��
#define KEY_RELEASE		(DIK_9)	// �j���L�[
#define NAME_RELEASE	("9")	// �j���\��
#define KEY_TYPE		(DIK_2)	// ��ޕύX�L�[
#define NAME_TYPE		("2")	// ��ޕύX�\��
#define KEY_STATE		(DIK_3)	// �����ԕύX�L�[
#define NAME_STATE		("3")	// �����ԕύX�\��
#define KEY_DODGE		(DIK_4)	// ���@�ύX�L�[
#define NAME_DODGE		("4")	// ���@�ύX�\��

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
	const char* SAVE_TXT = "data\\TXT\\save_obstacle.txt";	// ��Q���Z�[�u�e�L�X�g

	const float	INIT_ALPHA = 0.5f;	// �z�u�O�̃��l

	namespace coll
	{
		const int	PRIORITY	= 2;	// �����蔻��̗D�揇��
		const float	SIZE_MOVE	= 2.0f;	// �����蔻��̑傫���ύX��

		const D3DXCOLOR COLL_COL = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);	// �����蔻��̐F
	}
}

//************************************************************
//	�e�N���X [CEditObstacle] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEditObstacle::CEditObstacle()
{
#if _DEBUG

	// �����o�ϐ����N���A
	m_pEdit = NULL;			// �G�f�B�b�g�X�e�[�W�̏��
	m_pCollision = NULL;	// �����蔻��̏��
	memset(&m_obstacle, 0, sizeof(m_obstacle));	// ��Q���z�u���

#endif	// _DEBUG
}

//============================================================
//	�f�X�g���N�^
//============================================================
CEditObstacle::~CEditObstacle()
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	����������
//============================================================
HRESULT CEditObstacle::Init(void)
{
#if _DEBUG

	// �����o�ϐ���������
	m_pEdit = NULL;			// �G�f�B�b�g�X�e�[�W�̏��
	m_pCollision = NULL;	// �����蔻��̏��
	m_obstacle.pObstacle = NULL;			// ��Q�����
	m_obstacle.type = CObstacle::TYPE_BOX;	// ��Q�����

	// �����蔻��̐���
	m_pCollision = CObjectMeshCube::Create
	( // ����
		VEC3_ZERO,								// �ʒu
		VEC3_ZERO,								// ����
		VEC3_ZERO,								// �傫��
		coll::COLL_COL,							// �L���[�u�F
		XCOL_WHITE,								// �����F
		CObjectMeshCube::BORDER_OFF,			// �������
		0.0f,									// ����葾��
		CObjectMeshCube::TEXSTATE_ONE,			// �e�N�X�`�����
		CObjectMeshCube::ETexState(NONE_IDX),	// �e�N�X�`�����
		CObjectMeshCube::ORIGIN_DOWN			// ���_
	);
	if (m_pCollision == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pCollision->SetPriority(coll::PRIORITY);

	// ��Q���̐���
	m_obstacle.pObstacle = CObstacle::Create(m_obstacle.type, VEC3_ZERO, VEC3_ZERO);
	if (m_obstacle.pObstacle == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����x��ݒ�
	m_obstacle.pObstacle->SetAlpha(INIT_ALPHA);

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
void CEditObstacle::Uninit(void)
{
#if _DEBUG

	if (m_pCollision != NULL)
	{ // �����蔻��̏�񂪎g�p����Ă���ꍇ

		// �����蔻��̏��̏I��
		m_pCollision->Uninit();
	}
	else { assert(false); }	// ��g�p��

#endif	// _DEBUG
}

//============================================================
//	�X�V����
//============================================================
void CEditObstacle::Update(void)
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

	// ��ޕύX�̍X�V
	UpdateChangeType();

	// �����ԕύX�̍X�V
	UpdateChangeState();

	// ���@�ύX�̍X�V
	UpdateChangeDodge();

	// ��Q���̐���
	CreateObstacle();

	// ��Q���̔j��
	ReleaseObstacle();

	// ��Q���̕ۑ�
	SaveObstacle();

	// �ʒu�𔽉f
	m_obstacle.pObstacle->SetVec3Position(m_pEdit->GetVec3Position());
	m_pCollision->SetVec3Position(m_pEdit->GetVec3Position());

	// �����𔽉f
	m_obstacle.pObstacle->SetVec3Rotation(m_pEdit->GetVec3Rotation());
	m_pCollision->SetVec3Rotation(m_pEdit->GetVec3Rotation());

	// �傫���𔽉f
	D3DXVECTOR3 sizeColl = CObstacle::GetStatusInfo(m_obstacle.type).size * 0.5f;
	m_pCollision->SetVec3Sizing(sizeColl);

#endif	// _DEBUG
}

//============================================================
//	�\���̐ݒ菈��
//============================================================
void CEditObstacle::SetDisp(const bool bDisp)
{
	// �����X�V�E�����`���\���󋵂ɍ��킹��
	m_obstacle.pObstacle->SetEnableUpdate(bDisp);	// �X�V
	m_pCollision->SetEnableUpdate(bDisp);			// �X�V
	m_obstacle.pObstacle->SetEnableDraw(bDisp);		// �`��
	m_pCollision->SetEnableDraw(bDisp);				// �`��

	if (bDisp)
	{ // �\��ON�̏ꍇ

		// �ʒu�𔽉f
		m_obstacle.pObstacle->SetVec3Position(m_pEdit->GetVec3Position());
		m_pCollision->SetVec3Position(m_pEdit->GetVec3Position());
	}
	else
	{ // �\��OFF�̏ꍇ

		// ��Q���̐F�̑S������
		InitAllColorObstacle();

		// �ʒu���X�e�[�W�͈̔͊O�ɐݒ�
		D3DXVECTOR3 sizeObs = m_obstacle.pObstacle->GetVec3Sizing();
		D3DXVECTOR3 outLimit = D3DXVECTOR3(0.0f, 0.0f, CScene::GetStage()->GetStageLimit().fNear - ((sizeObs.z < sizeObs.x) ? sizeObs.x : sizeObs.z) * 0.5f);
		m_obstacle.pObstacle->SetVec3Position(outLimit);
		m_pCollision->SetVec3Position(outLimit);
	}
}

//============================================================
//	����\���̕`�揈��
//============================================================
void CEditObstacle::DrawDebugControl(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��

	pDebug->Print(CDebugProc::POINT_RIGHT, "��Q���ۑ��F[%s+%s]\n", NAME_DOUBLE, NAME_SAVE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "����g��F[%s/%s/%s+%s]\n", NAME_XSIZE_UP, NAME_YSIZE_UP, NAME_ZSIZE_UP, NAME_TRIGGER);
	pDebug->Print(CDebugProc::POINT_RIGHT, "����k���F[%s/%s/%s+%s]\n", NAME_XSIZE_DOWN, NAME_YSIZE_DOWN, NAME_ZSIZE_DOWN, NAME_TRIGGER);
	pDebug->Print(CDebugProc::POINT_RIGHT, "��ޕύX�F[%s/%s+%s]\n", NAME_TYPE, NAME_REVERSE, NAME_TYPE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�����ԕύX�F[%s]\n", NAME_STATE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "���@�ύX�F[%s]\n", NAME_DODGE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�폜�F[%s]\n", NAME_RELEASE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�ݒu�F[%s]\n", NAME_CREATE);
}

//============================================================
//	���\���̕`�揈��
//============================================================
void CEditObstacle::DrawDebugInfo(void)
{
	// �ϐ���錾
	CObstacle::SStatusInfo info = CObstacle::GetStatusInfo(m_obstacle.type);	// �X�e�|�^�X���

	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();				// �f�o�b�O�v���b�N�̏��
	static char* apState[] = { "�����Ԗ���", "�W�����v", "���n" };			// ������
	static char* apDodge[] = { "���@����", "�W�����v", "�X���C�f�B���O" };	// ���@

	// �����ԁE���@���̕s��v
	assert((sizeof(apState) / sizeof(apState[0])) == CObstacle::STATE_MAX);
	assert((sizeof(apDodge) / sizeof(apDodge[0])) == CObstacle::DODGE_MAX);

	pDebug->Print(CDebugProc::POINT_RIGHT, "%d�F[���]\n", m_obstacle.type);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%s�F[������]\n", apState[info.state]);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%s�F[���@]\n", apDodge[info.dodge]);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%f %f %f�F[����T�C�Y]\n", info.size.x, info.size.y, info.size.z);
}

//============================================================
//	�ۑ�����
//============================================================
void CEditObstacle::Save(FILE *pFile)
{
#if _DEBUG

	if (pFile != NULL)
	{ // �t�@�C�������݂���ꍇ

		// ���o���������o��
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#	��Q���̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		// ���J�n�n�_�������o��
		fprintf(pFile, "STAGE_OBSTACLESET\n\n");

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
	
					if (pObjCheck->GetLabel() != CObject::LABEL_OBSTACLE)
					{ // �I�u�W�F�N�g���x������Q���ł͂Ȃ��ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}
	
					if (pObjCheck == (CObject*)m_obstacle.pObstacle)
					{ // �����A�h���X�������ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}

					// ��Q���̏����擾
					D3DXVECTOR3 posObs = pObjCheck->GetVec3Position();	// �ʒu
					D3DXVECTOR3 rotObs = pObjCheck->GetVec3Rotation();	// ����
					int nType = pObjCheck->GetType();	// ���
	
					// ���������o��
					fprintf(pFile, "	OBSTACLESET\n");
					fprintf(pFile, "		TYPE = %d\n", nType);
					fprintf(pFile, "		POS = %.2f %.2f %.2f\n", posObs.x, posObs.y, posObs.z);
					fprintf(pFile, "		ROT = %.2f %.2f %.2f\n", rotObs.x, rotObs.y, rotObs.z);
					fprintf(pFile, "	END_OBSTACLESET\n\n");

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;
				}
			}
		}

		// ���I���n�_�������o��
		fprintf(pFile, "END_STAGE_OBSTACLESET\n\n");
	}

#endif	// _DEBUG
}

//============================================================
//	��������
//============================================================
CEditObstacle *CEditObstacle::Create(CEditStageManager *pEdit)
{
#if _DEBUG

	// �|�C���^��錾
	CEditObstacle *pEditObstacle = NULL;	// �G�f�B�b�g��Q�������p

	if (pEditObstacle == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pEditObstacle = new CEditObstacle;	// �G�f�B�b�g��Q��
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pEditObstacle != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �G�f�B�b�g��Q���̏�����
		if (FAILED(pEditObstacle->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pEditObstacle;
			pEditObstacle = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �G�f�B�b�g�X�e�[�W�̏���ݒ�
		pEditObstacle->m_pEdit = pEdit;

		// �m�ۂ����A�h���X��Ԃ�
		return pEditObstacle;
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
HRESULT CEditObstacle::Release(CEditObstacle *&prEditObstacle)
{
#if _DEBUG

	if (prEditObstacle != NULL)
	{ // �g�p���̏ꍇ

		// �G�f�B�b�g��Q���̏I��
		prEditObstacle->Uninit();

		// �������J��
		delete prEditObstacle;
		prEditObstacle = NULL;

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
void CEditObstacle::UpdateCollSize(void)
{
	// �ϐ���錾
	CObstacle::SStatusInfo info = CObstacle::GetStatusInfo(m_obstacle.type);	// �X�e�|�^�X���

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ����T�C�Y��ύX
	if (!m_pKeyboard->IsPress(KEY_TRIGGER))
	{
		if (m_pKeyboard->IsPress(KEY_ZSIZE_UP))
		{
			info.size.z += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_ZSIZE_DOWN))
		{
			info.size.z -= coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_XSIZE_UP))
		{
			info.size.x += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_XSIZE_DOWN))
		{
			info.size.x -= coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_YSIZE_UP))
		{
			info.size.y += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsPress(KEY_YSIZE_DOWN))
		{
			info.size.y -= coll::SIZE_MOVE;
		}
	}
	else
	{
		if (m_pKeyboard->IsTrigger(KEY_ZSIZE_UP))
		{
			info.size.z += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_ZSIZE_DOWN))
		{
			info.size.z -= coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_XSIZE_UP))
		{
			info.size.x += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_XSIZE_DOWN))
		{
			info.size.x -= coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_YSIZE_UP))
		{
			info.size.y += coll::SIZE_MOVE;
		}
		if (m_pKeyboard->IsTrigger(KEY_YSIZE_DOWN))
		{
			info.size.y -= coll::SIZE_MOVE;
		}
	}

	// �X�e�|�^�X���𔽉f
	CObstacle::SetStatusInfo(info, m_obstacle.type);
}

//============================================================
//	��ޕύX�̍X�V����
//============================================================
void CEditObstacle::UpdateChangeType(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ��ނ�ύX
	if (m_pKeyboard->IsPress(KEY_REVERSE))
	{
		if (m_pKeyboard->IsTrigger(KEY_TYPE))
		{
			// ��ނ�ύX
			m_obstacle.type = (CObstacle::EType)((m_obstacle.type + (CObstacle::TYPE_MAX - 1)) % CObstacle::TYPE_MAX);

			// ��ނ𔽉f
			m_obstacle.pObstacle->SetType(m_obstacle.type);
			m_obstacle.pObstacle->SetAlpha(INIT_ALPHA);	// �����x���Đݒ�
		}
	}
	else
	{
		if (m_pKeyboard->IsTrigger(KEY_TYPE))
		{
			// ��ނ�ύX
			m_obstacle.type = (CObstacle::EType)((m_obstacle.type + 1) % CObstacle::TYPE_MAX);

			// ��ނ𔽉f
			m_obstacle.pObstacle->SetType(m_obstacle.type);
			m_obstacle.pObstacle->SetAlpha(INIT_ALPHA);	// �����x���Đݒ�
		}
	}
}

//============================================================
//	�����ԕύX�̍X�V����
//============================================================
void CEditObstacle::UpdateChangeState(void)
{
	// �ϐ���錾
	CObstacle::SStatusInfo info = CObstacle::GetStatusInfo(m_obstacle.type);	// �X�e�|�^�X���

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �����Ԃ�ύX
	if (m_pKeyboard->IsTrigger(KEY_STATE))
	{
		info.state = (CObstacle::EState)((info.state + 1) % CObstacle::STATE_MAX);
	}

	// �X�e�|�^�X���𔽉f
	CObstacle::SetStatusInfo(info, m_obstacle.type);
}

//============================================================
//	���@�ύX�̍X�V����
//============================================================
void CEditObstacle::UpdateChangeDodge(void)
{
	// �ϐ���錾
	CObstacle::SStatusInfo info = CObstacle::GetStatusInfo(m_obstacle.type);	// �X�e�|�^�X���

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ���@��ύX
	if (m_pKeyboard->IsTrigger(KEY_DODGE))
	{
		info.dodge = (CObstacle::EDodge)((info.dodge + 1) % CObstacle::DODGE_MAX);
	}

	// �X�e�|�^�X���𔽉f
	CObstacle::SetStatusInfo(info, m_obstacle.type);
}

//============================================================
//	��Q���̐�������
//============================================================
void CEditObstacle::CreateObstacle(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();	// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 rotEdit = m_pEdit->GetVec3Rotation();	// �G�f�B�b�g�̌���

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ��Q����z�u
	if (m_pKeyboard->IsTrigger(KEY_CREATE))
	{
		//----------------------------------------------------
		//	��Q���̏���z�u�p�ɕύX
		//----------------------------------------------------
		// �����X�V�E�����`���ON�ɂ���
		m_obstacle.pObstacle->SetEnableUpdate(true);
		m_obstacle.pObstacle->SetEnableDraw(true);

		// �}�e���A�����Đݒ�
		m_obstacle.pObstacle->ResetMaterial();

		// ���ۑ���ݒ�
		m_pEdit->UnSave();

		//----------------------------------------------------
		//	�V������Q���̐���
		//----------------------------------------------------
		// ��Q���̐���
		m_obstacle.pObstacle = CObstacle::Create(m_obstacle.type, posEdit, rotEdit);
		assert(m_obstacle.pObstacle != NULL);

		// �����x��ݒ�
		m_obstacle.pObstacle->SetAlpha(INIT_ALPHA);
	}
}

//============================================================
//	��Q���̔j������
//============================================================
void CEditObstacle::ReleaseObstacle(void)
{
	// �ϐ���錾
	bool bRelease = false;	// �j����

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ��Q�����폜
	if (m_pKeyboard->IsTrigger(KEY_RELEASE))
	{
		// �j�������Ԃ�ݒ�
		bRelease = true;
	}

	// ��Q���̍폜����
	DeleteCollisionObstacle(bRelease);
}

//============================================================
//	��Q���̍폜����
//============================================================
void CEditObstacle::DeleteCollisionObstacle(const bool bRelase)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();				// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 sizeEdit = m_obstacle.pObstacle->GetVec3Sizing();	// �G�f�B�b�g��Q���̑傫��

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
				D3DXVECTOR3 posObs = VEC3_ZERO;	// ��Q���ʒu
				D3DXVECTOR3 sizeObs = VEC3_ZERO;	// ��Q���傫��

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_OBSTACLE)
				{ // �I�u�W�F�N�g���x������Q���ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_obstacle.pObstacle)
				{ // �����A�h���X�������ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// ��Q���̈ʒu���擾
				posObs = pObjCheck->GetVec3Position();

				// ��Q���̑傫�����擾
				sizeObs = pObjCheck->GetVec3Sizing();

				// ���̂̓����蔻��
				if (collision::Circle3D
				( // ����
					posEdit,	// ����ʒu
					posObs,	// ����ڕW�ʒu
					((sizeObs.x + sizeObs.z) * 0.5f) * 0.5f,	// ���蔼�a
					((sizeEdit.x + sizeEdit.z) * 0.5f) * 0.5f	// ����ڕW���a
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
//	��Q���̐F�̑S����������
//============================================================
void CEditObstacle::InitAllColorObstacle(void)
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

				if (pObjCheck->GetLabel() != CObject::LABEL_OBSTACLE)
				{ // �I�u�W�F�N�g���x������Q���ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_obstacle.pObstacle)
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

//============================================================
//	��Q���ۑ�����
//============================================================
void CEditObstacle::SaveObstacle(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ��Q����ۑ�
	if (m_pKeyboard->IsPress(KEY_DOUBLE))
	{
		if (m_pKeyboard->IsTrigger(KEY_SAVE))
		{
			// �ۑ�����
			Save();
		}
	}
}

//============================================================
//	�ۑ�����
//============================================================
void CEditObstacle::Save(void)
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
		fprintf(pFile, "#	��Q���Z�[�u�e�L�X�g [save_obstacle.txt]\n");
		fprintf(pFile, "#	Author : you\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "---------->--<---------- �������牺�� �R�s�[���\��t�� ---------->--<----------\n");
		fprintf(pFile, "\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#	�p�����[�^�[���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#	�����Ԗ���		�F0\n");
		fprintf(pFile, "#	�G���ƃW�����v����F1\n");
		fprintf(pFile, "#	���n�ł���			�F2\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#	�����@����		�F0\n");
		fprintf(pFile, "#	�W�����v���		�F1\n");
		fprintf(pFile, "#	�X���C�f�B���O���	�F2\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		// ���J�n�n�_�������o��
		fprintf(pFile, "STATUSSET\n\n");

		for (int nCntObs = 0; nCntObs < CObstacle::TYPE_MAX; nCntObs++)
		{ // ��Q���̎�ސ����J��Ԃ�

			// �ϐ���錾
			CObstacle::SStatusInfo info = CObstacle::GetStatusInfo(nCntObs);	// �X�e�|�^�X���

			// ���������o��
			fprintf(pFile, "	OBSTACLESET\n");
			fprintf(pFile, "		TYPE = %d\n", nCntObs);
			fprintf(pFile, "		SIZE = %.2f %.2f %.2f\n", info.size.x, info.size.y, info.size.z);
			fprintf(pFile, "		STATE = %d\n", info.state);
			fprintf(pFile, "		DODGE = %d\n", info.dodge);
			fprintf(pFile, "	END_OBSTACLESET\n\n");
		}

		// ���I���n�_�������o��
		fprintf(pFile, "END_STATUSSET\n\n");

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "��Q���Z�[�u�t�@�C���̏����o���Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}
}

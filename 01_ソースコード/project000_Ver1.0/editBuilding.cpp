//============================================================
//
//	�G�f�B�b�g�r������ [editBuilding.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "editBuilding.h"
#include "manager.h"
#include "input.h"
#include "collision.h"
#include "editStageManager.h"
#include "stage.h"
#include "effect3D.h"

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
#define KEY_COLL		(DIK_3)	// ����ύX�L�[
#define NAME_COLL		("3")	// ����ύX�\��

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
}

//************************************************************
//	�e�N���X [CEditBuilding] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEditBuilding::CEditBuilding()
{
#if _DEBUG

	// �����o�ϐ����N���A
	m_pEdit = NULL;	// �G�f�B�b�g�X�e�[�W�̏��
	memset(&m_building, 0, sizeof(m_building));	// �r���z�u���

#endif	// _DEBUG
}

//============================================================
//	�f�X�g���N�^
//============================================================
CEditBuilding::~CEditBuilding()
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	����������
//============================================================
HRESULT CEditBuilding::Init(void)
{
#if _DEBUG

	// �����o�ϐ���������
	m_pEdit = NULL;	// �G�f�B�b�g�X�e�[�W�̏��

	m_building.pBuilding = NULL;					// �r�����
	m_building.type = CBuilding::TYPE_00;			// �r�����
	m_building.coll = CBuilding::COLLISION_GROUND;	// �r������

	// �r���̐���
	m_building.pBuilding = CBuilding::Create(m_building.type, VEC3_ZERO, VEC3_ZERO, m_building.coll);
	if (m_building.pBuilding == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �F��ݒ�
	D3DXCOLOR col = m_building.pBuilding->GetColor();	// ���̐F���擾
	m_building.pBuilding->SetColor(D3DXCOLOR(col.r, col.g, col.b, INIT_ALPHA));

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
void CEditBuilding::Uninit(void)
{
#if _DEBUG
#endif	// _DEBUG
}

//============================================================
//	�X�V����
//============================================================
void CEditBuilding::Update(void)
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

	// ����ύX�̍X�V
	UpdateChangeColl();

	// �g�嗦�ύX�̍X�V
	UpdateChangeScale();

	// �����\���G�t�F�N�g�̐���
	CreateRotaEffect();

	// �r���̐���
	CreateBuilding();

	// �r���̔j��
	ReleaseBuilding();

	// �ʒu�𔽉f
	m_building.pBuilding->SetVec3Position(m_pEdit->GetVec3Position());

	// �����𔽉f
	m_building.pBuilding->SetVec3Rotation(m_pEdit->GetVec3Rotation());

	// ��ނ𔽉f
	m_building.pBuilding->SetType(m_building.type);

	// ����𔽉f
	m_building.pBuilding->SetState(m_building.coll);

#endif	// _DEBUG
}

//============================================================
//	�\���̐ݒ菈��
//============================================================
void CEditBuilding::SetDisp(const bool bDisp)
{
	// �����X�V�E�����`���\���󋵂ɍ��킹��
	m_building.pBuilding->SetEnableUpdate(bDisp);	// �X�V
	m_building.pBuilding->SetEnableDraw(bDisp);		// �`��

	if (bDisp)
	{ // �\��ON�̏ꍇ

		// �ʒu�𔽉f
		m_building.pBuilding->SetVec3Position(m_pEdit->GetVec3Position());
	}
	else
	{ // �\��OFF�̏ꍇ

		// �r���̐F�̑S������
		InitAllColorBuilding();

		// �ʒu���X�e�[�W�͈̔͊O�ɐݒ�
		D3DXVECTOR3 outLimit = D3DXVECTOR3(0.0f, 0.0f, CScene::GetStage()->GetStageLimit().fNear - m_building.pBuilding->GetVec3Sizing().z);
		m_building.pBuilding->SetVec3Position(outLimit);
	}
}

//============================================================
//	����\���̕`�揈��
//============================================================
void CEditBuilding::DrawDebugControl(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��

	pDebug->Print(CDebugProc::POINT_RIGHT, "��ޕύX�F[%s]\n", NAME_TYPE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "����ύX�F[%s]\n", NAME_COLL);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�g�嗦�㏸�F[%s]\n", NAME_SCALE_UP);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�g�嗦���~�F[%s]\n", NAME_SCALE_DOWN);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�폜�F[%s]\n", NAME_RELEASE);
	pDebug->Print(CDebugProc::POINT_RIGHT, "�ݒu�F[%s]\n", NAME_CREATE);
}

//============================================================
//	���\���̕`�揈��
//============================================================
void CEditBuilding::DrawDebugInfo(void)
{
	// �|�C���^��錾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();	// �f�o�b�O�v���b�N�̏��
	static char* apColl[] = { "����", "�n��", "�V��" };	// ����

	// ���萔�̕s��v
	assert((sizeof(apColl) / sizeof(apColl[0])) == CBuilding::COLLISION_MAX);

	pDebug->Print(CDebugProc::POINT_RIGHT, "%d�F[���]\n", m_building.type);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%s�F[����]\n", apColl[m_building.coll]);
	pDebug->Print(CDebugProc::POINT_RIGHT, "%f�F[�g�嗦]\n", m_building.pBuilding->GetScale());
}

//============================================================
//	�ۑ�����
//============================================================
void CEditBuilding::Save(FILE *pFile)
{
#if _DEBUG

	if (pFile != NULL)
	{ // �t�@�C�������݂���ꍇ

		// ���o���������o��
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#	�r���̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		// ���J�n�n�_�������o��
		fprintf(pFile, "STAGE_BUILDINGSET\n\n");

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
	
					if (pObjCheck->GetLabel() != CObject::LABEL_BUILDING)
					{ // �I�u�W�F�N�g���x�����r���ł͂Ȃ��ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}
	
					if (pObjCheck == (CObject*)m_building.pBuilding)
					{ // �����A�h���X�������ꍇ
	
						// ���̃I�u�W�F�N�g�ւ̃|�C���^����
						pObjCheck = pObjectNext;
	
						// ���̌J��Ԃ��Ɉڍs
						continue;
					}

					// �r���̏����擾
					D3DXVECTOR3 posBuild = pObjCheck->GetVec3Position();	// �ʒu
					D3DXVECTOR3 rotBuild = pObjCheck->GetVec3Rotation();	// ����
					int nType = pObjCheck->GetType();		// ���
					int nCollision = pObjCheck->GetState();	// �����蔻��
					float fScale = pObjCheck->GetScale();	// �g�嗦
	
					// ���������o��
					fprintf(pFile, "	BUILDINGSET\n");
					fprintf(pFile, "		TYPE = %d\n", nType);
					fprintf(pFile, "		POS = %.2f %.2f %.2f\n", posBuild.x, posBuild.y, posBuild.z);
					fprintf(pFile, "		ROT = %.2f %.2f %.2f\n", rotBuild.x, rotBuild.y, rotBuild.z);
					fprintf(pFile, "		COLL = %d\n", nCollision);
					fprintf(pFile, "		SCALE = %.2f\n", fScale);
					fprintf(pFile, "	END_BUILDINGSET\n\n");

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;
				}
			}
		}

		// ���I���n�_�������o��
		fprintf(pFile, "END_STAGE_BUILDINGSET\n\n");
	}

#endif	// _DEBUG
}

//============================================================
//	��������
//============================================================
CEditBuilding *CEditBuilding::Create(CEditStageManager *pEdit)
{
#if _DEBUG

	// �|�C���^��錾
	CEditBuilding *pEditBuilding = NULL;	// �G�f�B�b�g�r�������p

	if (pEditBuilding == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pEditBuilding = new CEditBuilding;	// �G�f�B�b�g�r��
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pEditBuilding != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �G�f�B�b�g�r���̏�����
		if (FAILED(pEditBuilding->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pEditBuilding;
			pEditBuilding = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �G�f�B�b�g�X�e�[�W�̏���ݒ�
		pEditBuilding->m_pEdit = pEdit;

		// �m�ۂ����A�h���X��Ԃ�
		return pEditBuilding;
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
HRESULT CEditBuilding::Release(CEditBuilding *&prEditBuilding)
{
#if _DEBUG

	if (prEditBuilding != NULL)
	{ // �g�p���̏ꍇ

		// �G�f�B�b�g�r���̏I��
		prEditBuilding->Uninit();

		// �������J��
		delete prEditBuilding;
		prEditBuilding = NULL;

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
void CEditBuilding::UpdateChangeType(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// ��ނ�ύX
	if (m_pKeyboard->IsTrigger(KEY_TYPE))
	{
		m_building.type = (CBuilding::EType)((m_building.type + 1) % CBuilding::TYPE_MAX);
	}
}

//============================================================
//	����ύX�̍X�V����
//============================================================
void CEditBuilding::UpdateChangeColl(void)
{
	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �����ύX
	if (m_pKeyboard->IsTrigger(KEY_COLL))
	{
		m_building.coll = (CBuilding::ECollision)((m_building.coll + 1) % CBuilding::COLLISION_MAX);
	}
}

//============================================================
//	�g�嗦�ύX�̍X�V����
//============================================================
void CEditBuilding::UpdateChangeScale(void)
{
	// �ϐ���錾
	float fScale = m_building.pBuilding->GetScale();	// �r���g�嗦

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

	// �r���g�嗦�𔽉f
	m_building.pBuilding->SetScale(fScale);
}

//============================================================
//	�r���̐�������
//============================================================
void CEditBuilding::CreateBuilding(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();	// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 rotEdit = m_pEdit->GetVec3Rotation();	// �G�f�B�b�g�̌���
	D3DXCOLOR colBuild = XCOL_WHITE;	// �F�ۑ��p
	float fScale = 0.0f;	// �g�嗦

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �r����z�u
	if (m_pKeyboard->IsTrigger(KEY_CREATE))
	{
		//----------------------------------------------------
		//	�r���̏���z�u�p�ɕύX
		//----------------------------------------------------
		// �����X�V�E�����`���ON�ɂ���
		m_building.pBuilding->SetEnableUpdate(true);
		m_building.pBuilding->SetEnableDraw(true);

		// �F��ݒ�
		colBuild = m_building.pBuilding->GetColor();	// ���̐F���擾
		m_building.pBuilding->SetColor(D3DXCOLOR(colBuild.r, colBuild.g, colBuild.b, 1.0f));

		// �g�嗦��ۑ�
		fScale = m_building.pBuilding->GetScale();

		// ���ۑ���ݒ�
		m_pEdit->UnSave();

		//----------------------------------------------------
		//	�V�����r���̐���
		//----------------------------------------------------
		// �r���̐���
		m_building.pBuilding = CBuilding::Create(m_building.type, posEdit, rotEdit, m_building.coll);
		assert(m_building.pBuilding != NULL);

		// �F��ݒ�
		colBuild = m_building.pBuilding->GetColor();	// ���̐F���擾
		m_building.pBuilding->SetColor(D3DXCOLOR(colBuild.r, colBuild.g, colBuild.b, INIT_ALPHA));

		// �g�嗦��ݒ�
		m_building.pBuilding->SetScale(fScale);
	}
}

//============================================================
//	�r���̔j������
//============================================================
void CEditBuilding::ReleaseBuilding(void)
{
	// �ϐ���錾
	bool bRelease = false;	// �j����

	// �|�C���^��錾
	CInputKeyboard *m_pKeyboard = CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h���

	// �r�����폜
	if (m_pKeyboard->IsTrigger(KEY_RELEASE))
	{
		// �j�������Ԃ�ݒ�
		bRelease = true;
	}

	// �r���̍폜����
	DeleteCollisionBuilding(bRelease);
}

//============================================================
//	�����\���G�t�F�N�g�̐�������
//============================================================
void CEditBuilding::CreateRotaEffect(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posEffect = VEC3_ZERO;								// �G�t�F�N�g�ʒu
	D3DXVECTOR3 posEdit   = m_pEdit->GetVec3Position();				// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 rotEdit   = m_pEdit->GetVec3Rotation();				// �G�f�B�b�g�̌���
	D3DXVECTOR3 sizeBuild = m_building.pBuilding->GetVec3Sizing();	// �r���傫��
	float fAverageSizeBuild = (sizeBuild.x + sizeBuild.z) * 0.5f;	// �r���傫������

	// �G�t�F�N�g�ʒu���v�Z
	posEffect.x = posEdit.x + sinf(rotEdit.y + D3DX_PI) * fAverageSizeBuild;
	posEffect.y = posEdit.y + sizeBuild.y * 2.0f;
	posEffect.z = posEdit.z + cosf(rotEdit.y + D3DX_PI) * fAverageSizeBuild;

	// �����\���G�t�F�N�g�𐶐�
	CEffect3D::Create(posEffect, EFFECT_RADIUS, CEffect3D::TYPE_NORMAL, EFFECT_LIFE);
}

//============================================================
//	�r���̍폜����
//============================================================
void CEditBuilding::DeleteCollisionBuilding(const bool bRelase)
{
	// �ϐ���錾
	D3DXVECTOR3 posEdit = m_pEdit->GetVec3Position();				// �G�f�B�b�g�̈ʒu
	D3DXVECTOR3 sizeEdit = m_building.pBuilding->GetVec3Sizing();	// �G�f�B�b�g�r���̑傫��

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
				D3DXVECTOR3 posBuild = VEC3_ZERO;	// �r���ʒu
				D3DXVECTOR3 sizeBuild = VEC3_ZERO;	// �r���傫��

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_BUILDING)
				{ // �I�u�W�F�N�g���x�����r���ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_building.pBuilding)
				{ // �����A�h���X�������ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �r���̈ʒu���擾
				posBuild = pObjCheck->GetVec3Position();

				// �r���̑傫�����擾
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
//	�r���̐F�̑S����������
//============================================================
void CEditBuilding::InitAllColorBuilding(void)
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

				if (pObjCheck->GetLabel() != CObject::LABEL_BUILDING)
				{ // �I�u�W�F�N�g���x�����r���ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck == (CObject*)m_building.pBuilding)
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

//============================================================
//
//	�r������ [building.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "building.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�}�N����`
//************************************************************
#define BUILDING_PRIO	(1)	// �r���̗D�揇��

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CBuilding::mc_apTextureFile[][6] =	// �e�N�X�`���萔
{
	{ // �r��00�e�N�X�`��
		"data\\TEXTURE\\buildingSide000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingSide000.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\buildingRoof000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingRoof000.png",	// ��e�N�X�`��
		"data\\TEXTURE\\buildingSide000.png",	// �O�e�N�X�`��
		"data\\TEXTURE\\buildingSide000.png",	// ��e�N�X�`��
	},

	{ // �r��01�e�N�X�`��
		"data\\TEXTURE\\buildingSide001.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingSide001.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\buildingRoof001.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingRoof001.png",	// ��e�N�X�`��
		"data\\TEXTURE\\buildingSide001.png",	// �O�e�N�X�`��
		"data\\TEXTURE\\buildingSide001.png",	// ��e�N�X�`��
	},

	{ // �r��02�e�N�X�`��
		"data\\TEXTURE\\buildingSide002.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingSide002.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\buildingRoof002.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingRoof002.png",	// ��e�N�X�`��
		"data\\TEXTURE\\buildingSide002.png",	// �O�e�N�X�`��
		"data\\TEXTURE\\buildingSide002.png",	// ��e�N�X�`��
	},

	{ // �r�����e�N�X�`��
		"data\\TEXTURE\\buildingSide003.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingSide003.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\buildingRoof003.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingRoof003.png",	// ��e�N�X�`��
		"data\\TEXTURE\\buildingSide003.png",	// �O�e�N�X�`��
		"data\\TEXTURE\\buildingSide003.png",	// ��e�N�X�`��
	},

	{ // �r�����e�N�X�`��
		"data\\TEXTURE\\buildingSide004.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingSide004.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\buildingRoof003.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingRoof003.png",	// ��e�N�X�`��
		"data\\TEXTURE\\buildingSide004.png",	// �O�e�N�X�`��
		"data\\TEXTURE\\buildingSide004.png",	// ��e�N�X�`��
	},

	{ // �r����e�N�X�`��
		"data\\TEXTURE\\buildingSide005.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingSide005.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\buildingRoof003.png",	// ���e�N�X�`��
		"data\\TEXTURE\\buildingRoof003.png",	// ��e�N�X�`��
		"data\\TEXTURE\\buildingSide005.png",	// �O�e�N�X�`��
		"data\\TEXTURE\\buildingSide005.png",	// ��e�N�X�`��
	},
};

CBuilding::SStatusInfo CBuilding::m_aStatusInfo[] =	// �X�e�[�^�X���
{
	{ // �r��00�X�e�[�^�X
		D3DXVECTOR3(280.0f, 560.0f, 280.0f),	// �傫��
	},

	{ // �r��01�X�e�[�^�X
		D3DXVECTOR3(280.0f, 560.0f, 280.0f),	// �傫��
	},

	{ // �r��02�X�e�[�^�X
		D3DXVECTOR3(280.0f, 560.0f, 280.0f),	// �傫��
	},

	{ // �r�����X�e�[�^�X
		D3DXVECTOR3(280.0f, 280.0f, 280.0f),	// �傫��
	},

	{ // �r�����ԃX�e�[�^�X
		D3DXVECTOR3(280.0f, 280.0f, 280.0f),	// �傫��
	},

	{ // �r����X�e�[�^�X
		D3DXVECTOR3(280.0f, 280.0f, 280.0f),	// �傫��
	},
};

//************************************************************
//	�q�N���X [CBuilding] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CBuilding::CBuilding() : CObjectMeshCube(CObject::LABEL_BUILDING, BUILDING_PRIO)
{
	// �����o�ϐ����N���A
	memset(&m_status, 0, sizeof(m_status));	// �X�e�[�^�X�萔
	m_collision = COLLISION_NONE;	// �����蔻��
	m_type = TYPE_00;	// ��ޒ萔
	m_fScale = 0.0f;	// �g�嗦
}

//============================================================
//	�f�X�g���N�^
//============================================================
CBuilding::~CBuilding()
{

}

//============================================================
//	����������
//============================================================
HRESULT CBuilding::Init(void)
{
	// �����o�ϐ���������
	memset(&m_status, 0, sizeof(m_status));	// �X�e�[�^�X�萔
	m_collision = COLLISION_NONE;	// �����蔻��
	m_type = TYPE_00;	// ��ޒ萔
	m_fScale = 1.0f;	// �g�嗦

	// �I�u�W�F�N�g���b�V���L���[�u�̏�����
	if (FAILED(CObjectMeshCube::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���_��ݒ�
	SetOrigin(CObjectMeshCube::ORIGIN_DOWN);

	// �L���[�u�F��ݒ�
	SetColor(XCOL_WHITE);

	// �����F��ݒ�
	SetBorderColor(XCOL_WHITE);

	// �����̏�Ԃ�ݒ�
	if (FAILED(SetBorderState(CObjectMeshCube::BORDER_OFF)))
	{ // �������̐ݒ�Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �����̑�����ݒ�
	SetBorderThick(0.0f);

	// �e�N�X�`���̏�Ԃ�ݒ�
	SetTextureState(CObjectMeshCube::TEXSTATE_SELECT);

	// �e�N�X�`���̕�����X��ݒ�
	SetTexturePatternX(VEC2_ONE);

	// �e�N�X�`���̕�����Y��ݒ�
	SetTexturePatternY(VEC2_ONE);

	// �e�N�X�`���̕�����Z��ݒ�
	SetTexturePatternZ(VEC2_ONE);

	// �J�����O��ݒ�
	SetCulling(D3DCULL_CCW);

	// ���C�e�B���O��ݒ�
	SetLighting(true);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CBuilding::Uninit(void)
{
	// �I�u�W�F�N�g���b�V���L���[�u�̏I��
	CObjectMeshCube::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CBuilding::Update(void)
{
	// �I�u�W�F�N�g���b�V���L���[�u�̍X�V
	CObjectMeshCube::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CBuilding::Draw(void)
{
	// �I�u�W�F�N�g���b�V���L���[�u�̕`��
	CObjectMeshCube::Draw();
}

//============================================================
//	��ނ̐ݒ菈��
//============================================================
void CBuilding::SetType(const int nType)
{
	// �ϐ���錾
	SFaceTex faceTex;	// �e�N�X�`���C���f�b�N�X�ݒ�p

	// �|�C���^��錾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	if (pTexture == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �����𔲂���
		assert(false);
		return;
	}

	if (nType > NONE_IDX && nType < TYPE_MAX)
	{ // ��ނ��͈͓��̏ꍇ

		// �����̎�ނ�ݒ�
		m_type = (EType)nType;

		// �����̎�ނ̃X�e�[�^�X��ݒ�
		m_status = m_aStatusInfo[m_type];	// �X�e�[�^�X���
		SetVec3Sizing(m_status.size * m_fScale);	// �傫��

		// �����̎�ނ̃e�N�X�`����o�^
		faceTex = SFaceTex
		( // ����
			pTexture->Regist(mc_apTextureFile[nType][0]),	// ��
			pTexture->Regist(mc_apTextureFile[nType][1]),	// �E
			pTexture->Regist(mc_apTextureFile[nType][2]),	// ��
			pTexture->Regist(mc_apTextureFile[nType][3]),	// ��
			pTexture->Regist(mc_apTextureFile[nType][4]),	// �O
			pTexture->Regist(mc_apTextureFile[nType][5])	// ��
		);
		BindTexture(faceTex);	// �e�N�X�`��������
	}
	else { assert(false); }	// ��ރI�[�o�[
}

//============================================================
//	��ގ擾����
//============================================================
int CBuilding::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//============================================================
//	�����蔻��̐ݒ菈��
//============================================================
void CBuilding::SetState(const int nState)
{
	if (nState > NONE_IDX && nState < COLLISION_MAX)
	{ // �C���f�b�N�X���͈͓��̏ꍇ

		// �����̓����蔻���ݒ�
		m_collision = (ECollision)nState;
	}
	else { assert(false); }	// �͈͊O
}

//============================================================
//	�����蔻��擾����
//============================================================
int CBuilding::GetState(void) const
{
	// �����蔻���Ԃ�
	return m_collision;
}

//============================================================
//	�g�嗦�̐ݒ菈��
//============================================================
void CBuilding::SetScale(const float fScale)
{
	// �����̊g�嗦��ݒ�
	m_fScale = fScale;

	// �傫����ݒ�
	SetVec3Sizing(m_status.size * m_fScale);
}

//============================================================
//	�g�嗦�擾����
//============================================================
float CBuilding::GetScale(void) const
{
	// �g�嗦��Ԃ�
	return m_fScale;
}

//============================================================
//	��������
//============================================================
CBuilding *CBuilding::Create
(
	const EType type,			// ���
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const ECollision collision,	// �����蔻��
	const float fScale			// �g�嗦
)
{
	// �|�C���^��錾
	CBuilding *pBuilding = NULL;	// �r�������p

	if (pBuilding == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pBuilding = new CBuilding;	// �r��
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pBuilding != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// �r���̏�����
		if (FAILED(pBuilding->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pBuilding;
			pBuilding = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// ��ނ�ݒ�
		pBuilding->SetType(type);

		// �ʒu��ݒ�
		pBuilding->SetVec3Position(rPos);

		// ������ݒ�
		pBuilding->SetVec3Rotation(rRot);

		// �����蔻���ݒ�
		pBuilding->SetState(collision);

		// �g�嗦��ݒ�
		pBuilding->SetScale(fScale);

		// �m�ۂ����A�h���X��Ԃ�
		return pBuilding;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//
//	�Ŕ��� [signboard.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "signboard.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "multiModel.h"

//************************************************************
//	�}�N����`
//************************************************************
#define SIGNBOARD_PRIO	(1)	// �Ŕ̗D�揇��

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const D3DXVECTOR3 DEFAULT_SIZE = D3DXVECTOR3(250.0f, 130.0f, 6.0f);	// �Ŕ̃f�t�H���g�̑傫��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CSignboard::mc_apTextureFile[][6] =	// �e�N�X�`���萔
{
	{ // �E�e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ��e�N�X�`��
		"data\\TEXTURE\\signboard000.png",		// �O�e�N�X�`��
		"data\\TEXTURE\\signboardBack000.png",	// ��e�N�X�`��
	},

	{ // ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ��e�N�X�`��
		"data\\TEXTURE\\signboard000.png",		// �O�e�N�X�`��
		"data\\TEXTURE\\signboardBack000.png",	// ��e�N�X�`��
	},

	{ // ��e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ��e�N�X�`��
		"data\\TEXTURE\\signboard000.png",		// �O�e�N�X�`��
		"data\\TEXTURE\\signboardBack000.png",	// ��e�N�X�`��
	},

	{ // ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// �E�e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ���e�N�X�`��
		"data\\TEXTURE\\signboardSide000.png",	// ��e�N�X�`��
		"data\\TEXTURE\\signboard000.png",		// �O�e�N�X�`��
		"data\\TEXTURE\\signboardBack000.png",	// ��e�N�X�`��
	},
};

const char *CSignboard::mc_apModelFile[] =	// ���f���萔
{
	"data\\MODEL\\SIGNBOARD\\signboard000.x",	// �X�^���h���f��
};

//************************************************************
//	�q�N���X [CSignboard] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSignboard::CSignboard() : CObjectMeshCube(CObject::LABEL_SIGNBOARD, SIGNBOARD_PRIO)
{
	// �����o�ϐ����N���A
	m_pStand = NULL;		// �ŔX�^���h�̏��
	m_type   = TYPE_LEFT;	// ���
	m_fScale = 0.0f;		// �g�嗦
}

//============================================================
//	�f�X�g���N�^
//============================================================
CSignboard::~CSignboard()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSignboard::Init(void)
{
	// �����o�ϐ���������
	m_pStand = NULL;		// �ŔX�^���h�̏��
	m_type   = TYPE_LEFT;	// ���
	m_fScale = 1.0f;		// �g�嗦

	//--------------------------------------------------------
	//	�I�u�W�F�N�g���b�V���L���[�u�̏�����
	//--------------------------------------------------------
	// �I�u�W�F�N�g���b�V���L���[�u�̏�����
	if (FAILED(CObjectMeshCube::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���_��ݒ�
	SetOrigin(CObjectMeshCube::ORIGIN_CENTER);

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

	//--------------------------------------------------------
	//	�ŔX�^���h�̏�����
	//--------------------------------------------------------
	// �ŔX�^���h�̐���
	m_pStand = CMultiModel::Create(VEC3_ZERO, VEC3_ZERO);
	if (m_pStand == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f��������
	m_pStand->BindModel(mc_apModelFile[MODEL_STAND]);

	// �e�I�u�W�F�N�g�̐ݒ�
	m_pStand->SetParentObject(this);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSignboard::Uninit(void)
{
	// �ŔX�^���h�̏I��
	m_pStand->Uninit();

	// �I�u�W�F�N�g���b�V���L���[�u�̏I��
	CObjectMeshCube::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSignboard::Update(void)
{
	// �ŔX�^���h�̍X�V
	m_pStand->Update();

	// �I�u�W�F�N�g���b�V���L���[�u�̍X�V
	CObjectMeshCube::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CSignboard::Draw(void)
{
	// �ŔX�^���h�̕`��
	m_pStand->Draw();

	// �I�u�W�F�N�g���b�V���L���[�u�̕`��
	CObjectMeshCube::Draw();
}

//============================================================
//	��ނ̐ݒ菈��
//============================================================
void CSignboard::SetType(const int nType)
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

	if (nType < TYPE_MAX)
	{ // ��ނ�����ꍇ

		// �����̎�ނ�ݒ�
		m_type = (EType)nType;

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

		// �e�N�X�`��������
		BindTexture(faceTex);
	}
	else { assert(false); }	// ��ރI�[�o�[
}

//============================================================
//	��ގ擾����
//============================================================
int CSignboard::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//============================================================
//	�g�嗦�̐ݒ菈��
//============================================================
void CSignboard::SetScale(const float fScale)
{
	// �����̊g�嗦��ݒ�
	m_fScale = fScale;

	// ���b�V���L���[�u�̑傫����ݒ�
	SetVec3Sizing(DEFAULT_SIZE * fScale);

	// ���f���̊g�嗦��ݒ�
	m_pStand->SetVec3Scaling(VEC3_ALL(fScale));
}

//============================================================
//	�g�嗦�擾����
//============================================================
float CSignboard::GetScale(void) const
{
	// �g�嗦��Ԃ�
	return m_fScale;
}

//============================================================
//	��������
//============================================================
CSignboard *CSignboard::Create
(
	const EType type,			// ���
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const float fScale,			// �g�嗦
	const D3DXCOLOR& rCol		// �F
)
{
	// �|�C���^��錾
	CSignboard *pSignboard = NULL;	// �Ŕ����p

	if (pSignboard == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pSignboard = new CSignboard;	// �Ŕ�
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pSignboard != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// �Ŕ̏�����
		if (FAILED(pSignboard->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pSignboard;
			pSignboard = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// ��ނ�ݒ�
		pSignboard->SetType(type);

		// �ʒu��ݒ�
		pSignboard->SetVec3Position(rPos);

		// ������ݒ�
		pSignboard->SetVec3Rotation(rRot);

		// �g�嗦��ݒ�
		pSignboard->SetScale(fScale);

		// �L���[�u�F��ݒ�
		pSignboard->SetColor(rCol);

		// �m�ۂ����A�h���X��Ԃ�
		return pSignboard;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

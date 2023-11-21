//============================================================
//
//	������ [window.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "window.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object3D.h"

#include "effect3D.h"

//************************************************************
//	�}�N����`
//************************************************************
#define WINDOW_FAR_PRIO		(4)	// �����̗D�揇��
#define WINDOW_NEAR_PRIO	(5)	// ��O���̗D�揇��

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CWindow::mc_apTextureFile[][WINDOW_MAX] =	// �e�N�X�`���萔
{
	{ // �ʏ�r�����e�N�X�`��
		"data\\TEXTURE\\wall000.png",			// ���E���e�N�X�`��
		"data\\TEXTURE\\buildingSide004.png",	// ���E�\�e�N�X�`��
		"data\\TEXTURE\\window000.png",			// ��O�E���e�N�X�`��
		"data\\TEXTURE\\wall000.png",			// ��O�E�\�e�N�X�`��
	},
};

CWindow::SStatusInfo CWindow::m_aStatusInfo[] =	// �X�e�[�^�X���
{
	{ // �ʏ�r�����X�e�[�^�X
		D3DXVECTOR3(280.0f, 280.0f, 280.0f),	// �傫��
	},
};

//************************************************************
//	�q�N���X [CWindow] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CWindow::CWindow() : CObject(CObject::LABEL_WINDOW)
{
	// �����o�ϐ����N���A
	memset(&m_pWall[0], 0, sizeof(m_pWall));	// ���̏��
	memset(&m_status, 0, sizeof(m_status));		// �X�e�[�^�X
	m_pos = VEC3_ZERO;		// �ʒu
	m_rot = VEC3_ZERO;		// ����
	m_size = VEC3_ZERO;		// �傫��
	m_type = TYPE_NORMAL;	// ���
	m_fScale = 0.0f;		// �g�嗦
}

//============================================================
//	�f�X�g���N�^
//============================================================
CWindow::~CWindow()
{

}

//============================================================
//	����������
//============================================================
HRESULT CWindow::Init(void)
{
	// �ϐ��z���錾
	static int aPrio[] = { WINDOW_FAR_PRIO, WINDOW_FAR_PRIO, WINDOW_NEAR_PRIO, WINDOW_NEAR_PRIO, };	// �D�揇��

	// �����o�ϐ���������
	memset(&m_pWall[0], 0, sizeof(m_pWall));	// ���̏��
	memset(&m_status, 0, sizeof(m_status));		// �X�e�[�^�X�萔
	m_pos = VEC3_ZERO;		// �ʒu
	m_rot = VEC3_ZERO;		// ����
	m_size = VEC3_ZERO;		// �傫��
	m_type = TYPE_NORMAL;	// ��ޒ萔
	m_fScale = 1.0f;		// �g�嗦

	// ���̐���
	for (int nCntWindow = 0; nCntWindow < WINDOW_MAX; nCntWindow++)
	{ // ���Ɏg�p����ǂ̑������J��Ԃ�

		// �ǂ̐���
		m_pWall[nCntWindow] = CObject3D::Create
		( // ����
			VEC3_ZERO,	// �ʒu
			VEC3_ZERO,	// �傫��
			VEC3_ZERO,	// ����
			XCOL_WHITE,	// �F
			CObject3D::ORIGIN_CENTER	// ���_
		);
		if (m_pWall[nCntWindow] == NULL)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_pWall[nCntWindow]->SetPriority(aPrio[nCntWindow]);
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CWindow::Uninit(void)
{
	// ���̏I��
	for (int nCntWindow = 0; nCntWindow < WINDOW_MAX; nCntWindow++)
	{ // ���Ɏg�p����ǂ̑������J��Ԃ�

		if (m_pWall[nCntWindow] != NULL)
		{ // �g�p���̏ꍇ

			// �ǂ̏I��
			m_pWall[nCntWindow]->Uninit();
		}
		else { assert(false); }	// ��g�p��
	}

	// ����j��
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CWindow::Update(void)
{
	// ���̍X�V
	for (int nCntWindow = 0; nCntWindow < WINDOW_MAX; nCntWindow++)
	{ // ���Ɏg�p����ǂ̑������J��Ԃ�

		if (m_pWall[nCntWindow] != NULL)
		{ // �g�p���̏ꍇ

			// �ǂ̍X�V
			m_pWall[nCntWindow]->Update();
		}
		else { assert(false); }	// ��g�p��
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�`�揈��
//============================================================
void CWindow::Draw(void)
{

}

//============================================================
//	�ʒu�̐ݒ菈��
//============================================================
void CWindow::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// �����̈ʒu��ݒ�
	m_pos = rPos;

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�ʒu�擾����
//============================================================
D3DXVECTOR3 CWindow::GetVec3Position(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//============================================================
//	�����̐ݒ菈��
//============================================================
void CWindow::SetVec3Rotation(const D3DXVECTOR3& rRot)
{
	// �����̌�����ݒ�
	m_rot = rRot;

	// �����̐��K��
	useful::Vec3NormalizeRot(m_rot);

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�����擾����
//============================================================
D3DXVECTOR3 CWindow::GetVec3Rotation(void) const
{
	// ������Ԃ�
	return m_rot;
}

//============================================================
//	�傫���̐ݒ菈��
//============================================================
void CWindow::SetVec3Sizing(const D3DXVECTOR3& rSize)
{
	// �����̑傫������
	m_size = rSize;

	for (int nCntWindow = 0; nCntWindow < WINDOW_MAX; nCntWindow++)
	{ // ���Ɏg�p����ǂ̑������J��Ԃ�

		if (m_pWall[nCntWindow] != NULL)
		{ // �g�p���̏ꍇ

			// �ǂ̑傫����ݒ�
			m_pWall[nCntWindow]->SetVec3Sizing(D3DXVECTOR3(rSize.x, rSize.y, 0.0f) * 2.0f);
		}
		else { assert(false); }	// ��g�p��
	}

	// ���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�傫���擾����
//============================================================
D3DXVECTOR3 CWindow::GetVec3Sizing(void) const
{
	// �傫����Ԃ�
	return m_size;
}

//============================================================
//	�F�̐ݒ菈��
//============================================================
void CWindow::SetColor(const D3DXCOLOR& rCol)
{
	for (int nCntWindow = 0; nCntWindow < WINDOW_MAX; nCntWindow++)
	{ // ���Ɏg�p����ǂ̑������J��Ԃ�

		if (m_pWall[nCntWindow] != NULL)
		{ // �g�p���̏ꍇ

			// �ǂ̐F��ݒ�
			m_pWall[nCntWindow]->SetColor(rCol);
		}
		else { assert(false); }	// ��g�p��
	}
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CWindow::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);	// ���g

	for (int nCntWindow = 0; nCntWindow < WINDOW_MAX; nCntWindow++)
	{ // ���Ɏg�p����ǂ̑������J��Ԃ�

		if (m_pWall[nCntWindow] != NULL)
		{ // �g�p���̏ꍇ

			// �ǂ̍X�V�󋵂�ݒ�
			m_pWall[nCntWindow]->SetEnableUpdate(bUpdate);
		}
		else { assert(false); }	// ��g�p��
	}
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CWindow::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g

	for (int nCntWindow = 0; nCntWindow < WINDOW_MAX; nCntWindow++)
	{ // ���Ɏg�p����ǂ̑������J��Ԃ�

		if (m_pWall[nCntWindow] != NULL)
		{ // �g�p���̏ꍇ

			// �ǂ̕`��󋵂�ݒ�
			m_pWall[nCntWindow]->SetEnableDraw(bDraw);
		}
		else { assert(false); }	// ��g�p��
	}
}

//============================================================
//	��ނ̐ݒ菈��
//============================================================
void CWindow::SetType(const int nType)
{
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

		// �����̎�ނ̃e�N�X�`����ݒ�
		for (int nCntWindow = 0; nCntWindow < WINDOW_MAX; nCntWindow++)
		{ // ���Ɏg�p����ǂ̑������J��Ԃ�

			if (m_pWall[nCntWindow] != NULL)
			{ // �g�p���̏ꍇ

				// �ǂ̃e�N�X�`�������蓖��
				m_pWall[nCntWindow]->BindTexture(mc_apTextureFile[nType][nCntWindow]);
			}
			else { assert(false); }	// ��g�p��
		}
	}
	else { assert(false); }	// ��ރI�[�o�[
}

//============================================================
//	��ގ擾����
//============================================================
int CWindow::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//============================================================
//	�g�嗦�̐ݒ菈��
//============================================================
void CWindow::SetScale(const float fScale)
{
	// �����̊g�嗦��ݒ�
	m_fScale = fScale;

	// �傫����ݒ�
	SetVec3Sizing(m_status.size * m_fScale);
}

//============================================================
//	�g�嗦�擾����
//============================================================
float CWindow::GetScale(void) const
{
	// �g�嗦��Ԃ�
	return m_fScale;
}

//============================================================
//	��������
//============================================================
CWindow *CWindow::Create
(
	const EType type,			// ���
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const float fScale			// �g�嗦
)
{
	// �|�C���^��錾
	CWindow *pWindow = NULL;	// �������p

	if (pWindow == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pWindow = new CWindow;	// ��
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pWindow != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// ���̏�����
		if (FAILED(pWindow->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pWindow;
			pWindow = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// ��ނ�ݒ�
		pWindow->SetType(type);

		// �ʒu��ݒ�
		pWindow->SetVec3Position(rPos);

		// ������ݒ�
		pWindow->SetVec3Rotation(rRot);

		// �g�嗦��ݒ�
		pWindow->SetScale(fScale);

		// �m�ۂ����A�h���X��Ԃ�
		return pWindow;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	���Έʒu�̐ݒ菈��
//============================================================
void CWindow::SetPositionRelative(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posNear = VEC3_ZERO;	// ��O�̈ʒu
	D3DXVECTOR3 posFar = VEC3_ZERO;		// ���̈ʒu

	// ���̈ʒu�����߂�
	posFar.x = m_pos.x + sinf(m_rot.y) * m_size.x;
	posFar.y = m_pos.y + m_size.y;
	posFar.z = m_pos.z + cosf(m_rot.y) * m_size.z;

	// ��O�̈ʒu�����߂�
	posNear.x = m_pos.x + sinf(m_rot.y + D3DX_PI) * m_size.x;
	posNear.y = m_pos.y + m_size.y;
	posNear.z = m_pos.z + cosf(m_rot.y + D3DX_PI) * m_size.z;

	// �ϐ��z���錾
	D3DXVECTOR3 aPos[] =	// �ʒu
	{
		posFar,		// ��O
		posFar,		// ��O
		posNear,	// ��
		posNear		// ��
	};

	for (int nCntWindow = 0; nCntWindow < WINDOW_MAX; nCntWindow++)
	{ // ���Ɏg�p����ǂ̑������J��Ԃ�

		// �ϐ���錾
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, m_rot.y + (D3DX_PI * (float)(nCntWindow % 2)), 0.0f);	// ����
		useful::Vec3NormalizeRot(rot);	// �������K��

		if (m_pWall[nCntWindow] != NULL)
		{ // �g�p���̏ꍇ

			// �ǂ̈ʒu��ݒ�
			m_pWall[nCntWindow]->SetVec3Position(aPos[nCntWindow]);

			// �ǂ̌�����ݒ�
			m_pWall[nCntWindow]->SetVec3Rotation(rot);
		}
		else { assert(false); }	// ��g�p��
	}
}

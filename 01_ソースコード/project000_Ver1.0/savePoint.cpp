//============================================================
//
//	�Z�[�u�|�C���g���� [savePoint.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "savePoint.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "collision.h"
#include "scene.h"
#include "player.h"
#include "particle3D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int	PRIORITY		= 4;		// �Z�[�u�|�C���g�̗D�揇��
	const int	CHANGE_MAT_ID	= 4;		// �ύX����}�e���A���̃C���f�b�N�X
	const int	RESET_MAT_CNT	= 45;		// �}�e���A���ύX�̍Đݒ�܂ł̃t���[��
	const float	COL_RADIUS		= 80.0f;	// �����蔻��̔��a
	const float	COL_HEIGHT		= 280.0f;	// �����蔻��̏c��

	// �p�[�e�B�N�����
	namespace particle
	{
		const D3DXCOLOR	COL_HEAL = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);	// �񕜃p�[�e�B�N���̐F
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CSavePoint::mc_apModelFile[] =	// ���f���萔
{
	"data\\MODEL\\SAVEPOINT\\savepoint000.x",	// �Z�[�u�|�C���g���f��
};
CObject *CSavePoint::m_pCurrentSave = NULL;	// ���݂̃Z�[�u�|�C���g�ւ̃|�C���^
int CSavePoint::m_nNumAll = 0;	// �Z�[�u�|�C���g�̑���

//************************************************************
//	�q�N���X [CSavePoint] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSavePoint::CSavePoint() : CObjectModel(CObject::LABEL_SAVEPOINT, PRIORITY), m_nThisSaveID(m_nNumAll)
{
	// �����o�ϐ����N���A
	m_state = STATE_NORMAL;	// ���
	m_nCounterState = 0;	// ��ԊǗ��J�E���^�[

	// �Z�[�u�|�C���g�̑��������Z
	m_nNumAll++;
}

//============================================================
//	�f�X�g���N�^
//============================================================
CSavePoint::~CSavePoint()
{
	// �Z�[�u�|�C���g�̑��������Z
	m_nNumAll--;
}

//============================================================
//	����������
//============================================================
HRESULT CSavePoint::Init(void)
{
	// �����o�ϐ���������
	m_state = STATE_NORMAL;	// ���
	m_nCounterState = 0;	// ��ԊǗ��J�E���^�[

	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f�������蓖��
	BindModel(mc_apModelFile[MODEL_SAVEPOINT]);

	if (m_nThisSaveID == 0)
	{ // ���g�̃Z�[�u�|�C���g����ڂ̏ꍇ

		// ���g�̃Z�[�u�|�C���g��ۑ�
		m_pCurrentSave = (CObject*)this;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSavePoint::Uninit(void)
{
	// �I�u�W�F�N�g���f���̏I��
	CObjectModel::Uninit();

	if (m_pCurrentSave == (CObject*)this)
	{ // ���݂̃Z�[�u�|�C���g�����g�������ꍇ

		// �������������ς݂̃Z�[�u�|�C���g��ݒ�
		m_pCurrentSave = GetSavePoint();
	}
}

//============================================================
//	�X�V����
//============================================================
void CSavePoint::Update(void)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NORMAL:

		// ����

		break;

	case STATE_SAVE:

		if (m_nCounterState < RESET_MAT_CNT)
		{ // �J�E���^�[�����l��菬�����ꍇ

			// �J�E���^�[�����Z
			m_nCounterState++;
		}
		else
		{ // �J�E���^�[�����l�ȏ�̏ꍇ

			// �J�E���^�[��������
			m_nCounterState = 0;

			// �}�e���A�����Đݒ�
			ResetMaterial();
		}

		break;

	default:
		assert(false);
		break;
	}

	// �v���C���[�Ƃ̓����蔻��
	CollisionPlayer();

	// �I�u�W�F�N�g���f���̍X�V
	CObjectModel::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CSavePoint::Draw(void)
{
	// �I�u�W�F�N�g���f���̕`��
	CObjectModel::Draw();
}

//============================================================
//	���g�̃Z�[�u�|�C���g�C���f�b�N�X�擾����
//============================================================
int CSavePoint::GetIndex(void) const
{
	// ���g�̃Z�[�u�|�C���g�C���f�b�N�X��Ԃ�
	return m_nThisSaveID;
}

//============================================================
//	���a�擾����
//============================================================
float CSavePoint::GetRadius(void) const
{
	// ���a��Ԃ�
	return COL_RADIUS;
}

//============================================================
//	��������
//============================================================
CSavePoint *CSavePoint::Create
(
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot		// ����
)
{
	// �|�C���^��錾
	CSavePoint *pSavePoint = NULL;	// �Z�[�u�|�C���g�����p

	if (pSavePoint == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pSavePoint = new CSavePoint;	// �Z�[�u�|�C���g
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pSavePoint != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// �Z�[�u�|�C���g�̏�����
		if (FAILED(pSavePoint->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pSavePoint;
			pSavePoint = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �ʒu��ݒ�
		pSavePoint->SetVec3Position(rPos);

		// ������ݒ�
		pSavePoint->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pSavePoint;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�����擾����
//============================================================
int CSavePoint::GetNumAll(void)
{
	// ������Ԃ�
	return m_nNumAll;
}

//============================================================
//	�Z�[�u�|�C���g�C���f�b�N�X�擾����
//============================================================
int CSavePoint::GetSavePointID(void)
{
	// ���g�̃Z�[�u�|�C���g�C���f�b�N�X��Ԃ�
	return m_pCurrentSave->GetIndex();
}

//============================================================
//	�Z�[�u�|�C���g���擾����
//============================================================
CSavePoint::SInfo CSavePoint::GetSavePointInfo(void)
{
	// �ϐ���錾
	SInfo info = { VEC3_ZERO, VEC3_ZERO };	// �Z�[�u�|�C���g���

	if (m_pCurrentSave != NULL)
	{ // �Z�[�u�|�C���g�����݂���ꍇ

		// �Z�[�u�|�C���g�̏���ݒ�
		info.pos = m_pCurrentSave->GetVec3Position();	// �ʒu
		info.rot = m_pCurrentSave->GetVec3Rotation();	// ����
	}
	else { assert(false); }	// �Z�[�u�|�C���g����

	// �Z�[�u�|�C���g����Ԃ�
	return info;
}

//============================================================
//	�v���C���[�Ƃ̓����蔻��
//============================================================
void CSavePoint::CollisionPlayer(void)
{
	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME
	||  CManager::GetInstance()->GetMode() == CScene::MODE_TUTORIAL)
	{ // �`���[�g���A���E�Q�[�����[�h�̏ꍇ

		// �|�C���^��錾
		CPlayer *pPlayer = CScene::GetPlayer();	// �v���C���[���
		if (pPlayer == NULL)
		{ // �v���C���[�����݂��Ȃ��ꍇ

			// �����𔲂���
			assert(false);
			return;
		}

		// �ϐ���錾
		D3DXVECTOR3 posPlayer = pPlayer->GetVec3Position();	// �v���C���[�ʒu
		D3DXVECTOR3 posSave = GetVec3Position();	// �Z�[�u�ʒu
		float fPlayerRadius = pPlayer->GetRadius();	// �v���C���[���a
		float fPlayerHeight = pPlayer->GetHeight();	// �v���C���[�c��
		bool  bHit = false;	// �����

		if ((CObject*)this != m_pCurrentSave)
		{ // ���݂̃Z�[�u�|�C���g�ƈ�v���Ȃ��ꍇ

			if (posPlayer.y + fPlayerHeight >= posSave.y
			&&  posPlayer.y <= posSave.y + COL_HEIGHT)
			{ // Y���W���͈͓��̏ꍇ

				// �v���C���[�Ƃ̔���
				bHit = collision::Circle2D
				( // ����
					posPlayer,		// ����ʒu
					posSave,		// ����ڕW�ʒu
					fPlayerRadius,	// ���蔼�a
					COL_RADIUS		// ����ڕW���a
				);
				if (bHit)
				{ // �v���C���[��������̏ꍇ

					// �Z�[�u�|�C���g�����g�ɕύX
					m_pCurrentSave = (CObject*)this;

					// �J�E���^�[��������
					m_nCounterState = 0;

					// �Z�[�u��Ԃ�ݒ�
					m_state = STATE_SAVE;

					// �}�e���A���𔭌��΂ɍ����ւ�
					SetMaterial(material::GlowGreen(), CHANGE_MAT_ID);

					// �񕜃p�[�e�B�N���𐶐�
					CParticle3D::Create(CParticle3D::TYPE_HEAL, posSave, particle::COL_HEAL);

					// �T�E���h�̍Đ�
					CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_SAVE);	// �Z�[�u��
				}
			}
		}
	}
}

//============================================================
//	�����ς݃Z�[�u�|�C���g�擾����
//============================================================
CObject *CSavePoint::GetSavePoint(void)
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

				if (pObjCheck->IsDeath() == true)
				{ // �I�u�W�F�N�g���x�����Z�[�u�|�C���g�ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// ���������Z�[�u�|�C���g��Ԃ�
				return pObjCheck;
			}
		}
	}

	// NULL��Ԃ�
	return NULL;
}

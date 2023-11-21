//============================================================
//
//	�e���� [shadow.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "shadow.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "texture.h"
#include "collision.h"
#include "field.h"
#include "stage.h"
#include "building.h"
#include "obstacle.h"

//************************************************************
//	�}�N����`
//************************************************************
#define SHADOW_PRIO	(2)		// �e�̗D�揇��
#define PLUS_POSY	(0.01f)	// ������h�~�p�̏c���W���Z��

#define MAX_DIS_HEIGHT	(200.0f)	// �e�Ɛe�̏c�̋����̍ő�l
#define MAX_PLUS_SIZE	(120.0f)	// �e�̑傫�����Z�ʂ̍ő�l

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CShadow::mc_apTextureFile[] =	// �e�N�X�`���萔
{
	"data\\TEXTURE\\shadow000.jpg",	// �ʏ�e�N�X�`��
};

//************************************************************
//	�q�N���X [CShadow] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CShadow::CShadow(const float fMinAlpha, const float fMaxAlpha) : CObject3D(CObject::LABEL_NONE, SHADOW_PRIO), m_fMinAlpha(fMinAlpha), m_fMaxAlpha(fMaxAlpha)
{
	// �����o�ϐ����N���A
	m_pParentObject = NULL;	// �e�I�u�W�F�N�g
}

//============================================================
//	�f�X�g���N�^
//============================================================
CShadow::~CShadow()
{

}

//============================================================
//	����������
//============================================================
HRESULT CShadow::Init(void)
{
	// �����o�ϐ���������
	m_pParentObject = NULL;	// �e�I�u�W�F�N�g

	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// Z�e�X�g�̐ݒ�
	SetFunc(D3DCMP_LESSEQUAL);

	// Z�o�b�t�@�̎g�p�󋵂̐ݒ�
	SetZEnable(false);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CShadow::Uninit(void)
{
	// �e�I�u�W�F�N�g�̍폜
	DeleteObjectParent();

	// �I�u�W�F�N�g3D�̏I��
	CObject3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CShadow::Update(void)
{
	// �`�����ݒ�
	if (FAILED(SetDrawInfo()))
	{ // �`����̐ݒ�Ɏ��s�����ꍇ

		// �I�u�W�F�N�g�̏I��
		Uninit();

		// �֐��𔲂���
		return;
	}

	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CShadow::Draw(void)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//============================================================
//	��������
//============================================================
CShadow *CShadow::Create
(
	const ETexture texture,		// ���
	const D3DXVECTOR3& rSize,	// �傫��
	CObject *pObject,			// �e�I�u�W�F�N�g
	const float fMinAlpha,		// �����x�̍ŏ��l
	const float fMaxAlpha		// �����x�̍ő�l
)
{
	// �ϐ���錾
	int nTextureID;	// �e�N�X�`���C���f�b�N�X

	// �|�C���^��錾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^
	CShadow *pShadow = NULL;	// �e�����p

	if (pShadow == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pShadow = new CShadow(fMinAlpha, fMaxAlpha);	// �e
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pShadow != NULL)
	{ // �m�ۂɐ������Ă���ꍇ

		// �e�̏�����
		if (FAILED(pShadow->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return NULL;
		}

		// �e�N�X�`����o�^
		nTextureID = pTexture->Regist(mc_apTextureFile[texture]);

		// �e�N�X�`��������
		pShadow->BindTexture(nTextureID);

		// ���̑傫����ݒ�
		pShadow->SetScalingOrigin(rSize);

		// �e�I�u�W�F�N�g��ݒ�
		pShadow->SetParentObject(pObject);

		// �`�����ݒ�
		if (FAILED(pShadow->SetDrawInfo()))
		{ // �`����̐ݒ�Ɏ��s�����ꍇ

			// �������J��
			delete pShadow;
			pShadow = NULL;

			// ���s��Ԃ�
			assert(false);
			return NULL;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pShadow;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	���̑傫���̐ݒ菈��
//============================================================
void CShadow::SetScalingOrigin(const D3DXVECTOR3& rSize)
{
	// �����̑傫������
	m_sizeOrigin = rSize;

	// �傫���̐ݒ�
	CObject3D::SetVec3Sizing(rSize);
}

//============================================================
//	�`����̐ݒ菈��
//============================================================
HRESULT CShadow::SetDrawInfo(void)
{
	if (m_pParentObject != NULL)
	{ // �e�I�u�W�F�N�g���g�p����Ă����ꍇ

		// �ϐ���錾
		D3DXVECTOR3 posParent = m_pParentObject->GetVec3Position();	// �e�I�u�W�F�N�g�ʒu
		D3DXVECTOR3 posShadow  = VEC3_ZERO;	// �e�ʒu
		D3DXVECTOR3 sizeShadow = VEC3_ZERO;	// �e�傫��
		float fDis = 0.0f;		// �e�Ɛe�̋���
		float fAlpha = 0.0f;	// �e�̓����x

		// �`��ʒu�̐ݒ�
		posShadow = SetDrawPosition();

		// �e�Ɛe�̏c���W�̋��������߂�
		fDis = fabsf(posParent.y - posShadow.y);		// �c�̋��������߂�
		useful::LimitNum(fDis, 0.0f, MAX_DIS_HEIGHT);	// �c�̋����𐧌�
		fDis *= 1.0f / MAX_DIS_HEIGHT;					// ������������

		// �e�̑傫�������߂�
		sizeShadow = D3DXVECTOR3(m_sizeOrigin.x + (MAX_PLUS_SIZE * fDis), 0.0f, m_sizeOrigin.z + (MAX_PLUS_SIZE * fDis));

		// ���l�����߂�
		fAlpha = fabsf(fDis - 1.0f);	// ���l��ݒ�
		useful::LimitNum(fAlpha, m_fMinAlpha, m_fMaxAlpha);	// ���l�𐧌�

		// �e�̕`�����ݒ�
		SetVec3Position(posShadow);	// �ʒu
		SetVec3Sizing(sizeShadow);	// �傫��
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha));	// �F

		// ������Ԃ�
		return S_OK;
	}
	else
	{ // �e�I�u�W�F�N�g���g�p����Ă��Ȃ������ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}
}

//============================================================
//	�`��ʒu�̐ݒ菈��
//============================================================
D3DXVECTOR3 CShadow::SetDrawPosition(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posParent = m_pParentObject->GetVec3Position();	// �e�I�u�W�F�N�g�ʒu
	D3DXVECTOR3 posShadow = VEC3_ZERO;	// �e�ʒu
	float fPosHeight = 0.0f;	// �r���̏���W

	// �|�C���^��錾
	CStage *pStage = CScene::GetStage();	// �X�e�[�W�̏��
	if (pStage == NULL)
	{ // �X�e�[�W�����݂��Ȃ��ꍇ

		// �֐��𔲂���
		return VEC3_ZERO;
	}

	// �e�̈ʒu�����߂�
	posShadow = posParent;	// �e�I�u�W�F�N�g�̍��W���

	if (CollisionObstacle(posParent, fPosHeight))
	{ // ��Q���͈͓̔��̏ꍇ

		// ��������Q���̏�ɐݒ�
		posShadow.y = fPosHeight + PLUS_POSY;
	}
	else if (CollisionBuilding(posParent, fPosHeight))
	{ // �r���͈͓̔��̏ꍇ

		// �������r���̏�ɐݒ�
		posShadow.y = fPosHeight + PLUS_POSY;
	}
	else if (pStage->IsFieldPositionRange(posParent))
	{ // �n�ʂ͈͓̔��̏ꍇ

		// ������n�ʂɐݒ�
		posShadow.y = pStage->GetFieldPositionHeight(posParent) + PLUS_POSY;
	}
	else
	{ // �S�Ă͈̔͊O�̏ꍇ

		// �����𐧌��ʒu�ɐݒ�
		posShadow.y = pStage->GetStageLimit().fField + PLUS_POSY;
	}

	// �e�ʒu��Ԃ�
	return posShadow;
}

//============================================================
//	�e�I�u�W�F�N�g�̐ݒ菈��
//============================================================
void CShadow::SetParentObject(CObject *pObject)
{
	// �����̃I�u�W�F�N�g��ݒ�
	m_pParentObject = pObject;
}

//============================================================
//	�e�I�u�W�F�N�g�̍폜����
//============================================================
void CShadow::DeleteObjectParent(void)
{
	// �e�I�u�W�F�N�g��NULL�ɂ���
	m_pParentObject = NULL;
}

//============================================================
//	��Q���Ƃ̓����蔻��
//============================================================
bool CShadow::CollisionObstacle(D3DXVECTOR3& rPos, float& rDrawPos)
{
	// �ϐ���錾
	float fDisPosY = 0.0f;	// �v���C���[�ƃr����Y����
	bool bInitDis = false;	// Y�����̏�������

	// �|�C���^��錾
	CObject *pCurrentObj = NULL;	// ���݂̉e�������I�u�W�F�N�g

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
				D3DXVECTOR3 pos0, pos1, pos2, pos3;	// ���_���W����p
				D3DXVECTOR3 posObs  = VEC3_ZERO;	// ��Q���ʒu
				D3DXVECTOR3 rotObs  = VEC3_ZERO;	// ��Q������
				D3DXVECTOR3 sizeObs = VEC3_ZERO;	// ��Q���傫��
				float fAngle  = 0.0f;	// �Ίp���̊p�x
				float fLength = 0.0f;	// �Ίp���̒���
				bool  bHit = false;		// ������

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_OBSTACLE)
				{ // �I�u�W�F�N�g���x������Q���ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				if (pObjCheck->GetState() != CObstacle::STATE_LAND)
				{ // �����Ԃ����n�ł���ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// ��Q���̏����擾
				posObs  = pObjCheck->GetVec3Position();	// �ʒu
				rotObs  = pObjCheck->GetVec3Rotation();	// ����
				sizeObs = pObjCheck->GetVec3Sizing();	// �傫��
				fAngle  = pObjCheck->GetAngle();		// �Ίp���p�x
				fLength = pObjCheck->GetLength();		// �Ίp������

				// ���_���W���v�Z
				pos0.x = posObs.x + sinf(rotObs.y + (D3DX_PI + fAngle)) * fLength;
				pos0.y = 0.0f;
				pos0.z = posObs.z + cosf(rotObs.y + (D3DX_PI + fAngle)) * fLength;
				pos1.x = posObs.x + sinf(rotObs.y + (D3DX_PI - fAngle)) * fLength;
				pos1.y = 0.0f;
				pos1.z = posObs.z + cosf(rotObs.y + (D3DX_PI - fAngle)) * fLength;
				pos3.x = posObs.x + sinf(rotObs.y - fAngle) * fLength;
				pos3.y = 0.0f;
				pos3.z = posObs.z + cosf(rotObs.y - fAngle) * fLength;
				pos2.x = posObs.x + sinf(rotObs.y + fAngle) * fLength;
				pos2.y = 0.0f;
				pos2.z = posObs.z + cosf(rotObs.y + fAngle) * fLength;

				// ��Q���Ƃ̔���
				bHit = collision::BoxOuterPillar
				( // ����
					pos0,	// �l�p�̊e���_
					pos1,	// �l�p�̊e���_
					pos2,	// �l�p�̊e���_
					pos3,	// �l�p�̊e���_
					rPos	// ����ʒu
				);

				if (bHit)
				{ // �������Ă����ꍇ

					// �ϐ���錾
					float fDis = rPos.y - (posObs.y + sizeObs.y);	// �e�Ə�Q����Y����

					if (fDis >= 0.0f)
					{ // �v���C���[�Ə�Q����Y�������v���X�̏ꍇ

						if (!bInitDis)
						{ // ���������Ă��Ȃ��ꍇ

							// ���݂̋�������
							fDisPosY = fDis;

							// ���݂̉e�������I�u�W�F�N�g����
							pCurrentObj = pObjCheck;

							// �������ς݂ɂ���
							bInitDis = true;
						}
						else
						{ // ���������Ă���ꍇ

							if (fDis < fDisPosY)
							{ // ���߂���Q���̏ꍇ

								// ���݂̋�������
								fDisPosY = fDis;

								// ���݂̉e�������I�u�W�F�N�g����
								pCurrentObj = pObjCheck;
							}
						}
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	if (pCurrentObj != NULL)
	{ // ��Q�����������ꍇ

		// �ϐ���錾
		D3DXVECTOR3 posObs = VEC3_ZERO;		// ��Q���ʒu
		D3DXVECTOR3 sizeObs = VEC3_ZERO;	// ��Q���傫��
		
		// ��Q���̈ʒu���擾
		posObs = pCurrentObj->GetVec3Position();

		// ��Q���̑傫�����擾
		sizeObs = pCurrentObj->GetVec3Sizing();

		// �`��ʒu��ݒ�
		rDrawPos = posObs.y + sizeObs.y;

		// �������Ă��锻���Ԃ�
		return true;
	}
	else
	{ // ��Q�����Ȃ������ꍇ

		// �������Ă��Ȃ������Ԃ�
		return false;
	}
}

//============================================================
//	�r���Ƃ̓����蔻��
//============================================================
bool CShadow::CollisionBuilding(D3DXVECTOR3& rPos, float& rDrawPos)
{
	// �ϐ���錾
	float fDisPosY = 0.0f;	// �v���C���[�ƃr����Y����
	bool bInitDis = false;	// Y�����̏�������

	// �|�C���^��錾
	CObject *pCurrentObj = NULL;	// ���݂̉e�������I�u�W�F�N�g

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
				D3DXVECTOR3 posBuild  = VEC3_ZERO;	// �r���ʒu
				D3DXVECTOR3 sizeBuild = VEC3_ZERO;	// �r���傫��
				bool bHit = false;	// �����

				// �|�C���^��錾
				CObject *pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() != CObject::LABEL_BUILDING)
				{ // �I�u�W�F�N�g���x�����r���ł͂Ȃ��ꍇ

					// ���̃I�u�W�F�N�g�ւ̃|�C���^����
					pObjCheck = pObjectNext;

					// ���̌J��Ԃ��Ɉڍs
					continue;
				}

				// �r���̈ʒu���擾
				posBuild = pObjCheck->GetVec3Position();

				// �r���̑傫�����擾
				sizeBuild = pObjCheck->GetVec3Sizing();

				// �r���Ƃ̓����蔻��
				bHit = collision::Box2D
				( // ����
					rPos,		// ����ʒu
					posBuild,	// ����ڕW�ʒu
					VEC3_ZERO,	// ����T�C�Y(�E�E��E��)
					VEC3_ZERO,	// ����T�C�Y(���E���E�O)
					sizeBuild,	// ����ڕW�T�C�Y(�E�E��E��)
					sizeBuild	// ����ڕW�T�C�Y(���E���E�O)
				);

				if (bHit)
				{ // �������Ă����ꍇ

					// �ϐ���錾
					float fDis = rPos.y - (posBuild.y + (sizeBuild.y * 2.0f));	// �e�ƃr����Y����

					if (fDis >= 0.0f)
					{ // �v���C���[�ƃr����Y�������v���X�̏ꍇ

						if (!bInitDis)
						{ // ���������Ă��Ȃ��ꍇ

							// ���݂̋�������
							fDisPosY = fDis;

							// ���݂̉e�������I�u�W�F�N�g����
							pCurrentObj = pObjCheck;

							// �������ς݂ɂ���
							bInitDis = true;
						}
						else
						{ // ���������Ă���ꍇ

							if (fDis < fDisPosY)
							{ // ���߂��r���̏ꍇ

								// ���݂̋�������
								fDisPosY = fDis;

								// ���݂̉e�������I�u�W�F�N�g����
								pCurrentObj = pObjCheck;
							}
						}
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}

	if (pCurrentObj != NULL)
	{ // �r�����������ꍇ

		// �ϐ���錾
		D3DXVECTOR3 posBuild = VEC3_ZERO;	// �r���ʒu
		D3DXVECTOR3 sizeBuild = VEC3_ZERO;	// �r���傫��
		
		// �r���̈ʒu���擾
		posBuild = pCurrentObj->GetVec3Position();

		// �r���̑傫�����擾
		sizeBuild = pCurrentObj->GetVec3Sizing();

		// �`��ʒu��ݒ�
		rDrawPos = posBuild.y + (sizeBuild.y * 2.0f);

		// �������Ă��锻���Ԃ�
		return true;
	}
	else
	{ // �r�����Ȃ������ꍇ

		// �������Ă��Ȃ������Ԃ�
		return false;
	}
}

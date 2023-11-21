//============================================================
//
//	�X�}�z�}�l�[�W���[���� [phoneManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "phoneManager.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "object2D.h"
#include "anim2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	// �����L���O��{���
	const int PRIORITY = 14;	// �X�}�z�̗D�揇��

	// �t�F�[�h��{���
	namespace fade
	{
		const D3DXCOLOR COL	= XCOL_AWHITE;		// �t�F�[�h�̐F

		const float CHANGE_ALPHA	= 0.01f;	// �t�F�[�h�̃��l�ύX��
		const float STOP_ALPHA		= 0.65f;	// �t�F�[�h�̍ő僿�l
	}

	// �X�}�z��{���
	namespace phone
	{
		const D3DXVECTOR3	POS		= D3DXVECTOR3(SCREEN_CENT.x, 1200.0f, 0.0f);	// �X�}�z�̏����ʒu
		const D3DXVECTOR3	SIZE	= D3DXVECTOR3(394.0f, 653.0f, 0.0f);			// �X�}�z�̑傫��
		const D3DXCOLOR		COL		= XCOL_WHITE;	// �X�}�z�̐F

		const int	CNT_WAIT_SCALE	= 15;				// �X�}�z�g��̑ҋ@�t���[��
		const int	CNT_WAIT_RETURN = 80;				// �X�}�z���܂��̑ҋ@�t���[��
		const float ADD_MOVE_TAKE	= 0.5f;				// �X�}�z���o�����̈ړ���
		const float ADD_MOVE_RETURN	= 0.4f;				// �X�}�z���܂����̈ړ���
		const float STOP_POS_TAKE	= SCREEN_CENT.y;	// �X�}�z�̒�~Y�ʒu
		const float STOP_POS_RETURN	= 1800.0f;			// �X�}�z�̒�~Y�ʒu
		const float SET_SCALE	= 2.5f;					// �X�}�z�̏����g�嗦
		const float ADD_SCALE	= 0.09f;				// �X�}�z�̊g�嗦���Z��
	}

	// ���b�Z�[�W��{���
	namespace message
	{
		const D3DXVECTOR3	POS		= D3DXVECTOR3(0.0f, -250.0f, 0.0f);		// ���b�Z�[�W�̏����ʒu
		const D3DXVECTOR3	SIZE	= D3DXVECTOR3(802.0f, 180.0f, 0.0f);	// ���b�Z�[�W�̑傫��
		const D3DXVECTOR3	SPACE	= D3DXVECTOR3(0.0f, 200.0f, 0.0f);		// ���b�Z�[�W�̋�

		const POSGRID2	TEX_PART	= POSGRID2(1, NUM_MESSAGE);	// ���b�Z�[�W�̃e�N�X�`��������

		const int INIT_CNT	= 40;	// ���b�Z�[�W�\���̑ҋ@�t���[���̏����l
		const int CNT_DISP	= 80;	// ���b�Z�[�W�\���̑ҋ@�t���[��
	}

	// ������{���
	namespace stress
	{
		const D3DXVECTOR3	POS = D3DXVECTOR3(220.0f, (float)SCREEN_HEIGHT - 220.0f, 0.0f);	// �����̏����ʒu
		const D3DXVECTOR3	ROT = D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(-45.0f));	// �����̏�������
		const D3DXVECTOR3	SIZE = D3DXVECTOR3(660.0f, 660.0f, 0.0f);	// �����̑傫��
		const D3DXCOLOR		COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.85f);	// �����̐F

		const float CHANGE_ALPHA = 0.025f;	// �����̃��l�ύX��
	}

	// �\���{���
	namespace face
	{
		const D3DXVECTOR3	POS = D3DXVECTOR3(150.0f, (float)SCREEN_HEIGHT - 150.0f, 0.0f);	// �\��̈ʒu
		const D3DXVECTOR3	SIZE = D3DXVECTOR3(320.0f, 320.0f, 0.0f);	// �\��̑傫��

		const int	CNT_WAIT_SCALE = 55;	// �\��g��̑ҋ@�t���[��
		const float	SET_SCALE = 0.0f;		// �\��̏����g�嗦
		const float	ADD_SCALE = 0.1f;		// �\��̊g�嗦���Z��
		const float CHANGE_ALPHA = 0.025f;	// �\��̃��l�ύX��
	}

	// ���o��{���
	namespace staging
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(-420.0f, 620.0f, 0.0f);	// ���o�̈ʒu
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(823.0f, 200.0f, 0.0f);	// ���o�̑傫��

		const int	CNT_WAIT_END = 95;	// �I���̑ҋ@�t���[��
		const float	MOVE_POS = 82.0f;	// �ړ���
		const float	STOP_POS = 450.0f;	// ��~�ʒu
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
const char *CPhoneManager::mc_apTextureFile[] =	// �e�N�X�`���萔
{
	"data\\TEXTURE\\phone000.png",	// �X�}�z�̃e�N�X�`��
	"data\\TEXTURE\\stress000.png",	// �����̃e�N�X�`��
};
const char *CPhoneManager::mc_apMessageTextureFile[] =	// ���b�Z�[�W�e�N�X�`���萔
{
	"data\\TEXTURE\\message000.png",	// �J�n���̃��b�Z�[�W�e�N�X�`��
	"data\\TEXTURE\\message001.png",	// �I�����̃��b�Z�[�W�e�N�X�`��
};
const char *CPhoneManager::mc_apFaceTextureFile[] =	// �\��e�N�X�`���萔
{
	"data\\TEXTURE\\face000.png",	// �J�n���̕\��e�N�X�`��
	"data\\TEXTURE\\face001.png",	// �I�����̕\��e�N�X�`��
};
const char *CPhoneManager::mc_apStagingTextureFile[] =	// ���o�e�N�X�`���萔
{
	"data\\TEXTURE\\staging000.png",	// �J�n���̉��o�e�N�X�`��
	"data\\TEXTURE\\staging001.png",	// �I�����̉��o�e�N�X�`��
};

//************************************************************
//	�e�N���X [CPhoneManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPhoneManager::CPhoneManager()
{
	// �����o�ϐ����N���A
	memset(&m_apMessage[0], 0, sizeof(m_apMessage));	// ���b�Z�[�W�̏��
	m_pStaging	= NULL;			// ���o�̏��
	m_pFace		= NULL;			// �\��̏��
	m_pStress	= NULL;			// �����̏��
	m_pPhone	= NULL;			// �X�}�z�̏��
	m_pFade		= NULL;			// �t�F�[�h�̏��
	m_state		= STATE_NONE;	// ���
	m_fMove		= 0.0f;			// �X�}�z�̈ړ���
	m_fScale	= 0.0f;			// �X�}�z�̊g�嗦
	m_bDisp		= false;		// �\����
	m_nCounterState	= 0;		// ��ԊǗ��J�E���^�[
	m_nCounterDisp = 0;			// �\���Ǘ��J�E���^�[
}

//============================================================
//	�f�X�g���N�^
//============================================================
CPhoneManager::~CPhoneManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPhoneManager::Init(void)
{
	// �����o�ϐ���������
	memset(&m_apMessage[0], 0, sizeof(m_apMessage));	// ���b�Z�[�W�̏��
	m_pStaging	= NULL;			// ���o�̏��
	m_pFace		= NULL;			// �\��̏��
	m_pStress	= NULL;			// �����̏��
	m_pPhone	= NULL;			// �X�}�z�̏��
	m_pFade		= NULL;			// �t�F�[�h�̏��
	m_state		= STATE_NONE;	// ���
	m_fMove		= 0.0f;			// �X�}�z�̈ړ���
	m_fScale	= 1.0f;			// �X�}�z�̊g�嗦
	m_bDisp		= false;		// �\����
	m_nCounterState	= 0;		// ��ԊǗ��J�E���^�[
	m_nCounterDisp = 0;			// �\���Ǘ��J�E���^�[

	//--------------------------------------------------------
	//	�t�F�[�h�̐����E�ݒ�
	//--------------------------------------------------------
	// �t�F�[�h�̐���
	m_pFade = CObject2D::Create
	( // ����
		SCREEN_CENT,	// �ʒu
		SCREEN_SIZE,	// �傫��
		VEC3_ZERO,		// ����
		fade::COL		// �F
	);
	if (m_pFade == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFade->SetPriority(PRIORITY);

	// �����`���OFF�ɐݒ�
	m_pFade->SetEnableDraw(false);

	//--------------------------------------------------------
	//	�X�}�z�̐����E�ݒ�
	//--------------------------------------------------------
	// �X�}�z�̐���
	m_pPhone = CObject2D::Create
	( // ����
		SCREEN_CENT,	// �ʒu
		phone::SIZE,	// �傫��
		VEC3_ZERO,		// ����
		phone::COL		// �F
	);
	if (m_pPhone == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pPhone->BindTexture(mc_apTextureFile[TEXTURE_PHONE]);

	// �D�揇�ʂ�ݒ�
	m_pPhone->SetPriority(PRIORITY);

	// �����`���OFF�ɐݒ�
	m_pPhone->SetEnableDraw(false);

	//--------------------------------------------------------
	//	���b�Z�[�W�̐����E�ݒ�
	//--------------------------------------------------------
	for (int nCntPhone = 0; nCntPhone < NUM_MESSAGE; nCntPhone++)
	{ // ��M���b�Z�[�W�����J��Ԃ�

		// ���b�Z�[�W�̐���
		m_apMessage[nCntPhone] = CAnim2D::Create
		( // ����
			message::TEX_PART.x,								// ��������
			message::TEX_PART.y,								// �c������
			message::POS + (message::SPACE * (float)nCntPhone),	// �ʒu
			message::SIZE										// �傫��
		);
		if (m_apMessage[nCntPhone] == NULL)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}

		// �D�揇�ʂ�ݒ�
		m_apMessage[nCntPhone]->SetPriority(PRIORITY);

		// �����`���OFF�ɐݒ�
		m_apMessage[nCntPhone]->SetEnableDraw(false);

		// �p�^�[����ݒ�
		m_apMessage[nCntPhone]->SetPattern(nCntPhone);
	}

	//--------------------------------------------------------
	//	�����̐����E�ݒ�
	//--------------------------------------------------------
	// �����̐���
	m_pStress = CObject2D::Create
	( // ����
		stress::POS,					// �ʒu
		stress::SIZE * face::SET_SCALE,	// �傫��
		stress::ROT,					// ����
		stress::COL						// �F
	);
	if (m_pStress == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pStress->BindTexture(mc_apTextureFile[TEXTURE_STRESS]);

	// �D�揇�ʂ�ݒ�
	m_pStress->SetPriority(PRIORITY);

	// �����`���OFF�ɐݒ�
	m_pStress->SetEnableDraw(false);

	//--------------------------------------------------------
	//	�\��̐����E�ݒ�
	//--------------------------------------------------------
	// �\��̐���
	m_pFace = CObject2D::Create
	( // ����
		face::POS,	// �ʒu
		face::SIZE * face::SET_SCALE	// �傫��
	);
	if (m_pFace == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pFace->SetPriority(PRIORITY);

	// �����`���OFF�ɐݒ�
	m_pFace->SetEnableDraw(false);

	//--------------------------------------------------------
	//	���o�̐����E�ݒ�
	//--------------------------------------------------------
	// ���o�̐���
	m_pStaging = CObject2D::Create
	( // ����
		staging::POS,	// �ʒu
		staging::SIZE	// �傫��
	);
	if (m_pStaging == NULL)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �D�揇�ʂ�ݒ�
	m_pStaging->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CPhoneManager::Uninit(void)
{
	for (int nCntPhone = 0; nCntPhone < NUM_MESSAGE; nCntPhone++)
	{ // ��M���b�Z�[�W�����J��Ԃ�

		// ���b�Z�[�W�̏I��
		m_apMessage[nCntPhone]->Uninit();
	}

	// ���o�̏I��
	m_pStaging->Uninit();

	// �\��̏I��
	m_pFace->Uninit();

	// �����̏I��
	m_pStress->Uninit();

	// �X�}�z�̏I��
	m_pPhone->Uninit();

	// �t�F�[�h�̏I��
	m_pFade->Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CPhoneManager::Update(void)
{
	// �X�}�z���o�X�L�b�v
	SkipPhoneStaging();

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:	// �������Ȃ����

		// ����

		break;

	case STATE_FADEIN:	// �t�F�[�h�C�����

		// �t�F�[�h�C���̍X�V
		UpdateFade();

		break;

	case STATE_PHONE_TAKE:	// �X�}�z�̎��o�����

		// �X�}�z��o�̍X�V
		UpdatePhoneTake();

		// �����𔲂���
		break;

	case STATE_PHONE_SCALE_WAIT:	// �X�}�z�̊g��ҋ@���

		if (UpdateDispWait(phone::CNT_WAIT_SCALE))
		{ // �ҋ@���������ꍇ

			// �g�嗦��������
			m_fScale = 1.0f;

			// �X�}�z�̊g���Ԃ�ݒ�
			m_state = STATE_PHONE_SCALE;
		}

		break;

	case STATE_PHONE_SCALE:	// �X�}�z�̊g����

		// �X�}�z�g��̍X�V
		UpdatePhoneScale();

		break;

	case STATE_MESSAGE:	// ���b�Z�[�W��M���

		// ���b�Z�[�W��M�̍X�V
		UpdateMessage();

		break;

	case STATE_FACE_WAIT:	// �\��̊g��ҋ@���

		if (UpdateDispWait(face::CNT_WAIT_SCALE))
		{ // �ҋ@���������ꍇ

			// �g�嗦��ݒ�
			m_fScale = face::SET_SCALE;

			// �����`���ON�ɐݒ�
			m_pStress->SetEnableDraw(true);
			m_pFace->SetEnableDraw(true);

			// �\��̊g���Ԃ�ݒ�
			m_state = STATE_FACE;
		}

		break;

	case STATE_FACE:	// �\��̊g����

		// �\��g��̍X�V
		UpdateFace();

		break;

	case STATE_PHONE_RETURN_WAIT:	// �X�}�z�̂��܂��ҋ@���

		if (UpdateDispWait(phone::CNT_WAIT_RETURN))
		{ // �ҋ@���������ꍇ

			// �X�}�z�̂��܂���Ԃ�ݒ�
			m_state = STATE_PHONE_RETURN;
		}

		break;

	case STATE_PHONE_RETURN:	// �X�}�z�̂��܂����

		// �X�}�z���[�̍X�V
		UpdatePhoneReturn();

		break;

	case STATE_STAGING:	// ���o�̕\�����

		// ���o�\���̍X�V
		UpdateStaging();

		break;

	case STATE_END_WAIT:	// �I���ҋ@���

		if (UpdateDispWait(staging::CNT_WAIT_END))
		{ // �ҋ@���������ꍇ

			// �I����Ԃ�ݒ�
			m_state = STATE_END;

			// ���o�̎����`���OFF�ɂ���
			m_pStaging->SetEnableDraw(false);

			// �\����OFF�ɂ���
			SetEnableDisp(false);
		}

		break;

	case STATE_END:	// �I�����

		// ����

		break;

	default:	// ��O����
		assert(false);
		break;
	}

	for (int nCntPhone = 0; nCntPhone < NUM_MESSAGE; nCntPhone++)
	{ // ��M���b�Z�[�W�����J��Ԃ�

		// ���b�Z�[�W�̍X�V
		m_apMessage[nCntPhone]->Update();
	}

	// ���o�̍X�V
	m_pStaging->Update();

	// �\��̍X�V
	m_pFace->Update();

	// �����̍X�V
	m_pStress->Update();

	// �X�}�z�̍X�V
	m_pPhone->Update();

	// �t�F�[�h�̍X�V
	m_pFade->Update();

	// ���b�Z�[�W���Έʒu�̐ݒ�
	SetPositionRelative();
}

//============================================================
//	�X�}�z�\���̊J�n����
//============================================================
void CPhoneManager::SetLook(const EType type)
{
	//--------------------------------------------------------
	//	�e�N�X�`���̐ݒ�
	//--------------------------------------------------------
	for (int nCntPhone = 0; nCntPhone < NUM_MESSAGE; nCntPhone++)
	{ // ��M���b�Z�[�W�����J��Ԃ�

		// ���b�Z�[�W�̃e�N�X�`����o�^�E����
		m_apMessage[nCntPhone]->BindTexture(mc_apMessageTextureFile[type]);
	}

	// �\��̃e�N�X�`����o�^�E����
	m_pFace->BindTexture(mc_apFaceTextureFile[type]);

	// ���o�̃e�N�X�`����o�^�E����
	m_pStaging->BindTexture(mc_apStagingTextureFile[type]);

	//--------------------------------------------------------
	//	���̏�����
	//--------------------------------------------------------
	// ���b�Z�[�W�̎����`���OFF�ɐݒ�
	for (int nCntPhone = 0; nCntPhone < NUM_MESSAGE; nCntPhone++)
	{ // ��M���b�Z�[�W�����J��Ԃ�

		m_apMessage[nCntPhone]->SetEnableDraw(false);
	}

	// ���o�̎����`���ON�ɂ���
	m_pStaging->SetEnableDraw(true);

	// ���o�̈ʒu��������
	m_pStaging->SetVec3Position(staging::POS);

	// �X�}�z�̈ʒu�E�傫����������
	m_pPhone->SetVec3Position(phone::POS);
	m_pPhone->SetVec3Sizing(phone::SIZE);

	// �|���S���̑傫����������
	m_pStress->SetVec3Sizing(stress::SIZE * face::SET_SCALE);	// ����
	m_pFace->SetVec3Sizing(face::SIZE * face::SET_SCALE);		// �\��

	// �|���S���̐F��������
	m_pPhone->SetColor(phone::COL);		// �X�}�z
	m_pFade->SetColor(fade::COL);		// �t�F�[�h
	m_pStress->SetColor(stress::COL);	// ����
	m_pFace->SetColor(XCOL_WHITE);		// �\��

	// ����������
	m_fScale = 1.0f;		// �g�嗦
	m_fMove = 0.0f;			// �X�}�z�̈ړ���
	m_nCounterState = 0;	// ��ԊǗ��J�E���^�[
	m_nCounterDisp = 0;		// �\���Ǘ��J�E���^�[

	// �\����ON�ɂ���
	SetEnableDisp(true);

	// ��Ԃ�ݒ�
	m_state = STATE_FADEIN;	// �t�F�[�h�C�����
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CPhoneManager::SetState(const EState state)
{
	// �����̏�Ԃ�ݒ�
	m_state = state;
}

//============================================================
//	��Ԏ擾����
//============================================================
CPhoneManager::EState CPhoneManager::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	�\���̐ݒ菈��
//============================================================
void CPhoneManager::SetEnableDisp(const bool bDisp)
{
	// �����̕\���󋵂�ݒ�
	m_bDisp = bDisp;

	// �`��󋵂�\���󋵂ƈ�v������
	m_pFade->SetEnableDraw(bDisp);
	m_pPhone->SetEnableDraw(bDisp);
	m_pStress->SetEnableDraw(bDisp);
	m_pFace->SetEnableDraw(bDisp);

	// ���b�Z�[�W�̎����`���OFF�ɐݒ�
	for (int nCntPhone = 0; nCntPhone < NUM_MESSAGE; nCntPhone++)
	{ // ��M���b�Z�[�W�����J��Ԃ�

		m_apMessage[nCntPhone]->SetEnableDraw(false);
	}
}

//============================================================
//	�\���擾����
//============================================================
bool CPhoneManager::IsDisp(void) const
{
	// �\���󋵂�Ԃ�
	return m_bDisp;
}

//============================================================
//	��������
//============================================================
CPhoneManager *CPhoneManager::Create(void)
{
	// �|�C���^��錾
	CPhoneManager *pPhoneManager = NULL;	// �X�}�z�}�l�[�W���[�����p

	if (pPhoneManager == NULL)
	{ // �g�p����Ă��Ȃ��ꍇ

		// �������m��
		pPhoneManager = new CPhoneManager;	// �X�}�z�}�l�[�W���[
	}
	else { assert(false); return NULL; }	// �g�p��

	if (pPhoneManager != NULL)
	{ // �g�p����Ă���ꍇ
		
		// �X�}�z�}�l�[�W���[�̏�����
		if (FAILED(pPhoneManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �������J��
			delete pPhoneManager;
			pPhoneManager = NULL;

			// ���s��Ԃ�
			return NULL;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pPhoneManager;
	}
	else { assert(false); return NULL; }	// �m�ێ��s
}

//============================================================
//	�j������
//============================================================
HRESULT CPhoneManager::Release(CPhoneManager *&prPhoneManager)
{
	if (prPhoneManager != NULL)
	{ // �g�p���̏ꍇ

		// �X�}�z�}�l�[�W���[�̏I��
		prPhoneManager->Uninit();

		// �������J��
		delete prPhoneManager;
		prPhoneManager = NULL;

		// ������Ԃ�
		return S_OK;
	}
	else { assert(false); return E_FAIL; }	// ��g�p��
}

//============================================================
//	�t�F�[�h�C���̍X�V����
//============================================================
void CPhoneManager::UpdateFade(void)
{
	// �ϐ���錾
	D3DXCOLOR colFade = m_pFade->GetColor();	// �t�F�[�h�̐F

	// �t�F�[�h�̃��l�����Z
	colFade.a += fade::CHANGE_ALPHA;
	
	if (colFade.a >= fade::STOP_ALPHA)
	{ // �t�F�[�h�̃��l�����l�ȏ�̏ꍇ

		// �t�F�[�h�̃��l��␳
		colFade.a = fade::STOP_ALPHA;

		// �X�}�z�̎��o����Ԃɂ���
		m_state = STATE_PHONE_TAKE;

		// �T�E���h�̍Đ�
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_VIBRATION);	// �X�}�z�o�C�u��
	}

	// �t�F�[�h�̐F�𔽉f
	m_pFade->SetColor(colFade);
}

//============================================================
//	�X�}�z��o�̍X�V����
//============================================================
void CPhoneManager::UpdatePhoneTake(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posPhone = m_pPhone->GetVec3Position();	// �X�}�z�̈ʒu

	// �X�}�z�̈ʒu���Z�ʂ����Z
	m_fMove += phone::ADD_MOVE_TAKE;

	// �X�}�z�̈ʒu�����Z
	posPhone.y -= m_fMove;

	if (posPhone.y <= phone::STOP_POS_TAKE)
	{ // �X�}�z�̈ʒu�����l�ȉ��̏ꍇ

		// �X�}�z�̈ʒu��␳
		posPhone.y = phone::STOP_POS_TAKE;

		// �X�}�z�̈ړ��ʂ�������
		m_fMove = 0.0f;

		// �X�}�z�̊g��ҋ@��Ԃ�ݒ�
		m_state = STATE_PHONE_SCALE_WAIT;
	}

	// �X�}�z�̈ʒu�𔽉f
	m_pPhone->SetVec3Position(posPhone);
}

//============================================================
//	�X�}�z�g��̍X�V����
//============================================================
void CPhoneManager::UpdatePhoneScale(void)
{
	// �g�嗦�����Z
	m_fScale += phone::ADD_SCALE;

	// �X�}�z�̑傫����ݒ�
	m_pPhone->SetVec3Sizing(phone::SIZE * m_fScale);

	if (m_fScale >= phone::SET_SCALE)
	{ // �g�嗦���ő�l�ȏ�̏ꍇ

		// �g�嗦��␳
		m_fScale = 1.0f;

		// �X�}�z�̑傫����␳
		m_pPhone->SetVec3Sizing(phone::SIZE * phone::SET_SCALE);

		// �J�E���^�[��ݒ�
		m_nCounterState = message::INIT_CNT;

		// ���b�Z�[�W��M��Ԃ�ݒ�
		m_state = STATE_MESSAGE;
	}
}

//============================================================
//	���b�Z�[�W��M�̍X�V����
//============================================================
void CPhoneManager::UpdateMessage(void)
{
	// ��ԊǗ��J�E���^�[�����Z
	m_nCounterState++;

	if (m_nCounterState >= message::CNT_DISP)
	{ // �J�E���^�[�����l�ȏ�̏ꍇ

		// ��ԊǗ��J�E���^�[��������
		m_nCounterState = 0;

		// ���b�Z�[�W��\��
		m_apMessage[m_nCounterDisp]->SetEnableDraw(true);

		// �T�E���h�̍Đ�
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_MESSAGE);	// ���b�Z�[�W��

		// �\���Ǘ��J�E���^�[�����Z
		m_nCounterDisp++;

		if (m_nCounterDisp >= NUM_MESSAGE)
		{ // ���ׂẴ��b�Z�[�W��\�������ꍇ

			// �\���Ǘ��J�E���^�[��������
			m_nCounterDisp = 0;

			// �\��̊g��ҋ@��Ԃ�ݒ�
			m_state = STATE_FACE_WAIT;
		}
	}
}

//============================================================
//	�\��g��̍X�V����
//============================================================
void CPhoneManager::UpdateFace(void)
{
	// �g�嗦�����Z
	m_fScale += face::ADD_SCALE;

	// �傫����ݒ�
	m_pFace->SetVec3Sizing(face::SIZE * m_fScale);		// �\��
	m_pStress->SetVec3Sizing(face::SIZE * m_fScale);	// ����

	if (m_fScale >= 1.0f)
	{ // �g�嗦���ő�l�ȏ�̏ꍇ

		// �g�嗦��␳
		m_fScale = 1.0f;

		// �傫����␳
		m_pFace->SetVec3Sizing(face::SIZE);		// �\��
		m_pStress->SetVec3Sizing(face::SIZE);	// ����

		// �X�}�z�̂��܂��ҋ@��Ԃ�ݒ�
		m_state = STATE_PHONE_RETURN_WAIT;

		// �T�E���h�̍Đ�
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_STICK);	// ��������
	}
}

//============================================================
//	�X�}�z���[�̍X�V����
//============================================================
void CPhoneManager::UpdatePhoneReturn(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posPhone = m_pPhone->GetVec3Position();	// ��Ⳃ̈ʒu
	D3DXCOLOR colFade = m_pFade->GetColor();			// �t�F�[�h�̐F
	D3DXCOLOR colFace = m_pFace->GetColor();			// �\��̐F
	D3DXCOLOR colStress = m_pStress->GetColor();		// �����̐F

	//--------------------------------------------------------
	//	�t�F�[�h�̓�����
	//--------------------------------------------------------
	if (colFade.a > 0.0f)
	{ // �t�F�[�h�̃��l�����l���傫���ꍇ

		// �t�F�[�h�̃��l�����Z
		colFade.a -= fade::CHANGE_ALPHA;

		if (colFade.a <= 0.0f)
		{ // �t�F�[�h�̃��l�����l�ȉ��̏ꍇ

			// �t�F�[�h�̃��l��␳
			colFade.a = 0.0f;
		}

		// �t�F�[�h�̐F�𔽉f
		m_pFade->SetColor(colFade);
	}

	//--------------------------------------------------------
	//	�\��̓�����
	//--------------------------------------------------------
	if (colFace.a > 0.0f)
	{ // �\��̃��l�����l���傫���ꍇ

		// �\��̃��l�����Z
		colFace.a -= face::CHANGE_ALPHA;

		if (colFace.a <= 0.0f)
		{ // �\��̃��l�����l�ȉ��̏ꍇ

			// �\��̃��l��␳
			colFace.a = 0.0f;
		}

		// �\��̐F�𔽉f
		m_pFace->SetColor(colFace);
	}

	//--------------------------------------------------------
	//	�����̓�����
	//--------------------------------------------------------
	if (colStress.a > 0.0f)
	{ // �����̃��l�����l���傫���ꍇ

		// �����̃��l�����Z
		colStress.a -= stress::CHANGE_ALPHA;

		if (colStress.a <= 0.0f)
		{ // �����̃��l�����l�ȉ��̏ꍇ

			// �����̃��l��␳
			colStress.a = 0.0f;
		}

		// �����̐F�𔽉f
		m_pStress->SetColor(colStress);
	}

	//--------------------------------------------------------
	//	�X�}�z�̈ړ�
	//--------------------------------------------------------
	if (posPhone.y < phone::STOP_POS_RETURN)
	{ // �X�}�z�̈ʒu�����l��菬�����ꍇ

		// �X�}�z�̈ړ��ʂ����Z
		m_fMove += phone::ADD_MOVE_RETURN;

		// �X�}�z�̈ʒu�����Z
		posPhone.y += m_fMove;
	}
	else if (posPhone.y >= phone::STOP_POS_RETURN)
	{ // �X�}�z�̈ʒu�����l�ȏ�̏ꍇ

		// �X�}�z�̈ʒu��␳
		posPhone.y = phone::STOP_POS_RETURN;

		// �X�}�z�̈ړ��ʂ�������
		m_fMove = 0.0f;

		if (colFade.a <= 0.0f
		&&  colFace.a <= 0.0f
		&&  colStress.a <= 0.0f)
		{ // ���l��������؂��Ă���ꍇ

			// ���o�̕\����Ԃ�ݒ�
			m_state = STATE_STAGING;

			// �\����OFF�ɂ���
			SetEnableDisp(false);
		}
	}

	// �X�}�z�̈ʒu�𔽉f
	m_pPhone->SetVec3Position(posPhone);
}

//============================================================
//	���o�\���̍X�V����
//============================================================
void CPhoneManager::UpdateStaging(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posStaging = m_pStaging->GetVec3Position();	// ���o�ʒu

	// ���ʒu���E�Ɉړ�
	posStaging.x += staging::MOVE_POS;

	if (posStaging.x > staging::STOP_POS)
	{ // �ʒu����~�ʒu�𒴂����ꍇ

		// ��~�ʒu�ɕ␳
		posStaging.x = staging::STOP_POS;

		// �I���ҋ@��Ԃ�ݒ�
		m_state = STATE_END_WAIT;

		// �T�E���h�̍Đ�
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DECISION_001);	// ���艹01
	}

	// ���o�ʒu�𔽉f
	m_pStaging->SetVec3Position(posStaging);
}

//============================================================
//	�X�}�z���o�X�L�b�v����
//============================================================
void CPhoneManager::SkipPhoneStaging(void)
{
	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= CManager::GetInstance()->GetKeyboard();	// �L�[�{�[�h
	CInputPad		*pPad		= CManager::GetInstance()->GetPad();		// �p�b�h

	if (pKeyboard->IsTrigger(DIK_RETURN)  || pKeyboard->IsTrigger(DIK_SPACE)
	||  pPad->IsTrigger(CInputPad::KEY_A) || pPad->IsTrigger(CInputPad::KEY_B)
	||  pPad->IsTrigger(CInputPad::KEY_X) || pPad->IsTrigger(CInputPad::KEY_Y))
	{
		if (m_state != STATE_END && m_state != STATE_END_WAIT && m_state != STATE_STAGING)
		{ // �X�L�b�v�ȍ~�̏�Ԃł͂Ȃ��ꍇ

			// ���o�̕\����Ԃ�ݒ�
			m_state = STATE_STAGING;

			// �\����OFF�ɂ���
			SetEnableDisp(false);
		}
	}
}

//============================================================
//	���b�Z�[�W���Έʒu�̐ݒ菈��
//============================================================
void CPhoneManager::SetPositionRelative(void)
{
	// �ϐ���錾
	D3DXVECTOR3 posPhone = m_pPhone->GetVec3Position();	// �X�}�z�ʒu

	for (int nCntPhone = 0; nCntPhone < NUM_MESSAGE; nCntPhone++)
	{ // ��M���b�Z�[�W�����J��Ԃ�

		// ���b�Z�[�W�̈ʒu��ݒ�
		m_apMessage[nCntPhone]->SetVec3Position(posPhone + message::POS + (message::SPACE * (float)nCntPhone));
	}
}

//============================================================
//	�\���ҋ@����
//============================================================
bool CPhoneManager::UpdateDispWait(const int nWait)
{
	if (m_nCounterState < nWait)
	{ // �J�E���^�[���ҋ@�J�E���g�܂ŒB���Ă��Ȃ��ꍇ

		// �J�E���^�[�����Z
		m_nCounterState++;

		// �ҋ@��������Ԃ�
		return false;
	}
	else
	{ // �J�E���^�[���ҋ@���������ꍇ

		// �J�E���^�[��������
		m_nCounterState = 0;

		// �ҋ@������Ԃ�
		return true;
	}
}

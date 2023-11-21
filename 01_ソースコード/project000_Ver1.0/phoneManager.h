//============================================================
//
//	�X�}�z�}�l�[�W���[�w�b�_�[ [phoneManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PHONE_MANAGER_H_
#define _PHONE_MANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"

//************************************************************
//	�}�N����`
//************************************************************
#define NUM_MESSAGE	(3)	// ��M���b�Z�[�W��

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X
class CAnim2D;		// �A�j���[�V����2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �X�}�z�}�l�[�W���[�N���X
class CPhoneManager
{
public:
	// �e�N�X�`����
	enum ETexture
	{
		TEXTURE_PHONE = 0,	// �X�}�z�̃e�N�X�`��
		TEXTURE_STRESS,		// �����̃e�N�X�`��
		TEXTURE_MAX			// ���̗񋓌^�̑���
	};

	// ��ޗ�
	enum EType
	{
		TYPE_START = 0,	// �J�n
		TYPE_END,		// �I��
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,				// �������Ȃ����
		STATE_FADEIN,				// �t�F�[�h�C�����
		STATE_PHONE_TAKE,			// �X�}�z�̎��o�����
		STATE_PHONE_SCALE_WAIT,		// �X�}�z�̊g��ҋ@���
		STATE_PHONE_SCALE,			// �X�}�z�̊g����
		STATE_MESSAGE,				// ���b�Z�[�W��M���
		STATE_FACE_WAIT,			// �\��̊g��ҋ@���
		STATE_FACE,					// �\��̊g����
		STATE_PHONE_RETURN_WAIT,	// �X�}�z�̂��܂��ҋ@���
		STATE_PHONE_RETURN,			// �X�}�z�̂��܂����
		STATE_STAGING,				// ���o�̕\�����
		STATE_END_WAIT,				// �I���ҋ@���
		STATE_END,					// �I�����
		STATE_MAX					// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CPhoneManager();

	// �f�X�g���N�^
	~CPhoneManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void SetLook(const EType type);			// �X�}�z�\���J�n
	void SetState(const EState state);		// ��Ԑݒ�
	EState GetState(void) const;			// ��Ԏ擾
	void SetEnableDisp(const bool bDisp);	// �\���ݒ�
	bool IsDisp(void) const;				// �\���擾

	// �ÓI�����o�֐�
	static CPhoneManager *Create(void);	// ����
	static HRESULT Release(CPhoneManager *&prPhoneManager);	// �j��

private:
	// �����o�֐�
	void UpdateFade(void);			// �t�F�[�h�C��
	void UpdatePhoneTake(void);		// �X�}�z��o
	void UpdatePhoneScale(void);	// �X�}�z�g��
	void UpdateMessage(void);		// ���b�Z�[�W��M
	void UpdateFace(void);			// �\��g��
	void UpdatePhoneReturn(void);	// �X�}�z���[
	void UpdateStaging(void);		// ���o�\��
	void SkipPhoneStaging(void);	// �X�}�z���o�X�L�b�v
	void SetPositionRelative(void);	// ���b�Z�[�W���Έʒu�ݒ�
	bool UpdateDispWait(const int nWait);	// �\���ҋ@

	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[];			// �e�N�X�`���萔
	static const char *mc_apMessageTextureFile[];	// ���b�Z�[�W�e�N�X�`���萔
	static const char *mc_apFaceTextureFile[];		// �\��e�N�X�`���萔
	static const char *mc_apStagingTextureFile[];	// ���o�e�N�X�`���萔

	// �����o�ϐ�
	CAnim2D *m_apMessage[NUM_MESSAGE];	// ���b�Z�[�W�̏��
	CObject2D *m_pStaging;	// ���o�̏��
	CObject2D *m_pFace;		// �\��̏��
	CObject2D *m_pStress;	// �����̏��
	CObject2D *m_pPhone;	// �X�}�z�̏��
	CObject2D *m_pFade;		// �t�F�[�h�̏��
	EState m_state;			// ���
	int m_nCounterState;	// ��ԊǗ��J�E���^�[
	int m_nCounterDisp;		// �\���Ǘ��J�E���^�[
	float m_fMove;			// �X�}�z�̈ړ���
	float m_fScale;			// �X�}�z�̊g�嗦
	bool m_bDisp;			// �\����
};

#endif	// _PHONE_MANAGER_H_

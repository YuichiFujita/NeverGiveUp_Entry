//============================================================
//
//	���w�b�_�[ [window.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _WINDOW_H_
#define _WINDOW_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "object.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject3D;	// �I�u�W�F�N�g3D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// ���N���X
class CWindow : public CObject
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_NORMAL = 0,	// �ʏ�r�����e�N�X�`��
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// ����
	enum EWindow
	{
		WINDOW_NEAR_FRONT = 0,	// ��O�E�\�̕�
		WINDOW_NEAR_BACK,		// ��O�E���̕�
		WINDOW_FAR_FRONT,		// ���E�\�̕�
		WINDOW_FAR_BACK,		// ���E���̕�
		WINDOW_MAX				// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CWindow();

	// �f�X�g���N�^
	~CWindow();

	// �X�e�[�^�X���\����
	struct SStatusInfo
	{
		D3DXVECTOR3 size;	// �傫��
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��

	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override;		// �ʒu�擾
	void SetVec3Rotation(const D3DXVECTOR3& rRot) override;	// �����ݒ�
	D3DXVECTOR3 GetVec3Rotation(void) const override;		// �����擾
	void SetVec3Sizing(const D3DXVECTOR3& rSize) override;	// �傫���ݒ�
	D3DXVECTOR3 GetVec3Sizing(void) const override;			// �傫���擾
	void SetColor(const D3DXCOLOR& rCol) override;			// �F�ݒ�
	void SetEnableUpdate(const bool bUpdate) override;		// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;			// �`��󋵐ݒ�

	void SetType(const int nType) override;		// ��ސݒ�
	int GetType(void) const override;			// ��ގ擾
	void SetScale(const float fScale) override;	// �g�嗦�ݒ�
	float GetScale(void) const override;		// �g�嗦�擾

	// �ÓI�����o�֐�
	static CWindow *Create	// ����
	( // ����
		const EType type,			// ���
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const float fScale = 1.0f	// �g�嗦
	);

private:
	// �����o�֐�
	void SetPositionRelative(void);	// ���Έʒu�ݒ�

	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[][WINDOW_MAX];	// �e�N�X�`���萔
	static SStatusInfo m_aStatusInfo[];	// �X�e�[�^�X���

	// �����o�ϐ�
	CObject3D *m_pWall[WINDOW_MAX];	// ���̏��
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_size;		// �傫��
	SStatusInfo m_status;	// �X�e�[�^�X�萔
	EType m_type;			// ��ޒ萔
	float m_fScale;			// �g�嗦
};

#endif	// _WINDOW_H_

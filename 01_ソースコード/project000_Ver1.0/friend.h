//============================================================
//
//	�F�B�w�b�_�[ [friend.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FRIEND_H_
#define _FRIEND_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectChara.h"
#include "scene.h"

//************************************************************
//	�O���錾
//************************************************************
class CObjectBillboard;	// �I�u�W�F�N�g�r���{�[�h�N���X
class CShadow;	// �e�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �F�B�N���X
class CFriend : public CObjectChara
{
public:
	// �e�N�X�`����
	enum ETexture
	{
		TEXTURE_HAPPY = 0,	// ����������
		TEXTURE_MAX			// ���̗񋓌^�̑���
	};

	// ���f����
	enum EModel
	{
		MODEL_WAIST = 0,	// ��
		MODEL_BODY,			// ��
		MODEL_HEAD,			// ��
		MODEL_ARMUL,		// ����r
		MODEL_ARMUR,		// �E��r
		MODEL_ARMDL,		// �����r
		MODEL_ARMDR,		// �E���r
		MODEL_HANDL,		// ����
		MODEL_HANDR,		// �E��
		MODEL_LEGUL,		// ��������
		MODEL_LEGUR,		// �E������
		MODEL_LEGDL,		// ����
		MODEL_LEGDR,		// �E��
		MODEL_FOOTL,		// ����
		MODEL_FOOTR,		// �E��
		MODEL_MAX			// ���̗񋓌^�̑���
	};

	// ���[�V������
	enum EMotion
	{
		MOTION_IDOL = 0,	// �ҋ@���[�V����
		MOTION_WAVEHAND,	// ��U�胂�[�V����
		MOTION_MAX			// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �������Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_UNION,	// �������
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// ����
	enum EAxis
	{
		AXIS_X = 0,	// X��
		AXIS_Y,		// Y��
		AXIS_Z,		// Z��
		AXIS_MAX	// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CFriend();

	// �f�X�g���N�^
	~CFriend();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��

	void SetState(const int nState) override;	// ��Ԑݒ�
	int GetState(void) const override;			// ��Ԏ擾
	float GetRadius(void) const override;		// ���a�擾
	float GetHeight(void) const override;		// �c���擾

	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	void SetEnableUpdate(const bool bUpdate) override;		// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;			// �`��󋵐ݒ�
	D3DXMATRIX GetMtxWorld(void) const override;			// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CFriend *Create(void);	// ����

private:
	// �����o�֐�
	void LoadSetup(void);		// �Z�b�g�A�b�v
	EMotion UpdateNormal(void);	// �ʏ��Ԏ��̍X�V
	EMotion UpdateUnion(void);	// ������Ԏ��̍X�V

	void UpdateOldPosition(void);			// �ߋ��ʒu�̍X�V
	void UpdateGravity(void);				// �d�͂̍X�V
	bool UpdateLanding(D3DXVECTOR3& rPos);	// ���n�󋵂̍X�V
	void UpdateRotation(D3DXVECTOR3& rRot);	// �����̍X�V
	void UpdateMotion(int nMotion);			// ���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V

	bool ResponseSingleBuilding(const EAxis axis, D3DXVECTOR3& rPos);	// �r���Ƃ̈ꎲ���Ƃ̓����蔻��
	bool LandObstacle(D3DXVECTOR3& rPos);		// ��Q���Ƃ̒��n����
	bool CollisionBuilding(D3DXVECTOR3& rPos);	// �r���Ƃ̓����蔻��

	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[];	// �e�N�X�`���萔
	static const char *mc_apModelFile[];	// ���f���萔

	// �����o�ϐ�
	CObjectBillboard *m_pEmotion;	// ������o���̏��
	CShadow *m_pShadow;				// �e�̏��
	D3DXVECTOR3	m_oldPos;			// �ߋ��ʒu
	D3DXVECTOR3	m_move;				// �ړ���
	D3DXVECTOR3	m_destRot;			// �ڕW����
	EState	m_state;				// ���
	int		m_nCounterState;		// ��ԊǗ��J�E���^�[
	bool	m_bJump;				// �W�����v��
};

#endif	// _FRIEND_H_

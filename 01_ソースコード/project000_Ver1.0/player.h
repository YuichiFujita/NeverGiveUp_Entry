//============================================================
//
//	�v���C���[�w�b�_�[ [player.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectChara.h"
#include "scene.h"
#include "retentionManager.h"

//************************************************************
//	�}�N����`
//************************************************************
#define NUM_ORBIT	(4)	// �O�Ղ̐�����

//************************************************************
//	�O���錾
//************************************************************
class CObjectOrbit;	// �O�ՃN���X
class CShadow;		// �e�N���X
class CGoalPoint;	// �S�[���|�C���g�N���X
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �v���C���[�N���X
class CPlayer : public CObjectChara
{
public:
	// �e�N�X�`����
	enum ETexture
	{
		TEXTURE_CLEAR = 0,	// �N���A�\��
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
		MOTION_MOVE,		// �ړ����[�V����
		MOTION_JUMP,		// �W�����v���[�V����
		MOTION_SLIDE,		// �X���C�f�B���O���[�V����
		MOTION_WALLDASH,	// �Ǒ��胂�[�V����
		MOTION_FALL,		// �������[�V����
		MOTION_WAVEHAND,	// ��U�胂�[�V����
		MOTION_MAX			// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �������Ȃ����
		STATE_SPAWN,	// �X�|�[�����
		STATE_NORMAL,	// �ʏ���
		STATE_DAMAGE,	// �_���[�W���
		STATE_UNION,	// �������
		STATE_CLEAR,	// �Q�[���N���A���
		STATE_OVER,		// �Q�[���I�[�o�[���
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// ���n��
	enum ELand
	{
		LAND_NONE = 0,	// ���n���Ă��Ȃ�
		LAND_BUILDING,	// �r�����n
		LAND_OBSTACLE,	// ��Q�����n
		LAND_OTHER,		// ���̑����n
		LAND_MAX		// ���̗񋓌^�̑���
	};

	// ����
	enum EAxis
	{
		AXIS_X = 0,	// X��
		AXIS_Y,		// Y��
		AXIS_Z,		// Z��
		AXIS_MAX	// ���̗񋓌^�̑���
	};

	// ������
	enum EDirection
	{
		DIRECTION_NONE = 0,	// ��������
		DIRECTION_DOWN,		// �����F0��
		DIRECTION_RIGHT,	// �����F90��
		DIRECTION_UP,		// �����F180��
		DIRECTION_LEFT,		// �����F270��
		DIRECTION_MAX		// ���̗񋓌^�̑���
	};
	
	// �R���X�g���N�^
	CPlayer();

	// �f�X�g���N�^
	~CPlayer();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��
	void Hit(void) override;		// �q�b�g

	void SetState(const int nState) override;	// ��Ԑݒ�
	int GetState(void) const override;			// ��Ԏ擾
	float GetRadius(void) const override;		// ���a�擾
	float GetHeight(void) const override;		// �c���擾

	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�
	D3DXMATRIX GetMtxWorld(void) const override;		// �}�g���b�N�X�擾

	// �ÓI�����o�֐�
	static CPlayer *Create(CScene::EMode mode);	// ����

	// �����o�֐�
	void SetSpawn(void);	// �o���ݒ�
	void SetGoal(CGoalPoint *pGoal);	// �S�[���ݒ�

private:
	// �����o�֐�
	void LoadSetup(void);		// �Z�b�g�A�b�v
	EMotion UpdateSpawn(void);	// �X�|�[����Ԏ��̍X�V
	EMotion UpdateNormal(void);	// �ʏ��Ԏ��̍X�V
	EMotion UpdateDamage(void);	// �_���[�W��Ԏ��̍X�V
	EMotion UpdateUnion(void);	// ������Ԏ��̍X�V
	void UpdateClear(void);		// �Q�[���N���A��Ԏ��̍X�V

	void UpdateOldPosition(void);			// �ߋ��ʒu�̍X�V
	EMotion UpdateMove(D3DXVECTOR3& rPos);	// �ړ��ʁE�Ǒ���̍X�V
	void UpdateWallDash(D3DXVECTOR3& rPos);	// �Ǒ���̍X�V
	void UpdateJump(void);					// �W�����v�̍X�V
	void UpdateSliding(void);				// �X���C�f�B���O�̍X�V
	void UpdateGravity(void);				// �d�͂̍X�V
	bool UpdateLanding(D3DXVECTOR3& rPos);	// ���n�󋵂̍X�V
	void UpdateRotation(D3DXVECTOR3& rRot);	// �����̍X�V
	void UpdateEffect(D3DXVECTOR3& rPos);	// �G�t�F�N�g�̍X�V
	void UpdateMotion(int nMotion);			// ���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V
	bool UpdateFadeOut(const float fAdd);	// �t�F�[�h�A�E�g��Ԏ��̍X�V
	bool UpdateFadeIn(const float fSub);	// �t�F�[�h�C����Ԏ��̍X�V

	void ResultTransition(const CRetentionManager::EResult result);		// ���U���g�J��
	EDirection FourDirection(const float fRot, const float fTolerance);	// �l�����ϊ�
	void CollisionRotationBuilding(D3DXVECTOR3& rPos);					// �����ύX�̓����蔻��
	bool ResponseSingleBuilding(const EAxis axis, D3DXVECTOR3& rPos);	// �r���Ƃ̈ꎲ���Ƃ̓����蔻��
	bool CollisionSignboard(D3DXVECTOR3& rPos, float *pRate = NULL);	// �ŔƂ̓����蔻��
	void CollisionObstacle(D3DXVECTOR3& rPos);	// ��Q���Ƃ̓����蔻��
	bool LandObstacle(D3DXVECTOR3& rPos);		// ��Q���Ƃ̒��n����
	bool CollisionBuilding(D3DXVECTOR3& rPos);	// �r���Ƃ̓����蔻��

	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[];	// �e�N�X�`���萔
	static const char *mc_apModelFile[];	// ���f���萔

	// �����o�ϐ�
	CObjectOrbit *m_apOrbit[NUM_ORBIT];	// �O�Ղ̏��
	CShadow *m_pShadow;			// �e�̏��
	CGoalPoint *m_pGoal;		// �S�[���̏��
	CObject2D *m_pClear;		// �N���A�\���̏��
	D3DXVECTOR3	m_oldPos;		// �ߋ��ʒu
	D3DXVECTOR3	m_move;			// �ړ���
	D3DXVECTOR3	m_destRot;		// �ڕW����
	ELand	m_land;				// ���n��
	EState	m_state;			// ���
	int		m_nCounterState;	// ��ԊǗ��J�E���^�[
	int		m_nCounterSlide;	// �X���C�f�B���O�Ǘ��J�E���^�[
	int		m_nCounterWallDash;	// �Ǒ���Ǘ��J�E���^�[
	int		m_nCounterLand;		// ���n�Ǘ��J�E���^�[
	int		m_nCounterJump;		// �W�����v�Ǘ��J�E���^�[
	float	m_fMove;			// �ړ���
	float	m_fPlusMove;		// �v���X�ړ���
	bool	m_bJump;			// �W�����v��
	bool	m_bJumpControl;		// �W�����v�����
	bool	m_bSlide;			// �X���C�f�B���O��
	bool	m_bSlideControl;	// �X���C�f�B���O�����
	bool	m_bWallDash;		// �Ǒ����
	bool	m_bWallDashControl;	// �Ǒ��葀���
};

#endif	// _PLAYER_H_

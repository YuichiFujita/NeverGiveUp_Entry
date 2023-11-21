//============================================================
//
//	��Q���w�b�_�[ [obstacle.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectModel.h"

//************************************************************
//	�N���X��`
//************************************************************
// ��Q���N���X
class CObstacle : public CObjectModel
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_BOX = 0,		// �����f��
		TYPE_BENCH,			// �x���`���f��
		TYPE_JUMPPAD,		// �W�����v�p�b�h���f��
		TYPE_FENCE,			// �t�F���X���f��
		TYPE_BLOCK,			// �u���b�N���f��
		TYPE_WALL,			// �ǃ��f��
		TYPE_BLUE_BOX,		// �����f��
		TYPE_CAR,			// �ԃ��f��
		TYPE_WHEEL,			// �^�C�����f��
		TYPE_DRUMTOWER,		// �h�����ʃ^���[���f��
		TYPE_PIPEFENCE,		// �p�C�v�t�F���X���f��
		TYPE_STRUCTURE_00,	// �X�g���N�`���[���f���i�ԁj
		TYPE_STRUCTURE_01,	// �X�g���N�`���[���f���i�E���j
		TYPE_STRUCTURE_02,	// �X�g���N�`���[���f���i���j
		TYPE_STRUCTURE_03,	// �X�g���N�`���[���f���i�ԁE�j
		TYPE_STRUCTURE_04,	// �X�g���N�`���[���f���i���E�΁j
		TYPE_STRUCTURE_05,	// �X�g���N�`���[���f���i�����Ȃ��F�ԁj
		TYPE_STRUCTURE_06,	// �X�g���N�`���[���f���i�����Ȃ��F�D�j
		TYPE_STRUCTURE_07,	// �X�g���N�`���[���f���i�����Ȃ��F���j
		TYPE_STRUCTURE_08,	// �X�g���N�`���[���f���i�����Ȃ��F�j
		TYPE_STRUCTURE_09,	// �X�g���N�`���[���f���i�����Ȃ��F�΁j
		TYPE_STRUCTURE_10,	// �X�g���N�`���[���f���i�����Ȃ��F���j
		TYPE_STRUCTURE_11,	// �X�g���N�`���[���f���i�D�j
		TYPE_STRUCTURE_12,	// �X�g���N�`���[���f���i�j
		TYPE_WOODGROUND,	// ���n��
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �����ԗ�
	enum EState
	{
		STATE_NONE = 0,	// �����Ԗ���
		STATE_JUMP,		// �G���ƃW�����v����
		STATE_LAND,		// ���n�ł���
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// ����
	enum EDodge
	{
		DODGE_NONE = 0,	// �����@����
		DODGE_JUMP,		// �W�����v���
		DODGE_SLIDE,	// �X���C�f�B���O���
		DODGE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CObstacle();

	// �f�X�g���N�^
	~CObstacle();

	// �X�e�[�^�X�\����
	struct SStatusInfo
	{
		D3DXVECTOR3 size;	// �傫��
		EState state;		// ������
		EDodge dodge;		// ���@
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��

	int GetType(void) const override;		// ��ގ擾
	int GetState(void) const override;		// �����Ԏ擾
	int GetDodge(void) const override;		// ���@�擾
	float GetAngle(void) const override;	// �p�x�擾
	float GetLength(void) const override;	// �����擾

	D3DXVECTOR3 GetVec3Sizing(void) const override;	// �傫���擾

	// �ÓI�����o�֐�
	static void LoadSetup(void);	// �Z�b�g�A�b�v
	static CObstacle *Create		// ����
	( // ����
		const EType type,			// ���
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot		// ����
	);
	static void SetStatusInfo(const SStatusInfo info, const int nID);	// �X�e�[�^�X���ݒ�
	static SStatusInfo GetStatusInfo(const int nID);					// �X�e�[�^�X���擾

	// �����o�֐�
	void SetType(const EType type);	// ��ސݒ�

private:
	// �ÓI�����o�ϐ�
	static const char *mc_apModelFile[];		// ���f���萔
	static SStatusInfo m_aStatusInfo[TYPE_MAX];	// �X�e�[�^�X���

	// �����o�ϐ�
	SStatusInfo m_status;	// �X�e�[�^�X
	EType m_type;			// ���
	float m_fAngle;			// �Ίp���̊p�x
	float m_fLength;		// �Ίp���̒���
};

#endif	// _OBSTACLE_H_

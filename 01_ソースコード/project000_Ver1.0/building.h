//============================================================
//
//	�r���w�b�_�[ [building.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _BUILDING_H_
#define _BUILDING_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectMeshCube.h"

//************************************************************
//	�N���X��`
//************************************************************
// �r���N���X
class CBuilding : public CObjectMeshCube
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_00 = 0,	// �r��00�e�N�X�`��
		TYPE_01,		// �r��01�e�N�X�`��
		TYPE_02,		// �r��02�e�N�X�`��
		TYPE_DOWN,		// �r�����e�N�X�`��
		TYPE_CENTER,	// �r�����ԃe�N�X�`��
		TYPE_UP,		// �r����e�N�X�`��
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �����蔻���
	enum ECollision
	{
		COLLISION_NONE = 0,	// �����蔻�薳��
		COLLISION_GROUND,	// �n��
		COLLISION_CEILING,	// �V��
		COLLISION_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CBuilding();

	// �f�X�g���N�^
	~CBuilding();

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
	void SetType(const int nType) override;		// ��ސݒ�
	int GetType(void) const override;			// ��ގ擾
	void SetState(const int nState) override;	// �����蔻��ݒ�
	int GetState(void) const override;			// �����蔻��擾
	void SetScale(const float fScale) override;	// �g�嗦�ݒ�
	float GetScale(void) const override;		// �g�嗦�擾

	// �ÓI�����o�֐�
	static CBuilding *Create	// ����
	( // ����
		const EType type,			// ���
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const ECollision collision,	// �����蔻��
		const float fScale = 1.0f	// �g�嗦
	);

private:
	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[][6];	// �e�N�X�`���萔
	static SStatusInfo m_aStatusInfo[];			// �X�e�[�^�X���

	// �����o�ϐ�
	ECollision m_collision;	// �����蔻��
	SStatusInfo m_status;	// �X�e�[�^�X
	EType m_type;			// ���
	float m_fScale;			// �g�嗦
};

#endif	// _BUILDING_H_

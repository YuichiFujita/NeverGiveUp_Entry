//============================================================
//
//	�Ŕw�b�_�[ [signboard.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SIGNBOARD_H_
#define _SIGNBOARD_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectMeshCube.h"

//************************************************************
//	�O���錾
//************************************************************
class CMultiModel;	// �}���`���f���N���X

//************************************************************
//	�N���X��`
//************************************************************
// �ŔN���X
class CSignboard : public CObjectMeshCube
{
public:
	// ���f����
	enum EModel
	{
		MODEL_STAND,	// �X�^���h���f��
		MODEL_MAX		// ���̗񋓌^�̑���
	};

	// ��ޗ�
	enum EType
	{
		TYPE_RIGHT = 0,	// �E�e�N�X�`��
		TYPE_LEFT,		// ���e�N�X�`��
		TYPE_UP,		// ��e�N�X�`��
		TYPE_DOWN,		// ���e�N�X�`��
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CSignboard();

	// �f�X�g���N�^
	~CSignboard();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��
	void SetType(const int nType) override;		// ��ސݒ�
	int GetType(void) const override;			// ��ގ擾
	void SetScale(const float fScale) override;	// �g�嗦�ݒ�
	float GetScale(void) const override;		// �g�嗦�擾

	// �ÓI�����o�֐�
	static CSignboard *Create	// ����
	( // ����
		const EType type,			// ���
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot,	// ����
		const float fScale = 1.20f,			// �g�嗦
		const D3DXCOLOR& rCol = XCOL_WHITE	// �F
	);

private:
	// �ÓI�����o�ϐ�
	static const char *mc_apTextureFile[][6];	// �e�N�X�`���萔
	static const char *mc_apModelFile[];		// ���f���萔

	// �����o�ϐ�
	CMultiModel *m_pStand;	// �ŔX�^���h�̏��
	EType m_type;			// ���
	float m_fScale;			// �g�嗦
};

#endif	// _SIGNBOARD_H_

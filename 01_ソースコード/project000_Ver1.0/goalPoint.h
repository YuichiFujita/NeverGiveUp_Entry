//============================================================
//
//	�S�[���|�C���g�w�b�_�[ [goalPoint.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _GOALPOINT_H_
#define _GOALPOINT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "object.h"

//************************************************************
//	�O���錾
//************************************************************
class CFriend;	// �F�B�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �S�[���|�C���g�N���X
class CGoalPoint : public CObject
{
public:
	// �R���X�g���N�^
	CGoalPoint();

	// �f�X�g���N�^
	~CGoalPoint();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override;		// �ʒu�擾
	void SetVec3Sizing(const D3DXVECTOR3& rSize) override;	// ����傫���ݒ�
	D3DXVECTOR3 GetVec3Sizing(void) const override;			// ����傫���擾
	void SetEnableUpdate(const bool bUpdate) override;		// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;			// �`��󋵐ݒ�

	// �ÓI�����o�֐�
	static CGoalPoint *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rSize	// �傫��
	);

	// �����o�֐�
	D3DXVECTOR3 GetVec3FriendPosition(void) const;	// �F�B�ʒu�擾

private:
	// �����o�֐�
	void CollisionPlayer(void);	// �v���C���[�Ƃ̓����蔻��

	// �����o�ϐ�
	CFriend *m_pFriend;	// �F�B�̏��
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_size;	// �傫��
};

#endif	// _GOALPOINT_H_

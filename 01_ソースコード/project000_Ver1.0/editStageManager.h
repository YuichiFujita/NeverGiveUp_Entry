//============================================================
//
//	�G�f�B�b�g�X�e�[�W�}�l�[�W���[�w�b�_�[ [editStageManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _EDIT_STAGEMANAGER_H_
#define _EDIT_STAGEMANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"

//************************************************************
//	�O���錾
//************************************************************
class CEditBuilding;	// �G�f�B�b�g�r���N���X
class CEditWindow;		// �G�f�B�b�g���N���X
class CEditSignboard;	// �G�f�B�b�g�ŔN���X
class CEditObstacle;	// �G�f�B�b�g��Q���N���X
class CEditSavePoint;	// �G�f�B�b�g�Z�[�u�|�C���g�N���X
class CEditGoalPoint;	// �G�f�B�b�g�S�[���|�C���g�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �G�f�B�b�g�X�e�[�W�}�l�[�W���[�N���X
class CEditStageManager
{
public:
	// �z�u����
	enum EThing
	{
		THING_BUILDING = 0,	// �r��
		THING_WINDOW,		// ��
		THING_SIGNBOARD,	// �Ŕ�
		THING_OBSTACLE,		// ��Q��
		THING_SAVEPOINT,	// �Z�[�u�|�C���g
		THING_GOALPOINT,	// �S�[���|�C���g
		THING_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CEditStageManager();

	// �f�X�g���N�^
	~CEditStageManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void UnSave(void);	// ���ۑ��ݒ�
	void SetEnableEdit(const bool bEdit);		// �G�f�B�b�g�󋵐ݒ�
	bool IsEdit(void) const;					// �G�f�B�b�g�󋵎擾
	D3DXVECTOR3 GetVec3Position(void) const;	// �ʒu�擾
	D3DXVECTOR3 GetVec3Rotation(void) const;	// �����擾

	// �ÓI�����o�֐�
	static CEditStageManager *Create(void);	// ����
	static HRESULT Release(CEditStageManager *&prEditStageManager);	// �j��

private:
	// �����o�֐�
	void UpdateChangeThing(void);	// �z�u���ύX�̍X�V
	void UpdateChangeMove(void);	// �ړ��ʕύX�̍X�V
	void UpdatePosition(void);		// �ʒu�X�V
	void UpdateRotation(void);		// �����X�V
	void UpdatePosCamera(void);		// �J�����ʒu�ύX�̍X�V
	void DrawDebugControl(void);	// ����\���`��
	void DrawDebugInfo(void);		// ���\���`��
	void SaveStage(void);			// �X�e�[�W�ۑ�
	void Save(void);				// �ۑ�

	// �����o�ϐ�
	CEditBuilding	*m_pBuilding;	// �G�f�B�b�g�r���̏��
	CEditWindow		*m_pWindow;		// �G�f�B�b�g���̏��
	CEditSignboard	*m_pSignboard;	// �G�f�B�b�g�Ŕ̏��
	CEditObstacle	*m_pObstacle;	// �G�f�B�b�g��Q���̏��
	CEditSavePoint	*m_pSavePoint;	// �G�f�B�b�g�Z�[�u�|�C���g�̏��
	CEditGoalPoint	*m_pGoalPoint;	// �G�f�B�b�g�S�[���|�C���g�̏��

	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	EThing m_thing;		// �z�u��
	float m_fMove;		// �ʒu�ړ���
	bool m_bSave;		// �ۑ���
	bool m_bEdit;		// �G�f�B�b�g��
};

#endif	// _EDIT_STAGEMANAGER_H_

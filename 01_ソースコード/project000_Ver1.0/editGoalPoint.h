//============================================================
//
//	�G�f�B�b�g�S�[���|�C���g�w�b�_�[ [editGoalPoint.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _EDIT_GOALPOINT_H_
#define _EDIT_GOALPOINT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "goalPoint.h"

//************************************************************
//	�O���錾
//************************************************************
class CEditStageManager;	// �G�f�B�b�g�X�e�[�W�}�l�[�W���[�N���X
class CObjectMeshCube;		// �I�u�W�F�N�g���b�V���L���[�u�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �G�f�B�b�g�S�[���|�C���g�N���X
class CEditGoalPoint
{
public:
	// �R���X�g���N�^
	CEditGoalPoint();

	// �f�X�g���N�^
	~CEditGoalPoint();

	// �S�[���|�C���g���\����
	struct SInfo
	{
		CGoalPoint *pGoalPoint;			// �S�[���|�C���g���
		CObjectMeshCube *pCollision;	// �����蔻��̏��
		bool bSet;						// �z�u��
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void SetDisp(const bool bDisp);	// �\���ݒ�
	void DrawDebugControl(void);	// ����\���`��
	void DrawDebugInfo(void);		// ���\���`��
	void Save(FILE *pFile);			// �ۑ�

	// �ÓI�����o�֐�
	static CEditGoalPoint *Create(CEditStageManager *pEdit);	// ����
	static HRESULT Release(CEditGoalPoint *&prEditGoalPoint);	// �j��

private:
	// �����o�֐�
	void UpdateCollSize(void);	// ����傫���̍X�V
	void CreateGoalPoint(void);	// �S�[���|�C���g����
	void UpdateSet(void);		// �ݒu�\��ʒu�̍X�V
	void UpdateColl(void);		// �����蔻��̍X�V

	// �����o�ϐ�
	CEditStageManager *m_pEdit;	// �G�f�B�b�g�X�e�[�W�̏��
	CObjectMeshCube *m_pSet;	// �ݒu�\��ʒu�̏��
	SInfo m_goalPoint;			// �S�[���|�C���g�z�u���
};

#endif	// _EDIT_GOALPOINT_H_

//============================================================
//
//	�G�f�B�b�g�Ŕw�b�_�[ [editSignboard.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _EDIT_SIGNBOARD_H_
#define _EDIT_SIGNBOARD_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "signboard.h"

//************************************************************
//	�O���錾
//************************************************************
class CEditStageManager;	// �G�f�B�b�g�X�e�[�W�}�l�[�W���[�N���X
class CObjectMeshCube;		// �I�u�W�F�N�g���b�V���L���[�u�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �G�f�B�b�g�ŔN���X
class CEditSignboard
{
public:
	// �R���X�g���N�^
	CEditSignboard();

	// �f�X�g���N�^
	~CEditSignboard();

	// �Ŕ��\����
	struct SInfo
	{
		CSignboard *pSignboard;	// �Ŕ��
		CSignboard::EType type;	// �Ŕ��
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
	static CEditSignboard *Create(CEditStageManager *pEdit);	// ����
	static HRESULT Release(CEditSignboard *&prEditSignboard);	// �j��

private:
	// �����o�֐�
	void UpdateChangeType(void);	// ��ޕύX�̍X�V
	void UpdateChangeScale(void);	// �g�嗦�ύX�̍X�V
	void UpdateCenter(void);		// ���S�\���̍X�V
	void CreateSignboard(void);		// �Ŕ���
	void ReleaseSignboard(void);	// �Ŕj��

	void DeleteCollisionSignboard(const bool bRelase);	// �Ŕ̍폜����
	void InitAllColorSignboard(void);					// �Ŕ̐F�S������

	// �����o�ϐ�
	CEditStageManager *m_pEdit;	// �G�f�B�b�g�X�e�[�W�̏��
	CObjectMeshCube *m_pCenter;	// ���S�̏��
	SInfo m_signboard;	// �Ŕz�u���
};

#endif	// _EDIT_SIGNBOARD_H_

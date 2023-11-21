//============================================================
//
//	�G�f�B�b�g���w�b�_�[ [editWindow.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _EDIT_WINDOW_H_
#define _EDIT_WINDOW_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "window.h"

//************************************************************
//	�O���錾
//************************************************************
class CEditStageManager;	// �G�f�B�b�g�X�e�[�W�}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �G�f�B�b�g���N���X
class CEditWindow
{
public:
	// �R���X�g���N�^
	CEditWindow();

	// �f�X�g���N�^
	~CEditWindow();

	// �����\����
	struct SInfo
	{
		CWindow *pWindow;		// �����
		CWindow::EType type;	// �����
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
	static CEditWindow *Create(CEditStageManager *pEdit);	// ����
	static HRESULT Release(CEditWindow *&prEditWindow);		// �j��

private:
	// �����o�֐�
	void UpdateChangeType(void);	// ��ޕύX�̍X�V
	void UpdateChangeScale(void);	// �g�嗦�ύX�̍X�V
	void MyCreateWindow(void);		// ������
	void ReleaseWindow(void);		// ���j��

	void DeleteCollisionWindow(const bool bRelase);	// ���̍폜����
	void InitAllColorWindow(void);					// ���̐F�S������

	// �����o�ϐ�
	CEditStageManager *m_pEdit;	// �G�f�B�b�g�X�e�[�W�̏��
	SInfo m_window;	// ���z�u���
};

#endif	// _EDIT_WINDOW_H_

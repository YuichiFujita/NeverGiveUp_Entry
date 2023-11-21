//============================================================
//
//	�G�f�B�b�g�Z�[�u�|�C���g�w�b�_�[ [editSavePoint.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _EDIT_SAVEPOINT_H_
#define _EDIT_SAVEPOINT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "savePoint.h"

//************************************************************
//	�O���錾
//************************************************************
class CEditStageManager;	// �G�f�B�b�g�X�e�[�W�}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �G�f�B�b�g�Z�[�u�|�C���g�N���X
class CEditSavePoint
{
public:
	// �R���X�g���N�^
	CEditSavePoint();

	// �f�X�g���N�^
	~CEditSavePoint();

	// �Z�[�u�|�C���g���\����
	struct SInfo
	{
		CSavePoint *pSavePoint;	// �Z�[�u�|�C���g���
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
	static CEditSavePoint *Create(CEditStageManager *pEdit);	// ����
	static HRESULT Release(CEditSavePoint *&prEditSavePoint);	// �j��

private:
	// �����o�֐�
	void CreateSavePoint(void);		// �Z�[�u�|�C���g����
	void ReleaseSavePoint(void);	// �Z�[�u�|�C���g�j��
	void CreateRotaEffect(void);	// �����\���G�t�F�N�g����

	void DeleteCollisionSavePoint(const bool bRelase);	// �Z�[�u�|�C���g�̍폜����
	void InitAllColorSavePoint(void);					// �Z�[�u�|�C���g�̐F�S������

	// �����o�ϐ�
	CEditStageManager *m_pEdit;	// �G�f�B�b�g�X�e�[�W�̏��
	SInfo m_savePoint;	// �Z�[�u�|�C���g�z�u���
};

#endif	// _EDIT_SAVEPOINT_H_

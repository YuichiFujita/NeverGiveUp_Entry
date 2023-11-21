//============================================================
//
//	�G�f�B�b�g�r���w�b�_�[ [editBuilding.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _EDIT_BUILDING_H_
#define _EDIT_BUILDING_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "building.h"

//************************************************************
//	�O���錾
//************************************************************
class CEditStageManager;	// �G�f�B�b�g�X�e�[�W�}�l�[�W���[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �G�f�B�b�g�r���N���X
class CEditBuilding
{
public:
	// �R���X�g���N�^
	CEditBuilding();

	// �f�X�g���N�^
	~CEditBuilding();

	// �r�����\����
	struct SInfo
	{
		CBuilding *pBuilding;		// �r�����
		CBuilding::EType type;		// �r�����
		CBuilding::ECollision coll;	// �r������
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
	static CEditBuilding *Create(CEditStageManager *pEdit);	// ����
	static HRESULT Release(CEditBuilding *&prEditBuilding);	// �j��

private:
	// �����o�֐�
	void UpdateChangeType(void);	// ��ޕύX�̍X�V
	void UpdateChangeColl(void);	// ����ύX�̍X�V
	void UpdateChangeScale(void);	// �g�嗦�ύX�̍X�V
	void CreateBuilding(void);		// �r������
	void ReleaseBuilding(void);		// �r���j��
	void CreateRotaEffect(void);	// �����\���G�t�F�N�g����

	void DeleteCollisionBuilding(const bool bRelase);	// �r���̍폜����
	void InitAllColorBuilding(void);					// �r���̐F�S������

	// �����o�ϐ�
	CEditStageManager *m_pEdit;	// �G�f�B�b�g�X�e�[�W�̏��
	SInfo m_building;	// �r���z�u���
};

#endif	// _EDIT_BUILDING_H_

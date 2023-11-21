//============================================================
//
//	�Z�[�u�|�C���g�w�b�_�[ [savePoint.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SAVEPOINT_H_
#define _SAVEPOINT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "objectModel.h"

//************************************************************
//	�N���X��`
//************************************************************
// �Z�[�u�|�C���g�N���X
class CSavePoint : public CObjectModel
{
public:
	// ���f����
	enum EModel
	{
		MODEL_SAVEPOINT = 0,	// �Z�[�u�|�C���g���f��
		MODEL_MAX				// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_NORMAL = 0,	// �ʏ���
		STATE_SAVE,			// �Z�[�u���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CSavePoint();

	// �f�X�g���N�^
	~CSavePoint();

	// �Z�[�u�|�C���g���\����
	struct SInfo
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
	};

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��
	int GetIndex(void) const override;		// ���g�̃Z�[�u�|�C���g�C���f�b�N�X�擾
	float GetRadius(void) const override;	// ���a�擾

	// �ÓI�����o�֐�
	static CSavePoint *Create	// ����
	( // ����
		const D3DXVECTOR3& rPos,	// �ʒu
		const D3DXVECTOR3& rRot		// ����
	);
	static int GetNumAll(void);		// �����擾
	static int GetSavePointID(void);	// �Z�[�u�|�C���g�C���f�b�N�X�擾
	static SInfo GetSavePointInfo(void);	// �Z�[�u�|�C���g���擾

private:
	// �����o�֐�
	void CollisionPlayer(void);	// �v���C���[�Ƃ̓����蔻��

	// �ÓI�����o�֐�
	static CObject *GetSavePoint(void);	// �����ς݃Z�[�u�|�C���g�擾

	// �ÓI�����o�ϐ�
	static const char *mc_apModelFile[];	// ���f���萔
	static CObject *m_pCurrentSave;			// ���݂̃Z�[�u�|�C���g�ւ̃|�C���^

	static int m_nNumAll;	// �Z�[�u�|�C���g�̑���

	// �����o�ϐ�
	EState m_state;				// ���
	int m_nCounterState;		// ��ԊǗ��J�E���^�[
	const int m_nThisSaveID;	// ���g�̃Z�[�u�|�C���g�C���f�b�N�X
};

#endif	// _SAVEPOINT_H_

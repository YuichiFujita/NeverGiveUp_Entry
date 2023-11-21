//============================================================
//
//	ゲームマネージャーヘッダー [gameManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"

//************************************************************
//	前方宣言
//************************************************************
class CPhoneManager;		// スマホマネージャー
class CEditStageManager;	// エディットステージマネージャークラス

//************************************************************
//	クラス定義
//************************************************************
// ゲームマネージャークラス
class CGameManager
{
public:
	// 状態列挙
	enum EState
	{
		STATE_NONE = 0,		// 何もしない状態
		STATE_INIT_PHONE,	// 遅刻表示初期化状態
		STATE_PHONE,		// 遅刻表示状態
		STATE_INIT_NORMAL,	// 通常初期化状態
		STATE_NORMAL,		// 通常状態
		STATE_INIT_END,		// クリア失敗表示の初期化状態
		STATE_END,			// クリア失敗表示の状態
		STATE_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CGameManager();

	// デストラクタ
	~CGameManager();

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void SetState(const EState state);	// 状態設定
	EState GetState(void) const;		// 状態取得

	// 静的メンバ関数
	static CGameManager *Create(void);	// 生成
	static HRESULT Release(CGameManager *&prGameManager);	// 破棄

	static CPhoneManager *GetPhone(void);			// スマホマネージャー取得
	static CEditStageManager *GetEditStage(void);	// エディットステージ取得

private:
	// 静的メンバ変数
	static CPhoneManager *m_pPhone;			// スマホマネージャーの情報
	static CEditStageManager *m_pEditStage;	// エディットステージの情報

	// メンバ変数
	EState m_state;	// 状態
};

#endif	// _GAMEMANAGER_H_

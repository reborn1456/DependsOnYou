#pragma once

#include <windows.h>
#include <d3dx9.h>
#include <string>

/* GameFrameに持たせたい自作クラス等のヘッダーをインクルードする */
/* ここから===================================================== */
#include "Define.h"
#include "CPlayer.h"
#include "scenes/CTitle.h"
#include "stages/prologue/CPrologue.h"
#include "scenes/CGame.h"
#include "scenes/CGameOver.h"
#include "scenes/CResult.h"
#include "stages/stage1/CItem.h"
/* ここまで===================================================== */


////////////////////////////////////////////////// 列挙型 //////////////////////////////////////////////////

enum SceneName
{
	//default starting as 0 and then +1 for each after it
	/* when use:
	   int scene = SceneName::Game_PROC; */

	TITLE_PROC, PROLOGUE_PROC, GAME_PROC, GAMEOVER_PROC, RESULT_PROC
};




////////////////////////////////////////////////// クラスの関数 //////////////////////////////////////////////////

/*
　GameFrameクラス
  DirectX9の初期化、Windowの作成などゲームループに必要な処理諸々をまとめたクラス
  ※ 本来1つのクラスに様々な機能を詰め込むのは設計ミスです
*/
class CGameFrame
{

public: // 以下の変数、関数は外部からアクセスできる

	CGameFrame();		// コンストラクタ
	~CGameFrame();		// デストラクタ

	// 変数=================================================
	int						mScene;


	// 関数=================================================
	void Create(HINSTANCE aHInst,const int aCmdShow);
	void Initialize();	// 初期化処理
	void Release();		// 終了処理
	void GameLoop();	// ゲームループ
	void LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const std::string & aFilePath, int aWidth, int aHeight, D3DCOLOR aColor);
	void CreateConsole();

	const LPDIRECT3DDEVICE9 GetD3DDevice();
	const HWND GetHwnd();

	CPlayer* GetPlayer();
	CTitle* GetTitle();
	CPrologue* GetPrologue();
	CGame* GetGame();
	CGameOver* GetGameOver();
	CResult* GetResult();


private: // 以下の変数、関数は外部からアクセスできない

	// 定数=================================================
	// 定数は全てコンストラクタで設定する必要がある
	const int			mScrollWidth;				// 画面横幅
	const int			mScrollHeight;				// 画面縦幅
	const std::string	mAppName;					// アプリケーション(ウィンドウ)名
	const int			mFvFVertex;					// ポリゴンの頂点情報
	

	// 変数=================================================
	HWND					mpHwnd;
	LPDIRECT3D9				mpD3D;		            // Direct3Dインターフェイス
	LPDIRECT3DDEVICE9		mpD3DDevice;        	// Direct3DDeviceインターフェイス
	D3DPRESENT_PARAMETERS	mD3Dpp;
	WNDCLASS				mWndClass;
	LPD3DXSPRITE			mpSprite;				// スプライト
	LPD3DXFONT				mpFont;					// フォント

	bool					mIsFullScreen;				// フルスクリーンにするかどうか
	bool				    mFullScreenCursor;			// フルスクリーンの時カーソルを表示するかどうか

	CPlayer					mPlayer;
	CTitle					mTitle;
	CPrologue				mPrologue;
	CGame                   mGame;
	CGameOver				mGameOver;
	CResult					mResult;

	int						mFrame;					//毎フレーム増える

	// 関数=================================================
	void Update();									// 更新関数
	void Draw();									// 描画
	void Draw2D();									// 2D描画
	void Draw3D();									// 3D描画

	HWND CreateHWND(HINSTANCE aHInst, const int aCmdShow);
	WNDCLASS CreateWNDCLASS(HINSTANCE aHInst);
	void CreateDirectX9();

};

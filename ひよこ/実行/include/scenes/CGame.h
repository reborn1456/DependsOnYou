#pragma once

#include <d3dx9.h>
#include "../CBasicShape.h"
#include "../sound/CSound.h"
#include "../stages/stage1/CStage1.h"
#include "../stages/stage2/CStage2.h"




////////////////////////////////////////////////// 列挙型 //////////////////////////////////////////////////

enum StageName
{
	//default starting as 0 and then +1 for each after it
	/* when use:
	   int scene = SceneName::Game_PROC; */

	STAGE1_PROC, STAGE2_PROC
};




////////////////////////////////////////////////// クラスの関数 //////////////////////////////////////////////////

class CGameFrame;     // クラスの前方宣言

class CGame
{
public:

	CGame();
	~CGame();

	// メンバ変数=================================================
	int						 mStage;
	
	// メンバ関数=================================================
	void Initialize();
	void Update();                                           // 更新
	void Draw(LPD3DXSPRITE apSprite);                        // 描画
	void Release();											 // 終了処理
	void SetOwner(CGameFrame* apOwner);						 // オーナ設定
	void SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice);

	//CBasicShape* GetBasicShape();
	CSound* GetSound();
	CStage1* GetStage1();
	CStage2* GetStage2();


private:

	// メンバ変数=================================================
	CGameFrame*              mpOwner;
	LPDIRECT3DDEVICE9        lpD3DDevice;

//	CBasicShape			     mShape;
	CSound				     mSound;
	CStage1					 mStage1;
	CStage2					 mStage2;
};
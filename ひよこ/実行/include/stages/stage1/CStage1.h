#pragma once

#include <d3dx9.h>
#include "CStage1Map.h"
#include "CItem.h"



////////////////////////////////////////////////// クラスの関数 //////////////////////////////////////////////////

class CGameFrame;     // クラスの前方宣言

class CStage1
{
public:

	CStage1();
	~CStage1();

	// メンバ変数=================================================


	// メンバ関数=================================================
	void Initialize();
	void Update();                                           // 更新
	void Draw(LPD3DXSPRITE apSprite);                        // 描画
	void SetOwner(CGameFrame* apOwner);						 // オーナ設定

	CStage1Map* GetStage1Map();



private:

	// メンバ変数=================================================
	CGameFrame*              mpOwner;

	CStage1Map				 mStage1Map;
	CItem					 mItem;


	// メンバ関数=================================================

};
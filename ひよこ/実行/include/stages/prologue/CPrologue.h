#pragma once

#include <d3dx9.h>
#include "CPMapChip.h"




////////////////////////////////////////////////// クラスの関数 //////////////////////////////////////////////////

class CGameFrame;     // クラスの前方宣言

class CPrologue
{
public:

	CPrologue();
	~CPrologue();

	// メンバ変数=================================================
	int						 mStage;
	
	// メンバ関数=================================================
	void Initialize();
	void Update();                                           // 更新
	void Draw(LPD3DXSPRITE apSprite);                        // 描画
	void SetOwner(CGameFrame* apOwner);						 // オーナ設定
	void SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice);

	CPMapChip* GetPMapChip();


private:

	// メンバ変数=================================================
	CGameFrame*              mpOwner;
	LPDIRECT3DDEVICE9        lpD3DDevice;

	CPMapChip				 mPMapChip;
};
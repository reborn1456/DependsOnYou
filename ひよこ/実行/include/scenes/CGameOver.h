#pragma once

#include <d3dx9.h>




////////////////////////////////////////////////// クラスの関数 //////////////////////////////////////////////////

class CGameFrame;     // クラスの前方宣言

class CGameOver
{
public:

	CGameOver();
	~CGameOver();

	// メンバ変数=================================================


	// メンバ関数=================================================
	void Initialize();
	void Update();                                           // 更新
	void Draw(LPD3DXSPRITE apSprite);                        // 描画
	void SetTexture(LPDIRECT3DTEXTURE9 apTexture);           // テクスチャ設定
	void SetOwner(CGameFrame* apOwner);						 // オーナ設定



private:

	// メンバ変数=================================================
	CGameFrame*              mpOwner;
	LPDIRECT3DTEXTURE9       mpTexture;
	D3DXVECTOR3              mPosition;
	D3DXMATRIX               mMatrix;


	// メンバ関数=================================================

};
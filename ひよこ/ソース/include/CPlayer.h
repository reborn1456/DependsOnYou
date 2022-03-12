#pragma once

#include <d3dx9.h>
#include "../include/stages/prologue/CPMapChip.h"

enum EPlayerDirection
{
	//default starting as 0 and then +1 for each after it
	/* when use:
	   int scene = SceneName::Game_PROC; */

	FRONT, L_SIDE, R_SIDE, BACK
};

class CGameFrame;   // クラスの前方宣言

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	// メンバ関数
	void Update();                                           // 更新
	void Draw(LPD3DXSPRITE apSprite);                        // 描画
	void SetTexture(LPDIRECT3DTEXTURE9 apTexture);           // テクスチャ設定
	void Initialize();

	void SetOwner(CGameFrame* apOwner);

	const D3DXVECTOR3 GetPlayerPosition();
	const eMoveState GetMoveState();

private:
	// メンバ変数
	LPDIRECT3DTEXTURE9     mpTexture;
	D3DXVECTOR3            mPosition;
	D3DXVECTOR3            mMovePosition;
	D3DXMATRIX             mMatrix;

	EPlayerDirection       mPlayerDir;

	eMoveState			   mMoveState;
	int					   mMoveWait;
	int					   mMoveCount;
	bool				   mMoveFlg;

	bool				   SceneFlg;

	CGameFrame*  mpOwner;   // オーナー
};
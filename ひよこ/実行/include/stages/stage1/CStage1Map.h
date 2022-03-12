#pragma once

#include <d3dx9.h>
#include "../../Define.h"
#include "../../enum.h"

class CGameFrame;   // クラスの前方宣言


class CStage1Map
{
public:
	CStage1Map();
	~CStage1Map();

	// メンバ関数
	void Update();                         // 更新
	void Draw(LPD3DXSPRITE apSprite);                        // 描画
	void SetTexture(LPDIRECT3DTEXTURE9 apTexture);           // テクスチャ設定
	void LoadMapFile();

	const bool MapHitCheck(eMoveState aMoveState, D3DXVECTOR3 aPos);

	const D3DXVECTOR3 GetPlayerPos();
	const float GetCameraX();
	const float GetCameraY();
	const int GetPlayerMoveX();
	const int GetPlayerMoveY();

	void SetItemTexture(LPDIRECT3DTEXTURE9 apTexture);

	void SetOwner(CGameFrame* apOwner);

private:
	// メンバ変数
	LPDIRECT3DTEXTURE9   mpTexture;
	LPDIRECT3DTEXTURE9	 mpItemTexture;
	D3DXVECTOR3          mPosition[MAPCHIP_NUM_H][MAPCHIP_NUM_W];
	D3DXVECTOR3			 mItemPosition[MAPCHIP_NUM_H][MAPCHIP_NUM_W];
	D3DXMATRIX           mMatrix[MAPCHIP_NUM_H][MAPCHIP_NUM_W];
	D3DXMATRIX			 mItemMatrix[MAPCHIP_NUM_H][MAPCHIP_NUM_W];
	int                  mMapChipList[MAPCHIP_NUM_H][MAPCHIP_NUM_W];
	int					 mItemChipList[MAPCHIP_NUM_H][MAPCHIP_NUM_W];

	eMoveState			 mState;

	bool				 mScrollFlg;
	int					 mScrollCnt;
	float				 mCameraX;
	float				 mCameraY;
	float				 mMoveX;
	float				 mMoveY;
	int					 mMoveWait;

	const float          mScrollWidth = 380.0f;
	const float          mLeftLimit = mScrollWidth;
	const float          mRightLimit = SCRW - mScrollWidth;
	const float          mScrollHeight = 200.0f;
	const float          mUpLimit = mScrollHeight;
	const float          mDownLimit = SCRH - mScrollHeight;

	D3DXVECTOR3          mPlayerPos;
	bool				 mPlayerMoveFlg;
	float				 mPlayerMoveX;
	float				 mPlayerMoveY;

	CGameFrame*  mpOwner;   // オーナー
};
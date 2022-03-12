#pragma once

#include <d3dx9.h>
#include "../../Define.h"
#include "../../enum.h"

#define MAP_HEIGHT  40
#define MAP_WIDTH   40
#define MAPCHIP_NUM_W 51
#define MAPCHIP_NUM_H 50

class CGameFrame;   // クラスの前方宣言

class CItem
{
public:

	CItem();	//コンストラクタ
	~CItem();	//デストラクタ

	//メンバ関数
	void Update();											 //更新
	void Draw(LPD3DXSPRITE apSprite);                        //描画
	void SetTexture(LPDIRECT3DTEXTURE9 apTexture);           //テクスチャ設定
	void LoadMapFile();										 //マップ読み込み
	
	const bool MapHitCheck(eMoveState aMoveState, D3DXVECTOR3 aPos);

	void SetOwner(CGameFrame* apOwner);

private:

	//メンバ変数
	int					 ItemChipList[MAPCHIP_NUM_H][MAPCHIP_NUM_W];			//チップセット
	LPDIRECT3DTEXTURE9   mpTexture;											//画像
	D3DXVECTOR3          mPosition[MAPCHIP_NUM_H][MAPCHIP_NUM_W];			//座標
	D3DXMATRIX           mMatrix[MAPCHIP_NUM_H][MAPCHIP_NUM_W];				//行列

	eMoveState			 mState;

	bool				 mScrollFlg;
	int					 mScrollCnt;
	float				 mCameraX;											//背景のX移動量
	float				 mCameraY;											//背景のY移動量
	float				 mMoveX;
	float				 mMoveY;
	int					 mMoveWait;

	const float          mScrollWidth = 160.0f;
	const float          mLeftLimit = mScrollWidth;
	const float          mRightLimit = SCRW - mScrollWidth;
	const float          mScrollHeight = 120.0f;
	const float          mUpLimit = mScrollHeight;
	const float          mDownLimit = SCRH - mScrollHeight;

	D3DXVECTOR3          mPlayerPos;
	bool				 mPlayerMoveFlg;
	float				 mPlayerMoveX;
	float				 mPlayerMoveY;

	CGameFrame*			 mpOwner;   // オーナー


};


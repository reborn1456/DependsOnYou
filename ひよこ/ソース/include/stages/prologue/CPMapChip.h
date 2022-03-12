#pragma once

#include <d3dx9.h>
#include "../../Define.h"
#include "../../enum.h"

class CGameFrame;   // クラスの前方宣言


class CPMapChip
{
public:
	CPMapChip();
	~CPMapChip();

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
	const bool GetSceneFlg();

	void SetOwner(CGameFrame* apOwner);

private:
	// メンバ変数
	LPDIRECT3DTEXTURE9   mpTexture;
	D3DXVECTOR3          mPosition[MAP_HEIGHT][MAP_WIDTH];
	D3DXMATRIX           mMatrix[MAP_HEIGHT][MAP_WIDTH];
	int                  mMapChipList[MAP_HEIGHT][MAP_WIDTH];

	eMoveState			 mState;

	bool				 mScrollFlg;
	int					 mScrollCnt;
	float				 mCameraX;
	float				 mCameraY;
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

	bool				 mSceneFlg;

	CGameFrame*  mpOwner;   // オーナー
};
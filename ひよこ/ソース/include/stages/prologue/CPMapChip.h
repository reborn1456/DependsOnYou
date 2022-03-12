#pragma once

#include <d3dx9.h>
#include "../../Define.h"
#include "../../enum.h"

class CGameFrame;   // �N���X�̑O���錾


class CPMapChip
{
public:
	CPMapChip();
	~CPMapChip();

	// �����o�֐�
	void Update();                         // �X�V
	void Draw(LPD3DXSPRITE apSprite);                        // �`��
	void SetTexture(LPDIRECT3DTEXTURE9 apTexture);           // �e�N�X�`���ݒ�
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
	// �����o�ϐ�
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

	CGameFrame*  mpOwner;   // �I�[�i�[
};
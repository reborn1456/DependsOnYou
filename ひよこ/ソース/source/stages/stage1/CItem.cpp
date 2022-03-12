#include "../../../include/stages/stage1/CItem.h"
#include "../../../include/CGameFrame.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

CItem::CItem() 
	: ItemChipList()
	, mpTexture(nullptr)
	, mMatrix()
	, mState(eMoveState::eNoMove)
	, mScrollFlg(false)
	, mScrollCnt(0)
	, mMoveX(0)
	, mMoveY(0)
	, mMoveWait(0)
	, mPlayerPos()
	, mPlayerMoveFlg(false)
	, mPlayerMoveX(0)
	, mPlayerMoveY(0)
{
	for (int i = 0; i < MAPCHIP_NUM_H; i++)
	{
		for (int j = 0; j < MAPCHIP_NUM_W; j++)
		{
			mPosition[i][j].x = j * MAP_WIDTH;
			mPosition[i][j].y = i * MAP_HEIGHT;
			mPosition[i][j].z = 0.f;
		}
	}

	mCameraX = -160;
	mCameraY = -160;
}

CItem::~CItem()
{
	//nullチェック
	if (mpTexture != nullptr)
	{
		mpTexture->Release();
		mpTexture = nullptr;
	}
}

void CItem::Update() 
{
	if (mScrollFlg && mScrollCnt == 0)
	{
		mScrollCnt = 1;
		printf("mScrollCnt: %d \n", mScrollCnt);
	}

	if (mScrollFlg)
	{
		mCameraX += mMoveX;
		mCameraY += mMoveY;
		printf("mCamera    X = %.2f \t Y = %.2f \n", mCameraX, mCameraY);
		printf("mCamera(chip)    X = %.2f \t Y = %.2f \n\n", mCameraX / 40, mCameraY / 40);

		mScrollCnt++;
		printf("mScrollCnt: %d \n", mScrollCnt);

		if (mScrollCnt > MOVECOUNT)   // 20回分
		{
			mScrollCnt = 0;
			mScrollFlg = false;
			mMoveX = 0;
			mMoveY = 0;
			printf("mPlayerPos.x = %.2f \t mPlayerPos.y = %.2f \n", mPlayerPos.x / 40, mPlayerPos.y / 40);
		}
	}
	else
	{
		mScrollCnt = 0;
	}

	// 移動行列作成
	for (int i = 0; i < MAPCHIP_NUM_H; i++)
	{
		for (int j = 0; j < MAPCHIP_NUM_W; j++)
		{
			D3DXMatrixTranslation(&mMatrix[i][j], mPosition[i][j].x + mCameraX, mPosition[i][j].y + mCameraY, mPosition[i][j].z);
		}
	}
}

//描画
void CItem::Draw(LPD3DXSPRITE apSprite)
{
	RECT rcItemChip;

	for (int i = 0; i < MAPCHIP_NUM_H; i++) {
		for (int j = 0; j < MAPCHIP_NUM_W; j++) {
			switch (ItemChipList[i][j])
			{
			case 0:
				rcItemChip = { 0,0,MAP_WIDTH,MAP_HEIGHT };
				break;
			case 1:
				rcItemChip = { MAP_WIDTH,0,MAP_WIDTH * 2,MAP_HEIGHT };
				break;
			case 2:
				rcItemChip = { MAP_WIDTH * 2,0,MAP_WIDTH * 3,MAP_HEIGHT };
				break;
			case 3:
				rcItemChip = { MAP_WIDTH * 3,0,MAP_WIDTH * 4,MAP_HEIGHT };
				break;
			case 4:
				rcItemChip = { MAP_WIDTH * 4,0,MAP_WIDTH * 5,MAP_HEIGHT };
				break;
			case 5:
				rcItemChip = { MAP_WIDTH * 5,0,MAP_WIDTH * 6,MAP_HEIGHT };
				break;
			case 6:
				rcItemChip = { MAP_WIDTH * 6,0,MAP_WIDTH * 7,MAP_HEIGHT };
				break;
			case 7:
				rcItemChip = { MAP_WIDTH * 7,0,MAP_WIDTH * 8,MAP_HEIGHT };
				break;
			case 8:
				rcItemChip = { 0,MAP_HEIGHT,MAP_WIDTH,MAP_HEIGHT * 2 };
				break;
			case 9:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT,MAP_WIDTH * 2,MAP_HEIGHT * 2 };
				break;
			case 10:
				rcItemChip = { MAP_WIDTH * 2 ,MAP_HEIGHT,MAP_WIDTH * 3,MAP_HEIGHT * 2 };
				break;
			case 11:
				rcItemChip = { MAP_WIDTH * 3 ,MAP_HEIGHT,MAP_WIDTH * 4,MAP_HEIGHT * 2 };
				break;
			case 12:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT,MAP_WIDTH * 5,MAP_HEIGHT * 2 };
				break;
			case 13:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT,MAP_WIDTH * 6,MAP_HEIGHT * 2 };
				break;
			case 14:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT,MAP_WIDTH * 7,MAP_HEIGHT * 2 };
				break;
			case 15:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT,MAP_WIDTH * 8,MAP_HEIGHT * 2 };
				break;
			case 16:
				rcItemChip = { 0,MAP_HEIGHT * 2,MAP_WIDTH,MAP_HEIGHT * 3 };
				break;
			case 17:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 2,MAP_WIDTH * 2,MAP_HEIGHT * 3 };
				break;
			case 18:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 2,MAP_WIDTH * 3,MAP_HEIGHT * 3 };
				break;
			case 19:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 2,MAP_WIDTH * 4,MAP_HEIGHT * 3 };
				break;
			case 20:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 2,MAP_WIDTH * 5,MAP_HEIGHT * 3 };
				break;
			case 21:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 2,MAP_WIDTH * 6,MAP_HEIGHT * 3 };
				break;
			case 22:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 2,MAP_WIDTH * 7,MAP_HEIGHT * 3 };
				break;
			case 23:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 2,MAP_WIDTH * 8,MAP_HEIGHT * 3 };
				break;
			case 24:
				rcItemChip = { 0 ,MAP_HEIGHT * 3,MAP_WIDTH,MAP_HEIGHT * 4 };
				break;
			case 25:
				rcItemChip = { MAP_WIDTH,MAP_HEIGHT * 3,MAP_WIDTH * 2,MAP_HEIGHT * 4 };
				break;
			case 26:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 3,MAP_WIDTH * 3,MAP_HEIGHT * 4 };
				break;
			case 27:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 3,MAP_WIDTH * 4,MAP_HEIGHT * 4 };
				break;
			case 28:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 3,MAP_WIDTH * 5,MAP_HEIGHT * 4 };
				break;
			case 29:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 3,MAP_WIDTH * 6,MAP_HEIGHT * 4 };
				break;
			case 30:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 3,MAP_WIDTH * 7,MAP_HEIGHT * 4 };
				break;
			case 31:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 3,MAP_WIDTH * 8,MAP_HEIGHT * 4 };
				break;
			case 32:
				rcItemChip = { 0 ,MAP_HEIGHT * 4,MAP_WIDTH,MAP_HEIGHT * 5 };
				break;
			case 33:
				rcItemChip = { MAP_WIDTH,MAP_HEIGHT * 4,MAP_WIDTH * 2,MAP_HEIGHT * 5 };
				break;
			case 34:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 4,MAP_WIDTH * 3,MAP_HEIGHT * 5 };
				break;
			case 35:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 4,MAP_WIDTH * 4,MAP_HEIGHT * 5 };
				break;
			case 36:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 4,MAP_WIDTH * 5,MAP_HEIGHT * 5 };
				break;
			case 37:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 4,MAP_WIDTH * 6,MAP_HEIGHT * 5 };
				break;
			case 38:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 4,MAP_WIDTH * 7,MAP_HEIGHT * 5 };
				break;
			case 39:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 4,MAP_WIDTH * 8,MAP_HEIGHT * 5 };
				break;
			case 40:
				rcItemChip = { 0 ,MAP_HEIGHT * 5,MAP_WIDTH,MAP_HEIGHT * 6 };
				break;
			case 41:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 5,MAP_WIDTH * 2,MAP_HEIGHT * 6 };
				break;
			case 42:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 5,MAP_WIDTH * 3,MAP_HEIGHT * 6 };
				break;
			case 43:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 5,MAP_WIDTH * 4,MAP_HEIGHT * 6 };
				break;
			case 44:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 5,MAP_WIDTH * 5,MAP_HEIGHT * 6 };
				break;
			case 45:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 5,MAP_WIDTH * 6,MAP_HEIGHT * 6 };
				break;
			case 46:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 5,MAP_WIDTH * 7,MAP_HEIGHT * 6 };
				break;
			case 47:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 5,MAP_WIDTH * 8,MAP_HEIGHT * 6 };
				break;
			case 48:
				rcItemChip = { 0 ,MAP_HEIGHT * 6,MAP_WIDTH,MAP_HEIGHT * 7 };
				break;
			case 49:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 6,MAP_WIDTH * 2,MAP_HEIGHT * 7 };
				break;
			case 50:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 6,MAP_WIDTH * 3,MAP_HEIGHT * 7 };
				break;
			case 51:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 6,MAP_WIDTH * 4,MAP_HEIGHT * 7 };
				break;
			case 52:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 6,MAP_WIDTH * 5,MAP_HEIGHT * 7 };
				break;
			case 53:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 6,MAP_WIDTH * 6,MAP_HEIGHT * 7 };
				break;
			case 54:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 6,MAP_WIDTH * 7,MAP_HEIGHT * 7 };
				break;
			case 55:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 6,MAP_WIDTH * 8,MAP_HEIGHT * 7 };
				break;
			case 56:
				rcItemChip = { 0 ,MAP_HEIGHT * 7,MAP_WIDTH,MAP_HEIGHT * 8 };
				break;
			case 57:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 7,MAP_WIDTH * 2,MAP_HEIGHT * 8 };
				break;
			case 58:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 7,MAP_WIDTH * 3,MAP_HEIGHT * 8 };
				break;
			case 59:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 7,MAP_WIDTH * 4,MAP_HEIGHT * 8 };
				break;
			case 60:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 7,MAP_WIDTH * 5,MAP_HEIGHT * 8 };
				break;
			case 61:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 7,MAP_WIDTH * 6,MAP_HEIGHT * 8 };
				break;
			case 62:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 7,MAP_WIDTH * 7,MAP_HEIGHT * 8 };
				break;
			case 63:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 7,MAP_WIDTH * 8,MAP_HEIGHT * 8 };
				break;
			case 64:
				rcItemChip = { 0 ,MAP_HEIGHT * 8,MAP_WIDTH,MAP_HEIGHT * 9 };
				break;
			case 65:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 8,MAP_WIDTH * 2,MAP_HEIGHT * 9 };
				break;
			case 66:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 8,MAP_WIDTH * 3,MAP_HEIGHT * 9 };
				break;
			case 67:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 8,MAP_WIDTH * 4,MAP_HEIGHT * 9 };
				break;
			case 68:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 8,MAP_WIDTH * 5,MAP_HEIGHT * 9 };
				break;
			case 69:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 8,MAP_WIDTH * 6,MAP_HEIGHT * 9 };
				break;
			case 70:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 8,MAP_WIDTH * 7,MAP_HEIGHT * 9 };
				break;
			case 71:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 8,MAP_WIDTH * 8,MAP_HEIGHT * 9 };
				break;
			case 72:
				rcItemChip = { 0 ,MAP_HEIGHT * 9,MAP_WIDTH,MAP_HEIGHT * 10 };
				break;
			case 73:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 9,MAP_WIDTH * 2,MAP_HEIGHT * 10 };
				break;
			case 74:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 9,MAP_WIDTH * 3,MAP_HEIGHT * 10 };
				break;
			case 75:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 9,MAP_WIDTH * 4,MAP_HEIGHT * 10 };
				break;
			case 76:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 9,MAP_WIDTH * 5,MAP_HEIGHT * 10 };
				break;
			case 77:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 9,MAP_WIDTH * 6,MAP_HEIGHT * 10 };
				break;
			case 78:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 9,MAP_WIDTH * 7,MAP_HEIGHT * 10 };
				break;
			case 79:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 9,MAP_WIDTH * 8,MAP_HEIGHT * 10 };
				break;
			case 80:
				rcItemChip = { 0 ,MAP_HEIGHT * 10,MAP_WIDTH,MAP_HEIGHT * 11 };
				break;
			case 81:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 10,MAP_WIDTH * 2,MAP_HEIGHT * 11 };
				break;
			case 82:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 10,MAP_WIDTH * 3,MAP_HEIGHT * 11 };
				break;
			case 83:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 10,MAP_WIDTH * 4,MAP_HEIGHT * 11 };
				break;
			case 84:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 10,MAP_WIDTH * 5,MAP_HEIGHT * 11 };
				break;
			case 85:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 10,MAP_WIDTH * 6,MAP_HEIGHT * 11 };
				break;
			case 86:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 10,MAP_WIDTH * 7,MAP_HEIGHT * 11 };
				break;
			case 87:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 10,MAP_WIDTH * 8,MAP_HEIGHT * 11 };
				break;
			case 88:
				rcItemChip = { 0 ,MAP_HEIGHT * 11,MAP_WIDTH,MAP_HEIGHT * 12 };
				break;
			case 89:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 11,MAP_WIDTH * 2,MAP_HEIGHT * 12 };
				break;
			case 90:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 11,MAP_WIDTH * 3,MAP_HEIGHT * 12 };
				break;
			case 91:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 11,MAP_WIDTH * 4,MAP_HEIGHT * 12 };
				break;
			case 92:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 11,MAP_WIDTH * 5,MAP_HEIGHT * 12 };
				break;
			case 93:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 11,MAP_WIDTH * 6,MAP_HEIGHT * 12 };
				break;
			case 94:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 11,MAP_WIDTH * 7,MAP_HEIGHT * 12 };
				break;
			case 95:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 11,MAP_WIDTH * 8,MAP_HEIGHT * 12 };
				break;
			case 96:
				rcItemChip = { 0 ,MAP_HEIGHT * 12,MAP_WIDTH,MAP_HEIGHT * 13 };
				break;
			case 97:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 12,MAP_WIDTH * 2,MAP_HEIGHT * 13 };
				break;
			case 98:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 12,MAP_WIDTH * 3,MAP_HEIGHT * 13 };
				break;
			case 99:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 12,MAP_WIDTH * 4,MAP_HEIGHT * 13 };
				break;
			case 100:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 12,MAP_WIDTH * 5,MAP_HEIGHT * 13 };
				break;
			case 101:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 12,MAP_WIDTH * 6,MAP_HEIGHT * 13 };
				break;
			case 102:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 12,MAP_WIDTH * 7,MAP_HEIGHT * 13 };
				break;
			case 103:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 12,MAP_WIDTH * 8,MAP_HEIGHT * 13 };
				break;
			case 104:
				rcItemChip = { 0 ,MAP_HEIGHT * 13,MAP_WIDTH,MAP_HEIGHT * 14 };
				break;
			case 105:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 13,MAP_WIDTH * 2,MAP_HEIGHT * 14 };
				break;
			case 106:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 13,MAP_WIDTH * 3,MAP_HEIGHT * 14 };
				break;
			case 107:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 13,MAP_WIDTH * 4,MAP_HEIGHT * 14 };
				break;
			case 108:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 13,MAP_WIDTH * 5,MAP_HEIGHT * 14 };
				break;
			case 109:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 13,MAP_WIDTH * 6,MAP_HEIGHT * 14 };
				break;
			case 110:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 13,MAP_WIDTH * 7,MAP_HEIGHT * 14 };
				break;
			case 111:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 13,MAP_WIDTH * 8,MAP_HEIGHT * 14 };
				break;
			case 112:
				rcItemChip = { 0 ,MAP_HEIGHT * 14,MAP_WIDTH,MAP_HEIGHT * 15 };
				break;
			case 113:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 14,MAP_WIDTH * 2,MAP_HEIGHT * 15 };
				break;
			case 114:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 14,MAP_WIDTH * 3,MAP_HEIGHT * 15 };
				break;
			case 115:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 14,MAP_WIDTH * 4,MAP_HEIGHT * 15 };
				break;
			case 116:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 14,MAP_WIDTH * 5,MAP_HEIGHT * 15 };
				break;
			case 117:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 14,MAP_WIDTH * 6,MAP_HEIGHT * 15 };
				break;
			case 118:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 14,MAP_WIDTH * 7,MAP_HEIGHT * 15 };
				break;
			case 119:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 14,MAP_WIDTH * 8,MAP_HEIGHT * 15 };
				break;
			case 120:
				rcItemChip = { 0 ,MAP_HEIGHT * 15,MAP_WIDTH,MAP_HEIGHT * 16 };
				break;
			case 121:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 15,MAP_WIDTH * 2,MAP_HEIGHT * 16 };
				break;
			case 122:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 15 ,MAP_WIDTH * 3,MAP_HEIGHT * 16 };
				break;
			case 123:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 15,MAP_WIDTH * 4,MAP_HEIGHT * 16 };
				break;
			case 124:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 15,MAP_WIDTH * 5,MAP_HEIGHT * 16 };
				break;
			case 125:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 15,MAP_WIDTH * 6,MAP_HEIGHT * 16 };
				break;
			case 126:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 15,MAP_WIDTH * 7,MAP_HEIGHT * 16 };
				break;
			case 127:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 15,MAP_WIDTH * 8,MAP_HEIGHT * 16 };
				break;
			case 128:
				rcItemChip = { 0 ,MAP_HEIGHT * 16,MAP_WIDTH,MAP_HEIGHT * 17 };
				break;
			case 129:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 16,MAP_WIDTH * 2,MAP_HEIGHT * 17 };
				break;
			case 130:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 16,MAP_WIDTH * 3,MAP_HEIGHT * 17 };
				break;
			case 131:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 16,MAP_WIDTH * 4,MAP_HEIGHT * 17 };
				break;
			case 132:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 16,MAP_WIDTH * 5,MAP_HEIGHT * 17 };
				break;
			case 133:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 16,MAP_WIDTH * 6,MAP_HEIGHT * 17 };
				break;
			case 134:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 16,MAP_WIDTH * 7,MAP_HEIGHT * 17 };
				break;
			case 135:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 16,MAP_WIDTH * 8,MAP_HEIGHT * 17 };
				break;
			case 136:
				rcItemChip = { 0 ,MAP_HEIGHT * 17,MAP_WIDTH,MAP_HEIGHT * 18 };
				break;
			case 137:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 17,MAP_WIDTH * 2,MAP_HEIGHT * 18 };
				break;
			case 138:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 17,MAP_WIDTH * 3,MAP_HEIGHT * 18 };
				break;
			case 139:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 17,MAP_WIDTH * 4,MAP_HEIGHT * 18 };
				break;
			case 140:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 17,MAP_WIDTH * 5,MAP_HEIGHT * 18 };
				break;
			case 141:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 17,MAP_WIDTH * 6,MAP_HEIGHT * 18 };
				break;
			case 142:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 17,MAP_WIDTH * 7,MAP_HEIGHT * 18 };
				break;
			case 143:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 17,MAP_WIDTH * 8,MAP_HEIGHT * 18 };
				break;
			case 144:
				rcItemChip = { 0 ,MAP_HEIGHT * 18,MAP_WIDTH,MAP_HEIGHT * 19 };
				break;
			case 145:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 18,MAP_WIDTH * 2,MAP_HEIGHT * 19 };
				break;
			case 146:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 18,MAP_WIDTH * 3,MAP_HEIGHT * 19 };
				break;
			case 147:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 18,MAP_WIDTH * 4,MAP_HEIGHT * 19 };
				break;
			case 148:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 18,MAP_WIDTH * 5,MAP_HEIGHT * 19 };
				break;
			case 149:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 18,MAP_WIDTH * 6,MAP_HEIGHT * 19 };
				break;
			case 150:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 18,MAP_WIDTH * 7,MAP_HEIGHT * 19 };
				break;
			case 151:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 18,MAP_WIDTH * 8,MAP_HEIGHT * 19 };
				break;
			case 152:
				rcItemChip = { 0 ,MAP_HEIGHT * 19,MAP_WIDTH,MAP_HEIGHT * 20 };
				break;
			case 153:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 19,MAP_WIDTH * 2,MAP_HEIGHT * 20 };
				break;
			case 154:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 19,MAP_WIDTH * 3,MAP_HEIGHT * 20 };
				break;
			case 155:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 19,MAP_WIDTH * 4,MAP_HEIGHT * 20 };
				break;
			case 156:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 19,MAP_WIDTH * 5,MAP_HEIGHT * 20 };
				break;
			case 157:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 19,MAP_WIDTH * 6,MAP_HEIGHT * 20 };
				break;
			case 158:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 19,MAP_WIDTH * 7,MAP_HEIGHT * 20 };
				break;
			case 159:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 19,MAP_WIDTH * 8,MAP_HEIGHT * 20 };
				break;
			case 160:
				rcItemChip = { 0 ,MAP_HEIGHT * 20,MAP_WIDTH,MAP_HEIGHT * 21 };
				break;
			case 161:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 20,MAP_WIDTH * 2,MAP_HEIGHT * 21 };
				break;
			case 162:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 20,MAP_WIDTH * 3,MAP_HEIGHT * 21 };
				break;
			case 163:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 20,MAP_WIDTH * 4,MAP_HEIGHT * 21 };
				break;
			case 164:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 20,MAP_WIDTH * 5,MAP_HEIGHT * 21 };
				break;
			case 165:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 20,MAP_WIDTH * 6,MAP_HEIGHT * 21 };
				break;
			case 166:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 20,MAP_WIDTH * 7,MAP_HEIGHT * 21 };
				break;
			case 167:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 20,MAP_WIDTH * 8,MAP_HEIGHT * 21 };
				break;
			case 168:
				rcItemChip = { 0 ,MAP_HEIGHT * 21,MAP_WIDTH,MAP_HEIGHT * 22 };
				break;
			case 169:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 21,MAP_WIDTH * 2,MAP_HEIGHT * 22 };
				break;
			case 170:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 21,MAP_WIDTH * 3,MAP_HEIGHT * 22 };
				break;
			case 171:
				rcItemChip = { MAP_WIDTH * 3,MAP_HEIGHT * 21,MAP_WIDTH * 4,MAP_HEIGHT * 22 };
				break;
			case 172:
				rcItemChip = { MAP_WIDTH * 4,MAP_HEIGHT * 21,MAP_WIDTH * 5,MAP_HEIGHT * 22 };
				break;
			case 173:
				rcItemChip = { MAP_WIDTH * 5,MAP_HEIGHT * 21,MAP_WIDTH * 6,MAP_HEIGHT * 22 };
				break;
			case 174:
				rcItemChip = { MAP_WIDTH * 6,MAP_HEIGHT * 21,MAP_WIDTH * 7,MAP_HEIGHT * 22 };
				break;
			case 175:
				rcItemChip = { MAP_WIDTH * 7,MAP_HEIGHT * 21,MAP_WIDTH * 8,MAP_HEIGHT * 22 };
				break;
			case 176:
				rcItemChip = { 0 ,MAP_HEIGHT * 22,MAP_WIDTH,MAP_HEIGHT * 23 };
				break;
			case 177:
				rcItemChip = { MAP_WIDTH ,MAP_HEIGHT * 22,MAP_WIDTH * 2,MAP_HEIGHT * 23 };
				break;
			case 178:
				rcItemChip = { MAP_WIDTH * 2,MAP_HEIGHT * 22,MAP_WIDTH * 3,MAP_HEIGHT * 23 };
				break;

			case 999:
				rcItemChip = {};

			}
			apSprite->SetTransform(&mMatrix[i][j]);
			apSprite->Draw(mpTexture, &rcItemChip, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		}
	}
}

//テクスチャ
void CItem::SetTexture(LPDIRECT3DTEXTURE9 apTexture)
{
	//コンパイルの時に読み込めてなかったらはじくように
	_ASSERT_EXPR(apTexture != nullptr, L"渡されたマップのテクスチャが空です");

	if (apTexture == nullptr)
	{
		return;
		// 早期リターン
		// テクスチャが空なので処理する意味が無い
	}
	mpTexture = apTexture;
}

//マップ読み込み
void CItem::LoadMapFile()
{
	ifstream map("resources/data/csv/Item.csv");

	if (!map)
	{
		_ASSERT_EXPR(map, "ERROR: File Open");
	}
	else
	{
		string s;
		int i = 0, j = 0;


		// ファイルの中身を一行ずつ読み取る
		while (getline(map, s))   // 改行まで読み込み、改行コードを削除
		{
			istringstream line(s);   // num(string型) に入れている一行を line(stream型) の中に入れる

			// 区切り文字がなくなるまで文字を区切っていく
			while (getline(line, s, ','))   // 区切る処理
			{
				// 区切られた文字が配列に入れる
				//printf("<%d>", s.length());
				//cout << s << "---";
				ItemChipList[i][j] = stoi(s);
				j++;
			}

			i++;
			j = 0;
		}

		map.close();

		//コンソール表示用
		for (int i = 0; i < MAPCHIP_NUM_H; i++)
		{
			for (int j = 0; j < MAPCHIP_NUM_W; j++)
			{
				printf("%2d", ItemChipList[i][j]);
			}
			printf("\n");
		}
	}
}

const bool CItem::MapHitCheck(eMoveState aMoveState, D3DXVECTOR3 aPos)
{
	mPlayerMoveFlg = false;

	mPlayerPos.x = aPos.x;
	mPlayerPos.y = aPos.y;

	//自機固定スクロール、プレイヤーではなくマップチップを移動
	mMoveX = 0.0f;   //移動量
	mMoveY = 0.0f;   //移動量

	mPlayerMoveX = 0;
	mPlayerMoveY = 0;

	// player movement
	switch (aMoveState)
	{
	case eMoveState::eNoMove:
		break;
	case eMoveState::eMoveUp:
		mPlayerMoveFlg = true;
		mPlayerMoveY = -MOVESPEED;
		break;
	case eMoveState::eMoveDown:
		mPlayerMoveFlg = true;
		mPlayerMoveY = MOVESPEED;
		break;
	case eMoveState::eMoveLeft:
		mPlayerMoveFlg = true;
		mPlayerMoveX = -MOVESPEED;
		break;
	case eMoveState::eMoveRight:
		mPlayerMoveFlg = true;
		mPlayerMoveX = MOVESPEED;
		break;
	default:
		break;
	}



	//the x and y of player in the next frame, future x and y
	float nextPlayerX = (mPlayerPos.x + mPlayerMoveX) - mCameraX;
	float nextPlayerY = (mPlayerPos.y + mPlayerMoveY) - mCameraY;
	printf("mPlayerPos.x = %.2f \t mPlayerPos.y = %.2f \n", mPlayerPos.x / 40, mPlayerPos.y / 40);
	printf("nextPlayerX = %.2f \t nextPlayerY = %.2f \n", nextPlayerX / 40, nextPlayerY / 40);

	float globalPlayerX = mPlayerPos.x - mCameraX;
	float globalPlayerY = mPlayerPos.y - mCameraY;
	printf("globalPlayerX = %.2f \t globalPlayerY = %.2f \n", globalPlayerX / 40, globalPlayerY / 40);


	// check if the character is out of frame
	// camera movement
	if (mPlayerPos.x + mPlayerMoveX < mLeftLimit)
	{
		mMoveX = MOVESPEED;
		mPlayerMoveX = 0;
		mPlayerPos.x = mLeftLimit;
		mPlayerMoveFlg = false;
		mScrollFlg = true;
	}
	else if (mPlayerPos.x + CHARA_SIZE + mPlayerMoveX > mRightLimit)
	{
		mMoveX = -MOVESPEED;
		mPlayerMoveX = 0;
		mPlayerPos.x = mRightLimit - CHARA_SIZE;
		mPlayerMoveFlg = false;
		mScrollFlg = true;
	}

	if (mPlayerPos.y + mPlayerMoveY < mUpLimit)
	{
		mMoveY = MOVESPEED;
		mPlayerMoveY = 0;
		mPlayerPos.y = mUpLimit;
		mPlayerMoveFlg = false;
		mScrollFlg = true;
	}
	else if (mPlayerPos.y + CHARA_SIZE + mPlayerMoveY > mDownLimit)
	{
		mMoveY = -MOVESPEED;
		mPlayerMoveY = 0;
		mPlayerPos.y = mDownLimit - CHARA_SIZE;
		mPlayerMoveFlg = false;
		mScrollFlg = true;
	}




	int mapChipi;
	int mapChipj;
	if (aMoveState == eMoveUp || aMoveState == eMoveLeft)
	{
		mapChipi = nextPlayerY / 40;
		mapChipj = nextPlayerX / 40;
		printf("mapChipi = %d \t mapChipj = %d \n\n", mapChipi, mapChipj);
	}
	else if (aMoveState == eMoveDown || aMoveState == eMoveRight)
	{
		mapChipi = (nextPlayerY + (40 - MOVESPEED)) / 40;
		mapChipj = (nextPlayerX + (40 - MOVESPEED)) / 40;
		printf("mapChipi = %d \t mapChipj = %d \n\n", mapChipi, mapChipj);
	}

	int mapChipNum = ItemChipList[mapChipi][mapChipj];
	printf("mapChipNum = %d\n", mapChipNum);
	if (mapChipNum != 999)
	{
		//short form of the x and y of the mapChip
		const float chipX = mPosition[mapChipi][mapChipj].x;
		const float chipY = mPosition[mapChipi][mapChipj].y;
		printf("chipX = %.2f \t chipY = %.2f \n", chipX, chipY);

		if (aMoveState == eMoveUp || aMoveState == eMoveDown)
		{
			//player's 左 and block's 右（縦判定）
			if ((mPlayerPos.x - mCameraX) < chipX + MAPCHIP_SIZE && (mPlayerPos.x - mCameraX) + CHARA_SIZE > chipX)
			{
				//blockの上からの判定
				if (nextPlayerY + CHARA_SIZE >= chipY && nextPlayerY <= chipY)
				{
					mPlayerPos.y = (chipY + mCameraY) - CHARA_SIZE;
					mPlayerMoveY = 0;
					mMoveY = 0;
					mPlayerMoveFlg = false;
					printf("%.2f \n", mPlayerPos.y);
				}
				//blockの下からの判定
				else if (nextPlayerY <= chipY + MAPCHIP_SIZE && nextPlayerY + CHARA_SIZE >= chipY + MAPCHIP_SIZE)
				{
					mPlayerPos.y = (chipY + mCameraY) + MAPCHIP_SIZE;
					mPlayerMoveY = 0;
					mMoveY = 0;
					mPlayerMoveFlg = false;
					printf("%.2f \n", mPlayerPos.y);
				}
			}
		}

		if (aMoveState == eMoveLeft || aMoveState == eMoveRight)
		{
			//player's 下 and block's 上（横判定）
			if ((mPlayerPos.y - mCameraY) + CHARA_SIZE > chipY && (mPlayerPos.y - mCameraY) < chipY + MAPCHIP_SIZE)
			{
				//blockの左からの判定
				if (nextPlayerX + CHARA_SIZE >= chipX && nextPlayerX <= chipX)
				{
					mPlayerPos.x = (chipX + mCameraX) - CHARA_SIZE;
					mPlayerMoveX = 0;
					mMoveX = 0;
					mPlayerMoveFlg = false;
					printf("%.2f \n", mPlayerPos.x);
				}
				//blockの右からの判定
				else if (nextPlayerX <= chipX + MAPCHIP_SIZE && nextPlayerX + CHARA_SIZE >= chipX + MAPCHIP_SIZE)
				{
					mPlayerPos.x = (chipX + mCameraX) + MAPCHIP_SIZE;
					mPlayerMoveX = 0;
					mMoveX = 0;
					mPlayerMoveFlg = false;
					printf("%.2f \n", mPlayerPos.x);
				}
			}
		}

	}



	return mPlayerMoveFlg;
}



//オーナー
void CItem::SetOwner(CGameFrame* apOwner)
{
	if (apOwner == nullptr)
	{
		_ASSERT_EXPR(apOwner != nullptr, L"なんでオーナーNULLなん？");
		return;
	}
	mpOwner = apOwner;
	return;
}
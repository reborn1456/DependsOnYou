#include "../../../include/CGameFrame.h"
#include "../../../include/stages/prologue/CPMapChip.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */
#include <sstream>

#include <string>
#include <fstream>
using namespace std;

CPMapChip::CPMapChip()
	: mpTexture(nullptr)
	, mPosition()
	, mMatrix()
	, mMapChipList()
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
	, mSceneFlg(false)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			mPosition[i][j].x = j * MAPCHIP_SIZE;
			mPosition[i][j].y = i * MAPCHIP_SIZE;
			mPosition[i][j].z = 0.f;
		}
	}
	mCameraX = -160;
	mCameraY = -40;

	//mPlayerPos = mpOwner->GetPlayer()->GetPlayerPosition();
}

CPMapChip::~CPMapChip()
{
	//safe release
	if (mpTexture != nullptr)   // if it is notyet destroyed, not 0
	{
		mpTexture->Release();
		mpTexture = nullptr;   // put null(0) inside it just incase it contains any rubbish which is still inside after release
	}
}

void CPMapChip::Update()
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
		printf("mCamera    X = %.2f \t Y = %.2f \n\n", mCameraX / 40, mCameraY / 40);

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
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			D3DXMatrixTranslation(&mMatrix[i][j], mPosition[i][j].x + mCameraX, mPosition[i][j].y + mCameraY, mPosition[i][j].z);
		}
	}
}

void CPMapChip::Draw(LPD3DXSPRITE apSprite)
{
	// マップチップ
	RECT rCPMapChip;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (mMapChipList[i][j] == 0)
			{
				rCPMapChip = { 0, 0, 40, 40 };
			}
			if (mMapChipList[i][j] == 1)
			{
				rCPMapChip = { 40, 0, 80, 40 };
			}
			if (mMapChipList[i][j] == 2)
			{
				rCPMapChip = { 80, 0, 120, 40 };
			}
			if (mMapChipList[i][j] == 3)
			{
				rCPMapChip = { 120, 0, 160, 40 };
			}
			if (mMapChipList[i][j] == 4)
			{
				rCPMapChip = { 0, 40, 40, 80 };
			}
			apSprite->SetTransform(&mMatrix[i][j]);
			apSprite->Draw(mpTexture, &rCPMapChip, &D3DXVECTOR3(0.0f, 0.0f, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CPMapChip::SetTexture(LPDIRECT3DTEXTURE9 apTexture)
{
	if (apTexture == nullptr)
	{
		// new version assert which will NOT appear when build in release mode
		// Capital L is needed infront of the "" for showing sentance when you want to show japanese. If without, it will show corruption of text
		_ASSERT_EXPR(apTexture != nullptr, L"渡されたテクスチャ情報が空です");


		return;
		// 早期リターン
		// テクスチャが空なので処理する意味が無い
	}
	mpTexture = apTexture;
}

void CPMapChip::LoadMapFile()
{
	ifstream map("resources/data/csv/PrologueMap.csv");

	//map.open("Map.csv");

	if (!map)
	{
		// new version assert which will NOT appear when build in release mode
		// Capital L is needed infront of the "" for showing sentance when you want to show japanese. If without, it will show corruption of text
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
				mMapChipList[i][j] = stoi(s);
				j++;
			}

			i++;
			j = 0;
		}

		map.close();



		//FILE *fp;
		//int error;

		//error = fopen_s(&fp, "Map.csv", "r");
		//// new version assert which will NOT appear when build in release mode
		//// Capital L is needed infront of the "" for showing sentance when you want to show japanese. If without, it will show corruption of text
		//_ASSERT_EXPR(error != 0, "");


		////to set the numbers in Map.csv to mMapChipList array
		//printf("OK \n");

		//for (int i = 0; i < MAP_HEIGHT; i++)
		//{
		//	for (int j = 0; j < MAP_WIDTH; j++)
		//	{
		//		fscanf_s(fp, "%d", &mMapChipList[i][j]);
		//	}
		//}

		//fclose(fp);


		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				printf("%d", mMapChipList[i][j]);
			}
			printf("\n");
		}
	}

}

const bool CPMapChip::MapHitCheck(eMoveState aMoveState, D3DXVECTOR3 aPos)
{
	mPlayerMoveFlg = false;

	mPlayerPos.x = aPos.x;
	mPlayerPos.y = aPos.y;

	//自機固定スクロール、プレイヤーではなくマップチップを移動
	mMoveX = 0.0f;   //移動量
	mMoveY = 0.0f;   //移動量

	mPlayerMoveX = 0;
	mPlayerMoveY = 0;

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

	/*mCameraX += mMoveX;
	mCameraY += mMoveY;*/

	//the x and y of player in the next frame, future x and y
	float nextPlayerX = (mPlayerPos.x + mPlayerMoveX) - mCameraX;
	float nextPlayerY = (mPlayerPos.y + mPlayerMoveY) - mCameraY;
	printf("mPlayerPos.x = %.2f \t mPlayerPos.y = %.2f \n", mPlayerPos.x / 40, mPlayerPos.y / 40);
	printf("nextPlayerX = %.2f \t nextPlayerY = %.2f \n", nextPlayerX / 40, nextPlayerY / 40);

	float globalPlayerX = mPlayerPos.x - mCameraX;
	float globalPlayerY = mPlayerPos.y - mCameraY;
	printf("globalPlayerX = %.2f \t globalPlayerY = %.2f \n", globalPlayerX / 40, globalPlayerY / 40);


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
	/*mapChipi = nextPlayerY / 40;
	mapChipj = nextPlayerX / 40;
	printf("mapChipi = %d \t mapChipj = %d \n\n", mapChipi, mapChipj);*/

	if (mMapChipList[mapChipi][mapChipj] == 2)
	{
		//short form of the x and y of the mapChip
		const float chipX = mPosition[mapChipi][mapChipj].x;
		const float chipY = mPosition[mapChipi][mapChipj].y;

		//player's 下 and block's 上
		if ((mPlayerPos.y - mCameraY) + CHARA_SIZE > chipY && (mPlayerPos.y - mCameraY) < chipY + MAPCHIP_SIZE)
		{
			//blockの左からの判定
			if (nextPlayerX + CHARA_SIZE >= chipX && nextPlayerX <= chipX)
			{
				mPlayerPos.x = (chipX + mCameraX) - CHARA_SIZE;
				mPlayerMoveX = 0;
				printf("%.2f \n", mPlayerPos.x);
			}
			//blockの右からの判定
			else if (nextPlayerX <= chipX + MAPCHIP_SIZE && nextPlayerX + CHARA_SIZE >= chipX + MAPCHIP_SIZE)
			{
				mPlayerPos.x = (chipX + mCameraX) + MAPCHIP_SIZE;
				mPlayerMoveX = 0;
				printf("%.2f \n", mPlayerPos.x);
			}
		}

		//player's 左 and block's 右
		if ((mPlayerPos.x - mCameraX) < chipX + MAPCHIP_SIZE && (mPlayerPos.x - mCameraX) + CHARA_SIZE > chipX)
		{
			//blockの上からの判定
			if (nextPlayerY + CHARA_SIZE >= chipY && nextPlayerY <= chipY)
			{
				mPlayerPos.y = (chipY + mCameraY) - CHARA_SIZE;
				mPlayerMoveY = 0;
			}
			//blockの下からの判定
			else if (nextPlayerY <= chipY + MAPCHIP_SIZE && nextPlayerY + CHARA_SIZE >= chipY + MAPCHIP_SIZE)
			{
				mPlayerPos.y = (chipY + mCameraY) + MAPCHIP_SIZE;
				mPlayerMoveY = 0;
			}
		}
	}

	if (mMapChipList[mapChipi][mapChipj] == 4)
	{
		mSceneFlg = true;
	}

	return mPlayerMoveFlg;
}

const D3DXVECTOR3 CPMapChip::GetPlayerPos()
{
	return mPlayerPos;
}

const float CPMapChip::GetCameraX()
{
	return mCameraX;
}

const float CPMapChip::GetCameraY()
{
	return mCameraY;
}

const int CPMapChip::GetPlayerMoveX()
{
	return mPlayerMoveX;
}

const int CPMapChip::GetPlayerMoveY()
{
	return mPlayerMoveY;
}

const bool CPMapChip::GetSceneFlg()
{
	return mSceneFlg;
}

void CPMapChip::SetOwner(CGameFrame* apOwner)
{
	mpOwner = apOwner;
}
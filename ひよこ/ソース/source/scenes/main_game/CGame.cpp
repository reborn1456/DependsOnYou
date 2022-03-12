#include "../../../include/CGameFrame.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */


CGame::CGame()
	: mStage(STAGE1_PROC)
	, mSound()
//	, mShape()
	, lpD3DDevice()
{
}

CGame::~CGame()
{
}

void CGame::Initialize()
{
	mpOwner->mScene = GAME_PROC;
	mStage = STAGE1_PROC;

	LPDIRECT3DTEXTURE9 tex = nullptr;
	//テクスチャ読み込み
	mpOwner->LoadTexture(&tex, "resources/images/stage1/Stage1FloorMap.png", 320, 320, NULL);
	mStage1.GetStage1Map()->SetTexture(tex);

	tex = nullptr;
	//テクスチャ読み込み
	mpOwner->LoadTexture(&tex, "resources/images/TestImages/testStage2.png", 1280, 720, D3DCOLOR_ARGB(255, 255, 255, 255));
	mStage2.SetTexture(tex);

	switch (mStage)
	{
	case STAGE1_PROC:
		mStage1.Initialize();
		break;
	case STAGE2_PROC:
		mStage2.Initialize();
		break;
	default:
		break;
	}
}

// 終了処理
void CGame::Release()
{
	mSound.Release();
//	mShape.Release();
	lpD3DDevice->Release();

}

void CGame::Update()
{
	switch (mStage)
	{
	case STAGE1_PROC:
		mStage1.Update();
		break;
	case STAGE2_PROC:
		mStage2.Update();
		break;
	default:
		break;
	}
}


void CGame::Draw(LPD3DXSPRITE apSprite)
{
	switch (mStage)
	{
	case STAGE1_PROC:
		mStage1.Draw(apSprite);
		break;
	case STAGE2_PROC:
		mStage2.Draw(apSprite);
		break;
	default:
		break;
	}
}

void CGame::SetOwner(CGameFrame* apOwner)
{
	if (apOwner == nullptr)
	{
		// new version assert which will NOT appear when build in release mode
		// Capital L is needed infront of the "" for showing sentance when you want to show japanese. If without, it will show corruption of text
		_ASSERT_EXPR(apOwner != nullptr, L"渡されたオーナー情報が空です\n確認ヨロ");

		return;
		// 早期リターン
	}

	mpOwner = apOwner;
}

void CGame::SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice)
{
	lpD3DDevice = apD3DDevice;
}

//CBasicShape* CGame::GetBasicShape()
//{
//	return &mShape;
//}

CSound* CGame::GetSound()
{
	return &mSound;
}

CStage1* CGame::GetStage1()
{
	return &mStage1;
}

CStage2* CGame::GetStage2()
{
	return &mStage2;
}
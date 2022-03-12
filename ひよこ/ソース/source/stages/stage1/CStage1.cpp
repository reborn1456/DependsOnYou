#include "../../../include/CGameFrame.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
}

void CStage1::Initialize()
{
	mpOwner->GetGame()->mStage = STAGE1_PROC;

	LPDIRECT3DTEXTURE9 tex = nullptr;
	//テクスチャ読み込み
	mpOwner->LoadTexture(&tex, "resources/images/stage1/Stage1FloorMap.png", 320, 320, D3DCOLOR_XRGB(255,255,255));
	mStage1Map.SetTexture(tex);

	tex = nullptr;
	mpOwner->LoadTexture(&tex, "resources/images/stage1/Item.png", 0, 0, D3DCOLOR_XRGB(255, 0, 0));
	mStage1Map.SetItemTexture(tex);
	//mItem.SetTexture(tex);

	mStage1Map.LoadMapFile();
	//mItem.LoadMapFile();


	mpOwner->GetGame()->GetSound()->LoadWAVE3D(mpOwner->GetGame()->GetSound()->lpSE, mpOwner->GetGame()->GetSound()->lp3DBGM, "resources/sounds/SE/TestSE.WAV");
	mpOwner->GetGame()->GetSound()->LoadWAVE3D(mpOwner->GetGame()->GetSound()->lpBGM, mpOwner->GetGame()->GetSound()->lp3DBGM, "resources/sounds/BGM/TestBGM.WAV");
	mpOwner->GetGame()->GetSound()->lp3DBGM->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);


//	mpOwner->GetGame()->GetSound()->lpBGM->Play(0, 0, DSBPLAY_LOOPING);
}

void CStage1::Update()
{
	if (GetAsyncKeyState('P') & 0x8000)
	{
		mpOwner->GetGame()->GetSound()->lpSE->Play(0, 0, 0);
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		mpOwner->GetGame()->GetStage2()->Initialize();
		mpOwner->GetGame()->GetSound()->lpBGM->Stop();
	}


	mpOwner->GetPlayer()->Update();
	mStage1Map.Update();
	//mItem.Update();





	/*
	//回転行列を作成, rotating on the z axis
	D3DXMatrixRotationZ(&RotMat, D3DXToRadian(angle));
	//拡縮行列を作成
	D3DXMatrixScaling(&ScaleMat, sizeW, sizeH, 1.0f);
	//座標行列を作成
	D3DXMatrixTranslation(&PosMat, playerX, playerY, 0.0f);
	//行列合成、この順番で掛け算（拡縮 * 回転 * 移動）
	playerMat = ScaleMat * RotMat * PosMat;
	//行列合成、この順番で掛け算（拡縮 * 移動 * 回転）,衛星みたいにくるくる回る
	playerMat = ScaleMat * PosMat * RotMat;   */
}

void CStage1::Draw(LPD3DXSPRITE apSprite)
{

	mStage1Map.Draw(apSprite);
	//mItem.Draw(apSprite);
	mpOwner->GetPlayer()->Draw(apSprite);



	//mShape.DrawSquare(200, 100, 200, 100, D3DCOLOR_ARGB(255, 0, 255, 0));
}

void CStage1::SetOwner(CGameFrame* apOwner)
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

CStage1Map* CStage1::GetStage1Map()
{
	return &mStage1Map;
}
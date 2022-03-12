#include "../../../include/CGameFrame.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */

CGameOver::CGameOver()
	: mpTexture(nullptr)
	, mPosition()
	, mMatrix()
{
}

CGameOver::~CGameOver()
{
	//safe release
	if (mpTexture != nullptr)   // if it is notyet destroyed, not 0
	{
		mpTexture->Release();
		mpTexture = nullptr;   // put null(0) inside it just incase it contains any rubbish which is still inside after release
	}
}

void CGameOver::Initialize()
{
	mpOwner->mScene = GAMEOVER_PROC;
}

void CGameOver::Update()
{
	if (GetAsyncKeyState('G') & 0x8000)
	{
		mpOwner->GetResult()->Initialize();
	}


	// 移動行列作成
	D3DXMatrixTranslation(&mMatrix, mPosition.x, mPosition.y, mPosition.z);
}

void CGameOver::Draw(LPD3DXSPRITE apSprite)
{
	// プレイヤ
	apSprite->SetTransform(&mMatrix);
	RECT rect = { 0, 0, 1280, 720 };
	apSprite->Draw(mpTexture, &rect, &D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CGameOver::SetTexture(LPDIRECT3DTEXTURE9 apTexture)
{
	if (apTexture == nullptr)
	{
		//// old version of assert which WILL appear even when build in release mode
		//assert(apTexture != nullptr);

		// new version assert which will NOT appear when build in release mode
		// Capital L is needed infront of the "" for showing sentance when you want to show japanese. If without, it will show corruption of text
		_ASSERT_EXPR(apTexture != nullptr, L"渡されたテクスチャ情報が空です\n確認ヨロ");


		return;
		// 早期リターン
		// テクスチャが空なので処理する意味が無い
	}
	mpTexture = apTexture;
}

void CGameOver::SetOwner(CGameFrame* apOwner)
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
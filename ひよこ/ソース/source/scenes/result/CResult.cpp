#include "../../../include/CGameFrame.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */

CResult::CResult()
	: mpTexture(nullptr)
	, mPosition()
	, mMatrix()
{
}

CResult::~CResult()
{
	//safe release
	if (mpTexture != nullptr)   // if it is notyet destroyed, not 0
	{
		mpTexture->Release();
		mpTexture = nullptr;   // put null(0) inside it just incase it contains any rubbish which is still inside after release
	}
}

void CResult::Initialize()
{
	mpOwner->mScene = RESULT_PROC;
}

void CResult::Update()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		mpOwner->GetTitle()->Initialize();
	}
	


	// 移動行列作成
	D3DXMatrixTranslation(&mMatrix, mPosition.x, mPosition.y, mPosition.z);
}

void CResult::Draw(LPD3DXSPRITE apSprite)
{
	// プレイヤ
	apSprite->SetTransform(&mMatrix);
	RECT rect = { 0, 0, 1280, 720 };
	apSprite->Draw(mpTexture, &rect, &D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CResult::SetTexture(LPDIRECT3DTEXTURE9 apTexture)
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

void CResult::SetOwner(CGameFrame* apOwner)
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
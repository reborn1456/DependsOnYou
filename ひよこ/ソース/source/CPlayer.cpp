#include "../include/CGameFrame.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */

CPlayer::CPlayer()
	: mpTexture(nullptr)
	, mPosition(600.f, 320.f, 0.f)
	, mMovePosition(0.f, 0.0f, 0.f)
	, mMatrix()
	, mPlayerDir(EPlayerDirection::FRONT)
	, mMoveState(eMoveState::eNoMove)
	, mpOwner(nullptr)
	, mMoveCount(0)
	, mMoveFlg(false)
	, SceneFlg(true)
{
}

CPlayer::~CPlayer()
{
	//safe release
	if (mpTexture != nullptr)   // if it is notyet destroyed, not 0
	{
		mpTexture->Release();
		mpTexture = nullptr;   // put null(0) inside it just incase it contains any rubbish which is still inside after release
	}
}

void CPlayer::Initialize()
{
	if (SceneFlg) 
	{
		mPosition.x = 640;
		mPosition.y = 600;
		SceneFlg = false;
	}
	
}

void CPlayer::Update()
{
	mMoveState = eMoveState::eNoMove;

	/*if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		mMoveState = eMoveState::eMoveRight;
		mPlayerDir = EPlayerDirection::R_SIDE;
		if (mpOwner->GetPrologue()->GetPMapChip()->MapHitCheck(mMoveState, mPosition) == true)
		{
			mPosition.x += mpOwner->GetPrologue()->GetPMapChip()->GetPlayerMoveX();
		}
		else
		{
			mPosition = mpOwner->GetPrologue()->GetPMapChip()->GetPlayerPos();
		}

		printf("Global   j(x) = %.2f \t i(y) = %.2f \n", (mPosition.x - mpOwner->GetPrologue()->GetPMapChip()->GetCameraX()) / 40, (mPosition.y - mpOwner->GetPrologue()->GetPMapChip()->GetCameraY()) / 40);
		printf("Local    j(x) = %.2f \t i(y) = %.2f \n\n", mPosition.x / 40, mPosition.y / 40);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		mMoveState = eMoveState::eMoveLeft;
		mPlayerDir = EPlayerDirection::L_SIDE;
		if (mpOwner->GetPrologue()->GetPMapChip()->MapHitCheck(mMoveState, mPosition) == true)
		{
			mPosition.x += mpOwner->GetPrologue()->GetPMapChip()->GetPlayerMoveX();
		}
		else
		{
			mPosition = mpOwner->GetPrologue()->GetPMapChip()->GetPlayerPos();
		}

		printf("Global   j(x) = %.2f \t i(y) = %.2f \n", (mPosition.x - mpOwner->GetPrologue()->GetPMapChip()->GetCameraX()) / 40, (mPosition.y - mpOwner->GetPrologue()->GetPMapChip()->GetCameraY()) / 40);
		printf("Local    j(x) = %.2f \t i(y) = %.2f \n\n", mPosition.x / 40, mPosition.y / 40);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		mMoveState = eMoveState::eMoveDown;
		mPlayerDir = EPlayerDirection::FRONT;
		if (mpOwner->GetPrologue()->GetPMapChip()->MapHitCheck(mMoveState, mPosition) == true)
		{
			mPosition.y += mpOwner->GetPrologue()->GetPMapChip()->GetPlayerMoveY();
		}
		else
		{
			mPosition = mpOwner->GetPrologue()->GetPMapChip()->GetPlayerPos();
		}

		printf("Global   j(x) = %.2f \t i(y) = %.2f \n", (mPosition.x - mpOwner->GetPrologue()->GetPMapChip()->GetCameraX()) / 40, (mPosition.y - mpOwner->GetPrologue()->GetPMapChip()->GetCameraY()) / 40);
		printf("Local    j(x) = %.2f \t i(y) = %.2f \n\n", mPosition.x / 40, mPosition.y / 40);
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		mMoveState = eMoveState::eMoveUp;
		mPlayerDir = EPlayerDirection::BACK;
		if (mpOwner->GetPrologue()->GetPMapChip()->MapHitCheck(mMoveState, mPosition) == true)
		{
			mPosition.y += mpOwner->GetPrologue()->GetPMapChip()->GetPlayerMoveY();
		}
		else
		{
			mPosition = mpOwner->GetPrologue()->GetPMapChip()->GetPlayerPos();
		}

		printf("Global   j(x) = %.2f \t i(y) = %.2f \n", (mPosition.x - mpOwner->GetPrologue()->GetPMapChip()->GetCameraX()) / 40, (mPosition.y - mpOwner->GetPrologue()->GetPMapChip()->GetCameraY()) / 40);
		printf("Local    j(x) = %.2f \t i(y) = %.2f \n\n", mPosition.x / 40, mPosition.y / 40);
	}*/



	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && mMoveCount == 0)
	{
		mMoveCount = 1;
		mMoveState = eMoveState::eMoveRight;
		mPlayerDir = EPlayerDirection::R_SIDE;
		if (mpOwner->mScene == PROLOGUE_PROC)
		{
			mMoveFlg = mpOwner->GetPrologue()->GetPMapChip()->MapHitCheck(mMoveState, mPosition);
			if (mMoveFlg == true)
			{
				mMovePosition.x += mpOwner->GetPrologue()->GetPMapChip()->GetPlayerMoveX();
			}
			else
			{
				mPosition = mpOwner->GetPrologue()->GetPMapChip()->GetPlayerPos();
			}
		}
		if (mpOwner->mScene == GAME_PROC)
		{
			switch (mpOwner->GetGame()->mStage)
			{
			case STAGE1_PROC:
				mMoveFlg = mpOwner->GetGame()->GetStage1()->GetStage1Map()->MapHitCheck(mMoveState, mPosition);
				if (mMoveFlg == true)
				{
					mMovePosition.x += mpOwner->GetGame()->GetStage1()->GetStage1Map()->GetPlayerMoveX();
				}
				else
				{
					mPosition = mpOwner->GetGame()->GetStage1()->GetStage1Map()->GetPlayerPos();
				}
				break;
			case STAGE2_PROC:
				break;
			default:
				break;
			}
		}

		printf("Global   j(x) = %.2f \t i(y) = %.2f \n", (mPosition.x - mpOwner->GetPrologue()->GetPMapChip()->GetCameraX()) / 40, (mPosition.y - mpOwner->GetPrologue()->GetPMapChip()->GetCameraY()) / 40);
		printf("Local    j(x) = %.2f \t i(y) = %.2f \n\n", mPosition.x / 40, mPosition.y / 40);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && mMoveCount == 0)
	{
		mMoveCount = 1;
		mMoveState = eMoveState::eMoveLeft;
		mPlayerDir = EPlayerDirection::L_SIDE;
		if (mpOwner->mScene == PROLOGUE_PROC)
		{
			mMoveFlg = mpOwner->GetPrologue()->GetPMapChip()->MapHitCheck(mMoveState, mPosition);
			if (mMoveFlg == true)
			{
				mMovePosition.x += mpOwner->GetPrologue()->GetPMapChip()->GetPlayerMoveX();
			}
			else
			{
				mPosition = mpOwner->GetPrologue()->GetPMapChip()->GetPlayerPos();
			}
		}
		if (mpOwner->mScene == GAME_PROC)
		{
			switch (mpOwner->GetGame()->mStage)
			{
			case STAGE1_PROC:
				mMoveFlg = mpOwner->GetGame()->GetStage1()->GetStage1Map()->MapHitCheck(mMoveState, mPosition);
				if (mMoveFlg == true)
				{
					mMovePosition.x += mpOwner->GetGame()->GetStage1()->GetStage1Map()->GetPlayerMoveX();
				}
				else
				{
					mPosition = mpOwner->GetGame()->GetStage1()->GetStage1Map()->GetPlayerPos();
				}
				break;
			case STAGE2_PROC:
				break;
			default:
				break;
			}
		}


		printf("Global   j(x) = %.2f \t i(y) = %.2f \n", (mPosition.x - mpOwner->GetPrologue()->GetPMapChip()->GetCameraX()) / 40, (mPosition.y - mpOwner->GetPrologue()->GetPMapChip()->GetCameraY()) / 40);
		printf("Local    j(x) = %.2f \t i(y) = %.2f \n\n", mPosition.x / 40, mPosition.y / 40);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && mMoveCount == 0)
	{
		mMoveCount = 1;
		mMoveState = eMoveState::eMoveDown;
		mPlayerDir = EPlayerDirection::FRONT;
		if (mpOwner->mScene == PROLOGUE_PROC)
		{
			mMoveFlg = mpOwner->GetPrologue()->GetPMapChip()->MapHitCheck(mMoveState, mPosition);
			if (mMoveFlg == true)
			{
				mMovePosition.y += mpOwner->GetPrologue()->GetPMapChip()->GetPlayerMoveY();
			}
			else
			{
				mPosition = mpOwner->GetPrologue()->GetPMapChip()->GetPlayerPos();
			}
		}
		if (mpOwner->mScene == GAME_PROC)
		{
			switch (mpOwner->GetGame()->mStage)
			{
			case STAGE1_PROC:
				mMoveFlg = mpOwner->GetGame()->GetStage1()->GetStage1Map()->MapHitCheck(mMoveState, mPosition);
				if (mMoveFlg == true)
				{
					mMovePosition.y += mpOwner->GetGame()->GetStage1()->GetStage1Map()->GetPlayerMoveY();
				}
				else
				{
					mPosition = mpOwner->GetGame()->GetStage1()->GetStage1Map()->GetPlayerPos();
				}
				break;
			case STAGE2_PROC:
				break;
			default:
				break;
			}
		}


		printf("Global   j(x) = %.2f \t i(y) = %.2f \n", (mPosition.x - mpOwner->GetPrologue()->GetPMapChip()->GetCameraX()) / 40, (mPosition.y - mpOwner->GetPrologue()->GetPMapChip()->GetCameraY()) / 40);
		printf("Local    j(x) = %.2f \t i(y) = %.2f \n\n", mPosition.x / 40, mPosition.y / 40);
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000 && mMoveCount == 0)
	{
		mMoveCount = 1;
		mMoveState = eMoveState::eMoveUp;
		mPlayerDir = EPlayerDirection::BACK;
		if (mpOwner->mScene == PROLOGUE_PROC)
		{
			mMoveFlg = mpOwner->GetPrologue()->GetPMapChip()->MapHitCheck(mMoveState, mPosition);
			if (mMoveFlg == true)
			{
				mMovePosition.y += mpOwner->GetPrologue()->GetPMapChip()->GetPlayerMoveY();
			}
			else
			{
				mPosition = mpOwner->GetPrologue()->GetPMapChip()->GetPlayerPos();
			}
		}
		if (mpOwner->mScene == GAME_PROC)
		{
			switch (mpOwner->GetGame()->mStage)
			{
			case STAGE1_PROC:
				mMoveFlg = mpOwner->GetGame()->GetStage1()->GetStage1Map()->MapHitCheck(mMoveState, mPosition);
				if (mMoveFlg == true)
				{
					mMovePosition.y += mpOwner->GetGame()->GetStage1()->GetStage1Map()->GetPlayerMoveY();
				}
				else
				{
					mPosition = mpOwner->GetGame()->GetStage1()->GetStage1Map()->GetPlayerPos();
				}
				break;
			case STAGE2_PROC:
				break;
			default:
				break;
			}
		}

		printf("Global   j(x) = %.2f \t i(y) = %.2f \n", (mPosition.x - mpOwner->GetPrologue()->GetPMapChip()->GetCameraX()) / 40, (mPosition.y - mpOwner->GetPrologue()->GetPMapChip()->GetCameraY()) / 40);
		printf("Local    j(x) = %.2f \t i(y) = %.2f \n\n", mPosition.x / 40, mPosition.y / 40);
	}



	if (mMoveFlg)
	{
		mPosition.x += mMovePosition.x;
		mPosition.y += mMovePosition.y;
		printf("Player Local    x = %.2f \t y = %.2f \n\n", mPosition.x / 40, mPosition.y / 40);

		mMoveCount++;
		printf("mMoveCount: %d \n", mMoveCount);

		if (mMoveCount > MOVECOUNT)   // 20回分
		{
			mMoveCount = 0;
			mMoveFlg = false;
			mMovePosition.x = 0.f;
			mMovePosition.y = 0.f;
		}
	}
	else
	{
		mMoveCount = 0;
	}

	/*mPosition.x += mMovePosition.x;
	mPosition.y += mMovePosition.y;

	int posChipi = mPosition.y / 40;
	int posChipj = mPosition.x / 40;*/


	// 移動行列作成
	D3DXMatrixTranslation(&mMatrix, mPosition.x, mPosition.y, mPosition.z);
}

void CPlayer::Draw(LPD3DXSPRITE apSprite)
{
	// キャラ
	RECT rect;
	if (mPlayerDir == FRONT)
	{
		rect = { 0, 0, 40, 40 };
	}
	if (mPlayerDir == L_SIDE)
	{
		rect = { 0, 40, 40, 80 };
	}
	if (mPlayerDir == R_SIDE)
	{
		rect = { 0, 80, 40, 120 };
	}
	if (mPlayerDir == BACK)
	{
		rect = { 0, 120, 40, 160 };
	}

	apSprite->SetTransform(&mMatrix);
	apSprite->Draw(mpTexture, &rect, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::SetTexture(LPDIRECT3DTEXTURE9 apTexture)
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

void CPlayer::SetOwner(CGameFrame* apOwner)
{
	mpOwner = apOwner;
}

const D3DXVECTOR3 CPlayer::GetPlayerPosition()
{
	return mPosition;
}

const eMoveState CPlayer::GetMoveState()
{
	return mMoveState;
}
#include "../../../include/CGameFrame.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */


CPrologue::CPrologue()
	: lpD3DDevice()
	, mPMapChip()
{
}

CPrologue::~CPrologue()
{
}

void CPrologue::Initialize()
{
	mpOwner->mScene = PROLOGUE_PROC;

	LPDIRECT3DTEXTURE9 tex = nullptr;
	//テクスチャ読み込み
	mpOwner->LoadTexture(&tex, "resources/images/prologue/Prologue.png", 320, 320, NULL);
	mPMapChip.SetTexture(tex);

	mPMapChip.LoadMapFile();


	
	mpOwner->GetGame()->GetSound()->LoadWAVE3D(mpOwner->GetGame()->GetSound()->lpSE, mpOwner->GetGame()->GetSound()->lp3DBGM, "resources/sounds/SE/TestSE.WAV");
	mpOwner->GetGame()->GetSound()->LoadWAVE3D(mpOwner->GetGame()->GetSound()->lpBGM, mpOwner->GetGame()->GetSound()->lp3DBGM, "resources/sounds/BGM/TestBGM.WAV");
	mpOwner->GetGame()->GetSound()->lp3DBGM->SetMode(DS3DMODE_DISABLE, DS3D_IMMEDIATE);


//	mpOwner->GetGame()->GetSound()->lpBGM->Play(0, 0, DSBPLAY_LOOPING);
}

void CPrologue::Update()
{
	if (mPMapChip.GetSceneFlg() || GetAsyncKeyState('A') & 0x8000)
	{
		mpOwner->GetGame()->Initialize();
		mpOwner->GetPlayer()->Initialize();
	}

	mpOwner->GetPlayer()->Update();
	mPMapChip.Update();

}


void CPrologue::Draw(LPD3DXSPRITE apSprite)
{
	mPMapChip.Draw(apSprite);
	mpOwner->GetPlayer()->Draw(apSprite);
}

void CPrologue::SetOwner(CGameFrame* apOwner)
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

void CPrologue::SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice)
{
	lpD3DDevice = apD3DDevice;
}

CPMapChip* CPrologue::GetPMapChip()
{
	return &mPMapChip;
}
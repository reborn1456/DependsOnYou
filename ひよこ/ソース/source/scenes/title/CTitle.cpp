#include "../../../include/CGameFrame.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */

CTitle::CTitle()
	: mpTexture(nullptr)
	, mpTitleTexture(nullptr)
	, mPosition()
	, mTitlePosition(640,370,0)
	, mMatrix()
	, mTitleMatrix()
{
}

CTitle::~CTitle()
{
	//safe release
	if (mpTexture != nullptr)   // if it is notyet destroyed, not 0
	{
//		mpTexture->Release();
		mpTexture = nullptr;   // put null(0) inside it just incase it contains any rubbish which is still inside after release
	}

	if (mpTitleTexture != nullptr)
	{
		mpTitleTexture = nullptr;
	}
}

void CTitle::Initialize()
{
	mpOwner->mScene = TITLE_PROC;
}

// �^�C�g���̃A�b�v�f�[�g
void CTitle::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		mpOwner->GetPrologue()->Initialize();
	}


	// �ړ��s��쐬
	D3DXMatrixTranslation(&mMatrix, mPosition.x, mPosition.y, mPosition.z);

	D3DXMatrixTranslation(&mTitleMatrix, mTitlePosition.x, mTitlePosition.y, mTitlePosition.z);
}

// �^�C�g�������_
void CTitle::Draw(LPD3DXSPRITE apSprite)
{
	//mShape.DrawSquare(200, 100, 200, 100, D3DCOLOR_ARGB(255, 255, 0, 0));

	//�w�i
	apSprite->SetTransform(&mMatrix);
	RECT rect = { 0, 0, 1280, 720 };
	apSprite->Draw(mpTexture, &rect, &D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_XRGB(255, 255, 255));

	//�^�C�g��
	apSprite->SetTransform(&mTitleMatrix);
	RECT rectT = { 0,0,500,500 };
	apSprite->Draw(mpTitleTexture, &rectT, &D3DXVECTOR3(250, 250, 0), nullptr, D3DCOLOR_XRGB(255, 255, 255));
}


void CTitle::SetTexture(LPDIRECT3DTEXTURE9 apTexture)
{
	if (apTexture == nullptr)
	{
		//// old version of assert which WILL appear even when build in release mode
		//assert(apTexture != nullptr);

		// new version assert which will NOT appear when build in release mode
		// Capital L is needed infront of the "" for showing sentance when you want to show japanese. If without, it will show corruption of text
		_ASSERT_EXPR(apTexture != nullptr, L"�n���ꂽ�e�N�X�`����񂪋�ł�\n�m�F����");


		return;
		// �������^�[��
		// �e�N�X�`������Ȃ̂ŏ�������Ӗ�������
	}
	mpTexture = apTexture;
}

void CTitle::SetTitleTexture(LPDIRECT3DTEXTURE9 apTexture)
{
	if (apTexture == nullptr)
	{
		_ASSERT_EXPR(apTexture != nullptr, L"�n���ꂽ�e�N�X�`����񂪋�ł�\n�m�F����");

		return;
		// �������^�[��
		// �e�N�X�`������Ȃ̂ŏ�������Ӗ�������
	}
	mpTitleTexture = apTexture;
}

void CTitle::SetOwner(CGameFrame* apOwner)
{
	if (apOwner == nullptr)
	{
		// new version assert which will NOT appear when build in release mode
		// Capital L is needed infront of the "" for showing sentance when you want to show japanese. If without, it will show corruption of text
		_ASSERT_EXPR(apOwner != nullptr, L"�n���ꂽ�I�[�i�[��񂪋�ł�\n�m�F����");

		return;
		// �������^�[��
	}

	mpOwner = apOwner;
}
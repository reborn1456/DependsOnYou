#include "../../../include/CGameFrame.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */

CStage2::CStage2()
	: mpTexture(nullptr)
	, mPosition()
	, mMatrix()
{
}

CStage2::~CStage2()
{
	//safe release
	if (mpTexture != nullptr)   // if it is notyet destroyed, not 0
	{
		mpTexture->Release();
		mpTexture = nullptr;   // put null(0) inside it just incase it contains any rubbish which is still inside after release
	}
}

void CStage2::Initialize()
{
	mpOwner->GetGame()->mStage = STAGE2_PROC;
}

void CStage2::Update()
{
	if (GetAsyncKeyState('F') & 0x8000)
	{
		mpOwner->GetGameOver()->Initialize();
	}
	if (GetAsyncKeyState('E') & 0x8000)
	{
		mpOwner->GetGame()->GetStage1()->Initialize();
	}






	// �ړ��s��쐬
	D3DXMatrixTranslation(&mMatrix, mPosition.x, mPosition.y, mPosition.z);

	/*
	//��]�s����쐬, rotating on the z axis
	D3DXMatrixRotationZ(&RotMat, D3DXToRadian(angle));
	//�g�k�s����쐬
	D3DXMatrixScaling(&ScaleMat, sizeW, sizeH, 1.0f);
	//���W�s����쐬
	D3DXMatrixTranslation(&PosMat, playerX, playerY, 0.0f);
	//�s�񍇐��A���̏��ԂŊ|���Z�i�g�k * ��] * �ړ��j
	playerMat = ScaleMat * RotMat * PosMat;
	//�s�񍇐��A���̏��ԂŊ|���Z�i�g�k * �ړ� * ��]�j,�q���݂����ɂ��邭����
	playerMat = ScaleMat * PosMat * RotMat;   */
}

void CStage2::Draw(LPD3DXSPRITE apSprite)
{
	// �v���C��
	apSprite->SetTransform(&mMatrix);
	RECT rect = { 0, 0, 1280, 720 };
	apSprite->Draw(mpTexture, &rect, &D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));



	//mShape.DrawSquare(200, 100, 200, 100, D3DCOLOR_ARGB(255, 0, 255, 0));
}

void CStage2::SetTexture(LPDIRECT3DTEXTURE9 apTexture)
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

void CStage2::SetOwner(CGameFrame* apOwner)
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
#pragma once

#include <d3dx9.h>
#include "../include/stages/prologue/CPMapChip.h"

enum EPlayerDirection
{
	//default starting as 0 and then +1 for each after it
	/* when use:
	   int scene = SceneName::Game_PROC; */

	FRONT, L_SIDE, R_SIDE, BACK
};

class CGameFrame;   // �N���X�̑O���錾

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	// �����o�֐�
	void Update();                                           // �X�V
	void Draw(LPD3DXSPRITE apSprite);                        // �`��
	void SetTexture(LPDIRECT3DTEXTURE9 apTexture);           // �e�N�X�`���ݒ�
	void Initialize();

	void SetOwner(CGameFrame* apOwner);

	const D3DXVECTOR3 GetPlayerPosition();
	const eMoveState GetMoveState();

private:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9     mpTexture;
	D3DXVECTOR3            mPosition;
	D3DXVECTOR3            mMovePosition;
	D3DXMATRIX             mMatrix;

	EPlayerDirection       mPlayerDir;

	eMoveState			   mMoveState;
	int					   mMoveWait;
	int					   mMoveCount;
	bool				   mMoveFlg;

	bool				   SceneFlg;

	CGameFrame*  mpOwner;   // �I�[�i�[
};
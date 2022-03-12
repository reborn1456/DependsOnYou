#pragma once

#include <d3dx9.h>




////////////////////////////////////////////////// �N���X�̊֐� //////////////////////////////////////////////////

class CGameFrame;     // �N���X�̑O���錾

class CGameOver
{
public:

	CGameOver();
	~CGameOver();

	// �����o�ϐ�=================================================


	// �����o�֐�=================================================
	void Initialize();
	void Update();                                           // �X�V
	void Draw(LPD3DXSPRITE apSprite);                        // �`��
	void SetTexture(LPDIRECT3DTEXTURE9 apTexture);           // �e�N�X�`���ݒ�
	void SetOwner(CGameFrame* apOwner);						 // �I�[�i�ݒ�



private:

	// �����o�ϐ�=================================================
	CGameFrame*              mpOwner;
	LPDIRECT3DTEXTURE9       mpTexture;
	D3DXVECTOR3              mPosition;
	D3DXMATRIX               mMatrix;


	// �����o�֐�=================================================

};
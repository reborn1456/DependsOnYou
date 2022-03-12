#pragma once

#include <d3dx9.h>




////////////////////////////////////////////////// �N���X�̊֐� //////////////////////////////////////////////////

class CGameFrame;     // �N���X�̑O���錾

class CTitle
{
public:

	CTitle();
	~CTitle();

	// �����o�ϐ�=================================================


	// �����o�֐�=================================================
	void Initialize();
	void Update();                                           // �X�V
	void Draw(LPD3DXSPRITE apSprite);                        // �`��
	void SetTexture(LPDIRECT3DTEXTURE9 apTexture);           // �e�N�X�`���ݒ�
	void SetTitleTexture(LPDIRECT3DTEXTURE9 apTexture);		 //�^�C�g���ݒ�
	void SetOwner(CGameFrame* apOwner);						 // �I�[�i�ݒ�



private:

	// �����o�ϐ�=================================================
	CGameFrame*              mpOwner;
	LPDIRECT3DTEXTURE9       mpTexture;
	LPDIRECT3DTEXTURE9		 mpTitleTexture;
	D3DXVECTOR3              mPosition;
	D3DXVECTOR3				 mTitlePosition;
	D3DXMATRIX               mMatrix;
	D3DXMATRIX				 mTitleMatrix;


	// �����o�֐�=================================================

};
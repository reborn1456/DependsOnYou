#pragma once

#include <d3dx9.h>
#include "CPMapChip.h"




////////////////////////////////////////////////// �N���X�̊֐� //////////////////////////////////////////////////

class CGameFrame;     // �N���X�̑O���錾

class CPrologue
{
public:

	CPrologue();
	~CPrologue();

	// �����o�ϐ�=================================================
	int						 mStage;
	
	// �����o�֐�=================================================
	void Initialize();
	void Update();                                           // �X�V
	void Draw(LPD3DXSPRITE apSprite);                        // �`��
	void SetOwner(CGameFrame* apOwner);						 // �I�[�i�ݒ�
	void SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice);

	CPMapChip* GetPMapChip();


private:

	// �����o�ϐ�=================================================
	CGameFrame*              mpOwner;
	LPDIRECT3DDEVICE9        lpD3DDevice;

	CPMapChip				 mPMapChip;
};
#pragma once

#include <d3dx9.h>
#include "CStage1Map.h"
#include "CItem.h"



////////////////////////////////////////////////// �N���X�̊֐� //////////////////////////////////////////////////

class CGameFrame;     // �N���X�̑O���錾

class CStage1
{
public:

	CStage1();
	~CStage1();

	// �����o�ϐ�=================================================


	// �����o�֐�=================================================
	void Initialize();
	void Update();                                           // �X�V
	void Draw(LPD3DXSPRITE apSprite);                        // �`��
	void SetOwner(CGameFrame* apOwner);						 // �I�[�i�ݒ�

	CStage1Map* GetStage1Map();



private:

	// �����o�ϐ�=================================================
	CGameFrame*              mpOwner;

	CStage1Map				 mStage1Map;
	CItem					 mItem;


	// �����o�֐�=================================================

};
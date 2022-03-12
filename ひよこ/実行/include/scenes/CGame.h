#pragma once

#include <d3dx9.h>
#include "../CBasicShape.h"
#include "../sound/CSound.h"
#include "../stages/stage1/CStage1.h"
#include "../stages/stage2/CStage2.h"




////////////////////////////////////////////////// �񋓌^ //////////////////////////////////////////////////

enum StageName
{
	//default starting as 0 and then +1 for each after it
	/* when use:
	   int scene = SceneName::Game_PROC; */

	STAGE1_PROC, STAGE2_PROC
};




////////////////////////////////////////////////// �N���X�̊֐� //////////////////////////////////////////////////

class CGameFrame;     // �N���X�̑O���錾

class CGame
{
public:

	CGame();
	~CGame();

	// �����o�ϐ�=================================================
	int						 mStage;
	
	// �����o�֐�=================================================
	void Initialize();
	void Update();                                           // �X�V
	void Draw(LPD3DXSPRITE apSprite);                        // �`��
	void Release();											 // �I������
	void SetOwner(CGameFrame* apOwner);						 // �I�[�i�ݒ�
	void SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice);

	//CBasicShape* GetBasicShape();
	CSound* GetSound();
	CStage1* GetStage1();
	CStage2* GetStage2();


private:

	// �����o�ϐ�=================================================
	CGameFrame*              mpOwner;
	LPDIRECT3DDEVICE9        lpD3DDevice;

//	CBasicShape			     mShape;
	CSound				     mSound;
	CStage1					 mStage1;
	CStage2					 mStage2;
};
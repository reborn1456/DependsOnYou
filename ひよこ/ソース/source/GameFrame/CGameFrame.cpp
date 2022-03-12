/*
  ゲーム本体に関連した関数のみのcppファイル
  基本的にここを改良していく
*/

#include "../../include/CGameFrame.h"

// テクスチャ読み込み
void CGameFrame::LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const std::string & aFilePath, int aWidth, int aHeight, D3DCOLOR aColor)
{
	if (aWidth == 0)aWidth = D3DX_DEFAULT;
	if (aHeight == 0)aHeight = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(mpD3DDevice, aFilePath.c_str(), aWidth, aHeight, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, aColor, NULL, NULL, lpTex);
}

/*
  コンストラクタ
  クラスのインスタンス(==実体)を生成(メモリ確保)時に呼ばれる
*/
CGameFrame::CGameFrame()
// 初期化子リスト
// コンストラクタ()の続きに[:]コロンを
// つけることで記述できる、区切りは[,]カンマ
// 変数宣言と同じ順番で書かないとバグの原因になる
	: mScrollWidth(SCRW)
	, mScrollHeight(SCRH)
	, mAppName("キミシダイ")
	, mIsFullScreen(true)
	, mFullScreenCursor(false)
	, mFvFVertex(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
	, mFrame()
	, mpHwnd(nullptr)
	, mpD3D(nullptr)
	, mpD3DDevice(nullptr)
	, mD3Dpp()
	, mWndClass()
	, mpSprite(nullptr)
	, mpFont(nullptr)
	, mScene(TITLE_PROC)
	, mPlayer()
	, mTitle()
	, mPrologue()
	, mGame()
	, mGameOver()
	, mResult()
{
}

/*
  デストラクタ
  クラスのインスタンス(==実体)を破棄(メモリ開放)時に呼ばれる
*/
CGameFrame::~CGameFrame()
{
	Release();
}

// 終了処理
void CGameFrame::Release()
{

	////コンソールの解放
	//FreeConsole();

	mGame.Release();

	// Direct3D オブジェクトを解放
	mpD3D->Release();
	mpD3DDevice->Release();

	mpSprite->Release();	// スプライト
	mpFont->Release();		// フォント
	

}

// 初期化
void CGameFrame::Initialize()
{
	//CreateConsole();

	mGame.GetSound()->Initialize(mpHwnd);
	mGame.SetD3DDevice(mpD3DDevice);

	// プレイヤにオーナーをセット
	mPlayer.SetOwner(this);
	// タイトル画面にオーナーをセット
	mTitle.SetOwner(this);     // thisは自分自身のポインタ
	// プロローグにオーナーをセット
	mPrologue.SetOwner(this);     // thisは自分自身のポインタ
	mPrologue.GetPMapChip()->SetOwner(this);
	// ゲームにオーナーをセット
	mGame.SetOwner(this);     // thisは自分自身のポインタ
	// ゲームオーバー画面にオーナーをセット
	mGameOver.SetOwner(this);     // thisは自分自身のポインタ
	// リザルト画面にオーナーをセット
	mResult.SetOwner(this);     // thisは自分自身のポインタ
	// ステージにオーナーをセット
	mGame.GetStage1()->SetOwner(this);
	mGame.GetStage1()->GetStage1Map()->SetOwner(this);
	mGame.GetStage2()->SetOwner(this);




	LPDIRECT3DTEXTURE9 tex = nullptr;
	//テクスチャ読み込み
	//CGameFrame::LoadTexture(&tex, "Texture/TestImages/testTitle.png", 1280, 720, D3DCOLOR_ARGB(255, 255, 0, 0));
	CGameFrame::LoadTexture(&tex, "resources/images/title/back.png", 1280, 720, D3DCOLOR_XRGB(255, 0, 0));
	mTitle.SetTexture(tex);
	CGameFrame::LoadTexture(&tex, "resources/images/title/キミシダイ.png", 500, 500, D3DCOLOR_XRGB(255, 255, 255));
	mTitle.SetTitleTexture(tex);

	tex = nullptr;
	//プレイヤーのテクスチャ読み込み
	CGameFrame::LoadTexture(&tex, "resources/images/chr.png", 256, 256, D3DCOLOR_ARGB(255, 255, 255, 255));
	mPlayer.SetTexture(tex);

	tex = nullptr;
	//テクスチャ読み込み
	CGameFrame::LoadTexture(&tex, "resources/images/TestImages/testGameOver.png", 1280, 720, D3DCOLOR_ARGB(255, 255, 255, 255));
	mGameOver.SetTexture(tex);

	tex = nullptr;
	//テクスチャ読み込み
	//CGameFrame::LoadTexture(&tex, "resources/images/TestImages/testResult.png", 1280, 720, D3DCOLOR_ARGB(255, 255, 0, 0));
	//mResult.SetTexture(tex);
	
	
}

// 更新
void CGameFrame::Update()
{
	mFrame++;

	switch (mScene)
	{
	case TITLE_PROC:
		mTitle.Update();
		break;
	case PROLOGUE_PROC:
		mPrologue.Update();
		break;
	case GAME_PROC:
		mGame.Update();
		break;
	case GAMEOVER_PROC:
		mGameOver.Update();
		break;
	case RESULT_PROC:
		mResult.Update();
		break;
	default:
		break;
	}
}

// 2D描画
void CGameFrame::Draw2D()
{
	// 描画開始
	mpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	switch (mScene)
	{
	case TITLE_PROC:
		mTitle.Draw(mpSprite);
		break;
	case PROLOGUE_PROC:
		mPrologue.Draw(mpSprite);
		break;
	case GAME_PROC:
		mGame.Draw(mpSprite);
		break;
	case GAMEOVER_PROC:
		mGameOver.Draw(mpSprite);
		break;
	case RESULT_PROC:
		mResult.Draw(mpSprite);
		break;
	default:
		break;
	}


	// 描画終了
	mpSprite->End();

	if (mScene==TITLE_PROC) {
		//文字表示(Endの後に行う)
		RECT rc = { 230,530,0,0 };	//座標
		char Text[256];	//文字変換用
		sprintf_s(Text, sizeof(Text), "エンターキーを押してスタート");	//配列に出力(printf:画面出力)
			//入れる場所,バイト数(最大文字数),入れる内容,%dの内容
		mpFont->DrawText(NULL,
			Text, //表示内容
			-1,	//全部表示(表示したい文字の数)
			&rc,//RECT
			DT_LEFT | DT_NOCLIP,//左詰め(右:RIGHT 中央:CENTER) | 文字折り返し
			D3DCOLOR_ARGB(mFrame%256, 135, 135, 135));
		//変数を表示しない場合は"Text"の部分に表示したい文字を入力
	}
	else if (mScene == RESULT_PROC) {
		//文字表示(Endの後に行う)
		RECT rc = { 480,360,0,0 };	//座標
		char Text[256];	//文字変換用
		sprintf_s(Text, sizeof(Text), "ゲームクリア");	//配列に出力(printf:画面出力)
			//入れる場所,バイト数(最大文字数),入れる内容,%dの内容
		mpFont->DrawText(NULL,
			Text, //表示内容
			-1,	//全部表示(表示したい文字の数)
			&rc,//RECT
			DT_LEFT | DT_NOCLIP,//左詰め(右:RIGHT 中央:CENTER) | 文字折り返し
			D3DCOLOR_ARGB(255, 225, 225, 225));
		//変数を表示しない場合は"Text"の部分に表示したい文字を入力
	}
}

// 3D描画
void CGameFrame::Draw3D()
{
}

//コンソール作成
void CGameFrame::CreateConsole()
{
	//コンソールを作成する
	AllocConsole();

	FILE *fp_c = NULL;

	freopen_s(&fp_c, "CONOUT$", "w", stdout);
	freopen_s(&fp_c, "CONIN$", "r", stdin);
}

const LPDIRECT3DDEVICE9 CGameFrame::GetD3DDevice()
{
	return mpD3DDevice;
}

const HWND CGameFrame::GetHwnd()
{
	return mpHwnd;
}

CPlayer* CGameFrame::GetPlayer()
{
	return &mPlayer;
}

CTitle* CGameFrame::GetTitle()
{
	return &mTitle;
}

CPrologue* CGameFrame::GetPrologue()
{
	return &mPrologue;
}

CGame* CGameFrame::GetGame()
{
	return &mGame;
}

CGameOver* CGameFrame::GetGameOver()
{
	return &mGameOver;
}

CResult* CGameFrame::GetResult()
{
	return &mResult;
}
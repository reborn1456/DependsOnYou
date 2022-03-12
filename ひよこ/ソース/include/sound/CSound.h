#pragma once

#include <dsound.h>
#include "wavread.h"

#pragma comment(lib, "dsound.lib")




////////////////////////////////////////////////// クラスの関数 //////////////////////////////////////////////////

class CSound
{
public:

	CSound();
	~CSound();

	// メンバ変数=================================================
	void Release();		// 終了処理

	//音を鳴らすのに必要
	LPDIRECTSOUNDBUFFER8     lpBGM;     //音を入れる入れ物
	LPDIRECTSOUNDBUFFER8     lpSE;      //音を入れる入れ物
	LPDIRECTSOUND3DBUFFER8   lp3DBGM;   //音の設定データ

	// メンバ関数=================================================
	void LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, const char *fname);
	void Initialize(HWND apHwnd);             	// サウンド初期化処理

private:

	// メンバ変数=================================================
	//音関係
	LPDIRECTSOUND8          lpDSound;       //DirectSoundオブジェクト
	LPDIRECTSOUNDBUFFER     lpSPrimary;

	// メンバ関数=================================================
};
#include "../../include/CGameFrame.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPSTR lpszCmdParam, int nCmdshow)
{
	MSG msg;

	// GameFrame 生成
	CGameFrame * pGameFrame = new CGameFrame();	// 生成(メモリ確保)
	pGameFrame->Create(hInst, nCmdshow);		// 固定機能作成
	pGameFrame->Initialize();					// 初期化

	timeBeginPeriod(1);   // タイマーの精度を上げる

	// メッセージループ
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			pGameFrame->GameLoop();
		}
	}

	timeEndPeriod(1);   // タイマーの精度を元に戻す

	// GameFrame 終了
	delete pGameFrame;	// 破棄(メモリ解放)

	return (int)msg.wParam;   // ここが最後
}

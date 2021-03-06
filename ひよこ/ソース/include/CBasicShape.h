#pragma once

#include <d3dx9.h>

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)




////////////////////////////////////////////////// 構造体宣言 //////////////////////////////////////////////////

// 頂点用の構造体を宣言
typedef struct VERTEX2D
{
	float x;			// x座標
	float y;			// y座標
	float z;			// 常に0
	float rhw;			// 常に1
	D3DCOLOR color;		// 色
}Vertex2D;




////////////////////////////////////////////////// クラスの関数 //////////////////////////////////////////////////

class CBasicShape
{
public:

	CBasicShape();
	~CBasicShape();

	// メンバ関数=================================================
	void Release();		// 終了処理
	void SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice);

	//// 点を描く関数
	void DrawPixel(float x, float y, D3DCOLOR colour);

	//// 2点間の線を描く関数
	void DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR colour);

	void DrawLineColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2);

	//// 三角形を線で描く関数
	void DrawLineTriangle(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR colour);

	void DrawLineTriColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2, float x3, float y3, D3DCOLOR colour3);

	//// 三角形を描く関数
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR colour);

	void DrawTriColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2, float x3, float y3, D3DCOLOR colour3);

	//// 四角形を線で描く関数
	void DrawLineSquare(float x, float y, int width, int height, D3DCOLOR colour);

	void DrawLineSquColGrad(float x, float y, int width, int height, D3DCOLOR colour1, D3DCOLOR colour2, D3DCOLOR colour3, D3DCOLOR colour4);

	//// 四角形を描く関数
	void DrawSquare(float x, float y, int width, int height, D3DCOLOR colour);

	void DrawSquColGrad(float x, float y, int width, int height, D3DCOLOR colour1, D3DCOLOR colour2, D3DCOLOR colour3, D3DCOLOR colour4);

	//// 円を点で描く関数
	void DrawDotCircle(float x, float y, float rx, float ry, D3DCOLOR colour);

	//// 円を線で描く関数
	void DrawLineCircle(float x, float y, float rx, float ry, D3DCOLOR colour);

	//// 円を描く関数
	void DrawCircle(float x, float y, float rx, float ry, D3DCOLOR colour);

	//// 多角形を点で描く関数
	void DrawDotPoly(float x, float y, float r, float poly, D3DCOLOR colour);

	//// 多角形を線で描く関数
	void DrawLinePoly(float x, float y, float r, float poly, float dir, D3DCOLOR colour);

	//// 多角形を描く関数
	void DrawPolygon(float x, float y, float r, float poly, float dir, D3DCOLOR colour);

private:

	// メンバ変数=================================================
	LPDIRECT3DDEVICE9        lpD3DDevice;

};
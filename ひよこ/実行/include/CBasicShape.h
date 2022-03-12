#pragma once

#include <d3dx9.h>

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)




////////////////////////////////////////////////// \‘¢‘ÌéŒ¾ //////////////////////////////////////////////////

// ’¸“_—p‚Ì\‘¢‘Ì‚ğéŒ¾
typedef struct VERTEX2D
{
	float x;			// xÀ•W
	float y;			// yÀ•W
	float z;			// í‚É0
	float rhw;			// í‚É1
	D3DCOLOR color;		// F
}Vertex2D;




////////////////////////////////////////////////// ƒNƒ‰ƒX‚ÌŠÖ” //////////////////////////////////////////////////

class CBasicShape
{
public:

	CBasicShape();
	~CBasicShape();

	// ƒƒ“ƒoŠÖ”=================================================
	void Release();		// I—¹ˆ—
	void SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice);

	//// “_‚ğ•`‚­ŠÖ”
	void DrawPixel(float x, float y, D3DCOLOR colour);

	//// 2“_ŠÔ‚Ìü‚ğ•`‚­ŠÖ”
	void DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR colour);

	void DrawLineColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2);

	//// OŠpŒ`‚ğü‚Å•`‚­ŠÖ”
	void DrawLineTriangle(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR colour);

	void DrawLineTriColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2, float x3, float y3, D3DCOLOR colour3);

	//// OŠpŒ`‚ğ•`‚­ŠÖ”
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR colour);

	void DrawTriColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2, float x3, float y3, D3DCOLOR colour3);

	//// lŠpŒ`‚ğü‚Å•`‚­ŠÖ”
	void DrawLineSquare(float x, float y, int width, int height, D3DCOLOR colour);

	void DrawLineSquColGrad(float x, float y, int width, int height, D3DCOLOR colour1, D3DCOLOR colour2, D3DCOLOR colour3, D3DCOLOR colour4);

	//// lŠpŒ`‚ğ•`‚­ŠÖ”
	void DrawSquare(float x, float y, int width, int height, D3DCOLOR colour);

	void DrawSquColGrad(float x, float y, int width, int height, D3DCOLOR colour1, D3DCOLOR colour2, D3DCOLOR colour3, D3DCOLOR colour4);

	//// ‰~‚ğ“_‚Å•`‚­ŠÖ”
	void DrawDotCircle(float x, float y, float rx, float ry, D3DCOLOR colour);

	//// ‰~‚ğü‚Å•`‚­ŠÖ”
	void DrawLineCircle(float x, float y, float rx, float ry, D3DCOLOR colour);

	//// ‰~‚ğ•`‚­ŠÖ”
	void DrawCircle(float x, float y, float rx, float ry, D3DCOLOR colour);

	//// ‘½ŠpŒ`‚ğ“_‚Å•`‚­ŠÖ”
	void DrawDotPoly(float x, float y, float r, float poly, D3DCOLOR colour);

	//// ‘½ŠpŒ`‚ğü‚Å•`‚­ŠÖ”
	void DrawLinePoly(float x, float y, float r, float poly, float dir, D3DCOLOR colour);

	//// ‘½ŠpŒ`‚ğ•`‚­ŠÖ”
	void DrawPolygon(float x, float y, float r, float poly, float dir, D3DCOLOR colour);

private:

	// ƒƒ“ƒo•Ï”=================================================
	LPDIRECT3DDEVICE9        lpD3DDevice;

};
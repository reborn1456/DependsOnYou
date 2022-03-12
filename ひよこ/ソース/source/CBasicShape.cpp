#include "../include/CBasicShape.h"


CBasicShape::CBasicShape()
	: lpD3DDevice()
{
}

CBasicShape::~CBasicShape()
{
}

// 終了処理
void CBasicShape::Release()
{
	lpD3DDevice->Release();
}

void CBasicShape::SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice)
{
	lpD3DDevice = apD3DDevice;
}


//// 点を描く関数
void CBasicShape::DrawPixel(float x, float y, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x, y, 0, 1, colour } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST /* primitive type, this draws a point */, 1 /* the amount of points */, vertex, sizeof(Vertex2D));
	//lpD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST /* primitive type, this draws a line between points */, 1 /* the amount of lines */, vertex, sizeof(Vertex2D));
	//lpD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP /* primitive type, this draws lines */, 3 /* the amount of lines */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

//// 2点間の線を描く関数
void CBasicShape::DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x1, y1, 0, 1, colour }, { x2, y2, 0, 1, colour } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST /* primitive type, this draws a line between points */, 1 /* the amount of lines */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

void CBasicShape::DrawLineColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x1, y1, 0, 1, colour1 }, { x2, y2, 0, 1, colour2 } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST /* primitive type, this draws a line between points */, 1 /* the amount of lines */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

//// 三角形を線で描く関数
void CBasicShape::DrawLineTriangle(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x1, y1, 0, 1, colour }, { x2, y2, 0, 1, colour }, { x2, y2, 0, 1, colour }, { x3, y3, 0, 1, colour }, { x3, y3, 0, 1, colour }, { x1, y1, 0, 1, colour } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST /* primitive type, this draws a line between points */, 3 /* the amount of lines */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

void CBasicShape::DrawLineTriColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2, float x3, float y3, D3DCOLOR colour3)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x1, y1, 0, 1, colour1 }, { x2, y2, 0, 1, colour2 }, { x2, y2, 0, 1, colour2 }, { x3, y3, 0, 1, colour3 }, { x3, y3, 0, 1, colour3 }, { x1, y1, 0, 1, colour1 } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST /* primitive type, this draws a line between points */, 3 /* the amount of lines */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

//// 三角形を描く関数
void CBasicShape::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x1, y1, 0, 1, colour }, { x2, y2, 0, 1, colour }, { x3, y3, 0, 1, colour } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST /* primitive type, this draws a line between points */, 1 /* the amount of lines */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

void CBasicShape::DrawTriColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2, float x3, float y3, D3DCOLOR colour3)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x1, y1, 0, 1, colour1 }, { x2, y2, 0, 1, colour2 }, { x3, y3, 0, 1, colour3 } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST /* primitive type, this draws a line between points */, 1 /* the amount of lines */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

//// 四角形を線で描く関数
void CBasicShape::DrawLineSquare(float x, float y, int width, int height, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x, y, 0, 1, colour }, { x + width, y, 0, 1, colour }, { x + width, y, 0, 1, colour }, { x + width, y + height, 0, 1, colour }, { x + width, y + height, 0, 1, colour }, { x, y + height, 0, 1, colour }, { x, y + height, 0, 1, colour }, { x, y, 0, 1, colour } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST /* primitive type, this draws a line between points */, 4 /* the amount of lines */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

void CBasicShape::DrawLineSquColGrad(float x, float y, int width, int height, D3DCOLOR colour1, D3DCOLOR colour2, D3DCOLOR colour3, D3DCOLOR colour4)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x, y, 0, 1, colour1 }, { x + width, y, 0, 1, colour2 }, { x + width, y, 0, 1, colour2 }, { x + width, y + height, 0, 1, colour3 }, { x + width, y + height, 0, 1, colour3 }, { x, y + height, 0, 1, colour4 }, { x, y + height, 0, 1, colour4 }, { x, y, 0, 1, colour1 } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST /* primitive type, this draws a line between points */, 4 /* the amount of lines */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

//// 四角形を描く関数
void CBasicShape::DrawSquare(float x, float y, int width, int height, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x, y, 0, 1, colour }, { x + width, y, 0, 1, colour }, { x, y + height, 0, 1, colour }, { x + width, y + height, 0, 1, colour } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP /* primitive type, this draws a line between points */, 2 /* the amount of primitives */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

void CBasicShape::DrawSquColGrad(float x, float y, int width, int height, D3DCOLOR colour1, D3DCOLOR colour2, D3DCOLOR colour3, D3DCOLOR colour4)
{
	// 頂点用変数の宣言
	Vertex2D vertex[] = { { x, y, 0, 1, colour1 }, { x + width, y, 0, 1, colour2 }, { x, y + height, 0, 1, colour3 }, { x + width, y + height, 0, 1, colour4 } };

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP /* primitive type, this draws a line between points */, 2 /* the amount of primitives */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

//// 円を点で描く関数
void CBasicShape::DrawDotCircle(float x, float y, float rx, float ry, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[360 + 1];

	float deg;   //Degree(0∼360)
	float rad;   //Radian(0∼2π)

	for (int i = 0; i < 360; i++)
	{
		deg = i;
		rad = D3DXToRadian(deg);
		vertex[i].x = x + cos(rad) * rx;
		vertex[i].y = y + sin(rad) * ry;
		vertex[i].z = 0.0f;
		vertex[i].rhw = 1.0f;
		vertex[i].color = colour;
	}

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST /* primitive type, this draws a point */, 360 /* the amount of points */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);

}

//// 円を線で描く関数
void CBasicShape::DrawLineCircle(float x, float y, float rx, float ry, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[60 + 1];

	float deg;   //Degree(0∼360)
	float rad;   //Radian(0∼2π)

	for (int i = 0; i < 60 + 1; i++)
	{
		deg = i * 6;
		rad = D3DXToRadian(deg);
		vertex[i].x = x + cos(rad) * rx;
		vertex[i].y = y + sin(rad) * ry;
		vertex[i].z = 0.0f;
		vertex[i].rhw = 1.0f;
		vertex[i].color = colour;
	}

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP /* primitive type, this draws a line between points */, 60 /* the amount of primitives */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);

}

//// 円を描く関数
void CBasicShape::DrawCircle(float x, float y, float rx, float ry, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[60 + 1];

	float deg;   //Degree(0∼360)
	float rad;   //Radian(0∼2π)

	for (int i = 0; i < 60 + 1; i++)
	{
		deg = i * 6;
		rad = D3DXToRadian(deg);
		vertex[i].x = x + cos(rad) * rx;
		vertex[i].y = y + sin(rad) * ry;
		vertex[i].z = 0.0f;
		vertex[i].rhw = 1.0f;
		vertex[i].color = colour;
	}

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN /* primitive type, this draws a line between points */, 60 - 1 /* the amount of primitives */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

//// 多角形を点で描く関数
void CBasicShape::DrawDotPoly(float x, float y, float r, float poly, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[360 + 1];

	float deg;   //Degree(0∼360)
	float rad;   //Radian(0∼2π)

	for (int i = 0; i < poly + 1; i++)
	{
		deg = i * (360 / poly);
		rad = D3DXToRadian(deg);
		vertex[i].x = x + cos(rad) * r;
		vertex[i].y = y + sin(rad) * r;
		vertex[i].z = 0.0f;
		vertex[i].rhw = 1.0f;
		vertex[i].color = colour;
	}

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST /* primitive type, this draws a point */, 360 /* the amount of points */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);

}

//// 多角形を線で描く関数
void CBasicShape::DrawLinePoly(float x, float y, float r, float poly, float dir, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[60 + 1];

	float deg;   //Degree(0∼360)
	float rad;   //Radian(0∼2π)

	for (int i = 0; i < poly + 1; i++)
	{
		deg = i * (360 / poly) + dir;
		rad = D3DXToRadian(deg);
		vertex[i].x = x + cos(rad) * r;
		vertex[i].y = y + sin(rad) * r;
		vertex[i].z = 0.0f;
		vertex[i].rhw = 1.0f;
		vertex[i].color = colour;
	}

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP /* primitive type, this draws a line between points */, poly /* the amount of primitives */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);

}

//// 多角形を描く関数
void CBasicShape::DrawPolygon(float x, float y, float r, float poly, float dir, D3DCOLOR colour)
{
	// 頂点用変数の宣言
	Vertex2D vertex[60 + 1];

	float deg;   //Degree(0∼360)
	float rad;   //Radian(0∼2π)

	for (int i = 0; i < poly + 1; i++)
	{
		deg = i * (360 / poly) + dir;
		rad = D3DXToRadian(deg);
		vertex[i].x = x + cos(rad) * r;
		vertex[i].y = y + sin(rad) * r;
		vertex[i].z = 0.0f;
		vertex[i].rhw = 1.0f;
		vertex[i].color = colour;
	}

	// FVF設定（頂点構造体の情報を伝える）
	lpD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	// 描画
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN /* primitive type, this draws a line between points */, (poly - 1) /* the amount of primitives */, vertex, sizeof(Vertex2D));

	// 元々のFVF設定に戻す
	lpD3DDevice->SetFVF(FVF_VERTEX);
}

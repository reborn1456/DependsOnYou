#pragma once

#include <d3dx9.h>

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)




////////////////////////////////////////////////// �\���̐錾 //////////////////////////////////////////////////

// ���_�p�̍\���̂�錾
typedef struct VERTEX2D
{
	float x;			// x���W
	float y;			// y���W
	float z;			// ���0
	float rhw;			// ���1
	D3DCOLOR color;		// �F
}Vertex2D;




////////////////////////////////////////////////// �N���X�̊֐� //////////////////////////////////////////////////

class CBasicShape
{
public:

	CBasicShape();
	~CBasicShape();

	// �����o�֐�=================================================
	void Release();		// �I������
	void SetD3DDevice(LPDIRECT3DDEVICE9 apD3DDevice);

	//// �_��`���֐�
	void DrawPixel(float x, float y, D3DCOLOR colour);

	//// 2�_�Ԃ̐���`���֐�
	void DrawLine(float x1, float y1, float x2, float y2, D3DCOLOR colour);

	void DrawLineColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2);

	//// �O�p�`����ŕ`���֐�
	void DrawLineTriangle(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR colour);

	void DrawLineTriColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2, float x3, float y3, D3DCOLOR colour3);

	//// �O�p�`��`���֐�
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR colour);

	void DrawTriColGrad(float x1, float y1, D3DCOLOR colour1, float x2, float y2, D3DCOLOR colour2, float x3, float y3, D3DCOLOR colour3);

	//// �l�p�`����ŕ`���֐�
	void DrawLineSquare(float x, float y, int width, int height, D3DCOLOR colour);

	void DrawLineSquColGrad(float x, float y, int width, int height, D3DCOLOR colour1, D3DCOLOR colour2, D3DCOLOR colour3, D3DCOLOR colour4);

	//// �l�p�`��`���֐�
	void DrawSquare(float x, float y, int width, int height, D3DCOLOR colour);

	void DrawSquColGrad(float x, float y, int width, int height, D3DCOLOR colour1, D3DCOLOR colour2, D3DCOLOR colour3, D3DCOLOR colour4);

	//// �~��_�ŕ`���֐�
	void DrawDotCircle(float x, float y, float rx, float ry, D3DCOLOR colour);

	//// �~����ŕ`���֐�
	void DrawLineCircle(float x, float y, float rx, float ry, D3DCOLOR colour);

	//// �~��`���֐�
	void DrawCircle(float x, float y, float rx, float ry, D3DCOLOR colour);

	//// ���p�`��_�ŕ`���֐�
	void DrawDotPoly(float x, float y, float r, float poly, D3DCOLOR colour);

	//// ���p�`����ŕ`���֐�
	void DrawLinePoly(float x, float y, float r, float poly, float dir, D3DCOLOR colour);

	//// ���p�`��`���֐�
	void DrawPolygon(float x, float y, float r, float poly, float dir, D3DCOLOR colour);

private:

	// �����o�ϐ�=================================================
	LPDIRECT3DDEVICE9        lpD3DDevice;

};
#pragma once

#include <d3dx9.h>




////////////////////////////////////////////////// クラスの関数 //////////////////////////////////////////////////

class CMaths
{
public:

	CMaths();
	~CMaths();

	// メンバ変数=================================================


	// メンバ関数=================================================

	////角度算出, Degree
	////相手の角度を求める関数,  Degree    Arctan Function
	////キャラ1から見たキャラ2（ターゲット）の角度
	float GetDegreeAngle(float x, float y, float tx, float ty);

	////角度算出, Radian
	////相手の角度を求める関数,  Radian    Arctan Function
	////キャラ1から見たキャラ2（ターゲット）の角度
	float GetRadianAngle(float x, float y, float tx, float ty);

	////直線距離算出
	float GetDistance(float x, float y, float tx, float ty);




private:

	// メンバ変数=================================================


	// メンバ関数=================================================

};
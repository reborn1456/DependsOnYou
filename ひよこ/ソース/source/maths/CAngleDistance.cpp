#include "../../include/CMaths.h"


CMaths::CMaths()
{
}

CMaths::~CMaths()
{
}

////角度算出, Degree
////相手の角度を求める関数,  Degree    Arctan Function
////キャラ1から見たキャラ2（ターゲット）の角度
float CMaths::GetDegreeAngle(float x, float y, float tx, float ty)
{
	float fx = tx - x;
	float fy = ty - y;

	if ((int)fx == 0.f && (int)fy == 0.f)
	{
		return 270.f;
	}

	float rad = atan2f(fy, fx)/* arc tangent with 2 points giving a float answer */;   //引数は縦、横の順番

	float deg = D3DXToDegree(rad);

	if (deg < 0)
	{
		deg += 360.0f;
	}

	/*double atan2(double y, double x);
	float atan2f(float y, float x);*/

	return deg;
}

////角度算出, Radian
////相手の角度を求める関数,  Radian    Arctan Function
////キャラ1から見たキャラ2（ターゲット）の角度
float CMaths::GetRadianAngle(float x, float y, float tx, float ty)
{
	float fx = tx - x;
	float fy = ty - y;

	if ((int)fx == 0.f && (int)fy == 0.f)
	{
		return 270.f;
	}

	float rad = atan2f(fy, fx)/* arc tangent with 2 points giving a float answer */;   //引数は縦、横の順番

	return rad;
}

////直線距離算出
float CMaths::GetDistance(float x, float y, float tx, float ty)
{
	float fx = tx - x;
	float fy = ty - y;

	//斜辺
	float dist = sqrt((fx * fx) + (fy * fy));

	return dist;
}

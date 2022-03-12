#include "../../include/CMaths.h"


CMaths::CMaths()
{
}

CMaths::~CMaths()
{
}

////�p�x�Z�o, Degree
////����̊p�x�����߂�֐�,  Degree    Arctan Function
////�L����1���猩���L����2�i�^�[�Q�b�g�j�̊p�x
float CMaths::GetDegreeAngle(float x, float y, float tx, float ty)
{
	float fx = tx - x;
	float fy = ty - y;

	if ((int)fx == 0.f && (int)fy == 0.f)
	{
		return 270.f;
	}

	float rad = atan2f(fy, fx)/* arc tangent with 2 points giving a float answer */;   //�����͏c�A���̏���

	float deg = D3DXToDegree(rad);

	if (deg < 0)
	{
		deg += 360.0f;
	}

	/*double atan2(double y, double x);
	float atan2f(float y, float x);*/

	return deg;
}

////�p�x�Z�o, Radian
////����̊p�x�����߂�֐�,  Radian    Arctan Function
////�L����1���猩���L����2�i�^�[�Q�b�g�j�̊p�x
float CMaths::GetRadianAngle(float x, float y, float tx, float ty)
{
	float fx = tx - x;
	float fy = ty - y;

	if ((int)fx == 0.f && (int)fy == 0.f)
	{
		return 270.f;
	}

	float rad = atan2f(fy, fx)/* arc tangent with 2 points giving a float answer */;   //�����͏c�A���̏���

	return rad;
}

////���������Z�o
float CMaths::GetDistance(float x, float y, float tx, float ty)
{
	float fx = tx - x;
	float fy = ty - y;

	//�Ε�
	float dist = sqrt((fx * fx) + (fy * fy));

	return dist;
}

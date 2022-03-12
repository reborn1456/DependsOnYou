#pragma once

#include <d3dx9.h>




////////////////////////////////////////////////// �N���X�̊֐� //////////////////////////////////////////////////

class CMaths
{
public:

	CMaths();
	~CMaths();

	// �����o�ϐ�=================================================


	// �����o�֐�=================================================

	////�p�x�Z�o, Degree
	////����̊p�x�����߂�֐�,  Degree    Arctan Function
	////�L����1���猩���L����2�i�^�[�Q�b�g�j�̊p�x
	float GetDegreeAngle(float x, float y, float tx, float ty);

	////�p�x�Z�o, Radian
	////����̊p�x�����߂�֐�,  Radian    Arctan Function
	////�L����1���猩���L����2�i�^�[�Q�b�g�j�̊p�x
	float GetRadianAngle(float x, float y, float tx, float ty);

	////���������Z�o
	float GetDistance(float x, float y, float tx, float ty);




private:

	// �����o�ϐ�=================================================


	// �����o�֐�=================================================

};
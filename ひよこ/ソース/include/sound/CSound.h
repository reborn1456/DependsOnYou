#pragma once

#include <dsound.h>
#include "wavread.h"

#pragma comment(lib, "dsound.lib")




////////////////////////////////////////////////// �N���X�̊֐� //////////////////////////////////////////////////

class CSound
{
public:

	CSound();
	~CSound();

	// �����o�ϐ�=================================================
	void Release();		// �I������

	//����炷�̂ɕK�v
	LPDIRECTSOUNDBUFFER8     lpBGM;     //����������ꕨ
	LPDIRECTSOUNDBUFFER8     lpSE;      //����������ꕨ
	LPDIRECTSOUND3DBUFFER8   lp3DBGM;   //���̐ݒ�f�[�^

	// �����o�֐�=================================================
	void LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, const char *fname);
	void Initialize(HWND apHwnd);             	// �T�E���h����������

private:

	// �����o�ϐ�=================================================
	//���֌W
	LPDIRECTSOUND8          lpDSound;       //DirectSound�I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER     lpSPrimary;

	// �����o�֐�=================================================
};
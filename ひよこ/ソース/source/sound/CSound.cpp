#include "../../include/sound/CSound.h"
#include <cassert>  /* this is the new version of assert which will NOT appear when build in release mode */

CSound::CSound()
	: lpBGM()
	, lpSE()
	, lp3DBGM()
	, lpDSound()
	, lpSPrimary()
{
}

CSound::~CSound()
{
}

// �I������
void CSound::Release()
{
	// �T�E���h�I������
	lpSPrimary->Release();
	lpDSound->Release();

	CoUninitialize();
}

void CSound::Initialize(HWND apHwnd)
{

	//������-------------------------------------------------------------
	//---------------------DirectSound�֘A-----------------------
	DirectSoundCreate8(NULL, &lpDSound, NULL);

	//�������x����ݒ�
	lpDSound->SetCooperativeLevel(apHwnd, DSSCL_PRIORITY);

	// �v���C�}���E�o�b�t�@�̍쐬
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	// �v���C�}���E�o�b�t�@���w��
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	// �o�b�t�@�����
	lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL);

	// �v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
	// �@�@�@�D�拦�����x���ȏ�̋������x�����ݒ肳��Ă���K�v������܂��D
	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX));
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;		// �Q�`�����l���i�X�e���I�j
	pcmwf.nSamplesPerSec = 44100;	// �T���v�����O�E���[�g�@44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = 16;		// 16�r�b�g
	lpSPrimary->SetFormat(&pcmwf);

	CoInitialize(NULL);
}

void CSound::LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, const char *fname)
{
	HRESULT hr;

	// WAVE�t�@�C�����J��
	CWaveSoundRead WaveFile;
	WaveFile.Open(fname);

	// �Z�J���_���E�o�b�t�@���쐬����
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	//(DSBCAPS_CTRL3D=�R�c�T�E���h���g�p)
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRL3D |
		DSBCAPS_CTRLVOLUME | /*DSBCAPS_CTRLPAN |*/ DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	//3D�T�E���h��HEL�A���S���Y����I��
	dsbdesc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
	//	dsbdesc.guid3DAlgorithm=DS3DALG_DEFAULT;

		// �o�b�t�@�����
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	mpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSData);
	pDSTmp->Release();

	// �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
	LPVOID lpvPtr1;		// �ŏ��̃u���b�N�̃|�C���^
	DWORD dwBytes1;		// �ŏ��̃u���b�N�̃T�C�Y
	LPVOID lpvPtr2;		// �Q�Ԗڂ̃u���b�N�̃|�C���^
	DWORD dwBytes2;		// �Q�Ԗڂ̃u���b�N�̃T�C�Y

	hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
	if (DSERR_BUFFERLOST == hr)
	{
		pDSData->Restore();
		hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ���b�N����

		// �����ŁC�o�b�t�@�ɏ�������
		// �o�b�t�@�Ƀf�[�^���R�s�[����
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// �������݂��I������炷����Unlock����D
		hr = pDSData->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}

	//3D�̃Z�J���_���o�b�t�@�����
	pDSData->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&pDSData3D);
}
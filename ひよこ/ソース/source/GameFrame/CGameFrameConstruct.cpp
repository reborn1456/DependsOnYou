/*
  DirextX9���ʂ̐����Ȃǂ��s���Ă���֐����u������cpp�t�@�C��
  ��{�I�Ɍ��Ȃ��Ă悢�B�C�ɂȂ�l�͌��Ă݂�̂��A��
*/

#include "../../include/CGameFrame.h"
#include <cassert>

LRESULT _stdcall WindowFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			if (MessageBox(hwnd, "Are you sure you want to quit?", "Message Box", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				PostQuitMessage(0);
			}

			/*PostQuitMessage(0);*/
			return 0;
		}
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CGameFrame::Create(HINSTANCE aHInst, const int aCmdShow)
{
	mWndClass = CreateWNDCLASS(aHInst);
	mpHwnd = CreateHWND(aHInst, aCmdShow);
	assert(mpHwnd != nullptr);
	CreateDirectX9();

	// �X�v���C�g�쐬
	D3DXCreateSprite(mpD3DDevice, &mpSprite);
	mpSprite->OnResetDevice();

	// �t�H���g�쐬
	D3DXCreateFont(mpD3DDevice, 30, 30, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "851�e�K�L�J�N�b�g", &mpFont);
	mpFont->OnResetDevice();
}

HWND CGameFrame::CreateHWND(HINSTANCE aHInst, const int aCmdShow)
{
	HWND result;
	result = CreateWindowEx(
		0,
		mAppName.c_str(),
		mAppName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		mScrollWidth, mScrollHeight,
		NULL, NULL, aHInst,
		NULL);

	if (!result)return nullptr;

	ShowWindow(result, aCmdShow);
	UpdateWindow(result);
	SetFocus(result);

	
	if (mIsFullScreen) {
		
		ShowCursor(mFullScreenCursor);
	}
	else {
		RECT rc = { 0,0,mScrollWidth,mScrollHeight };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(result, NULL, 50, 50, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	return result;
}

WNDCLASS CGameFrame::CreateWNDCLASS(HINSTANCE aHInst)
{
	WNDCLASS result;
	result.style = CS_DBLCLKS;
	result.lpfnWndProc = WindowFunc;
	result.cbClsExtra = 0;
	result.cbWndExtra = 0;
	result.hInstance = aHInst;
	result.hIcon = (HICON)LoadImage(NULL, "Texture/TestImages/icon256gimp.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	result.hCursor = LoadCursor(NULL, IDC_ARROW);
	result.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	result.lpszMenuName = NULL;
	result.lpszClassName = mAppName.c_str();

	RegisterClass(&result);
	return result;
}

void CGameFrame::CreateDirectX9()
{
	// Direct3D �I�u�W�F�N�g���쐬
	mpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (mpD3D == nullptr)
	{
		// �I�u�W�F�N�g�쐬���s
		MessageBox(NULL, "Direct3D �̍쐬�Ɏ��s���܂����B", "ERROR", MB_OK | MB_ICONSTOP);
		return;
	}
	int adapter;

	// �g�p����A�_�v�^�ԍ�
	adapter = D3DADAPTER_DEFAULT;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	ZeroMemory(&mD3Dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D �������p�����[�^�̐ݒ�
	if (mIsFullScreen)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
		mD3Dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		D3DDISPLAYMODE disp;
		// ���݂̉�ʃ��[�h���擾
		mpD3D->GetAdapterDisplayMode(adapter, &disp);
		mD3Dpp.BackBufferFormat = disp.Format;
	}
	// �\���̈�T�C�Y�̐ݒ�
	mD3Dpp.BackBufferWidth = mScrollWidth;
	mD3Dpp.BackBufferHeight = mScrollHeight;
	mD3Dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (mIsFullScreen == false)
	{
		// �E�C���h�E���[�h
		mD3Dpp.Windowed = 1;
	}

	// Z �o�b�t�@�̎����쐬
	mD3Dpp.EnableAutoDepthStencil = 1;
	mD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//�ޯ��ޯ̧��ۯ��\�ɂ���(GetDC���\�ɂȂ�)
	mD3Dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// �f�o�C�X�̍쐬 - T&L HAL
	if (FAILED(mpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, mpHwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &mD3Dpp, &mpD3DDevice)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(mpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, mpHwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3Dpp, &mpD3DDevice)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(mpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, mpHwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3Dpp, &mpD3DDevice)))
			{
				// ���ǎ��s����
				MessageBox(NULL, "DirectX9���������ł��܂���B\n���Ή��̃p�\�R���Ǝv���܂��B", "ERROR", MB_OK | MB_ICONSTOP);
				mpD3D->Release();
				// �I������
				return;
			}
		}
	}

	// �����_�����O�E�X�e�[�g��ݒ�
	// Z �o�b�t�@�L����->�O��֌W�̌v�Z�𐳊m�ɂ��Ă����
	mpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	mpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�u�����f�B���O�L����
	mpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// �A���t�@�u�����f�B���O���@��ݒ�
	mpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	mpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�
	mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// �e�N�X�`���̐F���g�p
	mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// ���_�̐F���g�p
	mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// �����_�����O���̐F�̌v�Z���@�̐ݒ�
	mpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//���ʃJ�����O
	mpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �t�B���^�ݒ�
	mpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	mpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	mpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// ���C�g
	mpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	mpD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	// ���_�t�H�[�}�b�g�̐ݒ�
	mpD3DDevice->SetFVF(mFvFVertex);
}

void CGameFrame::GameLoop()
{
	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	mpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	Update();

	// �`��J�n
	mpD3DDevice->BeginScene();

	D3DXMATRIX mView, mProj;

	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(0.0f, 0.0f, -10.0f),	// �J�����̈ʒu
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)mScrollWidth / (float)mScrollHeight, 1.0f, 1000.0f);

	//�s��ݒ�
	mpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	mpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	Draw();

	// �`��I��
	mpD3DDevice->EndScene();

	// �o�b�N�o�b�t�@���v���C�}���o�b�t�@�ɃR�s�[
	mpD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CGameFrame::Draw()
{
	Draw3D();
	Draw2D();
}
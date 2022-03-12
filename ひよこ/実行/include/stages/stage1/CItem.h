#pragma once

#include <d3dx9.h>
#include "../../Define.h"
#include "../../enum.h"

#define MAP_HEIGHT  40
#define MAP_WIDTH   40
#define MAPCHIP_NUM_W 51
#define MAPCHIP_NUM_H 50

class CGameFrame;   // �N���X�̑O���錾

class CItem
{
public:

	CItem();	//�R���X�g���N�^
	~CItem();	//�f�X�g���N�^

	//�����o�֐�
	void Update();											 //�X�V
	void Draw(LPD3DXSPRITE apSprite);                        //�`��
	void SetTexture(LPDIRECT3DTEXTURE9 apTexture);           //�e�N�X�`���ݒ�
	void LoadMapFile();										 //�}�b�v�ǂݍ���
	
	const bool MapHitCheck(eMoveState aMoveState, D3DXVECTOR3 aPos);

	void SetOwner(CGameFrame* apOwner);

private:

	//�����o�ϐ�
	int					 ItemChipList[MAPCHIP_NUM_H][MAPCHIP_NUM_W];			//�`�b�v�Z�b�g
	LPDIRECT3DTEXTURE9   mpTexture;											//�摜
	D3DXVECTOR3          mPosition[MAPCHIP_NUM_H][MAPCHIP_NUM_W];			//���W
	D3DXMATRIX           mMatrix[MAPCHIP_NUM_H][MAPCHIP_NUM_W];				//�s��

	eMoveState			 mState;

	bool				 mScrollFlg;
	int					 mScrollCnt;
	float				 mCameraX;											//�w�i��X�ړ���
	float				 mCameraY;											//�w�i��Y�ړ���
	float				 mMoveX;
	float				 mMoveY;
	int					 mMoveWait;

	const float          mScrollWidth = 160.0f;
	const float          mLeftLimit = mScrollWidth;
	const float          mRightLimit = SCRW - mScrollWidth;
	const float          mScrollHeight = 120.0f;
	const float          mUpLimit = mScrollHeight;
	const float          mDownLimit = SCRH - mScrollHeight;

	D3DXVECTOR3          mPlayerPos;
	bool				 mPlayerMoveFlg;
	float				 mPlayerMoveX;
	float				 mPlayerMoveY;

	CGameFrame*			 mpOwner;   // �I�[�i�[


};


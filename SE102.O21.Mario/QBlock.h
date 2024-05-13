#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_QBLOCK_QUES 2100
#define ID_ANI_QBLOCK_EMP 2200
#define QBLOCK_WIDTH 16
#define QBLOCK_BBOX_WIDTH 16
#define QBLOCK_BBOX_HEIGHT 16

#define QBLOCK_STATE_QUES 100
#define QBLOCK_STATE_EMP 200

#define QBLOCK_RINGING_TIME 100


class CQBlock : public CGameObject {
protected:
	DWORD ring_start;
	float min = 0;
	

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	

public:
	int setting = 0;
	int ringing = 0;
	int trigger = 0;
	int attack = 0;
	int stack = 1;
	CQBlock(float x, float y, int setting, int stack);
	CGameObject* ShowItem();
};
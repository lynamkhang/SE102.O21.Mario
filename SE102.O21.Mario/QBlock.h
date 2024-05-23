#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_QBLOCK_QUES 2100
#define ID_ANI_QBLOCK_EMP 2200
#define QBLOCK_WIDTH 16
#define QBLOCK_BBOX_WIDTH 16
#define QBLOCK_BBOX_HEIGHT 16

#define QBLOCK_STATE_HIT 100
#define QBLOCK_STATE_EMP 101

#define QBLOCK_BOUNCE_OFFSET 10
#define QBLOCK_BOUNCE_SPEED 0.2f



class CQBlock : public CGameObject {
protected:
	bool isEmpty = false;
	float baseY;
	int itemType = 0;

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	
public:
	CQBlock(float x, float y, int itemType);
	void ShowItem();
	virtual void SetState(int state);
};
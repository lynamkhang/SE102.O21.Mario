#pragma once
#include "GameObject.h"
#include "Game.h"

#define LEAF_BBOX_WIDTH  16
#define LEAF_BBOX_HEIGHT 14

#define LEAF_FALL_SPEED_VX	0.04f 
#define LEAF_FALL_SPEED_VY	0.02f

#define LEAF_RISING_SPEED 0.05f
#define LEAF_RISING_HEIGHT 32

#define LEAF_STATE_FALLING	100

#define ID_ANI_LEAF_FALL_RIGHT	3200
#define ID_ANI_LEAF_FALL_LEFT	3201



class CLeaf : public CGameObject
{
protected:

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT);

	float startY;
	float xMax = 0;
	float xMin = 0;

	DWORD rise_start;
	bool rising;

public:
	CLeaf(float x, float y);
	void StartRising() { rising = true; rise_start = DWORD(GetTickCount64()); }
	virtual void SetState(int state);
};
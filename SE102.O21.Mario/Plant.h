#pragma once

#include "GameObject.h"
#include "Mario.h"

#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 24

#define PLANT_RISING_TIME 6000
#define PLANT_DYING_TIME 800

#define PLANT_STATE_NORMAL 0 
#define PLANT_STATE_DIE 1

#define ID_ANI_PLANT_NORMAL 850 
#define ID_ANI_PLANT_DIE 851

class CPlant : public CGameObject
{
protected:
	float baseY;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPlant(float x, float y);
	virtual void SetState(int state);

};

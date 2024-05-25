#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"


#define FIREBALL_BBOX_WIDTH 9
#define FIREBALL_BBOX_HEIGHT 9

#define FIREBALL_MOVING_SPEED 0.05f

#define ID_ANI_FIREBALL 900

class CPlantFireBall : public CGameObject
{
protected:

	float vx, vy;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };


public:
	CPlantFireBall(float x, float y);
};
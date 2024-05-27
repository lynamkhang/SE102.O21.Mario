#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"


#define FIREBALL_BBOX_WIDTH 9
#define FIREBALL_BBOX_HEIGHT 9

#define FIREBALL_MOVING_SPEED 0.07f

#define ID_ANI_FIREBALL 900

class CPlantFireBall : public CGameObject
{
protected:

	float ax, ay;

	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; };


public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CPlantFireBall(float x, float y);
	float GetX() { return x; };
	float GetY() { return y; };
};
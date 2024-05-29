#pragma once
#include "GameObject.h"

#define FLYGOOMBA_GRAVITY 0.001f
#define FLYGOOMBA_WALKING_SPEED 0.025f



#define FLYGOOMBA_BBOX_WIDTH 16
#define FLYGOOMBA_BBOX_HEIGHT 19
#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define FLYGOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define FLYGOOMBA_STATE_WALKING 100
#define FLYGOOMBA_STATE_DIE 200
#define FLYGOOMBA_STATE_FLYING 300

#define ID_ANI_FLYGOOMBA_WALKING 5500
#define ID_ANI_FLYGOOMBA_DIE 5501
#define ID_ANI_FLYGOOMBA_FLYING 5502

class CFlyGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFlyGoomba(float x, float y);
	virtual void SetState(int state);
};
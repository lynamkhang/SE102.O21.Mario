#pragma once
#include "GameObject.h"

#define FLYGOOMBA_GRAVITY 0.0004f
#define FLYGOOMBA_FLY_GRAVITY 0.001f
#define FLYGOOMBA_WALKING_SPEED 0.03f
#define FLYGOOMBA_DIE_SPEED 0.36f


#define FLYGOOMBA_BBOX_WIDTH 16
#define FLYGOOMBA_BBOX_HEIGHT 19
#define FLYGOOMBA_FLY_BBOX_WIDTH 16
#define FLYGOOMBA_FLY_BBOX_HEIGHT 19
#define FLYGOOMBA_BBOX_HEIGHT_DIE 7

#define FLYGOOMBA_DIE_TIMEOUT 500

#define FLYGOOMBA_STATE_WALKING 100
#define FLYGOOMBA_STATE_DIE 200
#define FLYGOOMBA_STATE_FLY 300


#define ID_ANI_FLYGOOMBA_WALKING 5500
#define ID_ANI_FLYGOOMBA_FLY 5502
#define ID_ANI_FLYGOOMBA_FLY_WALKING 5502
#define ID_ANI_FLYGOOMBA_DIE 5501
#define DISTANCE_TO_FOLLOW 80
#define WALK_TIME 1000
#define FLY_SPEED 0.16f

class CFlyGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG die_start;
	ULONGLONG walk_start;
	bool isOnPlatform;
	bool isFly;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFlyGoomba(float x, float y);
	bool GetIsFly() { return isFly; };
	void SetIsFly(bool isFly) { this->isFly = isFly; };
	virtual void SetState(int state);
	void StartWalk() { walk_start = GetTickCount64(); }
};
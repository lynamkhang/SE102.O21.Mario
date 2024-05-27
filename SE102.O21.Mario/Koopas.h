#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "Goomba.h"
#include "Plant.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_INSHELL_SPEED 0.1f


#define KOOPA_BBOX_WIDTH 16
#define	KOOPA_BBOX_HEIGHT 17
#define KOOPA_INSHELL_BBOX_WIDTH 17
#define KOOPA_INSHELL_BBOX_HEIGHT 17
#define KOOPA_BBOX_HEIGHT_DIE 16

#define KOOPA_STATE_WALKING_LEFT 0
#define KOOPA_STATE_WALKING_RIGHT 1
#define KOOPA_STATE_INSHELL_IDLE 2
#define KOOPA_STATE_INSHELL_KICK 3
#define KOOPA_STATE_DIE 4

#define ID_ANI_KOOPA_WALKING_LEFT 750
#define ID_ANI_KOOPA_WALKING_RIGHT 751
#define ID_ANI_KOOPA_INSHELL_IDLE 752
#define ID_ANI_KOOPA_INSHELL_KICK 753
#define ID_ANI_KOOPA_DIE 754

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;
	bool isInShell;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
};
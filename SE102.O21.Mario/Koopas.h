#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Goomba.h"
#include "Collision.h"
#include "Plant.h"
#include "QBlock.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.025f
#define KOOPA_INSHELL_SPEED 0.2f


#define KOOPA_BBOX_WIDTH 16
#define	KOOPA_BBOX_HEIGHT 24
#define KOOPA_INSHELL_BBOX_WIDTH 16
#define KOOPA_INSHELL_BBOX_HEIGHT 14

#define KOOPA_STATE_WALKING_LEFT 0
#define KOOPA_STATE_WALKING_RIGHT 1
#define KOOPA_STATE_INSHELL_IDLE 2
#define KOOPA_STATE_INSHELL_KICK_LEFT 3
#define KOOPA_STATE_INSHELL_KICK_RIGHT 4
#define KOOPA_STATE_INSHELL_HOLD 5
#define KOOPA_STATE_DIE 6

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
	


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	bool IsOnPlatform(vector<LPGAMEOBJECT>* coObjects);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithQBlock(LPCOLLISIONEVENT e);

public:
	bool isInShell, isKicked, isHold;

	CKoopas(float x, float y);
	virtual void SetState(int state);
	float GetX() { return x; };
};
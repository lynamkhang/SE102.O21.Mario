#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_IDLE 0
#define COIN_STATE_FLY 1
#define COIN_STATE_DIE 2

#define COIN_FLY_SPEED 0.3f
#define COIN_GRAVITY 0.3f
#define COIN_FLY_HEIGHT 50.0f



class CCoin : public CGameObject {
	float startY;
public:
	CCoin(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};
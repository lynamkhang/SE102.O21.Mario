#pragma once

#include "GameObject.h"
#include "PlayScene.h"
#include "Mario.h"


#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 32

#define PLANT_RISING_SPEED 0.03f

#define PLANT_STATE_UP 0
#define PLANT_STATE_DOWN 1
#define PLANT_STATE_DIE 2

#define ID_ANI_PLANT_DOWN_LEFT 850
#define ID_ANI_PLANT_DOWN_LEFT_STILL 851
#define ID_ANI_PLANT_UP_LEFT 852
#define ID_ANI_PLANT_UP_LEFT_STILL 853
#define ID_ANI_PLANT_DOWN_RIGHT 854
#define ID_ANI_PLANT_DOWN_RIGHT_STILL 855
#define ID_ANI_PLANT_UP_RIGHT 856
#define ID_ANI_PLANT_UP_RIGHT_STILL 857
#define ID_ANI_PLANT_DIE 858

class CPlant : public CGameObject
{
protected:
		
	float baseY;
	float maxY;
	bool climax;

	ULONGLONG die_start;
	ULONGLONG rise_start;

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

#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_MOVING_SPEED 0.05f
#define MUSHROOM_RISING_TIME 500


#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16


#define MUSHROOM_STATE_MOVING 100
#define MUSHROOM_STATE_FLY 200

#define ID_ANI_MUSHROOM 6000


class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	DWORD rise_start;
	int rising = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y);
	void StartRising() { rising = 1; rise_start = DWORD(GetTickCount64()); }
	virtual void SetState(int state);
};
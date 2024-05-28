#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"

#define MUSHROOM_MOVING_SPEED 0.05f
#define MUSHROOM_RISING_SPEED 0.05f
#define MUSHROOM_RISING_HEIGHT 16
#define MUSHROOM_GRAVITY	0.002f


#define MUSHROOM_BBOX_WIDTH 14
#define MUSHROOM_BBOX_HEIGHT 14


#define MUSHROOM_STATE_MOVING 0
#define MUSHROOM_STATE_RISING 1


#define ID_ANI_MUSHROOM 6000


class CMushroom : public CGameObject
{
protected:
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float ax;
	float ay;
	int nx;
	float startY;

	DWORD rise_start;
	bool rising;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y);
	void StartRising() { rising = true; rise_start = DWORD(GetTickCount64()); }
	virtual void SetState(int state);
};
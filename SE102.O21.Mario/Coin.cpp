#include "Coin.h"

CCoin::CCoin(float x, float y) : CGameObject(x, y)
{
	this->startY = y;
	this->vy = 0;
	SetState(COIN_STATE_IDLE);
}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);
    y += vy * dt;

    if (state == COIN_STATE_FLY)
    {
        if (y <= startY - COIN_FLY_HEIGHT)
        {
            vy = COIN_GRAVITY; // Start falling down
        }
        else if (y >= startY)
        {
            vy = 0; // Stop moving
            y = startY; // Correct position
            SetState(COIN_STATE_IDLE); // Transition to idle state
        }
    }

    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case COIN_STATE_FLY:
        vy = -COIN_FLY_SPEED;
        break;
    case COIN_STATE_IDLE:
        vy = 0;
        break;
    }
}
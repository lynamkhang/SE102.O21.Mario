#include "Mushroom.h"

CMushroom::CMushroom(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	this->startY = y;
	StartRising();
	SetState(MUSHROOM_STATE_RISING);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (rising)
	{
		y -= MUSHROOM_RISING_SPEED * dt;
		if (startY - y >= MUSHROOM_RISING_HEIGHT)
		{
			rising = false;
			SetState(MUSHROOM_STATE_MOVING);
			y = startY - MUSHROOM_RISING_HEIGHT; 
		}
	}
	else
	{
		vy += ay * dt;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::Render()
{
	int aniId = ID_ANI_MUSHROOM;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case MUSHROOM_STATE_MOVING:
			vx = -MUSHROOM_MOVING_SPEED;
			break;
		case MUSHROOM_STATE_RISING:
			vx = 0;
			vy = 0;
			break;
	}
}

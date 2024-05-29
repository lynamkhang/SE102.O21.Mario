#include "FlyGoomba.h"

CFlyGoomba::CFlyGoomba(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = FLYGOOMBA_GRAVITY;
	die_start = -1;
	SetState(FLYGOOMBA_STATE_FLYING);
}

void CFlyGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLYGOOMBA_STATE_DIE)
	{
		left = x - FLYGOOMBA_BBOX_WIDTH / 2;
		top = y - FLYGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + FLYGOOMBA_BBOX_WIDTH;
		bottom = top + FLYGOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == FLYGOOMBA_STATE_WALKING)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
	else
	{
		left = x - FLYGOOMBA_BBOX_WIDTH / 2;
		top = y - FLYGOOMBA_BBOX_HEIGHT / 2;
		right = left + FLYGOOMBA_BBOX_WIDTH;
		bottom = top + FLYGOOMBA_BBOX_HEIGHT;
	}
}

void CFlyGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CFlyGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFlyGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CFlyGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == FLYGOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}



	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFlyGoomba::Render()
{
	int aniId = ID_ANI_FLYGOOMBA_WALKING;
	if (state == FLYGOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_FLYGOOMBA_DIE;
	}
	else if (state == FLYGOOMBA_STATE_FLYING)
	{
		aniId = ID_ANI_FLYGOOMBA_FLYING;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFlyGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLYGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (FLYGOOMBA_BBOX_HEIGHT - FLYGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case FLYGOOMBA_STATE_WALKING:
		vx = -FLYGOOMBA_WALKING_SPEED;
		y -= (FLYGOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT) / 2;
		break;
	case FLYGOOMBA_STATE_FLYING:
		vx = -FLYGOOMBA_WALKING_SPEED;
		break;
	}
}


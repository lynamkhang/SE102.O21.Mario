#include "Koopas.h"

CKoopas::CKoopas(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	die_start = -1;
	isInShell = false;
	isKicked = false;
	SetState(KOOPA_STATE_WALKING_LEFT);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPA_BBOX_WIDTH/2;
	top = y - KOOPA_BBOX_HEIGHT/2;
	right = left + KOOPA_BBOX_WIDTH;
	bottom = top + KOOPA_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (state == KOOPA_STATE_INSHELL_IDLE)
	{
		aniId = ID_ANI_KOOPA_INSHELL_IDLE;
	}
	else if (state == KOOPA_STATE_INSHELL_KICK)
	{
		aniId = ID_ANI_KOOPA_INSHELL_KICK;
	}
	else if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPA_DIE;
	}
	else if (vx > 0)
	{
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	else if (vx <= 0)
	{
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	switch (state)
	{
		case KOOPA_STATE_WALKING_LEFT:
			nx = -1;
			vx = KOOPA_WALKING_SPEED * nx;
			isInShell = false;
			isKicked = false;
			break;
		case KOOPA_STATE_WALKING_RIGHT:
			nx = 1;
			vx = KOOPA_WALKING_SPEED * nx;
			break;
		case KOOPA_STATE_INSHELL_IDLE:
			vx = 0;
			break;
		case KOOPA_STATE_INSHELL_KICK:
			vx = -KOOPA_INSHELL_SPEED;
			break;
		case KOOPA_STATE_DIE:
			die_start = GetTickCount64();
			break;
	}
}
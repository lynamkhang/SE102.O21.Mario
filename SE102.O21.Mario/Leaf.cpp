#include "Leaf.h"

CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->vx = LEAF_FALL_SPEED_VX;
	this->vy = 0;
	xMax = x + LEAF_BBOX_WIDTH * 2;
	xMin = x - 1;
	this->startY = y;
	rising = true;
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + LEAF_BBOX_WIDTH;
	bottom = y + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CLeaf*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (rising)
	{
		y -= LEAF_RISING_SPEED * dt;
		if (startY - y >= LEAF_RISING_HEIGHT)
		{
			rising = false;
			y = startY - LEAF_RISING_HEIGHT;
			SetState(LEAF_STATE_FALLING);
		}
	}

	if (state == LEAF_STATE_FALLING)
	{
		// Make the leaf move left and right while falling
		if (x > xMax || x < xMin)
		{
			vx = -vx;
		}
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::Render()
{
	int aniId = ID_ANI_LEAF_FALL_RIGHT;
	if (vx >= 0)
	{
		aniId = ID_ANI_LEAF_FALL_LEFT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_FALLING:
		vy = LEAF_FALL_SPEED_VY;
		break;
	}
}

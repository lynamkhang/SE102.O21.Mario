#include "Plant.h"

CPlant::CPlant(float x, float y) : CGameObject(x, y)
{
	this->baseY = y;
}

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLANT_BBOX_WIDTH / 2;
	top = y - PLANT_BBOX_HEIGHT / 2;
	right = left + PLANT_BBOX_WIDTH;
	bottom = top + PLANT_BBOX_HEIGHT;
}

void CPlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPlant*>(e->obj)) return;
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::Render()
{
	int aniId = ID_ANI_PLANT_NORMAL;
	if (state == PLANT_STATE_DIE)
	{
		//aniId = ID_ANI_PLANT_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case PLANT_STATE_NORMAL:
			break;
		case PLANT_STATE_DIE:
			break;
	}
}



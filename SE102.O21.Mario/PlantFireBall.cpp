#include "PlantFireBall.h"

CPlantFireBall::CPlantFireBall(float x, float y) : CGameObject(x, y)
{
	CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = dynamic_cast<CMario*>(currentScene->GetPlayer());
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);
	this->x = x;
	this->y = y;
	// Calculate the direction vector from the plant to Mario
	float dx = marioX - x;
	float dy = marioY - y;
	float length = sqrt(dx * dx + dy * dy);

	// Normalize the direction vector and multiply by speed
	this->vx = dx / length * FIREBALL_MOVING_SPEED;
	this->vy = dy / length * FIREBALL_MOVING_SPEED;
}

void CPlantFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void CPlantFireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPlantFireBall*>(e->obj)) return;
}

void CPlantFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlantFireBall::Render()
{
	CGame* game = CGame::GetInstance();
	float camX;
	float camY;
	float scrw = float(game->GetBackBufferWidth());
	game->GetCamPos(camX, camY);

	if (x > camX + scrw)		// if out of camera don't render
		return;

	int aniId = ID_ANI_FIREBALL;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
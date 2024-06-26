#include "Plant.h"

CPlant::CPlant(float x, float y) : CGameObject(x, y)
{
	SetState(PLANT_STATE_UP);
	this->baseY = y;
	this->maxY = y - PLANT_BBOX_HEIGHT;
}

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLANT_BBOX_WIDTH/2;
	top = y - PLANT_BBOX_HEIGHT/2;
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

	GetMarioPosition();

	// Check if mario is near
	bool marioIsNear = abs(marioX - this->x) < MARIO_PROXIMITY_THRESHOLD && abs(marioY - this->y) < MARIO_PROXIMITY_THRESHOLD;

	// if mario is near and plant is under pipe don't rise up
	if (marioIsNear && isUnderPipe)
	{
		SetState(PLANT_STATE_DOWN);
	}

	y += vy * dt;
	if (state == PLANT_STATE_DOWN) {
		if (y >= baseY) {
			y = baseY;
			vy = 0;
			isUnderPipe = true;
			if (GetTickCount64() - rise_start >= 2500) {
				SetState(PLANT_STATE_UP);
			}
		}
	}

	else if (state == PLANT_STATE_UP) {
		if (y <= baseY - PLANT_BBOX_HEIGHT) {
			y = baseY - PLANT_BBOX_HEIGHT;
			vy = 0;
			isUnderPipe = false;
			if (GetTickCount64() - rise_start >= 2500) {
				SetState(PLANT_STATE_DOWN);
				ShootFireBall();
			}
		}
	}
	
	if (y == maxY) //check if reach max height
	{
		climax = true;
	}
	else
	{
		climax = false;
	}

	if ((state == PLANT_STATE_DIE) && (GetTickCount64() - die_start) > PLANT_DIE_TIMEOUT)
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::Render()
{
	CGame* game = CGame::GetInstance();
	float camX;
	float camY;
	float scrw = float(game->GetBackBufferWidth());
	game->GetCamPos(camX, camY);

	GetMarioPosition();


	if (x > camX + scrw)		// if out of camera don't render
		return;

	int aniId = ID_ANI_PLANT_DOWN_LEFT;
	if (state == PLANT_STATE_DIE)
	{
		aniId = ID_ANI_PLANT_DIE;
	}
	//check mario location to render corresponding animations
	else if (marioX < this->x && marioY > this->y) 
	{
		if (climax) 
		{
			aniId = ID_ANI_PLANT_DOWN_LEFT_STILL;
		}
	}
	else if (marioX < this->x && marioY < this->y)
	{
		if (climax)
		{
			aniId = ID_ANI_PLANT_UP_LEFT_STILL;
		}
		else
		{
			aniId = ID_ANI_PLANT_UP_LEFT;
		}
	}
	else if (marioX > this->x && marioY > this->y)
	{
		if (climax)
		{
			aniId = ID_ANI_PLANT_DOWN_RIGHT_STILL;
		}
		else
		{
			aniId = ID_ANI_PLANT_DOWN_RIGHT;
		}
	}
	else if (marioX > this->x && marioY < this->y)
	{
		if (climax)
		{
			aniId = ID_ANI_PLANT_UP_RIGHT_STILL;
		}
		else
		{
			aniId = ID_ANI_PLANT_UP_RIGHT;
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case PLANT_STATE_DOWN:
			vy = PLANT_RISING_SPEED;
			rise_start = GetTickCount64();
			break;
		case PLANT_STATE_UP:
			vy -= PLANT_RISING_SPEED;
			rise_start = GetTickCount64();
		case PLANT_STATE_DIE:
			die_start = GetTickCount64();
			break;
	}
}

void CPlant::GetMarioPosition() {
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	mario->GetPosition(marioX, marioY);

	if (!mario)
		return;
}

void CPlant::ShootFireBall()
{
	// Calculate the distance to Mario
	float dx = marioX - this->x;
	float dy = marioY - this->y;
	float distance = sqrt(dx * dx + dy * dy);

	// Check if Mario is within shooting range
	if (distance <= PLANT_SHOOTING_RANGE)
	{
		// Create a new fireball
		CPlantFireBall* fireball = new CPlantFireBall(this->x + PLANT_BBOX_WIDTH/3, this->y);
		CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		currentScene->AddObject(fireball);
	}
}
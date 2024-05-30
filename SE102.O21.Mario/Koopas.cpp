#include "Koopas.h"

CKoopas::CKoopas(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	die_start = -1;
	isInShell = false;
	isKicked = false;
	isHold = false;
	SetState(KOOPA_STATE_WALKING_LEFT);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isInShell && !isKicked)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPA_INSHELL_BBOX_WIDTH / 2;
		top = y - KOOPA_INSHELL_BBOX_HEIGHT / 2;
		right = left + KOOPA_INSHELL_BBOX_WIDTH;
		bottom = top + KOOPA_INSHELL_BBOX_HEIGHT;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);

	vy += ay * dt;
	vx += ax * dt;

	if (!isInShell) {
		if (!IsOnPlatform(coObjects))
		{
			vx = -vx;
		}
	}

	if (mario->isHolding && this->isHold)
	{
		if (mario->GetDirection() > 0) // Mario is facing right
		{
			this->SetPosition(x + MARIO_BIG_BBOX_WIDTH, y);
		}
		else // Mario is facing left
		{
			this->SetPosition(x - KOOPA_BBOX_WIDTH, y);
		}
	}

	if (isHold)
	{
		vy = 0;
	}

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
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = -vx;
	}
	if (isKicked)
	{
		if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CPlant*>(e->obj))
			OnCollisionWithPlant(e);
		else if (dynamic_cast<CQBlock*>(e->obj))
			OnCollisionWithQBlock(e);
	}
}

void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (isInShell && !isKicked)
	{
		aniId = ID_ANI_KOOPA_INSHELL_IDLE;
	}
	else if (isInShell && isKicked)
	{
		aniId = ID_ANI_KOOPA_INSHELL_KICK;
	}
	else if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPA_DIE;	
	}
	else if (vx > 0 && !isInShell)
	{
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	else if (vx <= 0 && !isInShell)
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
			isInShell = false;
			isKicked = false;
			break;
		case KOOPA_STATE_INSHELL_IDLE:
			vx = 0;
			isInShell = true;
			isKicked = false;
			break;
		case KOOPA_STATE_INSHELL_KICK_LEFT:
			nx = -1;
			vx = KOOPA_INSHELL_SPEED * nx;
			isInShell = true;
			isKicked = true;
			break;
		case KOOPA_STATE_INSHELL_KICK_RIGHT:
			nx = 1;
			vx = KOOPA_INSHELL_SPEED * nx;
			isInShell = true;
			isKicked = true;
			break;
		case KOOPA_STATE_DIE:
			die_start = GetTickCount64();
			break;
	}
}

bool CKoopas::IsOnPlatform(vector<LPGAMEOBJECT>* coObjects)
{
	// Check if there's a platform ahead of Koopa
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	// Adjust the checking position based on Koopa's direction
	float check_x = (vx > 0) ? r : l;
	float check_y = b + 1; // Slightly below Koopa's feet

	// Check if there's a blocking object at the checking position
	for (size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (obj->IsBlocking())
		{
			float oL, oT, oR , oB;
			obj->GetBoundingBox(oL, oT, oR , oB);
			if (check_x >= oL && check_x <= oR && check_y >= oT && check_y <= oB)
			{
				return true;
			}
		}
	}
	return false;
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
	}
}

void CKoopas::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	CPlant* plant = dynamic_cast<CPlant*>(e->obj);

	if (plant->GetState() != PLANT_STATE_DIE)
	{
		plant->SetState(PLANT_STATE_DIE);
	}
}

void CKoopas::OnCollisionWithQBlock(LPCOLLISIONEVENT e)
{
	CQBlock* qblock = dynamic_cast<CQBlock*>(e->obj);

	if (qblock->GetState() != QBLOCK_STATE_EMP)
	{
		qblock->SetState(QBLOCK_STATE_EMP);
	}
}
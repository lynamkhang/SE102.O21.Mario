#include "QBlock.h"
#include "Mushroom.h"
#include "AssetIDs.h"

CQBlock::CQBlock(float x, float y, int setting, int stack):CGameObject(x, y)
{
	this->setting = setting;
	ring_start = NULL;
	min = y;
	this->stack = stack;
	SetState(QBLOCK_STATE_QUES);
}

void CQBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (GetTickCount64() - ring_start > QBLOCK_RINGING_TIME)
	{
		ring_start = 0;
		ringing = 0;
		y = min;
	}

	if (ringing)
	{
		if (GetTickCount64() - ring_start >= QBLOCK_RINGING_TIME / 2)
			y += 1.5;
		else
			y -= 1.5;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQBlock::Render()
{
	int aniId = ID_ANI_QBLOCK_QUES;
	if (state == QBLOCK_STATE_EMP)
	{
		aniId = ID_ANI_QBLOCK_EMP;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CQBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QBLOCK_BBOX_WIDTH / 2;
	t = y - QBLOCK_BBOX_HEIGHT / 2;
	r = l + QBLOCK_BBOX_WIDTH;
	b = t + QBLOCK_BBOX_HEIGHT;
}

CGameObject* CQBlock::ShowItem() 
{
	CGameObject* obj = NULL;
	if (setting == 0)
	{
		obj = new CMushroom(this->x, this->y);
	}

	return obj;
}



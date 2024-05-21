#include "QBlock.h"
#include "Mushroom.h"
#include "AssetIDs.h"

CQBlock::CQBlock(float x, float y, int itemType):CGameObject(x, y)
{
	this->itemType = itemType;
	baseY = y;
}

void CQBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//bug the question block fall out of scene
	CGameObject::Update(dt, coObjects);
	y += vy * dt;
	if (state = QBLOCK_STATE_HIT) 
	{
		if (y < baseY - QBLOCK_BOUND_OFFSET)
		{
			vy = QBLOCK_BOUND_SPEED;
			SetState(QBLOCK_STATE_EMP);
		}
		else if (state == QBLOCK_STATE_EMP)
		{
			if (y > baseY)
			{
				vy = 0;
				y = baseY;
			}
		}
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

void CQBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case QBLOCK_STATE_EMP:
		{
			vy = QBLOCK_BOUND_SPEED;
			isEmpty = true;
			break;
		}
		case QBLOCK_STATE_HIT:
		{
			vy = -QBLOCK_BOUND_SPEED;
			break;
		}
		default:
		{
			isEmpty = false;
			break;
		}
	}
}




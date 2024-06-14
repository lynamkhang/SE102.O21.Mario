#include "QBlock.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Coin.h"
#include "AssetIDs.h"
#include "Game.h"
#include "PlayScene.h"


CQBlock::CQBlock(float x, float y, int itemType):CGameObject(x, y)
{
	this->itemType = itemType;
	baseY = y;
}

void CQBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	y += vy * dt;

	if (state == QBLOCK_STATE_HIT)
	{
		if (y <= baseY - QBLOCK_BOUNCE_OFFSET)
		{
			vy = QBLOCK_BOUNCE_SPEED; // Start moving down
		}
		else if (y >= baseY)
		{
			vy = 0; // Stop moving
			y = baseY; // Correct position
			SetState(QBLOCK_STATE_EMP); // Transition to empty state	
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

void CQBlock::ShowItem() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (itemType == 0)
	{
		
		CCoin* coin = new CCoin(x, y - QBLOCK_BBOX_HEIGHT);
		coin->SetState(COIN_STATE_FLY); // Set the coin to fly

		// Add the coin to your game objects
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(coin);
	}

	else if (itemType == 1)
	{
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
		{
			CMushroom* mushroom = new CMushroom(x, y);

			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(mushroom);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_BIG)
		{
			CLeaf* leaf = new CLeaf(x, y);

			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(leaf);
		}

	}
}

void CQBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case QBLOCK_STATE_EMP:
		{
			ShowItem();
			vy = 0;
			isEmpty = true;
			break;
		}
		case QBLOCK_STATE_HIT:
		{
			vy = -QBLOCK_BOUNCE_SPEED;
			break;
		}
		default:
		{
			isEmpty = false;
			break;
		}
	}
}



#include "Environment.h"

void CEnvironment::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CEnvironment::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}
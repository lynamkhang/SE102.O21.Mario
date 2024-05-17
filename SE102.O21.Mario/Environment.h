#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ENVIRONMENT_WIDTH 16
#define ENVIRONMENT_BBOX_WIDTH 16
#define ENVIRONMENT_BBOX_HEIGHT 16

class CEnvironment : public CGameObject {
	int aniId;
public:
	CEnvironment(float x, float y, int ani_id)  {
		this->aniId = ani_id;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
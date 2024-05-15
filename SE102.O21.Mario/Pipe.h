#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PIPE_TOP_LEFT 10020
#define ID_ANI_PIPE_TOP_RIGHT 10021
#define ID_ANI_PIPE_BOTTOM_LEFT 10022
#define ID_ANI_PIPE_BOTTOM_RIGHT 10023

#define PIPE_WIDTH 16
#define PIPE_BBOX_WIDTH 16
#define PIPE_BBOX_HEIGHT 16

class CPipe : public CGameObject {
protected:
	int aniId;
public:
	CPipe(float x, float y, int aniId) : CGameObject(x, y) {
		this->aniId = aniId;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
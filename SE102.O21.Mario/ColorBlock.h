#pragma once

#include "GameObject.h"

class CColorBlock : public CGameObject {
protected:
	int length;
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	CColorBlock(float x, float y, float cell_width, float cell_height, int lenght, int sprite_id_begin, int sprite_id_middle, int sprite_id_end) : CGameObject(x, y) 
	{
		this->length = lenght;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;

	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
};

typedef CColorBlock* LPCOLORBLOCK;
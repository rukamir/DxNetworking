#pragma once

#include <vector>
#include <map>

#include "spriteelements.h"
#include "TextureManager.h"

class MenuObj :
	public SpriteElements
{
private:
	SpriteElements*						newElem;
	std::vector<SpriteElements*>		m_vObjInMenu;
	std::map<LPCSTR, SpriteElements*>	m_mObjInMenu;
public:
	MenuObj(void){}
	MenuObj(int id);
	~MenuObj(void);

	void AddButton(LPCSTR title, D3DXVECTOR2 pos);

	void Update(float dt);
};

class Button :
	public SpriteElements
{
public:
	Button(int id) :
		SpriteElements(id){
		SetTexture(gTextureMan->button);
		SetRect(0,0,184,38);
		SetPosition(D3DXVECTOR2(100.0f, 225.0f));
		SetCenter(D3DXVECTOR2(92.0f, 19.0f));
	}
};
#pragma once

#include <vector>
#include <map>
#include <string>

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

	SpriteElements* GetElemByTitle(LPCSTR title);

	void AddButton(LPCSTR title, D3DXVECTOR2 pos);
	void AddPlayerCount(LPCSTR title, D3DXVECTOR2 pos);

	void Update(float dt);
	void Draw(ID3DXSprite* SpriteInterface, ID3DXFont* FontInterface);
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

class PlayerDisplayCount :
	public SpriteElements
{
private:
	unsigned int		m_iPlayerCount;
public:
	PlayerDisplayCount(int id) :
		SpriteElements(id){
		SetTexture(gTextureMan->button);
		SetRect(0,0,184,38);
		SetPosition(D3DXVECTOR2(100.0f, 225.0f));
		SetCenter(D3DXVECTOR2(92.0f, 19.0f));
		m_iPlayerCount	=	0;
	}
	void SetPlayerCount(unsigned int numOfPlayers){
		m_iPlayerCount	=	numOfPlayers;
	}
	void Draw(ID3DXSprite* SpriteInterface, ID3DXFont* FontInterface){
		D3DXMatrixTransformation2D(&mat, &this->m_center, /*(*i)->GetScaleRotation()*/NULL, 
			&this->m_scale, &this->m_center, this->m_rotation, &this->GetPosition());
		SpriteInterface->SetTransform(&mat);
		SpriteInterface->Draw(this->m_pTexture, this->m_rect, 0, 0, D3DCOLOR_XRGB(255, 255, 255));
		FontInterface->DrawText(SpriteInterface, std::to_string(m_iPlayerCount).c_str(),-1,NULL,DT_CENTER|DT_VCENTER,D3DCOLOR_XRGB(0,0,0));
	}
};
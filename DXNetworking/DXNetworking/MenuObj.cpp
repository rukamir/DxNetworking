#include "MenuObj.h"


MenuObj::MenuObj(int id)
	: SpriteElements(id)
{
}


MenuObj::~MenuObj(void)
{
	for (const auto spt: m_vObjInMenu){
		delete spt;
	}
	m_vObjInMenu.clear();
	m_mObjInMenu.clear();
	newElem = NULL;
}

SpriteElements* MenuObj::GetElemByTitle(LPCSTR title){
	return m_mObjInMenu.find(title)->second;
}

void MenuObj::AddButton(LPCSTR title, D3DXVECTOR2 pos)
{
	newElem		= new Button(m_id);
	newElem->SetParentPos(&m_position);
	newElem->SetPosition(pos);
	newElem->SetText(title);

	// Put into map and vector
	m_vObjInMenu.push_back(newElem);
	m_mObjInMenu.insert(std::make_pair(title, newElem));
}

void MenuObj::AddPlayerCount(LPCSTR title, D3DXVECTOR2 pos)
{
	newElem		= new PlayerDisplayCount(m_id);
	newElem->SetParentPos(&m_position);
	newElem->SetPosition(pos);
	newElem->SetText(title);

	// Put into map and vector
	m_vObjInMenu.push_back(newElem);
	m_mObjInMenu.insert(std::make_pair(title, newElem));
}

void MenuObj::Update(float dt)
{
	//// Update all elements within this menu
	//for (auto spt: m_vObjInMenu)
	//{
	//	spt->Update(dt);
	//}
}

void MenuObj::Draw(ID3DXSprite* SpriteInterface, ID3DXFont* FontInterface)
{
	for (const auto spt: m_vObjInMenu)
	{
		spt->Draw(SpriteInterface, FontInterface);
	}
}
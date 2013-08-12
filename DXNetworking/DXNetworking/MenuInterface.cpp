#include "MenuInterface.h"

MenuInterface::MenuInterface()
{
	m_pos = D3DXVECTOR2(0.0f, 0.0f);
	m_active = true;
}

MenuInterface::~MenuInterface()
{
	VectSprtElemShPtrs::iterator i = m_vSptElem.begin();
	if(m_vSptElem.size())// != 0)
		for(;i != m_vSptElem.end(); i++)
		{
			(*i) = 0;
		}
}

void MenuInterface::AddElementToMenu(SprtElemShPtr menuItem)
{
	D3DXVECTOR2 hold;

	if (menuItem)
	{
		hold = menuItem->GetPosition();
		//set value relative to menu position
		//menuItem->SetPosition( hold + m_pos );
		menuItem->SetParentPos(&this->m_pos);
		m_vSptElem.push_back(menuItem);
	}
}

void MenuInterface::Activate()
{
	m_active = true;

	VectSprtElemShPtrs::iterator i = m_vSptElem.begin();
	for (; i != m_vSptElem.end(); i++)
	{
		(*i)->SetVisability(true);
	}

	this->m_pos = D3DXVECTOR2(100,100);

	//this->m_velocity = D3DXVECTOR2(0,1000);
}

void MenuInterface::Unactivate()
{
	m_active = false;

	VectSprtElemShPtrs::iterator i = m_vSptElem.begin();
	for (; i != m_vSptElem.end(); i++)
	{
		(*i)->SetVisability(false);
	}

	this->m_velocity = D3DXVECTOR2(0,-1000);
	//this->m_pos = D3DXVECTOR2(-2000,-2000);
}

bool MenuInterface::IsActive()
{
	return m_active;
}

//void MenuInterface::Draw(LPD3DXSPRITE SpriteObj, ID3DXFont* D3DFont)
//{
//	static RECT* rect = new RECT();
//	rect->top = 0;
//	rect->left = 5;
//	rect->bottom = 40;
//	rect->right = 120;
//
//	if(IsActive())
//	{
//		if (m_vSptElem.size() > 0)
//		{
//			VectSprtElemShPtrs::iterator i = m_vSptElem.begin();
//			for (;i != m_vSptElem.end(); i++)
//			{
//				D3DXMATRIX mat2;
//				D3DXMatrixTransformation2D(&mat2, &(*i)->GetCenter(), /*(*i)->GetScaleRotation()*/NULL, &(*i)->GetScale(),&(*i)->GetCenter(),(*i)->GetRotation(), 
//					&D3DXVECTOR2((*i)->GetPosition()+m_pos));
//				SpriteObj->SetTransform(&mat2);
//				SpriteObj->Draw((*i)->GetTexture(), (*i)->GetRect(), NULL/*(*i)->GetCenter()*/, NULL/*(*i)->GetPosition()*/, D3DCOLOR_XRGB(255, 255, 255));
//				D3DFont->DrawText(SpriteObj, (*i)->GetText(),-1,rect,DT_CENTER|DT_VCENTER,D3DCOLOR_XRGB(0,0,0));
//			}
//		}
//	}
//	else
//	{
//		this->SetPosition(D3DXVECTOR2(-200,-200));
//	}
//}

void MenuInterface::SetPosition(D3DXVECTOR2 pos)
{
	m_pos = pos;

	//VectSprtElemShPtrs::iterator i = m_vSptElem.begin();
	//for (; i != m_vSptElem.end(); i++)
	//{
	//	//(*i)->SetPosition()
	//}
}

void MenuInterface::Update(float dt)
{
	//VectSprtElemShPtrs::iterator i = m_vSptElem.begin();
	//for (; i != m_vSptElem.end(); i++)
	//{
	//	(*i)->Update(dt);
	//}

	if(!this->IsActive())
	{
		if(this->m_pos.y > -650)
		{
			//m_velocity = D3DXVECTOR2(0,-5);
			static D3DXVECTOR2 move = m_velocity * dt;
			m_pos += move;
		}
		else
			m_velocity = D3DXVECTOR2(0,0);
	}
	else
	{
		if(this->m_pos.y < 150)
		{
			//m_velocity = D3DXVECTOR2(0,-5);
			static D3DXVECTOR2 move = m_velocity * dt;
			m_pos += move;
		}
		else
			m_velocity = D3DXVECTOR2(0,0);
	}
}
#include "MenuElements.h"
#include "TextureManager.h"


//********************************************************
//                   BUTTON
//********************************************************

Button::Button(int id, LPCSTR text)
	: SpriteElements(id)
{
	//m_mainSptElem		=		0;
	m_id				=		id;
	m_text				=		text;
	m_elementType		=		basicButton;
	this->m_pTexture	=		gTextureMan->ButtonGrey;

	////create and align drop down arrow
	//element = 0;
	//element = SprtElemShPtr(new SpriteElements(m_id));
	//element->SetPosition(D3DXVECTOR2(100.0f, 50.0f));
	//element->SetText(text);
	//element->SetTexture(gTextureMan->ButtonGrey);
	//element->SetRect(0,0,184,38);
	//element->SetCenter(D3DXVECTOR2(92.0f, 19.0f));
}

//void Button::Draw(ID3DXSprite* SpriteInterface, ID3DXFont* FontInterface)
//{
//	D3DXMatrixTransformation2D(&mat, &this->m_center, /*(*i)->GetScaleRotation()*/NULL, 
//		&this->m_scale, &this->m_center, this->m_rotation, &this->GetPosition());
//	SpriteInterface->SetTransform(&mat);
//	SpriteInterface->Draw(this->m_pTexture, this->m_rect, 0, 0, D3DCOLOR_XRGB(255, 255, 255));
//	FontInterface->DrawText(SpriteInterface, this->m_text,-1,NULL,DT_CENTER|DT_VCENTER,D3DCOLOR_XRGB(0,0,0));
//}

//********************************************************
//				DROP DOWN MENU
//********************************************************

DropDownBar::DropDownBar(int id, LPCSTR barTitle)
{
	//m_mainSptElem		=		0;
	m_id				=		id;
	m_expanded			=		false;
	m_elementType		=		dropDown;

	//create default item
	AddItem(barTitle);

	////create and align drop down arrow
	//element = 0;
	//element = SprtElemShPtr(new SpriteElements(m_id));
	//element->SetText(NULL);
	//element->SetTexture(gTextureMan->DropDownArrow);
	//element->SetPosition(D3DXVECTOR2(480,0));
	//element->SetCenter(D3DXVECTOR2(16,16));

	//m_vListSprtPtr.push_back(element);
}

void DropDownBar::Update(float dt)
{
	//D3DXVECTOR2 placeObj(this->GetPosition().x, 33);
	//if(!IsExpanded())
	//{

	//}
	//else
	//{
	//	VectSprtElemShPtrs::iterator i = m_vListSprtPtr.begin();
	//	for(;i != m_vListSprtPtr.end(); i++)
	//	{
	//		(*i)->SetPosition(placeObj);
	//		placeObj.x = this->GetPosition().x;
	//		//of place 32 down from current
	//		placeObj.y += 32;
	//	}
	//}
}

void DropDownBar::AddItem(LPCSTR itemName)
{
	//element = 0;
	//element = SprtElemShPtr(new SpriteElements(m_id));
	//element->SetText(itemName);
	//element->SetTexture(gTextureMan->DropDownItem);
	//element->SetCenter(D3DXVECTOR2(256,16));

	//m_vListSprtPtr.push_back(element);
}

//********************************************************
//				CHECKBOX
//********************************************************

CheckBox::CheckBox(int id, LPCSTR text)
	: SpriteElements(id)
{
	m_id				=	id;
	m_elementType		=	checkBox;
	m_text				=	text;
	checkValue			=	false;
	checkedTexture		=	gTextureMan->CheckBoxActive;
	uncheckedTexture	=	gTextureMan->CheckBoxNotActive;

	//m_mainSptElem = SprtElemShPtr(new SpriteElements(m_id));
	//m_mainSptElem->SetCenter(D3DXVECTOR2(16,16));
}

//void CheckBox::Draw(ID3DXSprite* SpriteInterface, ID3DXFont* FontInterface)
//{
//	D3DXMatrixTransformation2D(&mat, &this->m_center, /*(*i)->GetScaleRotation()*/NULL, 
//		&this->m_scale, &this->m_center, this->m_rotation, &this->GetPosition());
//	SpriteInterface->SetTransform(&mat);
//	SpriteInterface->Draw(this->m_pTexture, this->m_rect, 0, 0, D3DCOLOR_XRGB(255, 255, 255));
//	FontInterface->DrawText(SpriteInterface, this->m_text,-1,NULL,DT_CENTER|DT_VCENTER,D3DCOLOR_XRGB(0,0,0));
//}

//***************************************************************
//						CREDITITEM
//***************************************************************

CreditItem::CreditItem(int id, LPCSTR text)
	: SpriteElements(id)
{
	//m_mainSptElem		=		0;
	m_id				=		id;
	m_text				=		text;
	m_elementType		=		basicButton;
	this->m_pTexture	=		0;//gTextureMan->ButtonGrey;

	////create and align drop down arrow
	//element = 0;
	//element = SprtElemShPtr(new SpriteElements(m_id));
	//element->SetPosition(D3DXVECTOR2(100.0f, 50.0f));
	//element->SetText(text);
	//element->SetTexture(gTextureMan->ButtonGrey);
	//element->SetRect(0,0,184,38);
	//element->SetCenter(D3DXVECTOR2(92.0f, 19.0f));
}

Logo::Logo(int id, LPCSTR text)
	: SpriteElements(id)
{
	//m_mainSptElem		=		0;
	m_id				=		id;
	m_text				=		text;
	m_elementType		=		basicButton;
	this->m_pTexture	=		gTextureMan->logo;

	////create and align drop down arrow
	//element = 0;
	//element = SprtElemShPtr(new SpriteElements(m_id));
	//element->SetPosition(D3DXVECTOR2(100.0f, 50.0f));
	//element->SetText(text);
	//element->SetTexture(gTextureMan->ButtonGrey);
	//element->SetRect(0,0,184,38);
	//element->SetCenter(D3DXVECTOR2(92.0f, 19.0f));
}


//***************************************************************
//						MISSICON
//***************************************************************

MissIcon::MissIcon(int id, LPCSTR text)
	: SpriteElements(id)
{
	//m_mainSptElem		=		0;
	m_id				=		id;
	m_text				=		text;
	m_elementType		=		basicButton;
	this->m_pTexture	=		gTextureMan->miss;

	////create and align drop down arrow
	//element = 0;
	//element = SprtElemShPtr(new SpriteElements(m_id));
	//element->SetPosition(D3DXVECTOR2(100.0f, 50.0f));
	//element->SetText(text);
	//element->SetTexture(gTextureMan->ButtonGrey);
	//element->SetRect(0,0,184,38);
	//element->SetCenter(D3DXVECTOR2(92.0f, 19.0f));
}

HitIcon::HitIcon(int id, LPCSTR text)
	: SpriteElements(id)
{
	//m_mainSptElem		=		0;
	m_id				=		id;
	m_text				=		text;
	m_elementType		=		basicButton;
	this->m_pTexture	=		gTextureMan->hit;

	////create and align drop down arrow
	//element = 0;
	//element = SprtElemShPtr(new SpriteElements(m_id));
	//element->SetPosition(D3DXVECTOR2(100.0f, 50.0f));
	//element->SetText(text);
	//element->SetTexture(gTextureMan->ButtonGrey);
	//element->SetRect(0,0,184,38);
	//element->SetCenter(D3DXVECTOR2(92.0f, 19.0f));
}

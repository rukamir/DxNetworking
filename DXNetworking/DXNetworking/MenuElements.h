#pragma once

#include "SpriteElements.h"
#include <d3dx9.h>
#include <memory>
#include <vector>

using namespace std;

typedef std::shared_ptr<SpriteElements> SprtElemShPtr;
typedef vector<SprtElemShPtr> VectSprtElemShPtrs;


//class MenuElementBase : public SpriteElements
//{
//protected:
//	_ElementType					buttonType;
//	SprtElemShPtr				m_mainSptElem;
//	SprtElemShPtr				element;
//
//public:
//	MenuElementBase(){}
//	~MenuElementBase(){}
//
//	virtual void Update(float dt) = 0;
//};

class Button : public SpriteElements
{
protected:
public:
	Button(int id)
		{m_id=id;}
	Button(int id, LPCSTR text);
};

class DropDownBar : public SpriteElements
{
protected:
	bool					m_expanded;
	//VectSprtElemShPtrs		m_vListSprtPtr;
	LPDIRECT3DTEXTURE9		itemTexture;
	LPDIRECT3DTEXTURE9		openTexture;
public:
	DropDownBar(int id, LPCSTR barTitle);

	void Expand()
	{	m_expanded=true;}
	void Close()
	{	m_expanded=false;}
	bool IsExpanded()
	{	return m_expanded;}

	void AddItem(LPCSTR itemName);
	void Update(float dt);
};

class CheckBox : public SpriteElements
{
protected:
	LPDIRECT3DTEXTURE9		checkedTexture;
	LPDIRECT3DTEXTURE9		uncheckedTexture;
	bool					checkValue;
public:
	CheckBox(int id, LPCSTR text);

	void Check()
	{	m_pTexture=checkedTexture;
		checkValue=true;}
	void Uncheck()
	{	m_pTexture=uncheckedTexture;
		checkValue=false;}
	bool IsChecked()
	{return checkValue;}
};

class CreditItem : public SpriteElements
{
protected:
public:
	CreditItem(int id)
		{m_id=id;}
	CreditItem(int id, LPCSTR text);
};

class Logo : public SpriteElements
{
protected:
public:
	Logo(int id)
		{m_id=id;}
	Logo(int id, LPCSTR text);
};



class MissIcon : public SpriteElements
{
protected:
public:
	MissIcon(int id)
		{m_id=id;}
	MissIcon(int id, LPCSTR text);
};

class HitIcon : public SpriteElements
{
protected:
public:
	HitIcon(int id)
		{m_id=id;}
	HitIcon(int id, LPCSTR text);
};

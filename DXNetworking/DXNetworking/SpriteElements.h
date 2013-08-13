#pragma once

#include <d3dx9.h>
#include <D3dx9core.h>

#pragma comment(lib,"D3dx9.lib")

enum ElementType
{
	basicButton = 0,
	dropDown = 1,
	dropDownSub,
	checkBox
};

class SpriteElements
{
protected:
	int						m_id;
	D3DXVECTOR2				m_center;
	D3DXVECTOR2				m_position;
	D3DXVECTOR2				m_velocity;
	LPCSTR					m_text;
	D3DCOLOR				m_fontColor;
	IDirect3DTexture9*		m_pTexture;
	D3DXVECTOR2				m_scale;
	float					m_rotation;
	float					m_scaleRotation;
	RECT*					m_rect;
	bool					m_visable;
	ElementType				m_elementType;
	D3DXVECTOR2*			m_parentPos;
	D3DXMATRIX				mat;

	float			x, y;
	POINT			clickPos, mouse;
	//static string			clickedText;
public:
	//SprtElemShPtr			m_parent;
	SpriteElements(){}
	SpriteElements(int id)
		: m_id(id)
		{m_center		= D3DXVECTOR2(0,0);
		 m_position		= D3DXVECTOR2(0,0);
		 m_velocity		= D3DXVECTOR2(0,0);
		 m_text			= 0;
		 m_fontColor	= D3DCOLOR();
		 m_pTexture		= 0;
		 m_scale		= D3DXVECTOR2(1,1);
		 m_rotation		= 0;
		 m_scaleRotation= 0;
		 //m_pSrcFile		= 0;
		 m_rect			= 0;
		 m_visable		= true;
		 m_rect			= 0;
		 m_parentPos	= 0;}

	SpriteElements(int id, D3DXVECTOR2 center, D3DXVECTOR2 pos, D3DXVECTOR2 velo, 
		LPCSTR text, D3DCOLOR textColor, IDirect3DTexture9* texture, 
		D3DXVECTOR2 scale, float rotation, LPCSTR SrcFile)
		{m_id		=	id;
		 m_center	=	center;
		 m_position	=	pos;
		 m_velocity	=	velo;
		 m_text		=	text;
		 m_fontColor=	textColor;
		 m_pTexture	=	texture;
		 m_scale	=	scale;
		 m_rotation	=	rotation;
		 //m_pSrcFile	=	SrcFile;
		 m_scaleRotation=0;}

	~SpriteElements(){
			delete m_rect;
		}

	virtual void Update(float dt){
		D3DXVECTOR2 move = m_velocity * dt;
		m_rotation += (m_scaleRotation * dt);
		if (m_parentPos){
			m_position += move;
			m_position += *m_parentPos;
		}else{
			m_position += move;
		}
	}

	virtual bool IsOver(HWND *win){
		static D3DXVECTOR2 posPlusDblCenter;
		//if(clicked)
		//{
			GetCursorPos(&mouse);
			ScreenToClient(*win, &mouse);
			clickPos = mouse;//hold values for debug

			x = (float)clickPos.x;//gDInput->mouseAX();
			y = (float)clickPos.y;//gDInput->mouseAY();
			//testElem->SetPosition(D3DXVECTOR2( x, y));
			//testElem->SetScale( D3DXVECTOR2(1.25, 1.25) );

			//should get bottom right corner
			posPlusDblCenter = m_position + (m_center+m_center);
			if(    clickPos.x < posPlusDblCenter.x		//click less than bottom right
				&& clickPos.x > m_position.x	//click more than pos
				&& clickPos.y < posPlusDblCenter.y		//
				&& clickPos.y > m_position.y	//
				)
			{
				return true;
				//if((*i)->GetId() == id)
				//	return true;
			}
		//}
			return false;
	}

	virtual void Draw(ID3DXSprite* SpriteInterface, ID3DXFont* FontInterface){
		D3DXMatrixTransformation2D(&mat, &this->m_center, /*(*i)->GetScaleRotation()*/NULL, 
			&this->m_scale, &this->m_center, this->m_rotation, &this->GetPosition());
		SpriteInterface->SetTransform(&mat);
		SpriteInterface->Draw(this->m_pTexture, this->m_rect, 0, 0, D3DCOLOR_XRGB(255, 255, 255));
		FontInterface->DrawText(SpriteInterface, this->m_text,-1,NULL,DT_CENTER|DT_VCENTER,D3DCOLOR_XRGB(0,0,0));
	}

	void SetCenter(D3DXVECTOR2 center)
		{m_center = center;}
	void SetPosition(D3DXVECTOR2 pos)
		{m_position = pos;}
	void SetVelocity(D3DXVECTOR2 velo)
		{m_velocity = velo;}
	void ScaleVelocity(D3DXVECTOR2 scal)
		{m_velocity.x *= scal.x;
		 m_velocity.y *= scal.y;}
	void SetText(LPCSTR text)
		{m_text = text;}
	void SetFontColor(D3DCOLOR color)
		{m_fontColor = color;}
	void SetTexture(IDirect3DTexture9* texture)
		{m_pTexture = texture;}
	void SetScale(D3DXVECTOR2 scale)
		{m_scale = scale;}
	void SetRotation(float rotate)
		{m_rotation = rotate;}
	void SetScaleRotation(float scaleRotate)
		{m_scaleRotation = scaleRotate;}
	//void SetSourceFile(LPCSTR SrcFile)
	//	{m_pSrcFile = SrcFile;}
	void SetRect(float minX, float minY, float maxX, float maxY)
		{
			if(!m_rect)
			{
				m_rect = new RECT();
				m_rect->left = (LONG)minX;
				m_rect->top = (LONG)minY;
				m_rect->right = (LONG)maxX;
				m_rect->bottom = (LONG)maxY;
			}
		}
	void SetVisability(bool visable)
		{m_visable=visable;}

	void SetParentPos(D3DXVECTOR2* parentPos)
		{m_parentPos=parentPos;}

	int GetId()
		{return m_id;}
	ElementType GetElementType()
		{return m_elementType;}
	D3DXVECTOR2 GetCenter()
		{return m_center;}
	D3DXVECTOR2 GetPosition()
		{if(m_parentPos)
			return *m_parentPos + m_position;
		else
			return m_position;}
	D3DXVECTOR2 GetVelocity()
		{return m_velocity;}
	LPCSTR GetText()
		{
			return m_text;
		}
	D3DCOLOR GetFontColor()
		{return m_fontColor;}
	IDirect3DTexture9* GetTexture()
		{return m_pTexture;}
	D3DXVECTOR2 GetScale()
		{return m_scale;}
	float GetRotation()
		{return m_rotation;}
	float GetScaleRotation()
		{return m_scaleRotation;}
	//LPCSTR GetSourceFile()
	//	{return m_pSrcFile;}
	RECT* GetRect()
		{return m_rect;}
	bool IsVisable()
		{return m_visable;}
};
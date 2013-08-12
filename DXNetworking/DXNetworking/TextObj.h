#pragma once

#include "DirectXFramework.h"
#include <string>

using namespace std;

class TextObj
{
protected:
	int			m_id;
	LPCSTR		m_text;
	D3DCOLOR	m_fontColor;
	RECT		m_rct;
public:
	TextObj(){}

	TextObj(int id, LPCSTR text, D3DCOLOR color, RECT rct)
		{m_id = id; m_text = text; 
		m_fontColor = color;	m_rct = rct;}

	TextObj(int id, string text, D3DCOLOR color, RECT rct)
		{m_id = id; m_text = text.c_str(); 
		m_fontColor = color; m_rct = rct;}

	void SetColor(int A, int R, int G, int B)
		{m_fontColor = D3DCOLOR_ARGB(A,R,G,B);}

	void SetRect(int top, int bottom, int left, int right)
		{m_rct.top = top; m_rct.bottom = bottom; 
		m_rct.left = left; m_rct.right = right;}
};
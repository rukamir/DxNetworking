#include "spriteManager.h"
#include <assert.h>
#include <sstream>
#include "DirectInput.h"
#include "TextureManager.h"
//#include "MenuElements.h"
#include <cmath>

//typedef shared_ptr<SpriteElements> SprtElemShPtr;

bool MeasureDistance(D3DXVECTOR2 item1, D3DXVECTOR2 item2, float range)
{
	float distanceSqrd;
	distanceSqrd = (item2.x - item1.x)*(item2.x - item1.x) + (item2.y - item1.y)*(item2.y - item1.y);

	if(range*range > distanceSqrd)
		return true;
	else
		return false;
}

SpriteManager::SpriteManager()
{
	m_pSpriteObj			= 0;
	m_pD3DFont				= 0;
	newTexture				= 0;
}

void SpriteManager::Initialize(LPDIRECT3DDEVICE9 d3ddev)
{
	// Create a D3DX font object
	m_pDevice = d3ddev;
}

bool SpriteManager::CreateSpriteInterface()
{
	//create sprite interface
	//checks to see if one has been made
	if (m_pSpriteObj == 0)
	{
		D3DXCreateSprite(m_pDevice, &m_pSpriteObj);
		return true;
	}
	else
		return false;
}

void SpriteManager::CreateFontInterface()
{
	//create font interface
	D3DXCreateFont( m_pDevice, 30, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
		TEXT("Elephant"), &m_pD3DFont );
}

//void SpriteManager::CreateFontInterface(
//    INT                     Height,
//    LPCSTR                  pFaceName)
//{
//	//create font interface
//	D3DXCreateFont( m_pDevice, Height, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, 
//		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
//		TEXT("Calibri"), &m_pD3DFont );
//
//}


//SprtElemShPtr SpriteManager::CreateSpriteElement(int id, D3DXVECTOR2 center, D3DXVECTOR2 pos, D3DXVECTOR2 velo, 
//		LPCSTR text, D3DCOLOR textColor, D3DXVECTOR2 scale, float rotation, LPCSTR SrcFile)
//{
//	element = 0;
//	newTexture = 0;
//
//	//create a texture for the new sprite object if not NULL
//	D3DXCreateTextureFromFile(m_pDevice, SrcFile, &newTexture);
//
//	//sets SpriteElement data
//	element = SprtElemShPtr(new Button(id));
//	element->SetCenter(center);
//	element->SetPosition(pos);
//	element->SetVelocity(velo);
//	//element->SetText(text);
//	element->SetFontColor(textColor);
//	element->SetTexture(newTexture);
//	element->SetScale(scale);
//	element->SetRotation(rotation);
//	element->SetScaleRotation(0);			//prevent from rotating
//	//element->SetSourceFile(SrcFile);
//
//	m_vectSprElem.push_back(element);
//
//	//clear pointer
//	newTexture = 0;
//
//	//return pointer to the new element
//	//return SprtElemShPtr(element);
//	return element;
//}

//void SpriteManager::CreateMenuElement(int id, D3DXVECTOR2 center, D3DXVECTOR2 pos, D3DXVECTOR2 velo, 
//	LPCSTR text, D3DCOLOR textColor, D3DXVECTOR2 scale, float rotation, LPCSTR SrcFile)
//{
//	element = 0;
//	newTexture = 0;
//
//	//create a texture for the new sprite object if not NULL
//	D3DXCreateTextureFromFile(m_pDevice, SrcFile, &newTexture);
//
//	//sets SpriteElement data
//	element = SprtElemShPtr(new Button(id));
//	element->SetCenter(center);
//	element->SetPosition(pos);
//	element->SetVelocity(velo);
//	element->SetText(text);
//	element->SetFontColor(textColor);
//	element->SetTexture(newTexture);
//	element->SetScale(scale);
//	element->SetRotation(rotation);
//	element->SetScaleRotation(0);			//prevent from rotating
//	element->SetSourceFile(SrcFile);
//
//	m_menu.AddElementToMenu(element);
//
//	//clear pointer
//	newTexture = 0;
//}

//SprtElemShPtr SpriteManager::CreateMenuButton(int id, LPCSTR text)
//{
//	element = 0;
//	newTexture = 0;
//
//	//sets SpriteElement data
//	element = SprtElemShPtr(new Button(id, text));
//	element->SetRect(0,0,184,38);
//	element->SetPosition(D3DXVECTOR2(120.0f, 315.0f));
//	element->SetCenter(D3DXVECTOR2(92.0f, 19.0f));
//	element->SetTexture(gTextureMan->ButtonGrey);
//
//	return element;
//}
//
//SprtElemShPtr SpriteManager::CreateMenuCheckBox(int id, LPCSTR text)
//{
//	element = 0;
//	newTexture = 0;
//
//	//sets SpriteElement data
//	element = SprtElemShPtr(new CheckBox(id, text));
//	element->SetRect(0,0,32,32);
//	element->SetPosition(D3DXVECTOR2(40.0f, 40.0f));
//	element->SetCenter(D3DXVECTOR2(16.0f, 16.0f));
//	element->SetTexture(gTextureMan->CheckBoxNotActive);
//
//	return element;
//}
//
//
//SprtElemShPtr SpriteManager::CreateMissIcon(int id, D3DXVECTOR2 pos)
//{
//	element = 0;
//	newTexture = 0;
//
//	//sets SpriteElement data
//	element = SprtElemShPtr(new MissIcon(id, 0));
//	element->SetRect(0,0,64,64);
//	element->SetPosition(pos);
//	element->SetCenter(D3DXVECTOR2(32.0f, 32.0f));
//	element->SetTexture(gTextureMan->miss);
//	element->SetScale(D3DXVECTOR2(0.5f, 0.5f));
//
//	return element;
//}
//
//SprtElemShPtr SpriteManager::CreateHitIcon(int id, D3DXVECTOR2 pos)
//{
//	element = 0;
//	newTexture = 0;
//
//	//sets SpriteElement data
//	element = SprtElemShPtr(new HitIcon(id, 0));
//	element->SetRect(0,0,64,64);
//	element->SetPosition(pos);
//	element->SetCenter(D3DXVECTOR2(32.0f, 32.0f));
//	element->SetTexture(gTextureMan->hit);
//	element->SetScale(D3DXVECTOR2(0.5f, 0.5f));
//
//
//	return element;
//}
//
//SprtElemShPtr SpriteManager::CreateLogo(int id, D3DXVECTOR2 pos)
//{
//	element = 0;
//	newTexture = 0;
//
//
//	//sets SpriteElement data
//	element = SprtElemShPtr(new Logo(id, 0));
//	element->SetRect(0,0,408,128);
//	element->SetPosition(pos);
//	element->SetCenter(D3DXVECTOR2(64.0f, 204.0f));
//	element->SetTexture(gTextureMan->logo);
//	element->SetScale(D3DXVECTOR2(1.0f, 1.0f));
//
//
//	return element;
//}



SpriteManager::~SpriteManager()
{
	//delete newTexture;
	this->Release();
	element = 0;
	//delete element;

	//delete vector of pointers
	//VectSprtElemShPtrs::iterator i = m_vectSprElem.begin();
	//for (; i != m_vectSprElem.end(); i++)
	//for (auto sprt: m_vectSprElem)
	//{
	//	(sprt) = 0;
	//}
	//m_vectSprElem.clear();
}

LPD3DXSPRITE* SpriteManager::GetSpriteObj()
{
	return &m_pSpriteObj;
}

//MenuInterface* SpriteManager::GetMenuObject()
//{
//	return &m_menu;
//}

SpriteElements* SpriteManager::GetSpriteElement(int id)
{
	//if (m_vectSprElem.size() > 0)
	//{
	//	VectSprtElemShPtrs::iterator i = m_vectSprElem.begin();
	//	for (;i != m_vectSprElem.end(); i++)
		for (auto sprt: m_vSprtElems)
		{
			if((sprt)->GetId() == id)
			{
				return (sprt);
			}
		}
	//}

	assert(false);
	return NULL;
}

SpriteElements* SpriteManager::GetElementByText(LPCSTR text)
{
	//if (m_vectSprElem.size() > 0)
	//{
		//VectSprtElemShPtrs::iterator i = m_vectSprElem.begin();
		//for (;i != m_vectSprElem.end(); i++)
		for (auto sprt: m_vSprtElems)
		{
			if((sprt)->GetText() == text)
			{
				return (sprt);
			}
		}
	//}
	return 0;
}

void SpriteManager::Draw()
{
	//if (m_vectSprElem.size() > 0)
	//{
		//VectSprtElemShPtrs::iterator i = m_vectSprElem.begin();
		//for (;i != m_vectSprElem.end(); i++)
	for (auto sprt: m_vSprtElems)
	{
		//(*i)->Draw(this->m_pSpriteObj, this->m_pD3DFont);
		sprt->Draw(this->m_pSpriteObj, this->m_pD3DFont);

		//D3DXMATRIX mat2;
		//D3DXMatrixTransformation2D(&mat2, &(*i)->GetCenter(), /*(*i)->GetScaleRotation()*/NULL, &(*i)->GetScale(),&(*i)->GetCenter(),(*i)->GetRotation(), 
		//	&(*i)->GetPosition());
		//m_pSpriteObj->SetTransform(&mat2);
		//m_pSpriteObj->Draw((*i)->GetTexture(), (*i)->GetRect(), NULL/*(*i)->GetCenter()*/, NULL/*(*i)->GetPosition()*/, D3DCOLOR_XRGB(255, 255, 255));
		//m_pD3DFont->DrawText(m_pSpriteObj, (*i)->GetText(),-1,NULL,DT_CENTER|DT_VCENTER,D3DCOLOR_XRGB(0,0,0));
	}
	//}
}

void SpriteManager::Update(float dt)
{
	//if (m_vectSprElem.size() > 0)
	//{
		VectSpritElem::iterator i = m_vSprtElems.begin();
		for (;i != m_vSprtElems.end(); i++)
		{
			(*i)->Update(dt);
		}
	//}

	//m_menu.Update(dt);
}

void SpriteManager::Begin()
{
	m_pSpriteObj->Begin(D3DXSPRITE_ALPHABLEND);
}

void SpriteManager::End()
{
	m_pSpriteObj->End();
}

void SpriteManager::Release()
{
	m_pSpriteObj->Release();
	m_pSpriteObj = 0;
	m_pD3DFont->Release();
	m_pD3DFont = 0;
}

void SpriteManager::ClearAllSprites()
{
	//delete vector of pointers
	//VectSprtElemShPtrs::iterator i = m_vectSprElem.begin();
	//for (; i != m_vectSprElem.end(); i++)
	//{
	//	delete *i;
	//}
	m_vSprtElems.clear();
}

void SpriteManager::AddSprite(SpriteElements *addThis)
{
	m_vSprtElems.push_back(addThis);
}

//void SpriteManager::CreateMenu()
//{
//	//menus position
//	//m_menu.SetPosition(D3DXVECTOR2(165.0f, 120.0f));
//
//	////464,470
//	//element = 0;
//	//newTexture = 0;
//	////sets SpriteElement data
//	//element = SprtElemShPtr(new Button(91));
//	////element->SetText("Exit");
//	//element->SetSourceFile("MenuBackdrop.png");
//	//D3DXCreateTextureFromFile(m_pDevice, element->GetSourceFile(), &newTexture);
//	//element->SetTexture(newTexture);
//	//element->SetRect(0,0,464,470);
//	//element->SetPosition(D3DXVECTOR2(0.0f, 0.0f));
//	//element->SetCenter(D3DXVECTOR2(232.0f, 235.0f));
//	//m_menu.AddElementToMenu(element);
//	//m_vectSprElem.push_back(element);
//
//	//exit button
//	element = 0;
//	newTexture = 0;
//	//sets SpriteElement data
//	element = CreateMenuButton(100, "Exit");
//	element->SetPosition(D3DXVECTOR2(120.0f, 315.0f));
//
//	m_menu.AddElementToMenu(element);
//	m_vectSprElem.push_back(element);
//
//	float offSet = 50.0f;
//	for(int i = 0; i<5;i++)
//	{
//		element = 0;
//		newTexture = 0;
//		//sets SpriteElement data
//		element = CreateMenuButton(101+i,"Hello2");
//		element->SetPosition(D3DXVECTOR2(20.0f, offSet));
//		m_menu.AddElementToMenu(element);
//		m_vectSprElem.push_back(element);
//
//		element = 0;
//		newTexture = 0;
//		//sets SpriteElement data
//		//element = SprtElemShPtr(new SpriteElements(120+i));
//		element = CreateMenuButton(107+i,"Hello");
//		element->SetPosition(D3DXVECTOR2(220.0f, offSet));
//		m_menu.AddElementToMenu(element);
//		m_vectSprElem.push_back(element);
//		offSet += 50.0f;
//	}
//
//	//exit button
//	element = 0;
//	//sets SpriteElement data
//	element = CreateMenuCheckBox(90, "Check");
//	element->SetPosition(D3DXVECTOR2(20.0f, 20.0f));
//
//	m_menu.AddElementToMenu(element);
//	m_vectSprElem.push_back(element);
//
//	//element = 0;
//}

//void SpriteManager::AddToMenu(SprtElemShPtr elem)
//{
//	m_menu.AddElementToMenu(elem);
//}

//void SpriteManager::CreateMenuButton(int id, D3DXVECTOR2 center, D3DXVECTOR2 pos, D3DXVECTOR2 velo, 
//		LPCSTR text, D3DCOLOR textColor, D3DXVECTOR2 scale, float rotation, LPCSTR SrcFile)
//{
//	element = 0;
//
//	//sets SpriteElement data
//	element = SprtElemShPtr(new Button(id));
//	element->SetCenter(center);
//	element->SetPosition(pos);
//	element->SetVelocity(velo);
//	element->SetText(text);
//	element->SetFontColor(textColor);
//	element->SetTexture(newTexture);
//	element->SetScale(scale);
//	element->SetRotation(rotation);
//	element->SetScaleRotation(0);			//prevent from rotating
//	//element->SetSourceFile(SrcFile);
//
//	m_menu.AddElementToMenu(element);
//
//	newTexture = 0;
//	element = 0;
//}

//SprtElemShPtr SpriteManager::CreateCreditItem(int id, LPCSTR text)
//{
//	element = 0;
//	newTexture = 0;
//
//	//sets SpriteElement data
//	element = SprtElemShPtr(new CreditItem(id, text));
//	element->SetRect(0,0,184,38);
//	element->SetPosition(D3DXVECTOR2(0.0f, 0.0f));
//	element->SetCenter(D3DXVECTOR2(92.0f, 19.0f));
//	element->SetTexture(0);
//
//	return element;
//}


//bool SpriteManager::CreateFpsDisplay()
//{
//	//create font interface
//	D3DXCreateFont( m_pDevice, 20, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, 
//		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
//		TEXT("Calibri"), &m_pD3DFSPDisplay );
//
//	m_FpsElement = CreateSpriteElement(2, D3DXVECTOR2(50,50), D3DXVECTOR2(12,10), D3DXVECTOR2(0,0), "HELLO", D3DCOLOR_ARGB(255,255,255,255), D3DXVECTOR2(1,1),
//		0.0f, 0);
//
//	return false;
//}

//void SpriteManager::DisplayFSP(float FPS)
//{
//	// Create a colour for the text - in this case blue
//	D3DCOLOR fontColor = D3DCOLOR_ARGB(255,255,255,255);    
//
//	//// Create a rectangle to indicate where on the screen it should be drawn
//	//RECT rct;
//	//rct.left=2;
//	//rct.right=78;
//	//rct.top=10;
//	//rct.bottom=rct.top+20;
// //
//	//// Draw some text 
//	////std::string temp = "text";
//
//
//	float Number = FPS;
//	string Result;          // string which will contain the result
//	ostringstream convert;   // stream used for the conversion
//	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
//	Result = convert.str(); // set 'Result' to the contents of the stream
//	Result += " fps";
//
//	static LPCSTR textS;
//	textS = Result.c_str();
//
//	m_FpsElement->SetText(textS);
//
//	//m_pD3DFSPDisplay->DrawText(NULL, Result.c_str(), -1, &rct, 0, fontColor );
//
//	//m_pD3DFSPDisplay->DrawText(m_pSpriteObj, m_FpsElement->GetText()/*Result.c_str()*/, -1, 0, 0, fontColor );
//}

//bool SpriteManager::OnClick3(int id)
//{
//	static float x=0;
//	static float y=0;
//	static POINT clickPos;
//	static string clickedText;
//	static SpriteElements* testElem = 0;// = this->GetSpriteElement(2);
//	//static D3DXVECTOR2 clickPoint;
//
//	//Get position of mouse on the screen
//	static POINT mouse;
//
//
//
//	static D3DXVECTOR2 posPlusDblCenter;
//	static bool debounce = false;
//
//	//on left click
//	if(gDInput->mouseButtonDown(0))
//	{
////if(!debounce)
////{
////	debounce = true;
//		GetCursorPos(&mouse);
//		ScreenToClient(*m_hWnd, &mouse);
//		clickPos = mouse;//hold values for debug
//
//		x = (float)clickPos.x;//gDInput->mouseAX();
//		y = (float)clickPos.y;//gDInput->mouseAY();
//		//testElem->SetPosition(D3DXVECTOR2( x, y));
//		//testElem->SetScale( D3DXVECTOR2(1.25, 1.25) );
//
//		//check for sprites within 25 pxl from mouse click
//		if (m_vSprtElems.size() > 0)
//		{
//			VectSpritElem::iterator i = m_vSprtElems.begin();
//			for (;i != m_vSprtElems.end(); i++)
//			{
//				//should get bottom right corner
//				posPlusDblCenter = (*i)->GetPosition() + ((*i)->GetCenter()+(*i)->GetCenter());
//				if(    clickPos.x < posPlusDblCenter.x		//click less than bottom right
//					&& clickPos.x > (*i)->GetPosition().x	//click more than pos
//					&& clickPos.y < posPlusDblCenter.y		//
//					&& clickPos.y > (*i)->GetPosition().y	//
//					)
//				{
//					if((*i)->GetId() == id)
//						return true;
//				}
//			}
//		}
//
////}
//	}
//	else
//	{
//		debounce = false;
//		return false;
//	}
//	return false;
//}


//bool SpriteManager::OnOver(int id)
//{
//	static float x=0;
//	static float y=0;
//	static POINT something;
//	static string clickedText;
//	static SpriteElements* testElem = 0;
//	static POINT mouse;
//
//	static D3DXVECTOR2 posPlusDblCenter;
//
//	//on left click
//	//if(gDInput->mouseButtonDown(0))
//	//{
//		GetCursorPos(&mouse);
//		ScreenToClient(*m_hWnd, &mouse);
//		something = mouse;//hold values for debug
//
//		x = (float)something.x;//gDInput->mouseAX();
//		y = (float)something.y;//gDInput->mouseAY();
//		//testElem->SetPosition(D3DXVECTOR2( x, y));
//		//testElem->SetScale( D3DXVECTOR2(1.25, 1.25) );
//
//		//check for sprites within 25 pxl from mouse click
//		if (m_vectSprElem.size() > 0)
//		{
//			VectSprtElemShPtrs::iterator i = m_vectSprElem.begin();
//			for (;i != m_vectSprElem.end(); i++)
//			{
//				//should get bottom right corner
//				posPlusDblCenter = (*i)->GetPosition() + ((*i)->GetCenter()+(*i)->GetCenter());
//				if( //posPlusDblCenter > D3DXVECTOR2(something.x, something.y)
//					//&& (*i)->GetPosition() < D3DXVECTOR2(something.x, something.y)
//					//MeasureDistance(D3DXVECTOR2(something.x, something.y), (*i)->GetPosition(), 40)
//					something.x < posPlusDblCenter.x && something.x > (*i)->GetPosition().x
//					&& something.y < posPlusDblCenter.y && something.y > (*i)->GetPosition().y
//					)
//				{
//					if((*i)->GetId() == id)
//						return true;
//				}
//			}
//		}
//		return false;
//
//	//}
//	//else
//	//{
//	//	return false;
//	//}
//}




//jj created this 
/*
//Create Text Element
 m_ElementCreator = 0;
 m_ElementCreator = std::shared_ptr<SpriteElement>(new Text());
 m_ElementCreator->SetScale(D3DXVECTOR2(DXI->GetScreenWidth()*0.001,DXI->GetScreenHeight()*0.001),0.0005);
 m_ElementCreator->SetPosition(D3DXVECTOR3(DXI->GetScreenWidth()/DXI->GetScreenWidth(),DXI->GetScreenHeight()/DXI->GetScreenHeight(),0));
 m_ElementCreator->SetCenter(D3DXVECTOR2(m_ElementCreator->GetPos().x+80,m_ElementCreator->GetPos().y + 5));
 m_ElementCreator->SetVelocity(D3DXVECTOR3(0,0,0));
 m_ElementCreator->SetRotation(0.0f);
 m_ElementCreator->SetText("Play Game");

 vSprites.push_back(m_ElementCreator);
 */
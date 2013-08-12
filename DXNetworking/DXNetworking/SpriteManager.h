#pragma once

#include "SpriteElements.h"
//#include "MenuInterface.h"
#include <memory>
#include <vector>

using namespace std;
typedef shared_ptr<SpriteElements> SprtElemShPtr;
typedef vector<SpriteElements*>		VectSpritElem;

class SpriteManager
{
protected:
	typedef vector<SprtElemShPtr> VectSprtElemShPtrs;
	LPDIRECT3DDEVICE9		m_pDevice;
	ID3DXFont*				m_pD3DFont;
	LPD3DXSPRITE			m_pSpriteObj;
	VectSprtElemShPtrs		m_vectSprElem;
	VectSpritElem			m_vSprtElems;

	//MenuInterface			m_menu;
	SpriteElements			*newElem;
	SprtElemShPtr			element;
	IDirect3DTexture9*		newTexture;

	//ID3DXFont*				m_pD3DFSPDisplay;
	HWND*					m_hWnd;

public:
	SpriteManager();
	~SpriteManager();
	void Initialize(LPDIRECT3DDEVICE9 d3ddev);
	void SetWindow(HWND* hwnd)
		{m_hWnd = hwnd;}

	bool CreateSpriteInterface();
	void CreateFontInterface();
    //void CreateFontInterface(
    //    INT                     Height,
    //    LPCSTR                  pFaceName);

	//SprtElemShPtr CreateSpriteElement(int id, D3DXVECTOR2 center, D3DXVECTOR2 pos, D3DXVECTOR2 velo, 
	//	LPCSTR text, D3DCOLOR textColor, D3DXVECTOR2 scale, float rotation, LPCSTR SrcFile);

	//void CreateMenuElement(int id, D3DXVECTOR2 center, D3DXVECTOR2 pos, D3DXVECTOR2 velo, 
	//	LPCSTR text, D3DCOLOR textColor, D3DXVECTOR2 scale, float rotation, LPCSTR SrcFile);

	void AddSprite(SpriteElements *addThis);
	//SprtElemShPtr CreateMenu(int id, LPCSTR text);
	//SprtElemShPtr CreateMenuButton(int id, LPCSTR text);
	//SprtElemShPtr CreateMenuCheckBox(int id, LPCSTR text);
	//SprtElemShPtr CreateMissIcon(int id, D3DXVECTOR2 pos);
	//SprtElemShPtr CreateHitIcon(int id, D3DXVECTOR2 pos);

	SprtElemShPtr CreateLogo(int id, D3DXVECTOR2 pos);


	SprtElemShPtr CreateCreditItem(int id, LPCSTR text);

	LPD3DXSPRITE* GetSpriteObj();
	//MenuInterface* GetMenuObject();
	SprtElemShPtr GetSpriteElement(int id);


	SprtElemShPtr GetElementByText(LPCSTR text);


	void Draw();//float dt);
	void Update(float dt);

	void Begin();
	void End();
	void Release();

	void ClearAllSprites();

	void CreateMenu();
	void AddToMenu(SprtElemShPtr elem);
	void CreateMenuButton(int id, D3DXVECTOR2 center, D3DXVECTOR2 pos, D3DXVECTOR2 velo, 
		LPCSTR text, D3DCOLOR textColor, D3DXVECTOR2 scale, float rotation, LPCSTR SrcFile);

	bool OnClick3(int id);
	bool OnOver(int id);

	SprtElemShPtr m_FpsElement;
	//bool CreateFpsDisplay();
	//void DisplayFSP(float FPS);
};
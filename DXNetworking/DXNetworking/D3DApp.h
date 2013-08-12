#pragma once
//#include "NetClient.h"
#include "DirectX.h"
#include "SpriteManager.h"
#include "FSM.h"
#include "Entity.h"

//class NetClient;

class D3DApp :
	public DirectX
{
protected:
	SpriteManager* m_pSrtMngr;
	ID3DXFont*	m_pTextFPS;
	FSM<D3DApp>* pFSM;
	D3DXVECTOR2 m_MousePos;
	//NetClient*		m_netClient;
	

public:
	void Update(float dt);

	D3DApp(void);
	~D3DApp(void);

	void InitD3D(HWND hWnd, HINSTANCE& hInst, bool bWindowed);
	void CreateSpriteManager();
	void ShutDownSpriteManager();

	D3DXVECTOR2 SetMousePos(HWND hwnd);
	void ChangeState(int);
	void ChangePreviousState();

	D3DXVECTOR2 GetMousePos()
		{return m_MousePos;}

	SpriteManager* GetSpriteManager()
		{return m_pSrtMngr;}
	LPDIRECT3DDEVICE9* GetDevice()
		{return &gD3DDev;}
	HWND* GetWindow()
		{return &m_hWnd;}
	void VertexDeclarations();
	void CreateFPSDisplay();

private:
	ID3DXFont*	statFont;
	float mFPS;
	float mMilliSecPerFrame;

	void calculateFPS(float dt);
	void DisplayStats();
	//void SetUpFSM();
};
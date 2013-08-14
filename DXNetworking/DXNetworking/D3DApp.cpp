//#include "NetClient.h"
#include "D3DApp.h"
#include "StatesD3DApp.h"
#include "Vertex.h"
#include <tchar.h>
//#include "ThreadController.h"

D3DApp::D3DApp(void)
{
	//create FSM
	//m_pSrtMngr = new SpriteManager();
	m_pTextFPS = 0;
	m_pSrtMngr = 0;
	pFSM = new FSM<D3DApp>(this);
	pFSM->m_pCurrentState = new IntState();//

	//m_netClient = new NetClient();
	//m_netClient->Initialize();
	//m_netClient->SetServIP("192.168.1.3");
	//m_netClient->Connect();
	//ThrdCon->CreateNewThread(NetClient::listen_loop, ((void*)m_netClient), false);

	//D3DXFONT_DESC fpsDesc;
	//fpsDesc.Height          = 20;
 //   fpsDesc.Width           = 5;
 //   fpsDesc.Weight          = FW_BOLD;
 //   fpsDesc.MipLevels       = 0;
 //   fpsDesc.Italic          = false;
 //   fpsDesc.CharSet         = DEFAULT_CHARSET;
 //   fpsDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
 //   fpsDesc.Quality         = DEFAULT_QUALITY;
 //   fpsDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
	////fpsDesc.FaceName		=	L"Arial";
 //   strcpy_s(fpsDesc.FaceName, _T("Comic Sans MS"));

	//D3DXCreateFontIndirect(this->m_pD3Device, &fpsDesc, &statFont);
}

D3DApp::~D3DApp(void)
{
	//m_netClient->Shutdown();
	//delete m_netClient;

	statFont->Release();
	delete pFSM;
	//m_pSrtMngr->Release();
	delete m_pSrtMngr;
	//delete m_di;
	//gD3DDev->Release();
	//m_pD3DObject->Release();
	//delete m_hWnd;
}

void D3DApp::CreateFPSDisplay()
{
	D3DXFONT_DESC fpsDesc;
	fpsDesc.Height          = 20;
    fpsDesc.Width           = 5;
    fpsDesc.Weight          = FW_BOLD;
    fpsDesc.MipLevels       = 0;
    fpsDesc.Italic          = false;
    fpsDesc.CharSet         = DEFAULT_CHARSET;
    fpsDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    fpsDesc.Quality         = DEFAULT_QUALITY;
    fpsDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
	//fpsDesc.FaceName		=	L"Arial";
    strcpy_s(fpsDesc.FaceName, _T("Comic Sans MS"));

	D3DXCreateFontIndirect(this->m_pD3Device, &fpsDesc, &statFont);
}


void D3DApp::Update(float dt)
{
	//update state machine
	pFSM->Update(dt);
	pFSM->Render();
	//calculateFPS(dt);
	//DisplayStats();
}

void D3DApp::InitD3D(HWND hWnd, HINSTANCE& hInst, bool bWindowed)
{
	this->InitializeDirect3D(hWnd, hInst, bWindowed);
	pFSM->CurrentState()->InitializeState(this);
}

void D3DApp::CreateSpriteManager()
{
	if(!m_pSrtMngr)
	{
		m_pSrtMngr = new SpriteManager();
		m_pSrtMngr->Initialize(gD3DDev);
	}
}

void D3DApp::ShutDownSpriteManager()
{
	delete m_pSrtMngr;
	m_pSrtMngr = 0;
}

D3DXVECTOR2 D3DApp::SetMousePos(HWND hwnd)
{
	// Get position of mouse on the screen
	static int number = 0;
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(hwnd, &mouse);
 
	m_MousePos.x = (float)mouse.x;
	m_MousePos.y = (float)mouse.y;

	//if(m_MousePos.x > 200)
	//{
	//	number++;
	//}

	return m_MousePos;
}

void D3DApp::ChangeState(int num)
{
	//Week1* Wk1 = new Week1();

	switch(num)
	{
	case 1:
		this->pFSM->ChangeState( new ServerLobby() );
		break;
	case 2:
		this->pFSM->ChangeState( new GameLobby() );
		break;
	case 3:
		//this->pFSM->ChangeState( new Demo3D() );
		break;
	case 4:
		//this->pFSM->ChangeState( new Credits() );
		break;
	default:
		return;
	}

	//Wk1 = 0;
}

void D3DApp::ChangePreviousState()
{
	pFSM->RevertToPreviousState();
}

void D3DApp::VertexDeclarations()
{
	D3DVERTEXELEMENT9 VertexPNTElements[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,
			D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,
			D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,
			D3DDECLUSAGE_TEXCOORD, 0},
		{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, 
			D3DDECLUSAGE_COLOR,   0},

		D3DDECL_END()
	};
	gD3DDev->CreateVertexDeclaration(VertexPNTElements, &VertexPNT::Decl);
};

void D3DApp::calculateFPS(float dt)
{
      // Make static so that their values persist across
      // function calls.
      static float numFrames   = 0.0f;
      static float timeElapsed = 0.0f;

      // Increment the frame count.
      numFrames += 1.0f;

      // Accumulate how much time has passed.
      timeElapsed += dt;

      if( timeElapsed >= 1.0f )
      {
            // Frames Per Second = numFrames / timeElapsed,
            // but timeElapsed approx. equals 1.0, so
            // frames per second = numFrames.

            mFPS = numFrames;

            // Average time, in milliseconds, it took to render a
            // single frame.
            mMilliSecPerFrame = 1000.0f / mFPS;

            // Reset time counter and frame count to prepare
            // for computing the average stats over the next second.
            timeElapsed = 0.0f;
            numFrames   = 0.0f;
      }
}

void D3DApp::DisplayStats()
{

	if (true)
	{
		// Make static so memory is not allocated every frame.
		static char buffer[256];


		sprintf_s(buffer, "FPS %.2f" , mFPS);
 
		RECT R = {50, 50, 0, 0};
		if (statFont)
			statFont->DrawText(0, buffer, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(255,255,255));
	}
}

//void D3DApp::SetUpFSM()
//{
//	pFSM->CurrentState()->InitializeState(this);
//}
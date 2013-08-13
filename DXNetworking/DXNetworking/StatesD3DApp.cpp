#include "StatesD3DApp.h"
#include "D3DApp.h"
#include "DirectInput.h"
//#include "Camera.h"
#include "WorldManager.h"
#include "Tiger.h"
#include "LinkedObjs.h"
//#include "NetworkController.h"

IntState::IntState()
{
}

IntState::~IntState()
{
}

void IntState::InitializeState(D3DApp* app)
{
	//WMI->m_NetControl->JoinServer();
}
void IntState::UpdateScene(D3DApp* app, float dt)
{

	app->ChangeState(1);
	//tiger->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//tiger->RotateY(45.0f);

	//	tiger = (Tiger*)WMI->CreateTiger();
	//tiger->SetPosition(D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	//tiger->RotateY(90.0f);


	//	tiger = (Tiger*)WMI->CreateTiger();
	//tiger->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 10.0f));
	//tiger->RotateY(20.0f);


	//	tiger = (Tiger*)WMI->CreateTiger();
	//tiger->SetPosition(D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	//tiger->RotateZ(45.0f);

}
void IntState::RenderScene(D3DApp* app)
{
}

void IntState::OnResetDevice(D3DApp* app)
{
}

void IntState::OnLostDevice(D3DApp* app)
{
}

void IntState::LeaveState(D3DApp* app)
{
}

//********************************************************
// Server Lobby State
//********************************************************
ServerLobby::ServerLobby()
{
}

ServerLobby::~ServerLobby()
{
}

void ServerLobby::InitializeState(D3DApp* app)
{
	WMI->myMenu	=	new MenuObj(9999);
	WMI->myMenu->AddButton("Server List", D3DXVECTOR2(5.0f, 5.0f));
	WMI->myMenu->AddButton("Game 1", D3DXVECTOR2(5.0f, 35.0f));
	WMI->myMenu->AddPlayerCount("Game1Count", D3DXVECTOR2(250.0f, 35.0f));
	WMI->myMenu->AddButton("Game 2", D3DXVECTOR2(5.0f, 65.0f));
	WMI->myMenu->AddPlayerCount("Game2Count", D3DXVECTOR2(250.0f, 65.0f));

	WMI->myMenu->SetPosition(D3DXVECTOR2(100.0f, 5.0f));
	WMI->m_SpriteMan->SetWindow( app->GetWindow() );
	WMI->m_SpriteMan->AddSprite(WMI->myMenu);
}

void ServerLobby::UpdateScene(D3DApp* app, float dt)
{
	//CAM->Update();
	WMI->Update(dt);

	if (gDInput->keyDown(DIK_2))
	{
		app->ChangeState(2);
	}

	// if left click
	if(gDInput->mouseButtonDown(0)){
		if (WMI->myMenu->GetElemByTitle("Game 1")->IsOver(ghWnd)){
			((PlayerDisplayCount*)WMI->myMenu->GetElemByTitle("Game1Count"))->SetPlayerCount(1);
		}
		if (WMI->myMenu->GetElemByTitle("Game 2")->IsOver(ghWnd)){
			((PlayerDisplayCount*)WMI->myMenu->GetElemByTitle("Game2Count"))->SetPlayerCount(1);
		}
	}
}
void ServerLobby::RenderScene(D3DApp* app)
{
	WMI->Render();
	//WMI->m_SpriteMan->Begin();
	//WMI->m_SpriteMan->Draw();
	//WMI->m_SpriteMan->End();
}

void ServerLobby::OnResetDevice(D3DApp* app)
{
}

void ServerLobby::OnLostDevice(D3DApp* app)
{
}

void ServerLobby::LeaveState(D3DApp* app)
{
	WMI->ResetWorldManager();
}

//***********************************************
//                 Demo2
//***********************************************

Demo2::Demo2()
{
}

Demo2::~Demo2()
{
}

void Demo2::InitializeState(D3DApp* app)
{
	Entity* ent = WMI->CreateBall();
	ent->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 0.0f));

	Tiger* tiger;
	tiger = (Tiger*)WMI->CreateTiger();
	tiger->SetPosition( D3DXVECTOR3(0.0f, -20.0f, 0.0f) );

}
void Demo2::UpdateScene(D3DApp* app, float dt)
{
	//static Sphere* sphere = GraphicsM->GetSphere(9999);
	//CAM->Update();
	WMI->Update(dt);

}
void Demo2::RenderScene(D3DApp* app)
{
	WMI->Render();
}

void Demo2::OnResetDevice(D3DApp* app)
{
}

void Demo2::OnLostDevice(D3DApp* app)
{
}

void Demo2::LeaveState(D3DApp* app)
{
	WMI->ResetWorldManager();
}


////********************************************************
////3DObject Demo State
////********************************************************
//Demo3D::Demo3D()
//{
//}
//
//Demo3D::~Demo3D()
//{
//}
//
//void Demo3D::InitializeState(D3DApp* app)
//{
//}
//void Demo3D::UpdateScene(D3DApp* app, float dt)
//{
//}
//void Demo3D::RenderScene(D3DApp* app)
//{
//}
//
//void Demo3D::OnResetDevice(D3DApp* app)
//{
//}
//
//void Demo3D::OnLostDevice(D3DApp* app)
//{
//}
//
//void Demo3D::LeaveState(D3DApp* app)
//{
//}
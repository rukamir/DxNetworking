#include "StatesD3DApp.h"
#include "D3DApp.h"
#include "DirectInput.h"
#include "Tiger.h"
#include "WorldManager.h"

IntState::IntState()
{
}

IntState::~IntState()
{
}

void IntState::InitializeState(D3DApp* app)
{
}
void IntState::UpdateScene(D3DApp* app, float dt)
{

	app->ChangeState(1);
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
	WMI->CreateServerMenu();
	WMI->m_SpriteMan->SetWindow( app->GetWindow() );
	WMI->m_SpriteMan->AddSprite(WMI->myMenu);
}

void ServerLobby::UpdateScene(D3DApp* app, float dt)
{
	WMI->Update(dt);

	if (gDInput->keyDown(DIK_2)){
		app->ChangeState(2);
	}

	// if left click
	if(gDInput->mouseButtonDown(0)){
		if(WMI->IsOverMenuButton("Game 1")){
			((PlayerDisplayCount*)WMI->GetMenuElemByTitle("Game1Count"))->SetPlayerCount(1);
			WMI->JoinGame(1);
		}
		if(WMI->IsOverMenuButton("Game 2")){
			((PlayerDisplayCount*)WMI->GetMenuElemByTitle("Game2Count"))->SetPlayerCount(1);
			WMI->JoinGame(2);
		}
		if(WMI->IsOverMenuButton("Game 3")){
			((PlayerDisplayCount*)WMI->GetMenuElemByTitle("Game3Count"))->SetPlayerCount(1);
			WMI->JoinGame(3);
		}
		if(WMI->IsOverMenuButton("Game 4")){
			((PlayerDisplayCount*)WMI->GetMenuElemByTitle("Game4Count"))->SetPlayerCount(1);
			WMI->JoinGame(4);
		}
	}
}
void ServerLobby::RenderScene(D3DApp* app)
{
	WMI->Render();
}

void ServerLobby::OnResetDevice(D3DApp* app)
{
}

void ServerLobby::OnLostDevice(D3DApp* app)
{
}

void ServerLobby::LeaveState(D3DApp* app)
{
	//WMI->DeleteServerMenu();
	WMI->m_SpriteMan->ClearAllSprites();
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
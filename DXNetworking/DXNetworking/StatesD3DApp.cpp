#include "StatesD3DApp.h"
#include "D3DApp.h"
#include "DirectInput.h"
//#include "Camera.h"
#include "WorldManager.h"
#include "Tiger.h"
#include "LinkedObjs.h"

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
//3DObject Demo State
//********************************************************
Demo1::Demo1()
{
}

Demo1::~Demo1()
{
}

void Demo1::InitializeState(D3DApp* app)
{
	WMI->myMenu	=	new MenuObj(9999);
	WMI->myMenu->AddButton("Title", D3DXVECTOR2(5.0f, 5.0f));
	WMI->myMenu->SetPosition(D3DXVECTOR2(5.0f, 5.0f));
	WMI->m_SpriteMan->SetWindow( app->GetWindow() );
	WMI->m_SpriteMan->AddSprite(WMI->myMenu);
}

void Demo1::UpdateScene(D3DApp* app, float dt)
{
	//CAM->Update();
	WMI->Update(dt);

	if (gDInput->keyDown(DIK_2))
	{
		app->ChangeState(2);
	}
}
void Demo1::RenderScene(D3DApp* app)
{
	WMI->Render();
	//WMI->m_SpriteMan->Begin();
	//WMI->m_SpriteMan->Draw();
	//WMI->m_SpriteMan->End();
}

void Demo1::OnResetDevice(D3DApp* app)
{
}

void Demo1::OnLostDevice(D3DApp* app)
{
}

void Demo1::LeaveState(D3DApp* app)
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
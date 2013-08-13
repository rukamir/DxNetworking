#include "NetClient.h"
#include "ThreadController.h"
#include "WorldManager.h"
#include "MeshManager.h"
#include "d3dUtil.h"
#include "GraphicsManager.h"
#include "Camera.h"
#include "FXManager.h"
#include "DirectX.h"
#include "Tiger.h"
#include "TextureManager.h"
#include "Vertex.h"
#include "Water.h"
#include "NetworkController.h"

WorldManager::WorldManager()
{
	m_iNVID = 0;

	//// Create Network Controller
	//m_NetControl	=	new NetworkController();

	//// Send different packets
	//m_NetControl->JoinServer();
	//m_NetControl->JoinGame(8);
	//m_NetControl->SendPlayerMove((char)8);
	////m_NetControl->SendPlayerFire(8);
	//m_NetControl->QuiteGame();
	//m_NetControl->QuiteServer();
	//m_NetControl->TestServerPackets();

	// Create Sprite Manager
	m_SpriteMan = NULL;

	m_SpriteMan	=	new SpriteManager();
	m_SpriteMan->Initialize( gD3DDev);
	m_SpriteMan->CreateSpriteInterface();
	m_SpriteMan->CreateFontInterface();
}

WorldManager::~WorldManager()
{
	// Delete Entities
	std::vector<Entity*>::iterator i = m_vEntities.begin();
	for(; i != m_vEntities.end(); i++)
	{
		delete (*i);
	}
	m_vEntities.clear();

	delete m_NetControl;
	//m_netClient->Shutdown();
	//delete m_netClient;
}

Entity* WorldManager::GetEntityById(int id)
{
	std::vector<Entity*>::iterator i = m_vEntities.begin();
	for(; i != m_vEntities.end(); i++)
	{
		if((*i)->GetID() == (unsigned int)id)
			return (*i);
	}
	return 0;
}

Entity* WorldManager::CreateTiger(){
	ent = new Tiger( GetNVID() );
	ent->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_vEntities.push_back(ent);
	return ent;
}

Entity* WorldManager::CreateBall(){
	ent = new Ball( GetNVID() );
	ent->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_vEntities.push_back(ent);
	return ent;
}

bool WorldManager::IsOverMenuButton(LPCSTR buttonTitle){
	return myMenu->GetElemByTitle(buttonTitle)->IsOver(ghWnd);
}

SpriteElements* WorldManager::GetMenuElemByTitle(LPCSTR buttonTitle){
	return myMenu->GetElemByTitle(buttonTitle);
}

void WorldManager::CreateServerMenu(){
	myMenu	=	new MenuObj(9999);
	myMenu->SetText("ServerMenu");
	myMenu->AddButton("Server List", D3DXVECTOR2(5.0f, 5.0f));
	myMenu->AddButton("Game 1", D3DXVECTOR2(5.0f, 35.0f));
	myMenu->AddPlayerCount("Game1Count", D3DXVECTOR2(250.0f, 35.0f));
	myMenu->AddButton("Game 2", D3DXVECTOR2(5.0f, 65.0f));
	myMenu->AddPlayerCount("Game2Count", D3DXVECTOR2(250.0f, 65.0f));
	myMenu->AddButton("Game 3", D3DXVECTOR2(5.0f, 95.0f));
	myMenu->AddPlayerCount("Game3Count", D3DXVECTOR2(250.0f, 95.0f));
	myMenu->AddButton("Game 4", D3DXVECTOR2(5.0f, 125.0f));
	myMenu->AddPlayerCount("Game4Count", D3DXVECTOR2(250.0f, 125.0f));

	myMenu->SetPosition(D3DXVECTOR2(100.0f, 5.0f));
}


void WorldManager::DeleteServerMenu(){
	delete myMenu;
}

void WorldManager::JoinGame(short gameId){
	m_NetControl->JoinGame(gameId);
}

void WorldManager::QuitGame(){
	m_NetControl->QuiteGame();
}

int WorldManager::GetNVID()
{
	m_iNVID++;
	return m_iNVID-1;
}

float GetSqDistance(D3DXVECTOR3 p1, D3DXVECTOR3 p2)
{
	float distSq = /*abs*/( 
		(p2.x - p1.x) * (p2.x - p1.x) + 
		(p2.y - p1.y) * (p2.y - p1.y) + 
		(p2.z - p1.z) * (p2.z - p1.z) );
	return distSq;
}

void WorldManager::Update(float dt)
{
	CAM->Update();
	m_SpriteMan->Update(dt);

	for(const auto &ents : m_vEntities){
		ents->Update(dt);
	}

	static float counter = 0.0f;
	//static Packet* packet = NULL;

	//// every two seconds
	//if (counter > 2.0f){
	//	packet = (Packet*)m_netClient->GetReceiveBuff();
	//	if (packet){
	//		GetEntityById(0)->SetPosition(D3DXVECTOR3(packet->x, 0.0f, packet->y));
	//	}
	//	counter = 0.0f;
	//} else{
	//	counter += dt;
	//}

	//linkedThing->Update(dt);
}

void WorldManager::Render()
{	
//	  //render-to-texture
//	  //set new render target
//	  gD3DDev->SetRenderTarget(0,gTextureMan->pRenderSurface);
//	  //clear texture
//	  gD3DDev->Clear(0,
//							   NULL,
//							   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
//							   D3DCOLOR_XRGB(200,200,200),
//							   1.0f,
//							   0);
//	  gD3DDev->BeginScene();
//
//	  //gD3DDev->SetTexture(0,gTextureMan->pRenderTexture);
//	  D3DXMATRIX matRotationY;
//	  D3DXMatrixRotationY(&matRotationY,D3DXToRadian(25.0f));
//	  D3DXMATRIX matTranslation;
//	  D3DXMatrixTranslation(&matTranslation,0.0f,0.0f,5.0f);
//	  gD3DDev->SetTransform(D3DTS_WORLD,
//									  &(matRotationY * matTranslation));
//	  //set projection matrix
//	  gD3DDev->SetTransform(D3DTS_PROJECTION,&CAM->GetProjectionMatrix());
//
//	  gD3DDev->SetStreamSource(0, myObj->m_VertBuff,0,sizeof(VertexPNT::Decl));
//	  gD3DDev->DrawPrimitive(D3DPT_TRIANGLELIST,0,4);
//
//myObj->m_Shader->effect->SetTexture(((BasicShader*)myObj->m_Shader)->tex0, gTextureMan->pRenderTexture);
//myObj->m_Shader->effect->CommitChanges();
//
//
//	 gD3DDev->EndScene();


	// Clear the backbuffer and depth buffer.
	HR(gD3DDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0));

	HR(gD3DDev->BeginScene());

	// Sprite Manager
	m_SpriteMan->Begin();
	m_SpriteMan->Draw();
	m_SpriteMan->End();

	//FXM->SetTechnique();
	GraphicsM->Render();

	HR(gD3DDev->EndScene());

	// Present the backbuffer.
	HR(gD3DDev->Present(0, 0, 0, 0));
}

void WorldManager::ResetWorldManager()
{
	std::vector<Entity*>::iterator i = m_vEntities.begin();
	for(; i != m_vEntities.end(); i++)
	{
		delete (*i);
	}
	m_vEntities.clear();
	MeshM->ClearMeshManager();
	m_iNVID = 0;
}

WorldManager* WorldManager::Instance()
{
	static WorldManager instance; 
	return &instance;
}
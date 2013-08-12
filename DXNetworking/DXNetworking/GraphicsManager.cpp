#include "GraphicsManager.h"
#include "MeshManager.h"
#include "DirectX.h"
#include "FXManager.h"
#include "Camera.h"
#include "TextureManager.h"

GraphicsManager::GraphicsManager()
{
	gTextureMan->LoadAllTextures(gD3DDev);
	myObj = new Obj3D(gD3DDev);
	myObj->SetPosition(0.0f, 0.0f, 0.0f);
}

GraphicsManager::~GraphicsManager()
{
	delete myObj;
	for(const auto &Sphere : m_vSpheres)
	{
		delete Sphere;
	}
	m_vSpheres.clear();

	for(const auto &mesh : m_vMeshList)
	{
		delete mesh;
	}
	m_vMeshList.clear();
}

void GraphicsManager::Render()
{
	//for(const auto &Sphere : m_vSpheres)
	//{
	//	Sphere->Render(NULL, NULL, 
	//		CAM->GetViewMatrix(), CAM->GetProjectionMatrix());
	//}

	for(const auto &MeshBase : m_vMeshList){
		MeshBase->Render();
	}

	myObj->Render(NULL, NULL, CAM->GetViewMatrix(), CAM->GetProjectionMatrix());
}

MeshBase* GraphicsManager::CreateSphere(int id)
{
	Sphere* sphere = new Sphere(id);
	m_vMeshList.push_back(sphere);
	return sphere;
}

MeshBase* GraphicsManager::CreateTiger(int id)
{
	TigerMesh* mesh = new TigerMesh(id);
	m_vMeshList.push_back(mesh);
	return mesh;
}


Sphere* GraphicsManager::GetSphere(int id)
{
	//for(const auto &Sphere : m_vSpheres)
	//{
	//	if(Sphere->GetID() == id)
	//		return Sphere;
	//}
	return NULL;
}
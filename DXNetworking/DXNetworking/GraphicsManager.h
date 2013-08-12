#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <vector>
#include "Shapes.h"
#include "MeshBase.h"
#include "3DObj.h"

#define GraphicsM GraphicsManager::Instance()

class GraphicsManager
{
private:
	std::vector<Sphere*>		m_vSpheres;
	std::vector<MeshBase*>		m_vMeshList;
	Obj3D*						myObj;

	// Vertex and Index buffers
	IDirect3DVertexBuffer9* mVB;
	IDirect3DIndexBuffer9*  mIB;


	GraphicsManager();
public:
	void Render();


	MeshBase*				CreateSphere(int id);
	Sphere*				GetSphere(int id);

	MeshBase* CreateTiger(int id);


	~GraphicsManager();
	static GraphicsManager* Instance()
		{	static GraphicsManager instance; return &instance; }
};

#endif
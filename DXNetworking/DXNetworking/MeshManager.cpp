#include "MeshManager.h"
#include "Vertex.h"
#include "d3dUtil.h"
#include "DirectX.h"
#include "Tiger.h"

MeshManager::MeshManager()
{
	//Create main sphere to be used to draw spheres place by user
	//Create a temporary sphere first
	ID3DXMesh* tempSphere;
	HR(D3DXCreateSphere(gD3DDev, 1.0f, 10, 16, &tempSphere, 0));
	//Clone temp sphere to the main sphere and give its vertices a color value
	HR(tempSphere->CloneMeshFVF( D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_DIFFUSE, gD3DDev, &m_mSphere ));
	//Release the temp sphere
	ReleaseCOM(tempSphere);
}

MeshManager::~MeshManager()
{
	//ReleaseCOM(m_mSphere);
}
ID3DXMesh* MeshManager::GetSphere()
{
	return m_mSphere;
}

void MeshManager::SetCurrentColor(D3DCOLOR color)
{

		//VertexPNT* v = 0;
		//HR(m_mSphere->LockVertexBuffer(0, (void**)&v));

		////int a = m_mSphere->GetNumVertices();
		////a = 5;

		////for ( unsigned int i = 0; i <= 152; i = i + 3 ) //give spiral effect on the ball
		//for ( unsigned int i = 0; i < m_mSphere->GetNumVertices(); ++i )
		//{
		//	v[i].color = color;
		//	//if(i != 0)
		//	//{
		//	//	int colorDegrade = 50;
		//	//	int r = ((RGBQUAD*)&color)->rgbRed		- colorDegrade;
		//	//	int g = ((RGBQUAD*)&color)->rgbGreen	- colorDegrade;
		//	//	int b = ((RGBQUAD*)&color)->rgbBlue		- colorDegrade;
		//	//	if(r < 0) { r = 0; }
		//	//	if(g < 0) { g = 0; }
		//	//	if(b < 0) { b = 0; }

		//	//	v[i - 1].color = D3DCOLOR_XRGB(r, g, b);

		//	//	colorDegrade = 100;
		//	//	r = ((RGBQUAD*)&color)->rgbRed		- colorDegrade;
		//	//	g = ((RGBQUAD*)&color)->rgbGreen	- colorDegrade;
		//	//	b = ((RGBQUAD*)&color)->rgbBlue		- colorDegrade;
		//	//	if(r < 0) { r = 0; }
		//	//	if(g < 0) { g = 0; }
		//	//	if(b < 0) { b = 0; }

		//	//	v[i - 2].color = D3DCOLOR_XRGB(r, g, b);

		//	//	//v[i - 1].col = WHITE;
		//	//}
		//}
		//HR(m_mSphere->UnlockVertexBuffer());
}

MeshBase* MeshManager::CreateTiger(int id, D3DXVECTOR3 pos, 
	float scaleX, float scaleY, float scaleZ)
{
	newMesh = new TigerMesh(id);
	newMesh->SetPos(pos);
	newMesh->SetScale(scaleX, scaleY, scaleZ);
	m_vMeshList.push_back(newMesh);
	return newMesh;
}

void MeshManager::ClearMeshManager()
{
}

void MeshManager::Render()
{
}
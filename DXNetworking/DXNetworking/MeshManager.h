#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <vector>
#include <D3DX9Mesh.h>
#include "MeshBase.h"

#define MeshM MeshManager::Instance()

using namespace std;

class MeshManager
{
private:
	ID3DXMesh*			m_mSphere;
	ID3DXMesh*			m_mTiger;

	std::vector<MeshBase*>		m_vMeshList;
	MeshBase*					newMesh;

	MeshManager();

public:
	~MeshManager();

	ID3DXMesh* GetSphere();
	void		SetCurrentColor(D3DCOLOR color);

	MeshBase* CreateTiger(int id, D3DXVECTOR3 pos, 
	float scaleX, float scaleY, float scaleZ);

	void ClearMeshManager();

	void Render();
	static MeshManager* Instance()
	{	static MeshManager instance; return &instance; }

};

#endif
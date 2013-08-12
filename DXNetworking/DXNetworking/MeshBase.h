#ifndef MESHOBJ_H
#define MESHOBJ_H

#include <D3DX9Mesh.h>
#include "BasicShader.h"

class MeshBase
{
private:
	virtual void LoadUniqueMesh()=0;
protected:
	unsigned int	m_id;
	void FinishLoadingMesh();
	LPD3DXMESH m_mesh;
	DWORD numMaterials;
	LPD3DXBUFFER bufMeshMaterial;
	D3DMATERIAL9* material;    // a pointer to a material buffer
	LPDIRECT3DTEXTURE9* texture;    // a pointer to a texture

	D3DXVECTOR3		m_pos;
	float rotX, rotY, rotZ;
	float scaleX, scaleY, scaleZ;		//for scale values
	void Draw(ShaderBase* pShader);
public:
	MeshBase(){}
	MeshBase(int id);
	~MeshBase();

	void SetPos(D3DXVECTOR3 pos)
		{m_pos=pos;}
	void SetScale(float x, float y, float z)
		{scaleX=x;
		 scaleY=y;
		 scaleZ=z;}
	void SetRotateX(float rot)
		{rotX=rot;}
	void SetRotateY(float rot)
		{rotY=rot;}
	void SetRotateZ(float rot)
		{rotZ=rot;}

	unsigned int GetId()
		{return m_id;}
	D3DXVECTOR3 GetPosition()
		{return m_pos;}

	virtual void Render()=0;
};

//*******************************************
//				TIGERMESH
//*******************************************
class TigerMesh : public MeshBase
{
private:
	ShaderBase*		transShader;
	virtual void LoadUniqueMesh();
public:
	TigerMesh(int id);
	~TigerMesh();

	virtual void Render();
};

class Sphere : public MeshBase
{
protected:
	ID3DXMesh*		m_mSphere;
	ShaderBase*		transShader;
	virtual void LoadUniqueMesh();
public:
	//Sphere();
	Sphere(int id);
	~Sphere();

	void Render();
	//void	Render(ID3DXEffect* FX, D3DXHANDLE mhWVP, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix);
};

#endif
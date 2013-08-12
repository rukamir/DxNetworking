#pragma once

#include <D3D9.h>
#include "Vertex.h"
#include "FXManager.h"
#include "Shapes.h"

//#define DEMOOBJ Obj3D::Instance()

class Obj3D : public ShapesBase
{
public:
	IDirect3DVertexBuffer9* m_VertBuff;
	IDirect3DIndexBuffer9* m_IndexBuff;

	IDirect3DVertexBuffer9* m_VBuff;
	IDirect3DIndexBuffer9* m_IBuff;
	float mCameraRotationY;
	float mCameraRadius;
	float mCameraHeight;
	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	IDirect3DDevice9* m_D3DDev;
	LPDIRECT3DTEXTURE9 mTex;
	VertexPNT* pVertices;
	//ShaderBase*		m_Shader;

public:
	Obj3D(IDirect3DDevice9* dev);
	~Obj3D();

	virtual void Render(ID3DXEffect* FX, D3DXHANDLE mhWVP, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix);
	//void Render(const D3DXVECTOR3 &pos);

	//static Obj3D* Instance()
	//{	static Obj3D instance; return &instance; }
};
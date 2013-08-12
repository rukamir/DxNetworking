#ifndef SHAPES_H
#define SHAPES_H

#include <D3dx9math.h>
#include <D3DX9Effect.h>
#include "ShaderBase.h"

class ShapesBase
{
protected:
	int					m_iID;
	D3DXVECTOR3			m_vPosition;
	D3DCOLOR			m_cColor;
	D3DXVECTOR3			m_vScale;
	D3DXVECTOR3			m_vHeading;
	D3DXQUATERNION		m_qHeading;
	LPDIRECT3DTEXTURE9	m_tTexture;
	ShaderBase			*m_Shader;

public:
	ShapesBase();
	~ShapesBase(){}

	int GetID(){return m_iID;}

	D3DXVECTOR3			GetPosition(){return m_vPosition;}
	void				SetPosition(D3DXVECTOR3 pos){
		m_vPosition=pos;
	}
	void				SetPosition(float x, float y, float z){m_vPosition=D3DXVECTOR3(x,y,z);}

	D3DCOLOR			GetColor(){return m_cColor;}
	void				SetColor(D3DCOLOR color){m_cColor=color;}
	void				SetColor(int R, int G, int B){m_cColor=D3DCOLOR_XRGB(R,G,B);}

	D3DXVECTOR3			GetScale(){return m_vScale;}
	void				SetScale(D3DXVECTOR3 scale){m_vScale = scale;}
	void				SetScale(float x, float y, float z){m_vScale=D3DXVECTOR3(x,y,z);}
	
	D3DXVECTOR3			GetHeading(){return m_vHeading;}
	void				SetHeading(D3DXVECTOR3 heading){m_vHeading=heading;}
	void				SetHeading(float x, float y, float z){m_vHeading=D3DXVECTOR3(x,y,z);}

	virtual void Render(ID3DXEffect* FX, D3DXHANDLE mhWVP, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)=0;
};

//class Sphere : public MeshBase
//{
//protected:
//	ID3DXMesh*		m_mSphere;
//	ShaderBase*		transShader;
//	virtual void LoadUniqueMesh();
//public:
//	//Sphere();
//	Sphere(int id);
//	~Sphere(){}
//
//	//void	Render(ID3DXEffect* FX, D3DXHANDLE mhWVP, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix);
//};

#endif
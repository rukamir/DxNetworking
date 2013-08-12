#ifndef TRANSFORMSHADER_H
#define TRANSFORMSHADER_H

#include "ShaderBase.h"

class BasicShader : public ShaderBase
{
public:
	virtual void GrabUniforms();
	LPDIRECT3DTEXTURE9* texture;
	//uniform handles
	D3DXHANDLE wvpM;		//WorldViewProjection
	D3DXHANDLE tex0;		//texture0
	D3DXVECTOR3 m_pos;
	float scaleX, scaleY, scaleZ;
	float rotX, rotY, rotZ;
public:
	BasicShader();
	~BasicShader();
	virtual void InitializeShader();
	virtual void Draw();
	void Draw2(D3DXMATRIX parentMat);

	void SetPosition(D3DXVECTOR3 pos)
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
	void SetTexture(LPDIRECT3DTEXTURE9* tex)
		{texture = tex;}
};

#endif
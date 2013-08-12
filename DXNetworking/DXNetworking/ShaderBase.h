#ifndef SHADERBASE_H
#define SHADERBASE_H

#include <D3DX9Effect.h>
#include "DirectX.h"

enum{
	BASICSHADER = 0,
	SUPERSHADER = 2,
	MORESHADES	= 8
};


class ShaderBase
{
public:
	DWORD				type;
	LPD3DXEFFECT		effect;
	LPD3DXBUFFER		compError;
	D3DXHANDLE			technique;

	//to be called during initialization
	void CreateShaderFromFile(LPCSTR shaderSrcName){
		HRESULT hr;
		compError = 0;
		hr = D3DXCreateEffectFromFile(gD3DDev, shaderSrcName, 0, 0, D3DXSHADER_DEBUG, 0, &effect, &compError);
		//This will pop up a debug window for HLSL, listing any errors in the shader file itself
		if( compError )
			 MessageBox(0, (char*)compError->GetBufferPointer(), 0, 0);
		//This will kill the program.  Typically shaders failing won't kill the program,, will just have jacked up render
		if (FAILED(hr))
		{
			MessageBox(0, "Shader Registration Failed", 0, 0);
			PostQuitMessage(0);
		}
	}
	//for grabbing DXHANDLES to uniforms
	virtual void GrabUniforms()=0;
public:
    D3DXMATRIX matProjection, matView;
	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;
	D3DXMATRIX matRotateX, matRotateY, matRotateZ;
	D3DXMATRIX world;
	ShaderBase(){D3DXMatrixIdentity(&matTrans);}
	~ShaderBase(){effect->Release();}
	virtual void InitializeShader()=0;
	virtual void Draw()=0;

	void Begin(){
		effect->Begin(NULL, NULL);
		effect->BeginPass(0);
	}
	void End(){
		effect->EndPass();
		effect->End();
	}
};

#endif
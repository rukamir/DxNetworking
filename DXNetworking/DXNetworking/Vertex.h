#pragma once

#include <D3dx9math.h>

struct VertexPNT
{
	VertexPNT()
		:pos(0.0f,0.0f,0.0f),
		normal(0.0f,0.0f,0.0f),
		texCoord0(0.0f,0.0f){}

	VertexPNT(const D3DXVECTOR3& v, 
		const D3DXVECTOR3& n, 
		const D3DXVECTOR2& uv)
		:pos(v),
		normal(n),
		texCoord0(uv){}

	D3DXVECTOR3	pos;
	D3DXVECTOR3	normal;
	D3DXVECTOR2 texCoord0;
	DWORD	color;

	static IDirect3DVertexDeclaration9* Decl;
};

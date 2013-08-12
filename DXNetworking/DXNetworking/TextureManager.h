#pragma once

#include <d3dx9.h>
#include <vector>

#define gTextureMan TextureManager::Instance()

class TextureManager
{
private:
	std::vector<LPDIRECT3DTEXTURE9> m_vD3DTextures;
	void ReleaseAll();
public:
	TextureManager(){}
	~TextureManager();

	void LoadTexture(LPDIRECT3DDEVICE9 d3ddev, 
		LPDIRECT3DTEXTURE9* texture, LPCTSTR  filename);
	void LoadAllTextures(LPDIRECT3DDEVICE9 d3ddev);

	LPDIRECT3DTEXTURE9		tS15;
	LPDIRECT3DTEXTURE9		water;
	LPDIRECT3DTEXTURE9		button;


	LPDIRECT3DTEXTURE9		pRenderTexture;
	LPDIRECT3DSURFACE9		pRenderSurface, pBackBuffer;
	D3DXMATRIX matProjection,matOldProjection;

	static TextureManager* Instance()
	{	static TextureManager instance; return &instance; }
};
//extern TextureManager* gTextureMan;
#include "TextureManager.h"

//TextureManager* gTextureMan = 0;

TextureManager::~TextureManager()
{

}

void TextureManager::ReleaseAll()
{
	//std::vector<LPDIRECT3DTEXTURE9>::iterator i = m_vD3DTextures.begin();
	//for (; i != m_vD3DTextures.end(); i++)
	//{
	//	(*i)->Release();
	//}
}

void TextureManager::LoadTexture(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DTEXTURE9* texture, LPCTSTR  filename)
{
	D3DXCreateTextureFromFileEx(d3ddev, filename, D3DX_DEFAULT, D3DX_DEFAULT,
        D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, 
        D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), NULL, NULL, texture);
		m_vD3DTextures.push_back(*texture);
}

void TextureManager::LoadAllTextures(LPDIRECT3DDEVICE9 d3ddev)
{
	LoadTexture(d3ddev, &water, "Textures/s13.jpg");
	LoadTexture(d3ddev, &tS15, "Textures/download.bmp");

	//LoadTexture(d3ddev, &button, "Textures/ButtonBlankGrey.png");
	LoadTexture(d3ddev, &button, "Textures/s13.jpg");

	////drop down menu
	//LoadTexture(d3ddev, &DropDownItem, "GUI/ButtonDropDownItem.png");
	//LoadTexture(d3ddev, &DropDownArrow, "GUI/ButtonDropDownTriangle.png");

	////checkbox
	//LoadTexture(d3ddev, &CheckBoxActive, "GUI/ButtonCheckBoxChecked.png");
	//LoadTexture(d3ddev, &CheckBoxNotActive, "GUI/ButtonCheckBoxUnchecked.png");

	////blank buttons
	//LoadTexture(d3ddev, &ButtonGrey, "GUI/ButtonBlankGrey.png");

	//LoadTexture(d3ddev, &logo, "Textures/tigerdrop.png"); //"Textures/rocks.jpg");


	//LoadTexture(d3ddev, &miss, "Textures/missX.png"); //"Textures/rocks.jpg");
	//LoadTexture(d3ddev, &hit, "Textures/hitX.png"); //"Textures/rocks.jpg");
	////LoadTexture(d3ddev, &rocks, "Textures/lava2.png");

	//D3DXCreateCubeTextureFromFile(d3ddev, "Textures/grassenvmap1024.dds", &cubeMap);
}
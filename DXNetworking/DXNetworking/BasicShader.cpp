#include "BasicShader.h"
#include "Camera.h"
#include "TextureManager.h"
#include "DirectX.h"
#include "d3dUtil.h"

BasicShader::BasicShader()
{
	scaleX = 1; scaleY = 1; scaleZ = 1;
	rotX = 0; rotY = 0; rotZ = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	effect = 0;
	compError = 0;
	technique = 0;
	wvpM = 0;
	type		=	BASICSHADER;
	texture		=	0;
	//texture		=	gTextureMan->tS15;

	//HR(D3DXCreateTextureFromFileEx(gD3DDev, "GUI/ButtonDropDownTriangle.png", D3DX_DEFAULT, D3DX_DEFAULT,
 //       D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, 
 //       D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), NULL, NULL, texture));
}

BasicShader::~BasicShader()
{
}

void BasicShader::GrabUniforms()
{
	wvpM = effect->GetParameterByName(0, "gWVP");
	tex0 = effect->GetParameterByName(0, "gTexture");
}

void BasicShader::InitializeShader()
{
	this->CreateShaderFromFile("Shaders/Transform.fx");//"Shaders/VertexShaders.fx");//
	this->GrabUniforms();
	//texture = &gTextureMan->rocks;
}

void BasicShader::Draw()
{
	//D3DXMATRIX matView;    // the view transform matrix
	matView = CAM->GetViewMatrix();

    //D3DXMATRIX matProjection;    // the view transform matrix
	matProjection = CAM->GetProjectionMatrix();

	//rotate on X matrix
    //D3DXMATRIX matRotateX;    // a matrix to store the rotation for each triangle
    D3DXMatrixRotationX(&matRotateX, D3DXToRadian(rotX));    // the rotation matrix

	//rotate on Y matrix
    //D3DXMATRIX matRotateY;    // a matrix to store the rotation for each triangle
    D3DXMatrixRotationY(&matRotateY, D3DXToRadian(rotY));    // the rotation matrix

	//rotate on Z matrix
    //D3DXMATRIX matRotateZ;    // a matrix to store the rotation for each triangle
    D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(rotZ));    // the rotation matrix

	//translation matrix
	//D3DXMATRIX matTrans;
	D3DXMatrixTranslation( &matTrans, m_pos.x, m_pos.y, m_pos.z);

	//scaling matrix
	/*D3DXMATRIX matScale;*/
	D3DXMatrixScaling(&matScale, scaleX, scaleY, scaleZ);

	//create combo world matrix
	D3DXMATRIX world = (matScale * matRotateX * matRotateY * matRotateZ * matTrans);

	//set uniforms
	effect->SetMatrix(wvpM, &(world * matView * matProjection));
	if(texture)
		effect->SetTexture(tex0, *texture);
	//effect->CommitChanges();
}

void BasicShader::Draw2(D3DXMATRIX parentMat)
{
	//D3DXMATRIX matView;    // the view transform matrix
	matView = CAM->GetViewMatrix();

    //D3DXMATRIX matProjection;    // the view transform matrix
	matProjection = CAM->GetProjectionMatrix();

	//rotate on X matrix
    //D3DXMATRIX matRotateX;    // a matrix to store the rotation for each triangle
    D3DXMatrixRotationX(&matRotateX, D3DXToRadian(rotX));    // the rotation matrix

	//rotate on Y matrix
    //D3DXMATRIX matRotateY;    // a matrix to store the rotation for each triangle
    D3DXMatrixRotationY(&matRotateY, D3DXToRadian(rotY));    // the rotation matrix

	//rotate on Z matrix
    //D3DXMATRIX matRotateZ;    // a matrix to store the rotation for each triangle
    D3DXMatrixRotationZ(&matRotateZ, D3DXToRadian(rotZ));    // the rotation matrix

	//translation matrix
	//D3DXMATRIX matTrans;
	D3DXMatrixTranslation( &matTrans, m_pos.x, m_pos.y, m_pos.z);

	//scaling matrix
	/*D3DXMATRIX matScale;*/
	D3DXMatrixScaling(&matScale, scaleX, scaleY, scaleZ);

	//world = (world*parentMat);

	//create combo world matrix
	world = (matScale * matRotateX * matRotateY * matRotateZ * (matTrans));


	//set uniforms
	effect->SetMatrix(wvpM, &(world * matView * matProjection));
	if(texture)
		effect->SetTexture(tex0, *texture);
	//effect->CommitChanges();
}
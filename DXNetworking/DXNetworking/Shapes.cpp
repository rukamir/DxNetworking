#include "Shapes.h"
#include "d3dUtil.h"
#include "DirectX.h"
#include "MeshManager.h"
#include "FXManager.h"
#include "BasicShader.h"
#include "TextureManager.h"

ShapesBase::ShapesBase()
{
	m_vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_cColor = D3DCOLOR_XRGB(255,255,255);
	m_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vHeading = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

////****************************************************************
////						SPHERE
////****************************************************************
//
//Sphere::Sphere(int id) : MeshBase()
//{
//	m_id = id;
//	m_mesh			=	MeshM->GetSphere();
//	texture			=	&gTextureMan->tS15;
//	transShader		=	FXM->GetFXByType(BASICSHADER);
//
//	m_id = id;
//	this->LoadUniqueMesh();
//	this->FinishLoadingMesh();
//
//	transShader		=	FXM->GetFXByType(BASICSHADER);
//	//transShader->InitializeShader();
//
//	scaleX = 1; scaleY = 1; scaleZ = 1;
//	rotX = 0; rotY = 0; rotZ = 0;
//	m_pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
//}

//void Sphere::Render(ID3DXEffect* FX, D3DXHANDLE mhWVP, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
//{
//	D3DXMATRIX Translation, Rotation, Scale;
//
//	((BasicShader*)transShader)->SetScale(scaleX, scaleY, scaleZ);
//	//((BasicShader*)m_Shader)->SetRotateY(m_vScale.y);
//	//((BasicShader*)m_Shader)->SetRotateZ(m_vScale.z);
//	((BasicShader*)transShader)->SetPosition(m_pos);
//
//	((BasicShader*)transShader)->SetTexture(texture);
//
//	transShader->Draw();
//	// Begin passes.
//	UINT numPasses = 0;
//	HR(transShader->effect->Begin(&numPasses, 0));
//	for(UINT i = 0; i < numPasses; ++i)
//	{
//		HR(transShader->effect->BeginPass(i));
//
//		//D3DXMatrixScaling(&Scale, m_vScale.x, m_vScale.y, m_vScale.z);
//		//D3DXMatrixRotationQuaternion(&Rotation, &m_qHeading);
//		D3DXMatrixIdentity(&Rotation);
//		//D3DXMatrixTranslation(&Translation, m_vPosition.x, m_vPosition.y, m_vPosition.z);
//
//
//		//HR(m_Shader->effect->SetMatrix(mhWVP, &(Scale*Rotation*Translation*viewMatrix*projMatrix)));
//		//HR(m_Shader->effect->CommitChanges());
////HR(transShader->DrawSubset(0));
//
//		HR(transShader->effect->EndPass());
//	}
//	HR(transShader->effect->End());
//
//}
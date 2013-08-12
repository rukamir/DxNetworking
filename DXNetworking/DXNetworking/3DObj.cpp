#include "3DObj.h"
#include "TextureManager.h"
//#include "DirectXBase.h"
#include "Camera.h"
#include "DirectInput.h"
#include "d3dUtil.h"
#include "Vertex.h"
#include "BasicShader.h"

#include <D3dtypes.h>


Obj3D::Obj3D(IDirect3DDevice9* dev)
	//: D3DApp()
{
	m_Shader		=	FXM->GetFXByType(BASICSHADER);
	m_tTexture		=	gTextureMan->water;
	m_vScale		=	D3DXVECTOR3(5.0f, 5.0f, 5.0f);



	m_D3DDev = dev;
	mTex = 0;//gTextureMan->rocks;

	//creating vertex buffer
	dev->CreateVertexBuffer(4*sizeof(VertexPNT), D3DUSAGE_WRITEONLY, 
		0, D3DPOOL_MANAGED, &m_VertBuff, NULL);

	//locking vertex buffer
	m_VertBuff->Lock( 0, 0, (void**)&pVertices, 0 );

	//define object
	//bottom
	pVertices[0].pos.x=-1.0f;
	pVertices[0].pos.y=-1.0f;
	pVertices[0].pos.z=1.0f;
	pVertices[0].texCoord0.x = 0.0f;
	pVertices[0].texCoord0.y = 0.0f;
	pVertices[0].normal.x = 0.0f;
	pVertices[0].normal.y = 1.0f;
	pVertices[0].normal.z = 0.0f;

	pVertices[1].pos.x=1.0f;
	pVertices[1].pos.y=-1.0f;
	pVertices[1].pos.z=1.0f;
	pVertices[1].texCoord0.x = 1.0f;
	pVertices[1].texCoord0.y = 0.0f;
	pVertices[1].normal.x = 0.0f;
	pVertices[1].normal.y = 1.0f;
	pVertices[1].normal.z = 0.0f;

	pVertices[2].pos.x=1.0f;
	pVertices[2].pos.y=-1.0f;
	pVertices[2].pos.z=-1.0f;
	pVertices[2].texCoord0.x = 1.0f;
	pVertices[2].texCoord0.y = 1.0f;
	pVertices[2].normal.x = 0.0f;
	pVertices[2].normal.y = 1.0f;
	pVertices[2].normal.z = 0.0f;

	pVertices[3].pos.x=-1.0f;
	pVertices[3].pos.y=-1.0f;
	pVertices[3].pos.z=-1.0f;
	pVertices[3].texCoord0.x = 0.0f;
	pVertices[3].texCoord0.y = 1.0f;
	pVertices[3].normal.x = 0.0f;
	pVertices[3].normal.y = 1.0f;
	pVertices[3].normal.z = 0.0f;

	//unlock vertex buffer
	m_VertBuff->Unlock();

	//create index buffer
	dev->CreateIndexBuffer(2*3*2,D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuff, NULL);

	//lock buffer
	WORD *indices=NULL;
	m_IndexBuff->Lock( 0, 0, (void**)&indices, 0 );

	indices[0]=0; indices[1]=1;	indices[2]=2;
	indices[3]=2; indices[4]=3; indices[5]=0;

	//unlock index buffer
	m_IndexBuff->Unlock();
}

Obj3D::~Obj3D()
{
	m_IndexBuff->Release();
	m_VertBuff->Release();
}

void Obj3D::Render(ID3DXEffect* FX, D3DXHANDLE mhWVP, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
{
	((BasicShader*)m_Shader)->SetScale(m_vScale.x, m_vScale.y, m_vScale.z);
	((BasicShader*)m_Shader)->SetPosition(m_vPosition);
	((BasicShader*)m_Shader)->SetTexture(&m_tTexture);
	m_Shader->Draw();

//	m_D3DDev->CreateTexture(256,
//                            256,
//                            1,
//                            D3DUSAGE_RENDERTARGET,
//                            D3DFMT_R5G6B5,
//                            D3DPOOL_DEFAULT,
//                            &gTextureMan->pRenderTexture,
//                            NULL);
//
//	gTextureMan->pRenderTexture->GetSurfaceLevel(0,&gTextureMan->pRenderSurface);
//	D3DXMatrixPerspectiveFovLH(&gTextureMan->matProjection,D3DX_PI / 4.0f,1,1,100);
//
//	m_D3DDev->GetTransform(D3DTS_PROJECTION,&gTextureMan->matOldProjection);
//	m_D3DDev->GetRenderTarget(0,&gTextureMan->pBackBuffer);
//
////render-to-texture
//  //set new render target
//  m_D3DDev->SetRenderTarget(0,gTextureMan->pRenderSurface);
//  //clear texture
//  m_D3DDev->Clear(0,
//                           NULL,
//                           D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
//                           D3DCOLOR_XRGB(100,100,100),
//                           1.0f,
//                           0);
//  m_D3DDev->BeginScene();
//
//  //m_D3DDev->SetTexture(0,pPyramideTexture);
//  ((BasicShader*)m_Shader)->SetTexture(&m_tTexture);
//
//
//  D3DXMatrixRotationY(&matRotationY,fRotation);
//  D3DXMatrixTranslation(&matTranslation,0.0f,0.0f,5.0f);
//  m_D3DDev->SetTransform(D3DTS_WORLD,
//                                  &(matRotationY * matTranslation));
//  //set projection matrix
//  m_D3DDev->SetTransform(D3DTS_PROJECTION,&matProjection);
//
//  m_D3DDev->SetStreamSource(0,m_VBuff,0,sizeof(D3DVERTEX));
//  m_D3DDev->DrawPrimitive(D3DPT_TRIANGLELIST,0,4);
//
//  m_D3DDev->EndScene();

	UINT numPasses = 0;
	HR(m_Shader->effect->Begin(&numPasses, 0));
	for(UINT i = 0; i < numPasses; ++i)
	{

		HR(m_Shader->effect->BeginPass(i));

		m_D3DDev->SetVertexDeclaration(VertexPNT::Decl);
		m_D3DDev->SetStreamSource( 0, m_VertBuff,0, sizeof(VertexPNT) );
		m_D3DDev->SetIndices( m_IndexBuff);

		//turn lighting off
		m_D3DDev->SetRenderState(D3DRS_LIGHTING, FALSE);
		//show wireframe
		//m_D3DDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		//enable z-buffer
		m_D3DDev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer

		//draw primitive with 4 verts 2 tris
		m_D3DDev->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,0,0,4,0,2);

		HR(m_Shader->effect->EndPass());
	}
	HR(m_Shader->effect->End());
}

//void Obj3D::Render(const D3DXVECTOR3 &pos)
//{
//	////set up camera
//	//D3DXMatrixLookAtLH(&mView, 
//	//	&D3DXVECTOR3 (0.0f, 0.0f, -30.0f),  //camera pos
//	//	&D3DXVECTOR3 (0.0f, 0.0f, 0.0f),   //look at pos
//	//	&D3DXVECTOR3 (0.0f, 1.0f, 0.0f));  //up position (y = up)
//	//set view transform
//	//m_D3DDev->SetTransform(D3DTS_VIEW, &mView);
//	//D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI * 0.25f, 4/3, 1.0f, 5000.0f);
//	////set projections transform
//	//m_D3DDev->SetTransform( D3DTS_PROJECTION, &mProj );
//
//	//D3DXMATRIX matScale;
//	//D3DXMATRIX matRotateX;
//	//static float degrees = 0;
//	//degrees++;
//	////D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);    // double the size of the model
//	//D3DXMatrixRotationX(&matRotateX, D3DXToRadian(degrees));    // rotate the model 90 degrees
//	//// set the world transform to the two matrices multiplied together
//	////m_D3DDev->SetTransform(D3DTS_WORLD, &(matRotateX * matScale));
//
//	////convert to world space
//	//D3DXMATRIX matWorld;
//	//D3DXMatrixTranslation(&matWorld,pos.x,pos.y,pos.z);
//	//m_D3DDev->SetTransform( D3DTS_WORLD, &(matRotateX /** matScale*/ * matWorld) );
//	//m_D3DDev->SetTexture(0, mTex);
//
//	m_D3DDev->SetVertexDeclaration(VertexPNT::Decl);
//	m_D3DDev->SetStreamSource( 0, m_VertBuff,0, sizeof(VertexPNT) );
//	m_D3DDev->SetIndices( m_IndexBuff);
//
//	//turn lighting off
//	m_D3DDev->SetRenderState(D3DRS_LIGHTING, FALSE);
//	//show wireframe
//	//m_D3DDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
//	//enable z-buffer
//	m_D3DDev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
//
//	//draw primitive with 18 verts 6 tris
//	m_D3DDev->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,0,0,4,0,2);
//
//	//m_Shader->effect->SetTexture(((BasicShader*)pShader)->tex0, texture[i]);
//	//m_Shader->effect->CommitChanges();
//
//}
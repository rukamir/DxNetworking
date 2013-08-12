#include "MeshBase.h"
#include "Camera.h"
#include "FXManager.h"
#include "d3dUtil.h"

//**********************************************************************
//                        MESHBASE
//**********************************************************************

MeshBase::MeshBase(int id)
{
	m_id = id;
}

MeshBase::~MeshBase()
{

	if(texture)
		delete texture;
	if(material)
		delete material;
}

void MeshBase::FinishLoadingMesh()
{
	// retrieve the pointer to the buffer containing the material information
	D3DXMATERIAL* tempMaterials = (D3DXMATERIAL*)bufMeshMaterial->GetBufferPointer();

	// create a new material buffer for each material in the mesh
	material = new D3DMATERIAL9[numMaterials];
	texture = new LPDIRECT3DTEXTURE9[numMaterials];
	for(DWORD i = 0; i < numMaterials; i++)    // for each material...
	{
		material[i] = tempMaterials[i].MatD3D;    // get the material info...
		material[i].Ambient = material[i].Diffuse;    // and make ambient the same as diffuse
		
		texture[i] = 0;
		if (tempMaterials[i].pTextureFilename)
		{
			D3DXCreateTextureFromFile(gD3DDev, tempMaterials[i].pTextureFilename, &texture[i]);

		}

	}
	bufMeshMaterial->Release();
}

void MeshBase::Draw(ShaderBase* pShader)
{

	D3DXMATRIX matView;
	matView = CAM->GetViewMatrix();
    gD3DDev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView 

    D3DXMATRIX matProjection;
	matProjection = CAM->GetProjectionMatrix();
    gD3DDev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

	for(DWORD i = 0; i < numMaterials; i++)    // loop through each subset
	{
		pShader->effect->SetTexture(((BasicShader*)pShader)->tex0, texture[i]);
		pShader->effect->CommitChanges();
		//gD3DDev->SetMaterial(&material[i]);    // set the appropriate material for the subset
		//if(texture[i] != NULL)    // if the subset has a texture (if texture is not NULL)
		//	gD3DDev->SetTexture(0, texture[i]);    // ...then set the texture
		m_mesh->DrawSubset(i);    // draw the subset
	}
}

//**********************************************************************
//                        TIGERMESH
//**********************************************************************

TigerMesh::TigerMesh(int id)
{
	m_id = id;
	this->LoadUniqueMesh();
	this->FinishLoadingMesh();

	transShader		=	FXM->GetFXByType(BASICSHADER);
	//transShader->InitializeShader();

	scaleX = 1; scaleY = 1; scaleZ = 1;
	rotX = 0; rotY = 0; rotZ = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

TigerMesh::~TigerMesh()
{
}

void TigerMesh::LoadUniqueMesh()
{
	D3DXLoadMeshFromX("Mesh/tiger.x", // load this file
					  D3DXMESH_SYSTEMMEM,    // load the mesh into system memory
					  gD3DDev,    // the Direct3D Device
					  NULL,    // we aren't using adjacency
					  &bufMeshMaterial,    // put the materials here
					  NULL,    // we aren't using effect instances
					  &numMaterials,    // the number of materials in this model
					  &m_mesh);    // put the mesh here
}

void TigerMesh::Render()
{
	//set shader information for proper tranforms
	((BasicShader*)transShader)->SetPosition(this->m_pos);
	((BasicShader*)transShader)->SetScale(this->scaleX, this->scaleY, this->scaleZ);
	((BasicShader*)transShader)->SetRotateX(this->rotX);
	((BasicShader*)transShader)->SetRotateY(this->rotY);
	((BasicShader*)transShader)->SetRotateZ(this->rotZ);

	//all the calls for drawing and manipulating the mesh
	transShader->Begin();
	((BasicShader*)transShader)->Draw2(transShader->world);
	//((BasicShader*)transShader)->Draw();
	this->Draw(transShader);
	transShader->End();
}

//****************************************************************
//						SPHERE
//****************************************************************

Sphere::Sphere(int id) : MeshBase()
{
	m_id = id;
	//m_mesh			=	MeshM->GetSphere();
	//texture			=	&gTextureMan->tS15;
	transShader		=	FXM->GetFXByType(BASICSHADER);
	numMaterials	=	1;

	m_id = id;
	this->LoadUniqueMesh();
	//this->FinishLoadingMesh();

	transShader		=	FXM->GetFXByType(BASICSHADER);
	//transShader->InitializeShader();

	scaleX = 1; scaleY = 1; scaleZ = 1;
	rotX = 0; rotY = 0; rotZ = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Sphere::~Sphere(){
}

void Sphere::LoadUniqueMesh(){
	//Create main sphere to be used to draw spheres place by user
	//Create a temporary sphere first
	ID3DXMesh* tempSphere;
	HR(D3DXCreateSphere(gD3DDev, 1.0f, 10, 16, &tempSphere, 0));
	//Clone temp sphere to the main sphere and give its vertices a color value
	HR(tempSphere->CloneMeshFVF( D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_DIFFUSE, gD3DDev, &m_mesh ));
	//Release the temp sphere
	ReleaseCOM(tempSphere);
}

void Sphere::Render()
{
	//set shader information for proper tranforms
	((BasicShader*)transShader)->SetPosition(this->m_pos);
	((BasicShader*)transShader)->SetScale(this->scaleX, this->scaleY, this->scaleZ);
	((BasicShader*)transShader)->SetRotateX(this->rotX);
	((BasicShader*)transShader)->SetRotateY(this->rotY);
	((BasicShader*)transShader)->SetRotateZ(this->rotZ);

	////all the calls for drawing and manipulating the mesh
	//transShader->Begin();
	//((BasicShader*)transShader)->Draw2(transShader->world);
	////((BasicShader*)transShader)->Draw();
	//this->Draw(transShader);
	//transShader->End();

	// Begin passes.
	LPD3DXEFFECT FX = transShader->effect;
	UINT numPasses = 0;

	HR(FX->Begin(&numPasses, 0));
	((BasicShader*)transShader)->Draw2(transShader->world);
	for(UINT i = 0; i < numPasses; ++i)
	{
		HR(FX->BeginPass(i));

		//D3DXMatrixScaling(&Scale, m_vScale.x, m_vScale.y, m_vScale.z);
		////D3DXMatrixRotationQuaternion(&Rotation, &m_qHeading);
		//D3DXMatrixIdentity(&Rotation);
		//D3DXMatrixTranslation(&Translation, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		//HR(FX->SetMatrix(mhWVP, &(Scale*Rotation*Translation*viewMatrix*projMatrix)));
		//HR(FX->CommitChanges());

		HR(m_mesh->DrawSubset(0));

		HR(FX->EndPass());
	}
	HR(FX->End());
	FX = 0;
}

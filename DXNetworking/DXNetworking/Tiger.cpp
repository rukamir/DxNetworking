#include "Tiger.h"
#include "MeshBase.h"
#include "MeshManager.h"
#include "GraphicsManager.h"

Tiger::Tiger(int id)
{
	m_id = id;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_acceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_forceAccum = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	orientation = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	damping = 0.98f;
	m_awarnessRad = 0;
	m_targetID=0;
	m_maxAccel = 100;
	m_mesh		=	GraphicsM->CreateTiger(id);
	//m_mesh = MeshM->CreateTiger(id, m_pos, 1, 1, 1);
	//m_Shader		=	FXM->GetFXByType(BASICSHADER);
}

Tiger::~Tiger()
{

}

Ball::Ball(int id){
	m_id = id;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_acceleration = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_forceAccum = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	orientation = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	damping = 0.98f;
	m_awarnessRad = 0;
	m_targetID=0;
	m_maxAccel = 100;
	m_mesh		=	GraphicsM->CreateSphere(id);
}

Ball::~Ball(){
}
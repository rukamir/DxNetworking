#include "LinkedObjs.h"

LinkedObjs::LinkedObjs(int id) : Tiger(id){
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

}

LinkedObjs::~LinkedObjs(){
	for(const auto &ents : m_vChildren){
		delete ents;
	}
}

Entity* LinkedObjs::AddChild(LinkedObjs* child, D3DXVECTOR3 offSetValue){
	info = new ChildInfo( child, offSetValue );
	m_vChildren.push_back( info );

	return info->childEnt;
}

void LinkedObjs::Update(float dt){

	// Update children
	for(const auto &ents : m_vChildren){
		ents->childEnt->SetPosition( m_pos + ents->offSet );
		((LinkedObjs*)ents->childEnt)->Update(dt);
	}

	this->UpdateHeading();
	static float rot = 45;
	orientation = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	if(m_mesh)
		m_mesh->SetPos(this->m_pos);


	this->m_mesh->SetRotateX(rot++);
}
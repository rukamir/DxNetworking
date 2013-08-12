#pragma once
#include "Tiger.h"

#include <vector>

using namespace std;

class LinkedObjs : public Tiger
{
public:
	struct ChildInfo{
		ChildInfo(Entity* ent, D3DXVECTOR3 offSetValue){
			childEnt = ent;
			offSet = offSetValue;
		}
		Entity*			childEnt;
		D3DXVECTOR3		offSet;
	};
private:
	ChildInfo				*info;
	Entity					*ent;
	vector<ChildInfo*>			m_vChildren;
public:
	LinkedObjs(int id);
	~LinkedObjs();

	Entity*		AddChild(LinkedObjs* child, D3DXVECTOR3 offSetValue);

	virtual void Update(float dt);
};
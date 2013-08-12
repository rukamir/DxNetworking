#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include "GraphMap.h"
#include "InfluenceMap.h"
#include <string>
#include <map>
#include <vector>
#include <D3dx9math.h>

//enum {
//	ALLY			= 0x01,
//	ENEMY			= 0x02,
//	HEALTH			= 0x04,
//	WEAPON			= 0x08,
//	TENSION			= 0x10,
//	VULNERABILITY	= 0x20,
//	INFLUENCE		= 0x40
//	//	OTHER		= 0x80
//};

class MapCreator
{
private:
	int						m_iMapSize;
	// Original map
	GraphMap*			mainOrigMap;
	// Used for creating maps
	InfluenceMap*			tempClone;
	struct Influence
	{
		int id;
		std::string		mapName;
		D3DXVECTOR3*	pos;
		float*			health;
		float			influenceValue;
	};
	// All maps
	std::map<std::string, InfluenceMap*>	m_mMapList;
	// List of all influences
	std::vector<Influence>					m_iInfluenceList;
	// List of all map names
	std::vector<std::string>				m_sMapNameList;

	// Iterators
	std::vector<std::string>::iterator	stringIt;
	std::vector<Influence>::iterator	infIt;
	VectGraphNodes::iterator			i, j;

public:
	MapCreator();
	~MapCreator();
	void CreateMap(std::string mapName);
	GraphMap* CreateNxNMap(std::string mapName, int* startOfIds, int size, float density);
	void AddInfluenceToMap(std::string mapName, D3DXVECTOR3 pos, float influence);

	//InfluenceMap* GetSelectedMap(DWORD mapTypeFlags);

	void CreateInfluence(std::string mapName, int id, D3DXVECTOR3* pos, 
						 float influence, float* health);
	// Modify Influences
	void ModifyRegInfluence(int id, float influneceValue);
	GraphNode*		GetHighestInfluence(std::string searchMapName);

	void Update(float dt);

	Influence* GetInfluence(int id){
		std::vector<Influence>::iterator i = m_iInfluenceList.begin();
		for(; i!=m_iInfluenceList.end();i++)
			if(id == (*i).id)
				return &(*i);
		return NULL;
	}

	void CreateGraphicsFor(std::string mapName);

	// Used for real time demo
	void CreateDynamicNode(int id, D3DXVECTOR3 pos, std::string mapName, float influence);
	D3DXVECTOR3 GetDyNodePos(){return *GetInfluence(8888)->pos;}
	void MoveDyNodeUp(){
		GetInfluence(8888)->pos->y++;
	}
	void MoveDyNodeDown(){GetInfluence(8888)->pos->y--;}
	void MoveDyNodeLeft(){GetInfluence(8888)->pos->x--;}
	void MoveDyNodeRight(){GetInfluence(8888)->pos->x++;}

	void IncreaseDyNode(){
		static float* value = &GetInfluence(8888)->influenceValue;
		if (*value < 20)
			(*value)++;
		//GetInfluence(8888)->influenceValue++;
	}
	void DecreaseDyNode(){//GetInfluence(8888)->influenceValue--;
		static float* value = &GetInfluence(8888)->influenceValue;
		if (*value > 0)
			(*value)--;
	}

	void MoveDyNodeUp2(){
		GetInfluence(8889)->pos->y++;
	}
	void MoveDyNodeDown2(){GetInfluence(8889)->pos->y--;}
	void MoveDyNodeLeft2(){GetInfluence(8889)->pos->x--;}
	void MoveDyNodeRight2(){GetInfluence(8889)->pos->x++;}

	void IncreaseDyNode2(){//GetInfluence(8889)->influenceValue++;
		static float* value = &GetInfluence(8889)->influenceValue;
		if (*value < 20)
			(*value)++;
	}
	void DecreaseDyNode2(){//GetInfluence(8889)->influenceValue--;
		static float* value = &GetInfluence(8889)->influenceValue;
		if (*value > 0)
			(*value)--;
	}


private:
	UINT aID, bID;
	VectGraphNodes rhsNodeList;
	VectGraphNodes origNodeList;
	GraphNode*	closestNode;
	GraphNode* FindClosestGraphNode(D3DXVECTOR3 pos);
};

#endif
#ifndef INFLUENCECLONE_H
#define INFLUENCECLONE_H

#include "GraphMap.h"
#include <vector>
#include <map>


class InfluenceMap

{
private:

	VectGraphNodes				m_vGraphNodes;
	std::map<int, GraphNode>	m_mGraphNodes;

	GraphNode*					m_nHighestValueNode;

	bool			AreAllNodesInfluenced();

	// Iterators
	VectGraphNodes::iterator i, j;
	VectGraphNodes addList;

public:
	InfluenceMap(){}
	InfluenceMap(GraphMap* cloneThis);
	~InfluenceMap();

	void			SetInfluence(int nodeIdToInfluence, float influence);
	//void			SetInfluence(int nodeIdToInfluence, float influence);
	//void			SetInfluence(int nodeIdToInfluence, float nearInfl, 
	//					float nearInflIncrRate, float peak, 
	//					float farInfl, float farDissipation);

	VectGraphNodes	GetAllNodes(){return m_vGraphNodes;}
	void			SetMapToZero();

	GraphNode*		GetLargestInflunece();
	std::vector<GraphNode*>	GetListOfLargest(const int numOfNodes);

	InfluenceMap* AddMap(InfluenceMap* addThis);
	InfluenceMap* SubtractMap(InfluenceMap* addThis);
	InfluenceMap*	MultiplyMap(InfluenceMap* addThis);

	GraphNode*		GetNodeById(int id);
	void			CreateGraphicObjects();
	void			Update(float dt);
};


#endif
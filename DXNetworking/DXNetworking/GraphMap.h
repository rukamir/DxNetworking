#ifndef INFLUENCEMAP_H
#define INFLUENCEMAP_H

#include "GraphNode.h"
#include <vector>

typedef std::vector<GraphNode*> VectGraphNodes;


class GraphMap
{
private:
	VectGraphNodes			m_vGraphNodes;
public:
	GraphMap();
	~GraphMap();

	GraphNode*		CreateGraphNode(int id, D3DXVECTOR3 pos);
	void			ConnectGraphNodes(GraphNode* A, GraphNode* B, bool twoWay);
	void			ConnectGraphNodes(int aID, int bID, bool twoWay);

	//void			SetInfluence(int nodeIdToInfluence, float influence);
	//void			SetInfluence(int nodeIdToInfluence, float nearInfl, 
	//					float nearInflIncrRate, float peak, 
	//					float farInfl, float farDissipation);

	void			CreateFromGraph(VectGraphNodes nodeList);
	GraphNode*		GetNodeById(int id);
	VectGraphNodes	GetAllNodes(){return m_vGraphNodes;}
	VectGraphNodes	GetPeaks();
	void			SetMapToZero();
	void			CreateGraphicObjects();
	void			SetUpAdjList();

	void Update(float dt);

	// Overloaded Operators
	GraphMap operator+=(GraphMap rhs);
	GraphMap operator-=(GraphMap rhs);

private:
	bool			AreAllNodesInfluenced();
};

#endif
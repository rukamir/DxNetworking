#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <D3dx9math.h>

class GraphNode
{
private:
	int				m_iID;
	D3DXVECTOR3		m_vPosition;
	//Sphere*			m_sphere;				// Graphics Sphere
	float			m_fInfluence;			// Current Influence
	float			m_fInflHigh;			// Influence High
	float			m_fInflLow;				// Influence Low

public:
	GraphNode(int id, D3DXVECTOR3 position);
	~GraphNode();

	int GetId(){return m_iID;}
	//Sphere*	GetGraphicsObject(){return m_sphere;}
	void Update();
	void CreateGraphicObject();

	float			GetInfluence(){return m_fInfluence;}
	void			SetInfluence(float influence);

	D3DXVECTOR3		GetPosition(){return m_vPosition;}
	void			SetPosition(D3DXVECTOR3 position){m_vPosition=position;}
	void			SetPosition(float x, float y, float z){m_vPosition=D3DXVECTOR3(x,y,z);}
};

#endif
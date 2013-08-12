#include "GraphNode.h"
#include "GraphicsManager.h"

GraphNode::GraphNode(int id, D3DXVECTOR3 position)
{
	m_iID		=	id;
	m_vPosition	=	position;
	m_fInfluence=	0.0f;
	m_fInflHigh	=	-99.0f;
	m_fInflLow	=	99.0f;
	//m_sphere	=	0;
}

GraphNode::~GraphNode()
{
	//if(m_sphere)
	//	delete m_sphere;
}

void GraphNode::Update()
{

	// Prevents dividing by 0
	//if(m_fInfluence == 0)
	//	m_fInfluence = 0.01f;
	//if(m_fInfluence > 20.0)
	//	m_fInfluence = 20.0f;

	//static int red = 0;
	//static int blue = 0;
	static int color = 0, color2 = 0;
	//color = (int)(((m_fInfluence)/10)*255);
	if (m_fInfluence == 0.0f)
		color = 0;
	else
		color = (int)(((m_fInfluence)/10)*255);


	//color = (int)(((m_fInfluence))*255);
	//color = 254;

	if(color > 255)
	{
		color2 = color - 255;
		color = 255;
	}
	else
		color2 = 0;

	//// If this object is associated with a graphics object
	//if(m_sphere)
	//{

	//	// Update graphics object
	//	m_sphere->SetPosition(m_vPosition);

	//	// Positive Influence
	//	if(m_fInfluence >= 0.0f)
	//	{
	//		//blue = (int)((m_fInfluence/3)*255);
	//		m_sphere->SetColor(color2, 0, color);
	//	}
	//	// Negative Influence
	//	else if(m_fInfluence < 0.0f)
	//	{
	//		// Inverted influence for color calculations
	//		//red = (int)(((m_fInfluence*-1)/3)*255);
	//		color *= -1;
	//		m_sphere->SetColor(color, color2, 0);
	//	}
	//}
}

void GraphNode::CreateGraphicObject()
{
	//if(!m_sphere)
	//{
	//	GraphicsM->CreateSphere(this->m_iID);
	//	m_sphere	=	GraphicsM->GetSphere(this->m_iID);
	//}
}

void GraphNode::SetInfluence(float influence)
{
	m_iID;
	m_fInfluence=influence;

	// Check if new influence is high
	if(m_fInfluence > m_fInflHigh)
		m_fInflHigh = m_fInfluence;

	// Check if new influence is low
	if(m_fInfluence < m_fInflLow)
		m_fInflLow = m_fInfluence;
}
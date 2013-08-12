#ifndef TIGER_H
#define TIGER_H

#include "Entity.h"

class Tiger : public Entity
{
private:
	int	m_ownerId;
public:
	Tiger(){}
	Tiger(int id);
	~Tiger();
	void SetOwnerId(int id)
		{m_ownerId=id;}
};

class Plane : public Entity
{
private:
public:
	Plane(int id);
	~Plane();

	Tiger* DropTiger();
};

class Ball : public Entity
{
public:
	Ball(int id);
	~Ball();
};

#endif
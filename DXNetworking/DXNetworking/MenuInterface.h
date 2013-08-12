#pragma once

#include "SpriteElements.h"
#include <d3dx9.h>
#include <memory>
#include <vector>

using namespace std;

//class SpriteElements;

typedef std::shared_ptr<SpriteElements> SprtElemShPtr;
typedef vector<SprtElemShPtr> VectSprtElemShPtrs;

class MenuInterface
{
private:
	D3DXVECTOR2					m_pos;
	D3DXVECTOR2					m_velocity;
	VectSprtElemShPtrs			m_vSptElem;
	bool						m_active;
public:
	MenuInterface();
	~MenuInterface();

	void AddElementToMenu(SprtElemShPtr menuItem);
	void Activate();
	void Unactivate();
	bool IsActive();

	void SetPosition(D3DXVECTOR2 pos);

	void Update(float dt);
};
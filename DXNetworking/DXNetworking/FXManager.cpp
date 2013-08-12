#include "FXManager.h"
#include "DirectX.h"
#include "d3dUtil.h"
#include "BasicShader.h"

FXManager::FXManager()
{
	newShader = new BasicShader();
	newShader->InitializeShader();
	m_mShaders.insert(std::make_pair(BASICSHADER, newShader));
	m_vShaders.push_back(newShader);
}

FXManager::~FXManager()
{
	for(const auto &sh : m_vShaders){
		delete sh;
	}
}
#ifndef FXMANAGER_H
#define FXMANAGER_H

#include <d3dx9effect.h>
#include "ShaderBase.h"
#include <vector>
#include <map>

#define FXM FXManager::Instance()


class FXManager
{
protected:
	std::map<DWORD, ShaderBase*>		m_mShaders;
	std::vector<ShaderBase*>			m_vShaders;
	ShaderBase* newShader;

	FXManager();
public:
	ShaderBase*			GetFXByType(DWORD shaderType){return m_mShaders.find(shaderType)->second;}
	~FXManager();


	static FXManager* Instance()
		{	static FXManager instance; return &instance; }
};

#endif
#pragma once

#include "State.h"

class D3DApp;

class IntState
	: public State<D3DApp>
{
protected:
public:
	IntState();
	~IntState();

	void InitializeState(D3DApp*);
	void UpdateScene(D3DApp*, float dt);
	void RenderScene(D3DApp*);
	void OnResetDevice(D3DApp*);
	void OnLostDevice(D3DApp*);
	void LeaveState(D3DApp*);
};

class ServerLobby
	: public State<D3DApp>
{
protected:
public:
	ServerLobby();
	~ServerLobby();

	void InitializeState(D3DApp*);
	void UpdateScene(D3DApp*, float dt);
	void RenderScene(D3DApp*);
	void OnResetDevice(D3DApp*);
	void OnLostDevice(D3DApp*);
	void LeaveState(D3DApp*);
};

class GameLobby
	: public State<D3DApp>
{
protected:
public:
	GameLobby();
	~GameLobby();

	void InitializeState(D3DApp*);
	void UpdateScene(D3DApp*, float dt);
	void RenderScene(D3DApp*);
	void OnResetDevice(D3DApp*);
	void OnLostDevice(D3DApp*);
	void LeaveState(D3DApp*);
};


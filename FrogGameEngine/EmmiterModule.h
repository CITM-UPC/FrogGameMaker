#pragma once

class Emmiter;

class EmmiterSpawnModule {
public:
	virtual void Update();

protected:
	Emmiter* owner;
};

class EmmiterUpdateModule {
public:
	virtual void Update();

protected:
	Emmiter* owner;
};

class EmmiterRenderModule {
public:
	virtual void Update();

protected:
	Emmiter* owner;
};
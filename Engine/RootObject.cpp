#include "RootObject.h"
#include "SceneManager.h"


RootObject::RootObject(GameObject* parent):
	GameObject(nullptr, "RootObject")
{
}


RootObject::~RootObject()
{
}

void RootObject::Initialize()
{
	Instantiate<SceneManager>(this);
}

void RootObject::Update()
{
}

void RootObject::Draw()
{
}

void RootObject::Release()
{
}

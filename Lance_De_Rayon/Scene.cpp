#include "stdafx.h"
#include "Scene.h"


Scene::Scene(void)
{
}

Scene::Scene(Camera _camera)
{
	camera = _camera;
}


Scene::~Scene(void)
{
}

void Scene::addObject(Object3D* object)
{
	objects.push_back(object);
}

void Scene::addLight(Light* light)
{
	lights.push_back(light);
}

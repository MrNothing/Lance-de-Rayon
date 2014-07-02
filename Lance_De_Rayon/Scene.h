#pragma once
#include "Object3D.h";
#include "Light.h";

class Scene
{
public:
	Scene(void);
	Scene(Camera camera);
	~Scene(void);
	Camera getCamera(){ return camera; }
	std::list<Object3D*> getObjects(){ return objects; }
	std::list<Light*> getLights(){ return lights; }
	void addObject(Object3D* object);
	void addLight(Light* light);
private:
	Camera camera;
	std::list<Object3D*> objects;
	std::list<Light*> lights;
};

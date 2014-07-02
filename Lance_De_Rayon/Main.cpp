// Lance_De_Rayon.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "BmpExporter.h"
#include "Scene.h"
#include "Renderer.h"
#include "Object3D.h"
#include "Triangle.h"
#include "primitives.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Camera* camera = &Camera();
	camera->position.x = 0;
	camera->position.y = 0;
	camera->position.z = 0;
	camera->viewPort.x = 240;
	camera->viewPort.y = 240;
	camera->focalDistance=100;
	camera->fogDistance=150;

	Scene* mainScene = new Scene(*camera);

	for(int i=0;i<=3;i++)
	{
		//for(int j=0;j<4;j++)
		{
			Color8 green; green.setColor(0, 255, 0, 255);
			Color8 red; red.setColor(255, 0, 0, 255);
			Color8 blue; blue.setColor(0, 0, 255, 255);
			Color8 white; white.setColor(255, 255, 255, 255);
			Vertice*v1=new Vertice(0, 0, 0, green);
			Vertice*v2=new Vertice(0, 50, 0, red);
			Vertice*v3=new Vertice(50, 0, 0, blue);

			Triangle* t = new Triangle(*v1, *v2, *v3);
			std::list<Triangle> tris;
			tris.push_back(*t);
			Object3D* triangle = new Object3D(MESH, tris, Vector3(i*50-50*2, 40, 20));
			//triangle->rotate(-PI/8*(i), 0, 0);
			//mainScene->addObject(triangle);
			
			/*Color8* yellow = &Color8(i*55, 255, 255, 255);
			Sphere* cube2 = &Sphere(20, &Vertice(i*30, 66, 0, *yellow));
			//cube2->scale(&Vector3(1, 2, 1));
	
			mainScene->addObject((Object3D*)cube2);*/
		}
	}

	Color8 white; white.setColor(255, 255, 255, 255);
	Object3D* plane = new Object3D(MESH, getPlane(30, white), Vector3(0, 0, 0));
	plane ->rotate(PI/2, 0, 0);
	//mainScene->addObject(plane);

	Color8 color2; color2.setColor(0, 0, 255, 255);
	Sphere* sphere = new Sphere(40,&Vertice(30, 30, 30, white));
	mainScene->addObject((Object3D*)sphere);

	Sphere* sphere2 = new Sphere(40,&Vertice(-30, 30, 60, white));
	mainScene->addObject((Object3D*)sphere2);

	Sphere* sphere6 = new Sphere(60,&Vertice(0, 0, 60, Color8(255, 0, 0, 255)));
	mainScene->addObject((Object3D*)sphere6);

	Cylinder* sphere3 = new Cylinder(&Vector3(0, 20, 50), &Vector3(0, 20, 0), 20, &Color8(255, 0, 0, 255));
	//mainScene->addObject((Object3D*)sphere3);
	
	Cylinder* sphere5 = new Cylinder(&Vector3(0, 0, 0), &Vector3(10, 30, 20), 10, &color2);
	//mainScene->addObject((Object3D*)sphere5);
	
	Cylinder* sphere4 = new Cylinder(&Vector3(-50, 0, 20), &Vector3(0, 0, 30), 20, &color2);
	//mainScene->addObject((Object3D*)sphere4);

	Light* light = new Light(DIRECTIONAL, Vector3(), Color8(255, 255, 255, 255), Vector3(1, 0, 0));
	//mainScene->addLight(light);

	Light* light2 = new Light(DIRECTIONAL, Vector3(), Color8(255, 255, 255, 255), Vector3(1, 1, 0));
	mainScene->addLight(light2);

	Renderer* renderer = new Renderer(*mainScene);
	ppm_image testImage = renderer->render(PERSPECTIVE);

	BmpExporter* exporter = new BmpExporter("test.bmp");
	
	exporter->export2(&testImage);

	return 0;
}


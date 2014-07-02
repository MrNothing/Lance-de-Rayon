#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(void)
{

}

Renderer::Renderer(Scene scene)
{
	mainScene = scene;
}

Renderer::~Renderer(void)
{
}

ppm_image Renderer::render(RenderMode mode)
{
	ppm_image frame;
	frame.width = mainScene.getCamera().viewPort.x;
	frame.height = mainScene.getCamera().viewPort.y;
	frame.size = frame.width*frame.height;
	frame.data=NULL;

	Color8* result = new Color8[frame.width*frame.height];

	int cameraSize = mainScene.getCamera().viewPort.x*mainScene.getCamera().viewPort.y;
	int cameraWidth = mainScene.getCamera().viewPort.x;
		
	Vector3 focalCenter = mainScene.getCamera().position+Vector3(0,0,-mainScene.getCamera().focalDistance);
		
	for(int i=0; i<cameraSize;i++)
	{
		if(i%cameraWidth*2==0)
			printf("Rendering... %f percent\n", floor(i/(mainScene.getCamera().viewPort.x*mainScene.getCamera().viewPort.y)*100));

		Vector3 point = Vector3();
		point.x = mainScene.getCamera().position.x-mainScene.getCamera().viewPort.x/2+i%cameraWidth;
		point.y = mainScene.getCamera().position.y-mainScene.getCamera().viewPort.y/2+_CMATH_::floor(i/cameraWidth);
		point.z = mainScene.getCamera().position.z-10;

		result[i] = Color8(40,40,40,0);

		Ray ray;
		if(mode==ISOMETRIC)
		{
			ray.origin = point;
			ray.dir = Vector3(0,0,1);
		}
		else
		{
			ray.origin = point;
			ray.dir = focalCenter-point;
		}

		float collision = -1;
		float lastCollisionDistanceWithCam;

		std::list<Object3D*> objects = mainScene.getObjects();
		for(std::list<Object3D*>::iterator it = objects.begin(); it != objects.end(); it++) 
		{
			if((**it).getPosition().getDistance(point)<(**it).getAvgScale()*2)
			{
				switch ((**it).getType())
				{
					case MESH:
					{
						std::list<Triangle> tris = (**it).getTrianglesWithGlobalPosition();
						for(std::list<Triangle>::iterator it2 = tris.begin(); it2 != tris.end(); it2++) 
						{
							Color8 color;

							Vector3 hitPoint;
							//if(collision2D((*it2).vertices, point))
							if(rayCast(ray,*it2, &hitPoint))
							{
								bool proceed = false;
								if(collision<0)
									proceed = true;
								else
								{
									if(hitPoint.getDistance(point)<lastCollisionDistanceWithCam)
									{
										proceed = true;
									}
								}
							
								if(proceed==true)
								{
									//printf(hitPoint.toString().c_str());
								
									lastCollisionDistanceWithCam = hitPoint.getDistance(point);

									float fog = (1-(lastCollisionDistanceWithCam/mainScene.getCamera().fogDistance));

									if(fog<0)
										fog=0;

									if(fog>1)
										fog=1;

									Color8 vertexColor =  (*it2).getColorFromPoint(hitPoint);

									if(fog>0)
									vertexColor = vertexColor*fog;

									Vertice luminosity = getGlobalDirectionalLightIntensity(&(*it2).getNormal(), 1);

									color = vertexColor*(1-luminosity.getColor().sizeNoAlpha()/255);

									color = color+luminosity.getColor()*(luminosity.getColor().sizeNoAlpha()/255);

									color = vertexColor*luminosity.x;

									/*if(vertexColor.a<255)
									{
										if(collision==0)
										{
											result[i] = color*(vertexColor.a/255);
										}
										else
										{
											result[i] = frame.data[i]*0.5+color*((vertexColor.a/255)*0.5);
										}
									}
									else*/
										result[i] = color;
								}

								collision=1;
							}
						}

						break;
					}

					default:
					{
						Color8 color;
						Color8 primitiveColor;

						Vector3 hitPoint;
						Vector3 normal;

						bool hasHit=false;

						switch ((**it).getType())
						{
							case PRIMITIVE_SPHERE:
							{
								primitiveColor = static_cast<Sphere*>(*it)->getColor();
								hasHit=rayCast(ray, *(static_cast<Sphere*>(*it)), &hitPoint, &normal);
								break;
							}
							case PRIMITIVE_CYLINDER:
							{
								primitiveColor = static_cast<Cylinder*>(*it)->getColor();
								hasHit=rayCast(ray, *(static_cast<Cylinder*>(*it)), &hitPoint, &normal);
								break;
							}
							case PRIMITIVE_CONE:
							{
								primitiveColor = static_cast<Cone*>(*it)->getColor();
								hasHit=rayCast(ray, *(static_cast<Cone*>(*it)), &hitPoint, &normal);
								break;
							}
						}

						if(hasHit)
						{
							bool proceed = false;
							if(collision<0)
								proceed = true;
							else
							{
								if(hitPoint.getDistance(point)<lastCollisionDistanceWithCam)
								{
									proceed = true;
								}
							}
							
							if(proceed==true)
							{
								lastCollisionDistanceWithCam = hitPoint.getDistance(point);

								float fog = (1-((lastCollisionDistanceWithCam)/mainScene.getCamera().fogDistance));

								if(fog<0)
									fog=0;

								if(fog>1)
									fog=1;

								if(fog>0)
									primitiveColor = primitiveColor*fog;

								Vertice luminosity = getGlobalDirectionalLightIntensity(&normal, 5);

								color = primitiveColor*(1-luminosity.getColor().sizeNoAlpha()/255);

								color = color+luminosity.getColor()*(luminosity.getColor().sizeNoAlpha()/255);

								color = primitiveColor*luminosity.x;

								result[i] = color;
							}

							collision=1;
						}
							
						break;
					}
				}
			}
			else
			{
				if(collision<0)
				{
					Color8 color;color.setColor(40,40,40,0);
					result[i] = color;
				}
			}
		}
	}
	
	frame.data = result;

	return frame;
}

AffineFunction getAffineFunctionFrom2Points(Segment ab)
{
	//get a=(xb-xa/yb-ya)
	AffineFunction function;
	function.a = (ab.end.x-ab.start.x)/(ab.end.y-ab.start.y);

	//get b=-ax-y
	//for point A we apply this equation:
	function.b = -ab.start.x*function.a-ab.start.y;

	return function;
}

Vector2 getIntersectionBetweenTwoSegments(Segment ab, Segment cd)
{
	AffineFunction func1 = getAffineFunctionFrom2Points(ab);
	AffineFunction func2 = getAffineFunctionFrom2Points(cd);

	Vector2 intersection;
	
	intersection.x = (func2.b-func1.b)/(func1.a-func2.a);
	intersection.y = func1.getY(intersection.x);

	return intersection;
}

 bool Renderer::rayCast(Ray r, Triangle T, Vector3* I)
 { 
	 return T.rayCast(r, I);
 }

 bool Renderer::rayCast(Ray r, Sphere s, Vector3* I, Vector3* N)
 { 
	float t;
	if(s.intersects(r, &t))
	{
		*I = r.origin+r.dir*t;
		*N = s.getPosition()-*I;

		return true;
	}
	else
	{
		return false;
	}
 }

 bool Renderer::rayCast(Ray r, Cone c, Vector3* I, Vector3* N)
 { 
	return c.intersects(r, I, N);
 }

  bool Renderer::rayCast(Ray r, Cylinder c, Vector3* I, Vector3* N)
 { 
	return c.intersects(r, I, N);
 }

/*
	This tests collsion from a ray over the whole scene (used for shadows, refletions...)
*/
 bool Renderer::rayCast(Ray r, Vertice* hitPoint)
 {
	return NULL;
 }

bool Renderer::collision2D(std::list<Vertice> tab, Vector3 start)
{
	int i=0;
	int nbp = tab.size();

	for(std::list<Vertice>::iterator it = tab.begin(); it != tab.end(); it++) 
	{

		Vector3 A = *it;
		Vector3 B;
		if (i==nbp-1) 
			B = *tab.begin();
		else    
		{
			it++;
			B = *it;
			it--;
		}
		Vector2 D,T;
		D.x = B.x - A.x;
		D.y = B.y - A.y;
		T.x = start.x - A.x;
		T.y = start.y - A.y;
		float d = D.x*T.y - D.y*T.x;

		if (d>=0)
			return false; 

		i++;
	}
  return true; 
}

Vertice Renderer::getGlobalDirectionalLightIntensity(Vector3* normal, float compatibility)
{
	std::list<Light*> lights = mainScene.getLights();

	if(lights.size()>0)
	{
		float totalItensity = 0;
		Color8 finalLightColor = Color8();
		
		for(std::list<Light*>::iterator it = lights.begin(); it != lights.end(); it++) 
		{
			if((**it).getType()==DIRECTIONAL)
			{
				float intensity = dot((*normal).normalized(), (**it).getDirection().normalized())/lights.size()*compatibility;
				
				if(intensity>1)
					intensity=1;
				if(intensity<=0)
					intensity=0;

				finalLightColor = finalLightColor+(**it).getColor()*intensity;

				if(totalItensity<intensity)
				{
					totalItensity = intensity;
				}
			}
		}
		
		return Vertice(totalItensity, 0, 0, finalLightColor);
	}
	else
	{
		return Vertice();
	}
}

#include <iostream>
#include <iostream>
#include <math.h>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "PedestrianRenderer.h"

extern glm::mat4 MVP,View,Projection;

using namespace std;
class Pedestrian
{
	private:
		int id;		
	public:
		GLfloat px,py;		
		GLfloat vx,vy;
		GLfloat ax,ay;
		void draw();
		void destroy();
		void clearForces();
		Pedestrian(int PID, GLfloat PX, GLfloat PY);
		Pedestrian(){};
    	PedestrianRenderer* renderer;
};

Pedestrian::Pedestrian(int PID, GLfloat PX, GLfloat PY)
{
	id = PID;
	px = PX;
	py = PY;
	vx = 0.0f;
	vy = 0.0f;
	ax = 0.0f;
	ay = 0.0f;
	renderer = new PedestrianRenderer();
}

void Pedestrian::clearForces()
{
	ax = 0;
	ay = 0;
}


void Pedestrian::draw()
{	
	vx += ax;
	vy += ay;
	if(vx >   1.6)
		vx =  1.6;
	if(vx < - 1.6)
		vx =- 1.6;
	if(vy >   1.6)
		vy =  1.6;
	if(vy < - 1.6)
		vy =- 1.6;
	px += vx;
	py += vy;	
	glm::mat4 Model;
	Model = glm::translate(Model, glm::vec3(px, py, 0.0f));	
	renderer->draw(Model);
}

void Pedestrian::destroy()
{
	renderer->clearBuffers();
}


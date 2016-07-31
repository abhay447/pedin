#include <iostream>
#include <iostream>
#include <math.h>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "WallRenderer.h"

extern glm::mat4 MVP,View,Projection;

using namespace std;
class Wall
{
	private:
		int id;		
	public:
		GLfloat cx,cy;
		GLfloat length;
		GLfloat nx,ny;
		GLfloat netForce;
		int collisionCount;
		void draw();
		void destroy();
		void clearForces();
		Wall(int WID, GLfloat CX,GLfloat CY,GLfloat NX,GLfloat NY,GLfloat LENGTH);
    	WallRenderer* renderer;
};

Wall::Wall(int WID, GLfloat CX,GLfloat CY,GLfloat NX,GLfloat NY,GLfloat LENGTH )
{
	id=WID;
	cx = CX;
	cy = CY;
	nx = NX;
	ny = NY;
	length   = LENGTH;
	renderer = new WallRenderer(length);
	netForce = 0;
}

void Wall::clearForces()
{
	netForce = 0;
	collisionCount = 0;
}


void Wall::draw()
{
	glm::mat4 Model;
	Model = glm::translate(Model, glm::vec3(cx, cy, 0.0f));
	Model = glm::rotate(Model, GLfloat(atan(-nx/ny)), glm::vec3(0, 0, 1));
	renderer->draw(Model);
}

void Wall::destroy()
{
	renderer->clearBuffers();
}


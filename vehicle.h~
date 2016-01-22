#include <iostream>
#include <iostream>
#include <math.h>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "renderer.h"

extern glm::mat4 MVP,View,Projection;
float vWIDTH=0.5f,vLENGTH=0.5f;
using namespace std;
class vehicle
{
	private:
		static GLfloat vertices[12];
    	static GLuint indices[6];
	public:
		string name;
		GLuint VBO,VAO,EBO;
		vehicle(string vName,glm::vec3 Position,float vSpeed);
		void showVehicle();
		Renderer* renderer;
		glm::vec3 vPosition;
		float speed,normalSpeed,acceleration;
};



vehicle::vehicle(string vName,glm::vec3 Position,float vSpeed)
{
	renderer = new Renderer(1.8f,4.0f);
	name=vName;
	vPosition = Position;
	speed = vSpeed;
}

void vehicle::showVehicle()
{
    glm::mat4 MVP,Model;
    vPosition.x += speed*0.001f;
    Model = glm::translate(Model, vPosition);
    renderer->draw(Model);
}



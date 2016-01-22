#include <iostream>
#include <math.h>
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// GLFW
#include <GLFW/glfw3.h>

extern glm::vec3 camPosition;
//extern GLFWwindow* window;

using namespace std;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	float camHeight=camPosition.z;
	if(camHeight<=990 && yoffset<0)
		camHeight+=10;
	if(camHeight>=20 && yoffset>0)
		camHeight-=10;
	camPosition.z=camHeight;	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_RIGHT && camPosition.x<990)
    {
    	camPosition.x += 10;
    }
    else if (key == GLFW_KEY_LEFT && camPosition.x>-990)
    {
    	camPosition.x -= 10;
    }
    else if (key == GLFW_KEY_KP_ADD && camPosition.z>20)
    {
    	camPosition.z -= 10;
    }
    else if (key == GLFW_KEY_KP_SUBTRACT && camPosition.z<990)
    {
    	camPosition.z += 10;
    }
}



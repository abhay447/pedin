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
	if(camHeight<=9900 && yoffset<00)
		camHeight+=100;
	if(camHeight>=200 && yoffset>00)
		camHeight-=100;
	camPosition.z=camHeight;	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_RIGHT && camPosition.x<9900)
    {
    	camPosition.x += 100;
    }
    else if (key == GLFW_KEY_LEFT && camPosition.x>-9900)
    {
    	camPosition.x -= 100;
    }
    else if (key == GLFW_KEY_KP_ADD && camPosition.z>200)
    {
    	camPosition.z -= 100;
    }
    else if (key == GLFW_KEY_KP_SUBTRACT && camPosition.z<9900)
    {
    	camPosition.z += 100;
    }
    else if (key == GLFW_KEY_UP)
    {
    	camPosition.y += 100;
    }
    else if (key == GLFW_KEY_DOWN)
    {
    	camPosition.y -= 100;
    }
    
}



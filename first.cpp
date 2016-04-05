#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>

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


#include "windowCreater.h"
#include "SocialForce.cpp"
#include "Environment.cpp"
glm::mat4 View,Projection;
glm::vec3 camPosition;
vector<Wall> myWalls;
vector<Pedestrian> myPeds;
int main()
{
    createWindow();
    glViewport(0, 0, WIDTH, HEIGHT);
       
    CreateMap();
    AddAgents();
	
    Projection = glm::perspective(glm::radians(45.0f), (float) 1300 / 800, 0.1f, 10000.0f);
	camPosition = glm::vec3(50,70,3000);
	
    while (!glfwWindowShouldClose(window))
    {
    	glfwPollEvents();
    	View = glm::lookAt(
                 camPosition, // Camera position
                glm::vec3(camPosition.x,camPosition.y,0), // Camera target
                glm::vec3(0,1,0)  // Camera up direction
                );
                
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if(myPeds.size()==0)
        	break;
        for(int i=0;i<myPeds.size();i++)
        	myPeds[i].clearForces();
        ApplyTargetAttractionForces();
        ApplyPedestrianRepulsionForces();
        ApplyWallRepulsionForces();

        clearPedestrians();
        for(int i=0;i<myPeds.size();i++)
        	myPeds[i].draw();
        for(int i=0;i<myWalls.size();i++)
        	myWalls[i].draw();
        glfwSwapBuffers(window);
    }
    
	for(int i=0;i<myPeds.size();i++)
        	myPeds[i].destroy();
	for(int i=0;i<myWalls.size();i++)
       	myWalls[i].destroy();
    glfwTerminate();
    return 0;
}


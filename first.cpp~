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

#include "windowCreater.h"
#include "vehicle.h"
#include "collisions.h"
#include "roads.h"

glm::mat4 View,Projection;
glm::vec3 camPosition;
vector<vehicle> allVehicles;
vector<lane> allLanes;

int main()
{
    createWindow();
    glViewport(0, 0, WIDTH, HEIGHT);
    for(int i=0;i<7;i++)
    {
		vehicle myVehicle("Alto"+to_string(i),glm::vec3(-70*i+5,0.0f,0.0f),pow(i,2));
		allVehicles.push_back(myVehicle);
	}
	
	for(int i=0;i<3;i++)
    {
		lane myLane(i);
		allLanes.push_back(myLane);
	}
	
	//Get matrix's uniform location and set matrix
    Projection = glm::perspective(glm::radians(45.0f), (float) 1300 / 800, 0.1f, 10000.0f);
	camPosition = glm::vec3(0,0,200);                
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
        
        for(int i=0;i<3;i++)
    	{
			allLanes[i].draw();
		}
        
        if(allVehicles.size()>1)
        	checkCollsions();
        for(int i=0;i<allVehicles.size();i++)
        	allVehicles[i].showVehicle();
        	
        glfwSwapBuffers(window);
    }
    
    for(int i=0;i<allVehicles.size();i++)
    	allVehicles[i].renderer->clearBuffers();
    
    for(int i=0;i<3;i++)
    	allLanes[i].clearBuffers();

    glfwTerminate();
    return 0;
}


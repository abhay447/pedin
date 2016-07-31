#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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
int main(int argc, char* argv[])
{
	clock_t begin = clock(),now,end;
    double elapsed_secs=0;
    createWindow();
    glViewport(0, 0, WIDTH, HEIGHT);       
    CreateMap();
    int numAgents = 100;
    if(argc>1)
    {
        numAgents = atoi(argv[1]);        
    }    
    AddAgents(numAgents);            
	
    Projection = glm::perspective(glm::radians(45.0f), (float) 1300 / 800, 0.1f, 10000.0f);
	camPosition = glm::vec3(50,70,3000);
	
    while (!glfwWindowShouldClose(window))
    {
        now = clock();
		elapsed_secs = double(now - begin) / CLOCKS_PER_SEC;
		
    	glfwPollEvents();
    	View = glm::lookAt(
                 camPosition, // Camera position
                glm::vec3(camPosition.x,camPosition.y,0), // Camera target
                glm::vec3(0,1,0)  // Camera up direction
                );
                
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        cout<<"\r"<<setfill(' ') << setw(3)<<myPeds.size()<<" : Pedestrians remaining ";
        if(myPeds.size()==0)
        	break;
        for(int i=0;i<myPeds.size();i++)
        	myPeds[i].clearForces();
        for(int i=0;i<myWalls.size();i++)
        	myWalls[i].clearForces();
        ApplyTargetAttractionForces();
        ApplyPedestrianRepulsionForces();
        ApplyWallRepulsionForces();

        clearPedestrians();
        for(int i=0;i<myPeds.size();i++)
        	myPeds[i].draw();
        for(int i=0;i<myWalls.size();i++)
        	myWalls[i].draw();
                
		writeWallForces(elapsed_secs);
        glfwSwapBuffers(window);
    }
    
	for(int i=0;i<myPeds.size();i++)
        	myPeds[i].destroy();
	for(int i=0;i<myWalls.size();i++)
       	myWalls[i].destroy();
    glfwTerminate();
    end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout<<endl<<"Elapsed time "<<elapsed_secs<<endl;
	cout<<numAgents<<","<<elapsed_secs<<endl;
    return 0;
}


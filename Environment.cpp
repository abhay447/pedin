#include <iostream>
extern vector<Wall> myWalls;
extern vector<Pedestrian> myPeds;

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void CreateMap()
{
	myWalls.push_back(Wall(0, 500.0f, 000.0f, 0.0f, 1.0f, 1000.0f));
	myWalls.push_back(Wall(1,1000.0f, 320.5f,-1.0f, 0.0f, 650.0f));
	myWalls.push_back(Wall(2,1000.0f,1070.5f,-1.0f, 0.0f, 650.0f));
	myWalls.push_back(Wall(3, 500.0f,1400.0f, 0.0f,-1.0f,1000.0f));
	myWalls.push_back(Wall(4, 000.0f, 700.0f, 1.0f, 0.0f,1400.0f));
}

void AddAgents()
{	
    for(int i=0;i<100;i++)
    {
    	myPeds.push_back(Pedestrian(i, RandomFloat(20.0f,980.0f),RandomFloat(20.0f,1380.0f)));
    }
          
}


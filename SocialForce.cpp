#include <iostream>
#include <fstream>
#include <string>

#include "Pedestrian.cpp"
#include "Wall.cpp"
#include "WallForce.cpp"
#include "PedestrianForce.cpp"
#include "TargetForce.cpp"


#define _USE_MATH_DEFINES

using namespace std;
extern vector<Wall> myWalls;
extern vector<Pedestrian> myPeds;

float getDirection(float a, float b)
{
	 if(a>=b)
	 	return 1.0f;
	 else
	 	return -1.0f;
}

void ApplyWallRepulsionForces()
{
	for(int i=0;i<myPeds.size();i++)
	{
		for(int j=0;j<myWalls.size();j++)
		{
			float force = 0.0f;
			if(inWallForceZone(myWalls[j],myPeds[i]) == -1)	//wall collision
			{
				force = getWallRepelMag(myWalls[j],myPeds[i]);//10.0f;
				myPeds[i].px += 2.5*myWalls[j].nx;
				myPeds[i].py += 2.5*myWalls[j].ny;
				myWalls[j].netForce += fabs(80.0*force);
				myWalls[j].collisionCount += 1;
			}
			else if(inWallForceZone(myWalls[j],myPeds[i]) == 1)	//wall repulsion
			{
				force = getWallRepelMag(myWalls[j],myPeds[i]);
			}
			myPeds[i].ax += force*myWalls[j].nx;
			myPeds[i].ay += force*myWalls[j].ny;			
		}
	}
}

void ApplyPedestrianRepulsionForces()
{

	for(int i=0;i<myPeds.size()-1;i++)
	{
		for(int j=i+1;j<myPeds.size();j++)
		{
			float forceMagnitude = 0.0f;
			float pedDistance = pow(pow((myPeds[i].px-myPeds[j].px),2) + pow((myPeds[i].py-myPeds[j].py),2),0.5f);
			if(pedDistance<90)	//pedestrian collision
			{
				forceMagnitude = 15.0f;
				pedCollision(&myPeds.at(i),&myPeds.at(j));
			}
			else if(pedDistance<200)	//pedestrian repulsion
			{
				forceMagnitude = getPedRepelMag(myPeds[i],myPeds[j]);
			}
			float cx,cy;
			cx = (myPeds[i].px + myPeds[j].px)/2;
			cy = (myPeds[i].py + myPeds[j].py)/2;
			myPeds[i].ax +=  forceMagnitude*fabs(cos(atan((myPeds[i].py-cy)/(myPeds[i].px-cx))*180*M_1_PI))*getDirection(myPeds[i].px,cx);
			myPeds[i].ay +=  forceMagnitude*fabs(sin(atan((myPeds[i].py-cy)/(myPeds[i].px-cx))*180*M_1_PI))*getDirection(myPeds[i].py,cy);
			myPeds[j].ax +=  forceMagnitude*fabs(cos(atan((myPeds[j].py-cy)/(myPeds[j].px-cx))*180*M_1_PI))*getDirection(myPeds[j].px,cx);
			myPeds[j].ay +=  forceMagnitude*fabs(sin(atan((myPeds[j].py-cy)/(myPeds[j].px-cx))*180*M_1_PI))*getDirection(myPeds[j].py,cy);
		}
	}
}


void ApplyTargetAttractionForces()
{
	for(int i=0;i<myPeds.size();i++)
	{
		float targetDistance = (pow((myPeds[i].px-1000.0f),2) + pow((myPeds[i].py-700.0f),2));
		float forceMagnitude = -getAttractionMagnitude(1000.0f,700.0f,myPeds[i]);
		myPeds[i].ax += -forceMagnitude*fabs(cos(atan((myPeds[i].py-700.0f)/(myPeds[i].px-1000.0f))*180/3.14))*getDirection(myPeds[i].px,1000.0f);
		myPeds[i].ay += -forceMagnitude*fabs(sin(atan((myPeds[i].py-700.0f)/(myPeds[i].px-1000.0f))*180/3.14))*getDirection(myPeds[i].py,700.0f);
	}
}

void clearPedestrians()
{
	for(int i=0;i<myPeds.size();i++)
	{
		if(myPeds[i].px >= 1000.0f || myPeds[i].px <= 0.0f || myPeds[i].py >= 1400.0f || myPeds[i].py <= 0.0f)
		{
			myPeds[i].destroy();
			myPeds.erase(myPeds.begin()+i);
		}
	}
}

void writeWallForces(double time)
{
	for(int i=0;i<myWalls.size();i++)
	{
		int passivePed = myPeds.size()-myWalls[i].collisionCount;
		ofstream outfile;
		outfile.open("forceStats/"+to_string(i)+".csv", std::ios_base::app);		
		outfile << time<<","<<myWalls[i].collisionCount<<","<<passivePed<<","<<myWalls[i].netForce<<"\n";
	}
}





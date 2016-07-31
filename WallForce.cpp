#include <iostream>
#include "math.h"
#define WallSpeedCoeff 0.00846
#define WallAccelCoeff 0.02201
#define WallDistCoeff  0.03095
using namespace std;
int inWallForceZone(Wall myWall,Pedestrian myPed)
{	
	float alongWall = abs((myPed.px - myWall.cx)*myWall.ny - (myPed.py - myWall.cy)*myWall.nx);
	float perpWall  = abs((myPed.px - myWall.cx)*myWall.nx + (myPed.py - myWall.cy)*myWall.ny);
	if(perpWall > 80)
		return 0;
	if(alongWall > myWall.length/2)
		return 0;
	if(perpWall < 80)
		return -1;
	return 1;
}

float getWallRepelMag(Wall myWall, Pedestrian myPed)
{
	float perpWall  = fabs((myPed.px - myWall.cx)*myWall.nx + (myPed.py - myWall.cy)*myWall.ny)/100.0f;
	float accelPerp = fabs(myPed.ax*myWall.nx + myPed.ay*myWall.ny)/100.0f;
	float speedAlong= fabs(myPed.vx*myWall.ny - myPed.ay*myWall.nx)/100.0f;
	float force     = (WallDistCoeff*exp(-perpWall) + WallAccelCoeff*accelPerp + WallSpeedCoeff*speedAlong);
	return force*100;
}


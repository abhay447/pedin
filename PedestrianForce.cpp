#include <iostream>
#include "math.h"
#define _USE_MATH_DEFINES
#define PedSpeedCoeff 0.01225
#define PedAccelCoeff 0.03188
#define PedDistCoeff  0.04264
using namespace std;

float getPedRepelMag(Pedestrian ped1, Pedestrian ped2)
{
	float pedDistance = pow(pow((ped1.px-ped2.px),2) + pow((ped1.py-ped2.py),2),0.5f)/100.0;
	float speedAlong  = ped1.vx*(ped2.px - ped1.px)    + ped1.vy*(ped2.py - ped1.py);
	speedAlong       += ped2.vx*(ped2.px - ped1.px)    + ped2.vy*(ped2.py - ped1.py);
	speedAlong       = fabs(speedAlong)/pow(pow( (ped2.px - ped1.px),2) + pow((ped2.py - ped1.py),2),0.5f)/100;
	float AccelPerp  = ped1.ax*(ped2.py - ped1.py)    - ped1.vy*(ped2.px - ped1.px);
   	AccelPerp        = ped2.ax*(ped2.py - ped1.py)    - ped2.vy*(ped2.px - ped1.px);
	AccelPerp        = fabs(AccelPerp)/pow(pow( (ped2.px - ped1.px),2) + pow((ped2.py - ped1.py),2),0.5f)/100;
	float force      = (PedDistCoeff*exp(-pedDistance) + PedAccelCoeff*AccelPerp + PedSpeedCoeff*speedAlong);
	return force*100;	
}


void pedCollision(Pedestrian *ped1,Pedestrian *ped2)
{	
	float speed1Perp  = -ped1->vx*(ped2->py - ped1->py)    + ped1->vy*(ped2->px - ped1->px);
	speed1Perp       /=  pow(pow( (ped2->px - ped1->px),2) + pow((ped2->py - ped1->py),2),0.5f);
	float speed2Perp  = -ped2->vx*(ped2->py - ped1->py)    - ped2->vy*(ped2->px - ped1->px);
	speed2Perp       /=  pow(pow( (ped2->px - ped1->px),2) + pow((ped2->py - ped1->py),2),0.5f);
	float v1x         =  speed1Perp *cos(atan(-(ped2->px - ped1->px)/(ped2->py - ped1->py)));
	float v1y         =  speed1Perp *sin(atan(-(ped2->px - ped1->px)/(ped2->py - ped1->py)));
	float v2x         =  speed2Perp *cos(atan(-(ped2->px - ped1->px)/(ped2->py - ped1->py)));
	float v2y         =  speed2Perp *sin(atan(-(ped2->px - ped1->px)/(ped2->py - ped1->py)));
	ped1->vx           = v1x;
	ped1->vy           = v1y;
	ped2->vx           = v2x;
	ped2->vy           = v2y;
	return ;
}


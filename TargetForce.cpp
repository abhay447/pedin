#include <iostream>
#include "math.h"
#define VeloCoeff   0.08824453
#define StableCoeff -0.38086628
#define DistCoeff    0.03996966
using namespace std;

float getAttractionMagnitude(float tx, float ty, Pedestrian myPed)
{
	float targetDistance = pow(pow((myPed.px-tx),2) + pow((myPed.py-ty),2),0.5f)/100;
	float accelPerp      = fabs(myPed.ax*(ty-myPed.py) - myPed.ay*(tx-myPed.px))/(pow(pow((tx-myPed.px),2)+pow((ty-myPed.py),2),0.5f)*100);
	float speedAlong     = fabs(myPed.ax*(ty-myPed.py) - myPed.ay*(tx-myPed.px))/(pow(pow((tx-myPed.px),2)+pow((ty-myPed.py),2),0.5f)*100);
	float force          = VeloCoeff*exp(-speedAlong) + StableCoeff*exp(-accelPerp) + DistCoeff*exp(-exp(-targetDistance));
	return 100*force;
}


#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;

extern vector<vehicle> allVehicles;

bool vehicleSorterL2R(const vehicle& lhs, const vehicle& rhs)
{
  return lhs.vPosition.x < rhs.vPosition.x;
}


void checkCollsions()
{
	std::sort(allVehicles.begin(), allVehicles.end(), &vehicleSorterL2R);
	for(int i=0;i<allVehicles.size()-1;i++)
	{
		float inLaneDist=fabs(allVehicles[i+1].vPosition.x - allVehicles[i].vPosition.x);
		if(inLaneDist<=4.0)
		{
			cout<<"deleting "<<allVehicles[i].name<<" and deleting "<<allVehicles[i+1].name<<endl;
			allVehicles.erase(allVehicles.begin()+i);
			allVehicles.erase(allVehicles.begin()+i);
		}
	}
	sort(allVehicles.begin(), allVehicles.end(), &vehicleSorterL2R);
}

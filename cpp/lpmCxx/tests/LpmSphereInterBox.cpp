#include "LpmConfig.h"
#include "LpmTypeDefs.h"
#include "LpmOutputMessage.h"
#include "LpmLogger.h"
#include "LpmEuclideanCoords.h"
#include "LpmSphericalCoords.h"
#include "LpmOctree.h"
#include "LpmCoords.h"
#include "LpmXyzVector.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <numeric>

using namespace Lpm;

int main (int argc, char* argv[])
{
  scalar_type testPoints [20][20][20];
  int pointsContained = 0;
  Sphere sphere(5, 0,0,0);
  Box3d truebox(-1,1,-1,1,-1,1);
  Box3d falsebox(6,10,6,10,-3,3);

  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 20; j++){
      for(int k = 0; k < 20; k++){
	if(j == 0 && k == 0) testPoints[i][j][k] = 1;
	else testPoints[i][j][k] = 0;
      }
    }
  }

  //Check if sphere(radius) intersects box(tree nodes). 
  if(sphere.intersectsBox(sphere,truebox)){
      std::cout<<"Sphere/Box intersection test: passed \n";
  }else std::cout<<"Sphere/Box intersection test: failed\n";

  //Check how many points are within sphere. 
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 20; j++){
      for(int k = 0; k < 20; k++){
	if(testPoints[i][j][k]){
	    if(sphere.containedInSphere(sphere,i,j,k)) pointsContained++;
	  }
	}
      }
    }
  
    if(pointsContained == 5) std::cout<<"Points inside of sphere test: passed\n";
    else std::cout<<"Points inside of sphere test: failed \n";
}
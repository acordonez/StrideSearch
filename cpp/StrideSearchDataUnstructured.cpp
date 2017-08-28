#include "StrideSearch_Config.h"
#include "StrideSearch_TypeDefs.h"
#include "LpmOutputMessage.h"
#include "LpmLogger.h"
#include "LpmEuclideanCoords.h"
#include "LpmSphericalCoords.h"
#include "LpmBox3d.h"
#include "LpmOctree.h"
#include "LpmXyzVector.h"

#include "StrideSearchDataLatLon.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <numeric>

using namespace Lpm;
using namespace StrideSearch;

int main(int argc, char* argv[]){
  const std::string testfilename = "sresa1b_ncar_ccsm3-example.nc";
  std::string file = StrideSearch_TEST_DATA_DIR;
  file += "/";
  file += testfilename;
  std::cout << "looking for file : " << file << std::endl;
  
  const std::string uvarname = "ua";
  const std::string tempvarname = "tas";
  const std::string precipvarname = "pr";
  
  StrideSearchDataLatLon ssData(file);
  const int nMax = ssData.lats.size()*ssData.lons.size();
  //std::shared_ptr<SphericalCoords> sc(new SphericalCoords(nMax));
  std::shared_ptr<SphericalCoords> sc(new SphericalCoords(nMax));
  
  GeometryType geom = sc->geometry();
  std::cout << "geometry: " << geom << std::endl;
  switch (geom){
  case PLANAR_GEOMETRY : {
    std::cout << "planar geometry";
    break;
  }
  case SPHERICAL_SURFACE_GEOMETRY : {
    std::cout << "spherical surface geometry";
  }
  case CARTESIAN_3D_GEOMETRY : {
    std::cout << "Cartesian 3D geometry";
  }
  }
  std::cout << std::endl;
  
  sc->initWithNCData(&ssData);  
  //sc->initRandom();
  
  std::ofstream cfile("octreeSphereCoords.txt");
  sc->writeCoordsCSV(cfile);
  cfile.close();
  
  const scalar_type maxAspectRatio = 2.0;
  
  std::shared_ptr<Tree> tree(new Tree(sc, maxAspectRatio));
  std::cout << tree->infoString();
  
  const int nCoordsPerNode = 20;
  
  tree->buildTree(nCoordsPerNode);
  std::cout << "returned from generateTree:" << std::endl;
  std::cout << "\t nNodes = " << tree->nNodes() << std:: endl;
  std::cout << "\n nRecursiveNodes " << tree->recursiveNNodes() <<std::endl;
  std::cout << "\t treeDepth = " << tree->depth() << std::endl;
  
  std::cout << tree->infoString();
  
  const std::string fname("sphereOctreeUnitTest.vtk");
  std::stringstream ss;
  ss << "nCoords = " << nMax << ", nCoordsPerNode = " << nCoordsPerNode;
  tree->writeToVtk(fname, ss.str());
  tree->sphere = Sphere(2,0,0,0);
  std::cout << "Running radius search..\n";
  tree->radiusSearch();
  std::cout << "Number of points found within radius of " << tree->sphere.radius << ": " << tree->nodes <<"\n";
  tree->nodes = 0;
}


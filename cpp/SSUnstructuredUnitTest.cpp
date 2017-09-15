#include "StrideSearch_Config.h"
#include "StrideSearch_TypeDefs.h"
#include "StrideSearchOctree.h"
#include "StrideSearchBox3d.h"
#include "StrideSearchDataLatLon.h"

using namespace StrideSearch;

int main() {
  const std::string testfilename = "sresa1b_ncar_ccsm3-example.nc";
  std::string file = StrideSearch_TEST_DATA_DIR;
  file += "/";
  file += testfilename;
  std::cout << "looking for file: " << file << std::endl;
  const std::string uvarname = "ua";
  const std::string tempvarname = "tas";
  const std::string precipvarname = "pr";

  StrideSearchDataLatLon ssData(file);

   Box3d unitBox(-1,1,-1,1,-1,1);
   std::cout << "Unit Box : " << unitBox.infoString();
   std::cout << "\tvolume = " << unitBox.volume() << std::endl;
   //std::cout << "\tcentroid = " << unitBox.centroid() << std::endl;
   std::cout << "\tcontains origin ? : " << (unitBox.containsPoint(0.0, 0.0, 0.0) ? "true" : "false") << std::endl;
   std::cout << "\tlongestEdge = " << unitBox.longestEdge() << std::endl;
   std::cout << "\tshortestEdge = " << unitBox.shortestEdge() << std::endl;
   std::cout << "\taspectRatio = " << unitBox.aspectRatio() << std::endl;

   std::vector<Box3d> kids = unitBox.bisectAll();
   for (int i = 0; i < 8; ++i) {
     std::cout << "child " << i << ": " << kids[i].infoString();
   }
   
   Box3d boxCopy(kids[1]);
   std::cout << "BoxCopy " << boxCopy.infoString();
   Box3d boxAssign = boxCopy;
   std::cout << "BoxAssign " << boxAssign.infoString();
	
   std::shared_ptr<Tree> tree(new Tree(ssData.x, ssData.y, ssData.z,1.5));
   //tree.buildTree(5);
   std::cout << "tree info: " << tree->infoString();
   tree->buildTree(1);
   std::cout << "returned from generateTree:" << std::endl;
   std::cout << "\t nNodes = " << tree -> nNodes() << std::endl;
   std::cout << "\t nRecursiveNodes " << tree->recursiveNNodes() << std::endl;
   std::cout << "\t treeDepth = " << tree->depth() << std::endl;
  
   std::cout << tree->infoString();

   //tree->printTree(tree->_root.get());

   tree->sphere = Sphere(20,0,0,0);
   std::cout<<"Running radius search...\n";
   tree->radiusSearch();
   std::cout<<"Number of points found within radius of " << tree->sphere.radius<< ": " << tree->nodes<<"\n";
   tree->nodes = 0;
}

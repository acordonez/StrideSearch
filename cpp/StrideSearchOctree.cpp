#include "StrideSearchOctree.h"
#include <vector>
#include <memory>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cmath>

namespace StrideSearch {

  Tree::Tree(const std::vector<scalar_type> xs, const std::vector<scalar_type> ys, const std::vector<scalar_type> zs, const scalar_type maxRatio, const int prank) : x(xs), y(ys), z(zs), _maxAspectRatio(maxRatio), _depth(0), _nnodes(1) {

    scalar_type minX = *std::min_element(x.begin(), x.end());
    scalar_type minY = *std::min_element(y.begin(), y.end());
    scalar_type minZ = *std::min_element(z.begin(), z.end());
    scalar_type maxX = *std::max_element(x.begin(), x.end());
    scalar_type maxY = *std::max_element(y.begin(), y.end());
    scalar_type maxZ = *std::max_element(z.begin(), z.end());

    Box3d rbox(minX - BOX_PADDING_FACTOR * minX,
	       maxX + BOX_PADDING_FACTOR * maxX,
	       minY - BOX_PADDING_FACTOR * minY,
	       maxY + BOX_PADDING_FACTOR * maxY,
	       minZ - BOX_PADDING_FACTOR * minZ,
	       maxZ + BOX_PADDING_FACTOR * maxZ);

    std::vector<index_type> rinds;
    rinds.reserve(x.size());
    for(index_type i = 0; i < xs.size(); ++i) {
      rinds.push_back(i);
    }

    Node* rparent = NULL;

    _root = std::unique_ptr<Node>(new Node(rbox, rparent, rinds));
  }

  std::string Tree::infoString() const {
    std::stringstream ss;
    ss << "Tree info:" << std::endl;
    ss << "\tnNodes = " << _nnodes << std::endl;
    ss << "\tdepth = " << _depth << std::endl;
    ss << "\tmaxAspectRatio = " << _maxAspectRatio << std::endl;
    ss << _root->infoString();
    return ss.str();
  }

  std::string Node::infoString() const {
    std::stringstream ss;
    ss << "Treenode info: " << std::endl;
    ss << "\tbox: " << box.infoString();
    ss << "\tlevel = " << level << std:: endl;
    ss << "\t&parent = " << (level > 0 ? parent : 0) << std::endl;
    ss << "\thasKids = " << (hasKids() ? "true" : "false") << ", kids.size() = " << kids.size() << std::endl;
    ss << "\tcoordsContained.size() = " << coordsContained.size() << std::endl;
    return ss.str();
  }

  Node::Node(const Box3d& bbox, Node* pparent, const std::vector<index_type>& crdInds) : box(bbox), parent(pparent), coordsContained(crdInds) {
    if(pparent) {
      level = pparent->level + 1;
    }else {
      level = 0;
    }
  }

  void Tree::buildTree(const index_type maxCoordsPerNode) {
    generateTree(_root.get(), maxCoordsPerNode);
    _depth = computeTreeDepth(_root.get());
  }

  void Tree::generateTree(Node* node, const index_type maxCoordsPerNode) {
    int index = 0;
    if (node->coordsContained.size() <= maxCoordsPerNode) {
      return;
    }
    else {
      bool splitDims[3];
      int splitCount = 0;
      const scalar_type edgeThreshold = node->box.longestEdge() / _maxAspectRatio;
      for (int i = 0; i < 3; ++i) {
	if (node->box.edgeLength(i) >= edgeThreshold) {
	  splitDims[i] = true;
	  splitCount += 1;
	}
	else {
	  splitDims[i] = false;
	}
      }
      std::vector<Box3d> kidboxes = node->box.bisectAlongDims(splitDims);
      for (int i = 0; i < kidboxes.size(); ++i) {
	std::vector<index_type> kidcoords;
	kidcoords.reserve(node->coordsContained.size());
	for(index_type j = 0; j < node->coordsContained.size(); ++j) {
	  index = node->coordsContained[j];
	  if (kidboxes[i].containsPoint(x[index],y[index],z[index])) {
	    kidcoords.push_back(node->coordsContained[j]);
	  }
	}
	if(!kidcoords.empty()) {
	  kidcoords.shrink_to_fit();
	  node->kids.push_back(std::unique_ptr<Node>(new Node(kidboxes[i], node, kidcoords)));
	}
      }
      if (node->kids.empty()) {
	//OutputMessage errMsg("All kids are empty, this should't happen.", OutputMessage::errorPriority, "Tree::buildTree");
	//log->logMessage(errMsg);
	return;
      }
      else {
	_nnodes += node->kids.size();
	for(int i = 0; i < node->kids.size(); ++i) {
	  shrinkBox(node->kids[i].get());
	  generateTree(node->kids[i].get(), maxCoordsPerNode);
	}
      }
    }
  }
  void Tree::shrinkBox(Node* node) {
    scalar_type xmin = std::numeric_limits<scalar_type>::max();
    scalar_type xmax = std::numeric_limits<scalar_type>::lowest();
    scalar_type ymin = xmin;
    scalar_type ymax = xmax;
    scalar_type zmin = xmin;
    scalar_type zmax = xmax;
    for(index_type i = 0; i < node->coordsContained.size(); ++i) {
      if(x[i] < xmin) xmin = x[i];
      if(x[i] > xmax) xmax = x[i];
      if(y[i] < ymin) ymin = y[i];
      if(y[i] > ymax) ymax = y[i];
      if(z[i] < zmin) zmin = z[i];
      if(z[i] > zmax) zmax = z[i];
      node->box.xmin = xmin;
      node->box.xmax = xmax;
      node->box.ymin = ymin;
      node->box.ymax = ymax;
      node->box.zmin = zmin;
      node->box.zmax = zmax;
    }
  }

  index_type Tree::recursiveNodeCount(Node* node) const {
    index_type result = 1;
    //result += node->kids.size();
    if(node->hasKids()) {
      for(int i = 0; i < node->kids.size(); ++i) {
	result += recursiveNodeCount(node->kids[i].get());
      }
    }
    return result;
  }

  int Tree::computeTreeDepth(Node* node) const {
    int result = 0;
    if(node->level > result) result = node->level;
    if(node->hasKids()) {
      for(int i = 0; i < node->kids.size(); ++i) {
	result = computeTreeDepth(node->kids[i].get());
      }
    }
    return result;
  }

  bool Sphere::intersectsBox(const Box3d& bbox){
    index_type x,y,z,distance;
    x = std::max(bbox.xmin, std::min(cx,bbox.xmax));
    y = std::max(bbox.ymin, std::min(cy,bbox.ymax));
    z = std::max(bbox.zmin, std::min(cz,bbox.zmax));

    distance = ((x - cx) * (x - cx) +
		(y - cy) * (y - cy) +
		(z - cz) * (z - cz));

    return distance < (radius*radius); 
  }

  bool Sphere::containedInSphere(const scalar_type pointX, const scalar_type pointY, const scalar_type pointZ){
    return (pointX-cx)*(pointX-cx)+(pointY-cy)*(pointY-cy)+(pointZ-cz)*(pointZ-cz)<radius*radius;
  }

  void Tree::radiusSearch()
  {
    radiusSearch(_root.get());
  }
  
  void Tree::radiusSearch(Node* node)
  {
    int index = 0;
      if(sphere.intersectsBox(node->box) && node->nCoords() > 0) {
	for(int i = 0; i < node->nCoords(); i++) {
	  index = node->coordsContained[i];
	  if(sphere.containedInSphere(x[index],y[index],z[index])) {
	    nodes++;
	  }
	}
      return;
      }
      else {
      for(int i = 0; i < node->kids.size(); i++) {
	radiusSearch(node->kids[i].get());
      }
      }
  }
}

#ifndef KDD_RADIUS_H
#define KDD_RADIUS_H

#include "StrideSearchUtilities.h" 
#include "StrideSearch_TypeDefs.h"
#include "nanoflann.hpp"
#include <vector>
#include <string>

namespace StrideSearch{
class kdd_radius
{
 public:
  kdd_radius(std::vector<scalar_type> lat, std::vector<scalar_type> lon);
  void runtest(int radius, double center);
  int treeBuilt = 0;
  struct PointCloud
  {
    struct Point
    {
      scalar_type  x,y,z,vals;
    };
    
    std::vector<Point>  pts;
    
    // Must return the number of data points
    inline size_t kdtree_get_point_count() const { return pts.size(); }
    
    // Returns the distance between the vector "p1[0:size-1]" and the data point with index "idx_p2" stored in the class:
    inline scalar_type kdtree_distance(const scalar_type *p1, const size_t idx_p2,size_t /*size*/) const
    {
      double latA;
      double lonA;
      double latB;
      double lonB;
      const scalar_type d0A = p1[0];
      const scalar_type d1A = p1[1];
      const scalar_type d2A = p1[2];
      const scalar_type d0B = pts[idx_p2].x;
      const scalar_type d1B = pts[idx_p2].y;
      const scalar_type d2B = pts[idx_p2].z;
      XyzToLL(latA,lonA,d0A,d1A,d2A);
      XyzToLL(latB,lonB,d0B,d1B,d2B);
      return sphereDistance(latA,lonA,latB,lonB);
    }
    
    // Returns the dim'th component of the idx'th point in the class:
    // Since this is inlined and the "dim" argument is typically an immediate value, the
    //  "if/else's" are actually solved at compile time.
	inline scalar_type kdtree_get_pt(const size_t idx, int dim) const
    {
      if (dim==0) return pts[idx].x;
      else if (dim==1) return pts[idx].y;
      else return pts[idx].z;
    }
    
    // Optional bounding-box computation: return false to default to a standard bbox computation loop.
	//   Return true if the BBOX was already computed by the class and returned in "bb" so it can be avoided to redo it again.
	//   Look at bb.size() to find out the expected dimensionality (e.g. 2 or 3 for point clouds)
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& /*bb*/) const { return false; }
    
  };

 protected:
  //std::vector<scalar_type> lons;
  //std::vector<scalar_type> lats;
  double* x;
  double* y;
  double* z;
  //int numLat;
  //int numLon;
};
}

#endif

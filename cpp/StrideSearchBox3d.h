#ifndef _STRIDE_SEARCH_BOX_3D_H_
#define _STRIDE_SEARCH_BOX_3D_H_

#include "StrideSearch_Config.h"
#include "StrideSearch_TypeDefs.h"

namespace StrideSearch {
struct Box3d {
  Box3d() : xmin(0.0), xmax(0.0), ymin(0.0), ymax(0.0), zmin(0.0), zmax(0.0) {};

  Box3d(const scalar_type x0, const scalar_type x1, const scalar_type y0, const scalar_type y1, const scalar_type z0, 
	const scalar_type z1) : xmin(x0), xmax(x1), ymin(y0), ymax(y1), zmin(z0), zmax(z1) {};

  inline scalar_type volume() const {return (xmax - xmin) * (ymax - ymin) * (zmax - zmin);}
  inline scalar_type area2d() const {return (xmax - xmin) * (ymax - ymin);}

  inline bool containsPoint(scalar_type x, scalar_type y, scalar_type z) const {return (xmin <= x && x < xmax) &&
                                                                                       (ymin <= y && y < ymax) &&
                                                                                       (zmin <= z && z < zmax);}

  scalar_type longestEdge() const;
  scalar_type shortestEdge() const; 
  scalar_type aspectRatio() const;

  scalar_type edgeLength(const int dim) const;

  std::vector<Box3d> bisectAll() const;
  std::vector<Box3d> bisectAlongDims(const bool* dims) const;

  std::string infoString() const;

  scalar_type radius() const;
  
  scalar_type xmin;
  scalar_type xmax;
  scalar_type ymin;
  scalar_type ymax;
  scalar_type zmin;
  scalar_type zmax;
};
}
#endif

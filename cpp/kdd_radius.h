#ifndef KDD_RADIUS_H
#define KDD_RADIUS_H

#include "StrideSearchUtilities.h"
#include "StrideSearchData_Base.h"
#include "StrideSearchDateTime.h"
#include <vector> 
#include <string>

namespace StrideSearch{
class kdd_radius
{
 public:
  kdd_radius(std::vector<scalar_type> lat, std::vector<scalar_type> lon);
  void runtest();

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

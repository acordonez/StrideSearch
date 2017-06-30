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
  kdd_radius(const StrideSearchData* data);
  void runtest();
  void convertLLToXY();
  void allocateMem();

 protected:
  StrideSearchData* nc_data;
  int numLat;
  int numLon;
  double* x;
  double* y;
  double* z;
  double* vals;
};
}

#endif

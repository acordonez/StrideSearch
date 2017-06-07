#ifndef KDD_RADIUS_H
#define KDD_RADIUS_H

#include "StrideSearchUtilities.h"
#include "StrideSearchData_Base.h"
#include "StrideSearchDateTime.h"
#include "StrideSearchWorkspace.h"
#include <vector> 
#include <string>

class kdd_radius
{
 public:
  kdd_radius(Workspace2D& data, int& nLat, int& nLon);
  void runtest();
  void convertLLToXY();
  void allocateMem();

 protected:
  Workspace2D nc_data;
  int numLat;
  int numLon;
  double* x;
  double* y;
  double* z;
  double* vals;
};

#endif

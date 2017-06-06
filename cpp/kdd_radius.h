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
  kdd_radius(Workspace2D& data);
  void runtest();
  Workspace2D nc_data;
};

#endif

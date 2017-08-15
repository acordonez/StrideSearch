#ifndef _STRIDE_SEARCH_TYPE_DEFS_H_
#define _STRIDE_SEARCH_TYPE_DEFS_H_

#include "StrideSearch_Config.h"
#include <vector>

#ifdef USE_NANOFLANN
#include "nanoflann.hpp"
#endif

namespace StrideSearch {

  class PointCloud;

    /// Real number type
    typedef double scalar_type;
    
    /// Memory index type
    typedef long index_type;

    /// Latitude-Longitude coordinate pair type
    typedef std::pair<scalar_type, scalar_type> ll_coord_type;

    /// Vector of index_type type
    typedef std::vector<index_type> vec_indices_type;
    
#ifdef USE_NANOFLANN
    //#include "kdd_radius.h"

    typedef StrideSearch::PointCloud cloud_type;
    typedef nanoflann::KDTreeSingleIndexAdaptor<nanoflann::L2_Simple_Adaptor<scalar_type, cloud_type > ,cloud_type,3 /* dim */> my_kd_tree_t;
#endif
}

#endif

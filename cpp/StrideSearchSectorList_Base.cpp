#include "StrideSearchUtilities.h"
#include "StrideSearchSectorList_Base.h"
#include "StrideSearchData_Base.h"
#include <vector>
#include <cmath>
#include <memory>
#include <iostream>
#include <sstream>
#include <cassert>

namespace StrideSearch {

SectorList::SectorList(const scalar_type sb, const scalar_type nb, const scalar_type wb, const scalar_type eb, 
    const scalar_type sector_radius_km) : southBnd(sb), northBnd(nb), westBnd(wb), eastBnd(eb), radius(sector_radius_km) 
{
    const scalar_type sector_arc_length(radius / EARTH_RADIUS_KM);
    nStrips = index_type(std::floor( (deg2rad * northBnd - deg2rad * southBnd) / sector_arc_length) + 1);
    lat_stride_deg = (northBnd - southBnd) / (nStrips - 1);

    lon_strides_deg = std::vector<scalar_type>(nStrips, -1.0);
    for (index_type i = 0; i < nStrips; ++i){
        const scalar_type cLat(southBnd + i * lat_stride_deg);
        if (std::abs(std::abs(cLat) - 90.0) > ZERO_TOL) 
            lon_strides_deg[i] = radius / (EARTH_RADIUS_KM * std::cos(deg2rad * cLat)) / deg2rad;
        else
            lon_strides_deg[i] = 360.0;
    }
    
    for (index_type i = 0; i < nStrips; ++i) {
        const scalar_type latI = southBnd + i * lat_stride_deg;
        const index_type nLonsThisStrip(std::ceil((eastBnd - westBnd) / lon_strides_deg[i]));
        for (index_type j = 0; j < nLonsThisStrip; ++j) {
            const scalar_type lonJ = westBnd + j * lon_strides_deg[i];
            sectors.push_back(std::unique_ptr<Sector>(new Sector(latI, lonJ, radius, i)));
        }
    }
}

SectorList::SectorList(const std::vector<ll_coord_type>& centers, const std::vector<scalar_type>& radii) {
    for (index_type i = 0; i < centers.size(); ++i) {
        sectors.push_back(std::unique_ptr<Sector>(new Sector(centers[i].first, centers[i].second, radii[i], -1)));
    }
}

#ifdef USE_NANOFLANN
  void SectorList::fastLinkSectorsToData(const StrideSearchData* data_ptr){
    std::cout<<"NanoFlann connected\n";
  }
#endif

void SectorList::linkSectorsToData(const StrideSearchData* data_ptr) {
    for (index_type sec_i = 0; sec_i < sectors.size(); ++sec_i) {
        for (index_type i = 0; i < data_ptr->lats.size(); ++i) {
           for (index_type j = 0; j < data_ptr->lons.size(); ++j) {
                const scalar_type dist = sphereDistance(sectors[sec_i]->centerLat, sectors[sec_i]->centerLon,
                    data_ptr->lats[i], data_ptr->lons[j]);
                if ( dist <= sectors[sec_i]->radius ) {
                    sectors[sec_i]->data_coords.push_back(ll_coord_type(data_ptr->lats[i], data_ptr->lons[j]));
                    const std::vector<index_type> ind = {i, j};
                    sectors[sec_i]->data_indices.push_back(ind);
                }         
           } 
        }
    }
}


void SectorList::buildWorkspaces(const std::vector<IDCriterion*>& criteria) {
    for (index_type i = 0; i < sectors.size(); ++i) {
        sectors[i]->defineWorkspace(criteria);
        sectors[i]->allocWorkspace(criteria);
    }
}

void SectorList::buildWorkspaces(const std::vector<std::vector<IDCriterion*>>& separate_criteria) {
    assert(separate_criteria.size() == sectors.size());
    for (int i = 0; i < sectors.size(); ++i) {
        sectors[i]->defineWorkspace(separate_criteria[i]);
        sectors[i]->allocWorkspace(separate_criteria[i]);
    }
}

std::vector<ll_coord_type> SectorList::listSectorCenters() const {
    std::vector<ll_coord_type> result;
    for (index_type i = 0; i < sectors.size(); ++i)
        result.push_back(ll_coord_type(sectors[i]->centerLat, sectors[i]->centerLon));
    return result;
}

std::string SectorList::sectorInfoString(const index_type secInd, const bool printAllData) const {
    return sectors[secInd]->infoString(0, printAllData);
}

std::string SectorList::infoString() const {
    std::ostringstream ss;
    ss << "Sector List Record: \n";
    ss << "nSectors = " << nSectors();
    if (lon_strides_deg.size() > 0) {
        ss << "\tnumber of latitude strips = " << nStrips << std::endl;
        ss << "\tlat stride (deg) = " << lat_stride_deg << std::endl;
        ss << "\tlon strides (deg) = ";
        for (index_type i = 0; i < lon_strides_deg.size() - 1; ++i)
            ss << lon_strides_deg[i] << ", ";
        ss << lon_strides_deg[lon_strides_deg.size() - 1] << std::endl;
    }
    
    ss << std::endl << "-------------------" << std::endl;
    return ss.str();
}

}

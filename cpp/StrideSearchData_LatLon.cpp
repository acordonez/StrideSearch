#include "StrideSearchUtilities.h"
#include "StrideSearchData_Base.h"
#include "StrideSearchData_LatLon.h"
#include "StrideSearchWorkspace.h"
#include "kdd_radius.h"
#include <netcdf>
#include <iostream>
#include <sstream>

namespace StrideSearch {

void StrideSearchData_LatLon::initDimensions(){
    netCDF::NcFile file(filename, netCDF::NcFile::read);
    
    netCDF::NcVar latVar(file.getVar("lat"));
    netCDF::NcVar lonVar(file.getVar("lon"));
    
    nLat = latVar.getDim(0).getSize();
    nLon = lonVar.getDim(0).getSize();
    
    scalar_type latArr[nLat];
    scalar_type lonArr[nLon];
    latVar.getVar(latArr);
    lonVar.getVar(lonArr);
      
    lats = std::vector<scalar_type>(&latArr[0], &latArr[0] + nLat);
    lons = std::vector<scalar_type>(&lonArr[0], &lonArr[0] + nLon);
    
   nc_data = Workspace2D(variables, nLat, nLon);
}

void StrideSearchData_LatLon::buildTree(){
  kdd_radius* kdd = new kdd_radius(nc_data, nLat, nLon);
  kdd->runtest();
}

void StrideSearchData_LatLon::getGridDescription(int* gridDescInts) const {
    gridDescInts[0] = nLat;
    gridDescInts[1] = nLon;
}

std::string StrideSearchData_LatLon::basicInfo() const {
    std::stringstream ss;
    ss << "filename = " << filename << std::endl;
    ss << "nTimesteps = " << fileNTimesteps << ", start time = " << time[0] <<
        ", end time = " << time[time.size() - 1] << std::endl;
    ss << "nLat = " << nLat << " == " << lats.size() << ", nLon = " << nLon << " == " << lons.size() << std::endl;
    ss << nc_data.basicInfo(); 
    return ss.str();
}

void StrideSearchData_LatLon::readFullFile(const std::string var)
{
  for(int j = 0; j < 3; j++){
    for(int i = 0; i < nLat; i++){
      read2DDataFromSingle(var,i);
    }
  }
};

void StrideSearchData_LatLon::read2DDataFromSingle(const std::string var, const int latIndex)
{
  for(int i = 0; i < nLon; ++i){
    getDatumValue(var,latIndex,i);
  }
}; 

void StrideSearchData_LatLon::readFullWChunks(const int time_index)
{
  for(int i = 0; i < nLon*3; ++i){
    read2DDataFromTimestep(time_index,0);
  }
};

void StrideSearchData_LatLon::read2DDataFromTimestep(const int time_index, const int level_index){
    netCDF::NcFile file(filename, netCDF::NcFile::read);  
    for (auto& elem : nc_data.data2d) {
        netCDF::NcVar ncv(file.getVar(elem.first));
        std::vector<netCDF::NcDim> dims(ncv.getDims());
        if (dims.size() == 3) {
            std::vector<size_t> readStart;
            readStart.push_back(time_index);
            readStart.push_back(0);
            readStart.push_back(0);
            std::vector<size_t> readCount;
            readCount.push_back(1);
            readCount.push_back(1);
            readCount.push_back(nLon);
        
            for (int i = 0; i < nLat; ++i) {
                readStart[1] = i;
                ncv.getVar(readStart, readCount, elem.second[i]);        
            }
        }
        else if (dims.size() == 4) {
            std::vector<size_t> readStart;
            readStart.push_back(time_index);
            readStart.push_back(level_index);
            readStart.push_back(0);
            readStart.push_back(0);
            std::vector<size_t> readCount;
            readCount.push_back(1);
            readCount.push_back(1);
            readCount.push_back(1);
            readCount.push_back(nLon);
            
            for (int i = 0; i < nLat; ++i) {
                readStart[2] = i;
                ncv.getVar(readStart, readCount, elem.second[i]);
            }
        }
    }
};

double StrideSearchData_LatLon::getDatumValue(const std::string var, const int latInd, const int lonInd) {
    return nc_data[var][latInd][lonInd];
}

Workspace1D StrideSearchData_LatLon::getSectorWorkingData(const std::vector<std::string>& crit_vars, 
        const std::vector<ll_index_type>& dataIndices) {
    Workspace1D result(crit_vars, dataIndices.size());
    for (int key_num = 0; key_num < crit_vars.size(); ++key_num) {
        for (int i = 0; i < dataIndices.size(); ++i) {
            result[crit_vars[key_num]][i] = 
                nc_data[crit_vars[key_num]][dataIndices[i].first][dataIndices[i].second];
        }
    }
    return result;
}

std::vector<ll_coord_type > StrideSearchData_LatLon::getLLCoordsFromIndices(
    const std::vector<ll_index_type>& dataIndices) const {
    
    std::vector<ll_coord_type > result;
    for (int i = 0; i < dataIndices.size(); ++i) {
        result.push_back(ll_coord_type(lats[dataIndices[i].first], lons[dataIndices[i].second]));
    }
    return result;
}

}

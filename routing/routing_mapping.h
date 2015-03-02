#pragma once

#include "osrm2feature_map.hpp"
#include "router.hpp"
#include "osrm_data_facade.hpp"

#include "../indexer/index.hpp"

#include "../3party/osrm/osrm-backend/DataStructures/QueryEdge.h"
#include "../3party/osrm/osrm-backend/DataStructures/RawRouteData.h"

namespace routing
{
typedef OsrmDataFacade<QueryEdge::EdgeData> DataFacadeT;

/// Datamapping and facade for single MWM and MWM.routing file
struct RoutingMapping
{
  DataFacadeT m_dataFacade;
  OsrmFtSegMapping m_segMapping;
  CrossRoutingContextReader m_crossContext;

  ///@param fName: mwm file path
  RoutingMapping(string const & fName, Index const * pIndex);

  ~RoutingMapping();

  void Map();

  void Unmap();

  void LoadFacade();

  void FreeFacade();

  void LoadCrossContext();

  void FreeCrossContext();

  bool IsValid() const {return m_isValid;}

  IRouter::ResultCode GetError() const {return m_error;}

  string GetName() const {return m_baseName;}

  Index::MwmId GetMwmId() const {return m_mwmId;}

private:
  size_t m_mapCounter;
  size_t m_facadeCounter;
  size_t m_crossContextCounter;
  string m_baseName;
  FilesMappingContainer m_container;
  Index::MwmId m_mwmId;
  bool m_isValid;
  IRouter::ResultCode m_error;
};

typedef shared_ptr<RoutingMapping> RoutingMappingPtrT;

//! \brief The MappingGuard struct. Asks mapping to load all data on construction and free it on destruction
class MappingGuard
{
  RoutingMappingPtrT const m_mapping;

public:
  MappingGuard(RoutingMappingPtrT const mapping): m_mapping(mapping)
  {
    m_mapping->Map();
    m_mapping->LoadFacade();
  }

  ~MappingGuard()
  {
    m_mapping->Unmap();
    m_mapping->FreeFacade();
  }
};
}
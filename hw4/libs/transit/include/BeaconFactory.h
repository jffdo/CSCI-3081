#ifndef BEACON_FACTORY_H_
#define BEACON_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "Beacon.h"

/**
 *@brief Beacon Factory to produce Beacons class.
 **/
class BeaconFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for IEntityFactory class.
   **/
  virtual ~BeaconFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif

#ifndef RADIUS_MARKER_FACTORY_H_
#define RADIUS_MARKER_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "RadiusMarker.h"

/**
 *@brief Drone Factory to produce Drones class.
 **/
class RadiusMarkerFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for IEntityFactory class.
   **/
  virtual ~RadiusMarkerFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif

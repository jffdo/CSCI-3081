#include "RadiusMarkerFactory.h"

IEntity* RadiusMarkerFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("radius_marker") == 0) {
    return new RadiusMarker(entity);
  }
  return nullptr;
}

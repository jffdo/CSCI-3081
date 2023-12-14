#include "BeaconFactory.h"

IEntity* BeaconFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("beacon") == 0) {
    std::cout << "Beacon Created" << std::endl;
    return new Beacon(entity);
  }
  return nullptr;
}

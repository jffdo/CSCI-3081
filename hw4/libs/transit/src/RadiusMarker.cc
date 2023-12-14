#include "RadiusMarker.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>

RadiusMarker::RadiusMarker(JsonObject &obj) : details(obj) {
  available = true;
}

void RadiusMarker::Initalize(IEntity* bea_, int mid, int res_) {
  Beacon* bea = dynamic_cast<Beacon*>(bea_);
  markerID = mid;
  float rad = bea->GetRadius();
  position = {(rad*(std::cos(mid*(2*M_PI/res_))))+bea->GetPosition().x,
    bea->GetPosition().y,
    (rad*(std::sin(mid*(2*M_PI/res_))))+bea->GetPosition().z};
  JsonArray pos = {position[0], position[1], position[2]};
  details["position"] = pos;
  std::string result = bea->GetColor();;
  details["color"] = result;
}


JsonObject RadiusMarker::GetDetails() const { return details; }

void RadiusMarker::SetAvailability(bool choice) { available = choice; }

void RadiusMarker::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

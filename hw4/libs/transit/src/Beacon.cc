#define _USE_MATH_DEFINES
#include "Beacon.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Robot.h"
#include "Drone.h"

Beacon::Beacon(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  radius = obj["radius"];

  speed = obj["speed"];

  available = true;
  int i = (this->GetId()) * 160000 - (this->GetId()) * 1600;
  std::ostringstream ss;
  ss << std::setfill('0') << std::setw(8) << std::hex << i;
  std::string result = ss.str();
  result = "#" + result.substr(1, 6);
  color = result;
}

Beacon::~Beacon() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
}
void Beacon::AddDrone(Drone* newDrone_) {
  newDrone_->beacon = this;
  newDrone_->SetPosition(position);
  newDrone_->SetDirection({1, 0, 0});
  drones.push_back(newDrone_);
}
bool Beacon::RemoveDrone(Drone* newDrone_) {
  for (int i = 0; i < drones.size(); i += 1) {
    if (newDrone_ == drones[i]) {
      while (i + 1 < drones.size()) {
        drones[i] = drones[i + 1];
        i += 1;
      }
      drones.pop_back();
      return true;
    }
  }
  return false;
}

void Beacon::Notify(IEntity* newEntity) {
  for (int i = 0; i < drones.size(); i++) {
    // std::cout << details["name"] << "is notifying" << std::endl;
    // std::cout << drones[i]->GetDetails()["name"] << std::endl;
    if (drones[i]->Noitfied(newEntity) == true) {
      drones[i]->SetColor(color);
      if ( dynamic_cast<Robot*>(newEntity) != nullptr ) {
          dynamic_cast<Robot*>(newEntity)->prevbeacon = this;
       }
      break;
    }
  }
}
void Beacon::Update(double dt, std::vector<IEntity*> scheduler) {
  for (int i = 0; i < scheduler.size(); i++) {
    if (dynamic_cast<Robot*>(scheduler[i]) != nullptr
    && dynamic_cast<Robot*>(scheduler[i]) ->prevbeacon != this) {
      if (scheduler[i]->GetAvailability() &&
          position.Distance(scheduler[i]->GetPosition()) < radius) {
        Notify(scheduler[i]);
      }
    }
  }
}

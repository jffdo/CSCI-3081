#include "Robot.h"
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
#include "Beacon.h"

Robot::Robot(JsonObject &obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  speed = obj["speed"];
  available = true;
}
void Robot::Update(double dt, std::vector<IEntity*> scheduler) {
  if (!available) {
    if (toFinalDestination) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
    }
    wait = 0;
  }
  if (available && position.Distance(destination) > 4.0) {
    wait += 1;
  }
  if (wait ==5) {
    toFinalDestination =
        new JumpDecorator(new AstarStrategy(position, destination, graph));
  }
  if (toFinalDestination) {
    toFinalDestination->Move(this, dt/5);
    if (toFinalDestination->IsCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
      available = false;
    }
  }
}


JsonObject Robot::GetDetails() const { return details; }

void Robot::SetAvailability(bool choice) { available = choice; }

void Robot::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

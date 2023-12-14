#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
#include "Beacon.h"

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
}


// void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
//   float minDis = std::numeric_limits<float>::max();
//   for (auto entity : scheduler) {
//     if (entity->GetAvailability() && entity->GetPosition().
//            Distance(beacon->GetPosition()) <= beacon->GetRadius()) {
//       float disToEntity = this->position.Distance(entity->GetPosition());
//       if (disToEntity <= minDis) {
//         minDis = disToEntity;
//         nearestEntity = entity;
//       }
//     }
//   }

//   if (nearestEntity) {
//       // set availability to the nearest entity
//     nearestEntity->SetAvailability(false);
//     available = false;
//     pickedUp = false;

//     destination = nearestEntity->GetPosition();
//     Vector3 finalDestination = nearestEntity->GetDestination();

//     toRobot = new BeelineStrategy(position, destination);

//     std::string strat = nearestEntity->GetStrategyName();
//     if (strat == "astar")
//       toFinalDestination =
//         new JumpDecorator(new AstarStrategy
//                (destination, finalDestination, graph));
//     else if (strat == "dfs")
//       toFinalDestination =
//         new SpinDecorator(new JumpDecorator
//              (new DfsStrategy(destination, finalDestination, graph)));
//     else if (strat == "dijkstra")
//       toFinalDestination =
//         new JumpDecorator(new SpinDecorator
//              (new DijkstraStrategy(destination, finalDestination, graph)));
//     else
//       toFinalDestination = new BeelineStrategy
//              (destination, finalDestination);
//   }
// }

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
  // if (available)
  //   GetNearestEntity(scheduler);

  if (nearestEntity
    && position.Distance(beacon->GetPosition()) >= beacon->GetRadius()) {
    nearestEntity->SetAvailability(true);
    delete toRobot;
    delete toFinalDestination;
    toRobot = nullptr;
    pickedUp = false;
    nearestEntity = nullptr;
    available = true;
    toFinalDestination = new BeelineStrategy(position, beacon->GetPosition());
  }

  if (toRobot) {
    //  std::cout<< details["name"]<<"is on the move"<<std::endl;
    toRobot->Move(this, dt);

    if (toRobot->IsCompleted()) {
      delete toRobot;
      toRobot = nullptr;
      pickedUp = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->Move(this, dt);

    if (nearestEntity && pickedUp) {
      nearestEntity->SetPosition(position);
      nearestEntity->SetDirection(direction);
    }

    if (toFinalDestination->IsCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
      nearestEntity = nullptr;
      available = true;
      color = "#ffffff";
      pickedUp = false;
    }
  }
    // Return back to beacon when complete
  if (position.Distance(beacon->GetPosition())
    >= 4.0 && toFinalDestination == nullptr) {
    toFinalDestination = new BeelineStrategy(position, beacon->GetPosition());
    color = "#ffffff";
    if (nearestEntity) {
      toRobot = nullptr;
      pickedUp = false;
      nearestEntity = nullptr;
      available = true;
    }
  }
}

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}
bool Drone::Noitfied(IEntity* newEntity) {
  if (available) {
    nearestEntity = newEntity;
    std::cout<< details["name"] <<
      "has been notitfied and is avalable" << std::endl;

    nearestEntity->SetAvailability(false);
    available = false;
    pickedUp = false;

    destination = nearestEntity->GetPosition();
    Vector3 finalDestination = nearestEntity->GetDestination();

    toRobot = new BeelineStrategy(position, destination);
    std::cout<< details["name"] << ": " <<
      nearestEntity->GetDetails()["name"] << std::endl;

    std::string strat = nearestEntity->GetStrategyName();
    if (strat == "astar")
      toFinalDestination =
        new JumpDecorator(new AstarStrategy
          (destination, finalDestination, graph));
    else if (strat == "dfs")
      toFinalDestination =
        new SpinDecorator(new JumpDecorator
          (new DfsStrategy(destination, finalDestination, graph)));
    else if (strat == "dijkstra")
      toFinalDestination =
        new JumpDecorator(new SpinDecorator
          (new DijkstraStrategy(destination, finalDestination, graph)));
    else
      toFinalDestination = new BeelineStrategy(destination, finalDestination);
    return true;
    } else {
      //  std::cout<<"Drone has been notitfied and is not avalable"<<std::endl;
      return false;
    }
  }

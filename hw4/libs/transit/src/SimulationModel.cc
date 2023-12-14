#include "SimulationModel.h"

#include "DroneFactory.h"
#include "RobotFactory.h"
#include "HumanFactory.h"
#include "HelicopterFactory.h"
#include "BeaconFactory.h"
#include "RadiusMarkerFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HumanFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new BeaconFactory());
  AddFactory(new RadiusMarkerFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (int i = 0; i < entities.size(); i++) {
    delete entities[i];
  }
  for (int i = 0; i < scheduler.size(); i++) {
    delete scheduler[i];
  }
  for (int i = 0; i < radentities.size(); i++) {
    delete radentities[i];
  }
  delete graph;
  delete compFactory;
}

void SimulationModel::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  if (type.compare("beacon") == 0) {
    numBeacons += 1;
    std::cout << name << ": " << position << std::endl;

    IEntity* myNewEntity = compFactory->CreateEntity(entity);
    myNewEntity->SetGraph(graph);

    // Call AddEntity to add it to the view
    controller.AddEntity(*myNewEntity);
    entities.push_back(myNewEntity);
    // Creating radius markers
    // resolution size
    int res = 64;
    JsonObject details;
    details["type"] = "radius_marker";
    details["mesh"] = "assets/model/radius_marker.glb";
    JsonArray pos = {498.292, 270, -228.623};
    details["position"] = pos;
    JsonArray scale = {0.2, 0.2, 0.2};
    details["scale"] = scale;
    for (int i = 0; i < res; i++) {
      details["name"] = "rad";
      RadiusMarker* radmark =
        dynamic_cast<RadiusMarker*>(compFactory->CreateEntity(details));
      radmark->Initalize(myNewEntity, i, res);
      radmark->SetGraph(graph);

      controller.AddEntity(*radmark);
      radentities.push_back(radmark);
    }
  } else  if (type.compare("drone") == 0) {
    if (numBeacons >= 1) {
      beaconID+=1;
      int beaconCount = 0;
      std::cout << name << ": " << position << std::endl;

      IEntity* myNewEntity = compFactory->CreateEntity(entity);
      myNewEntity->SetGraph(graph);

      // Call AddEntity to add it to the view
      controller.AddEntity(*myNewEntity);
      entities.push_back(myNewEntity);

      // Assigns Drones to Beacons
      for (int i = 0; i < entities.size(); i++) {
        if (dynamic_cast<Beacon*>(entities[i]) != nullptr) {
          if (beaconCount == (beaconID % numBeacons)) {
            dynamic_cast<Beacon*>(entities[i])->
              AddDrone(dynamic_cast<Drone*>(myNewEntity));
            break;
          } else {
            beaconCount +=1;
          }
        }
      }
      std::cout << "Beacon pos: " <<
        dynamic_cast<Drone*>(myNewEntity)->
        beacon->GetDetails()["name"] << std::endl;
      } else {
        std::cout << "Unable to add "<< name << std::endl;
      }
  } else {
    std::cout << name << ": " << position << std::endl;

    IEntity* myNewEntity = compFactory->CreateEntity(entity);
    myNewEntity->SetGraph(graph);

    // Call AddEntity to add it to the view
    controller.AddEntity(*myNewEntity);
    entities.push_back(myNewEntity);
  }
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 &&
        entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      entity->SetStrategyName(strategyName);
      scheduler.push_back(entity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    entities[i]->Update(dt, scheduler);
    controller.UpdateEntity(*entities[i]);
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}

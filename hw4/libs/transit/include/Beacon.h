#ifndef BEACON_H_
#define BEACON_H_

#include <vector>

#include "IEntity.h"
#include "Drone.h"
#include "IStrategy.h"
#include "math/vector3.h"
class Drone;

// Represents a Beacon in a physical system.
// Beacons move using euler integration based on a specified
// velocity and direction.
// Uses this model https://sketchfab.com/3d-models/radio-tower-from-poly-by-google-268b4970a174419f8d621f469454be84#download
/**
 * @class Beacon
 * @brief Represents a Beacon in a physical system. Beacons move using euler
 * integration based on a specified velocity and direction.
 */
class Beacon : public IEntity {
 public:
  /**
   * @brief Beacons are created with a name
   * @param obj JSON object containing the Beacon's information
   */
  Beacon(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Beacon();

  /**
   * @brief Gets the speed of the Beacon
   * @return The speed of the Beacon
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the Beacon
   * @return The position of the Beacon
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the Beacon
   * @return The direction of the Beacon
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the Beacon
   * @return The destination of the Beacon
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the Beacon
   * @return The color of the Beacon
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the Beacon
   * @return The details information of the Beacon
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Gets the availability of the Beacon
   * @return The availability of the Beacon
   */
  bool GetAvailability() const { return available; }
  /**
   * @brief Sets the position of the Beacon
   * @param pos_ The new position of the Beacon
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the Beacon
   * @param dir_ The new direction of the Beacon
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the Beacon
   * @param des_ The new destination of the Beacon
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the Beacon
   * @param col_ The new color of the Beacon
   */
  void SetColor(std::string col_) { color = col_; }
  /**
   * @brief Sets the radius of the Beacon
   * @param rad_ The new radius of the Beacon
   */
  void SetRadius(float rad_) { radius = rad_; }
  /**
   * @brief Gets the radius of the Beacon
   */
  float GetRadius() { return radius; }
  /**
   * @brief Sets the drone vector of the Beacon
   * @param drone_ The new array of drones of the Beacon
   */
  void SetDrones(std::vector<Drone*> drone_) { drones = drone_; }
  /**
   * @brief Gets the drones of the Beacon
   */
  std::vector<Drone*> GetDrones() { return drones; }
  /**
   * @brief Adds a new drone to the vector of drones
   * @param newDrone_ The new drone that is added to the drones vector
   */
  void AddDrone(Drone* newDrone_);
   /**
   * @brief Adds a new drone to the vector of drones
   * @param drone_ The new drone that is added to the drones vector
   * @return true if removed false if not found
   */
  bool RemoveDrone(Drone* drone_);
   /**
   * @brief Updates the beacon, handles notifications 
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);
    /**
   * @brief notifies the drones that a robot has entered the beacons range
   * @param  newEntity the entity that notify is sending information about
   */
  void Notify(IEntity* newEntity);
  /**
   * @brief Removing the copy constructor and assignment operator
   * so that Beacons cannot be copied.
   */
  Beacon(const Beacon& Beacon) = delete;
  Beacon& operator=(const Beacon& Beacon) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  std::string color = "None";  // None means default color
  Vector3 destination;
  float speed;
  bool available;
  bool pickedUp;
  IEntity* nearestEntity = nullptr;
  IStrategy* toRobot = nullptr;
  IStrategy* toFinalDestination = nullptr;
  float radius;
  std::vector<Drone*> drones;

};

#endif

#ifndef RADIUS_MARKER_H
#define RADIUS_MARKER_H
#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"
#include "Beacon.h"

/**
 * @class RadiusMarker
 * @brief Represents a RadiusMarker in a physical system
 *
 * RadiusMarkers move using euler integration based on a specified
 * velocity and direction.
 */
class RadiusMarker : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the RadiusMarker's information
   */
  RadiusMarker(JsonObject& obj);
  /**
   * @brief Destructor
   */
  ~RadiusMarker() override = default;
  /**
   * @brief Initalizes the set of RadiusMarkers
   * @param bea_ the Beacon that the radius marker is used
   * @param markerID the number of this marker
   * @param res_ the total number of the markers for this beacon
   */
  void Initalize(IEntity* bea_, int markerID, int res_);
  /**
   * @brief Sets the RadiusMarker's id
   * @param choice The new availability of the RadiusMarker
   */
  void SetId(int id) {markerID = id;}

  /**
   * @brief Gets the RadiusMarker's position
   * @return The RadiusMarker's position
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the RadiusMarker's direction
   * @return The RadiusMarker's direction
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the RadiusMarker's destination
   * @return The RadiusMarker's destination
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the RadiusMarker's availability
   * @return The RadiusMarker's availability
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Gets the RadiusMarker's details
   * @return The RadiusMarker's details
   */
  JsonObject GetDetails() const override;

  /**
   * @brief Gets the RadiusMarker's speed
   * @return The RadiusMarker's speed
   */
  float GetSpeed() const { return speed; }
  /**
   * @brief Sets the RadiusMarker's availability
   * @param choice The new availability of the RadiusMarker
   */
  void SetAvailability(bool choice);

  /**
   * @brief Sets the RadiusMarker's position
   * @param pos_ The new position of the RadiusMarker
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the RadiusMarker's direction
   * @param dir_ The new direction of the RadiusMarker
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the RadiusMarker's destination
   * @param des_ The new destination of the RadiusMarker
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Rotates the RadiusMarker
   * @param angle The angle by which the RadiusMarker should be rotated
   */
  void Rotate(double angle);

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  bool available;
  std::string strategyName;
  Beacon* beacon;
  int markerID;
};

#endif  // RadiusMarker_H

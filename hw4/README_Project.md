@@ -1,4 +1,19 @@
# Team-001-40-homework4
Developed by Jeffrey Do (do000043@umn.edu) and Kris Moe (moe00013@umn.edu)

## Description
This project is an new feature extenstion to the Drone Simulation project for CSCI 3081W Program Design and Development at the Uninversity of Minnesota. The project simulates a drone traveling to an available object (which is a robot in this simulation) to a desired location.

The new feature adds beacons to the drone simulation. At each beacon, a drone is assigned to the beacon and can only traverse in the radius of the beacon. As such, to reach a destination the robot will traverse through multiple beacons. The drone will move the robot to the edge where beacons overlap to hand off to next drone until the robot had reached its destination.

The idea of the extension is to simulate an effective range that a drone can travel. The implementation of the extension uses the Observer pattern as its main design pattern.

## Table of Contents
- [Getting Started](#getting-started)
- [Extention Funtionallity](#extention-functionallity)
- [UML](#uml)
- [Credits](#credits)

## Getting Started

Here is a quick overview of how to run the visualization :
    ```bash
    # Go to the project directory
    cd /path/to/repo/project
    
    # Build the project
    make -j
    
    # Run the project (./build/web-app <port> <web folder>)
    ./build/bin/transit_service 8081 apps/transit_service/web/
    ```
    
Navigate to http://127.0.0.1:8081 and you should see a visualization.
Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

*Note: 8081 will depends on what port you used. If you use port 8082, then it will be http://127.0.0.1:8082 instead.*

## Extention Functionallity
TODO: *"What does the function do specifically?"*\
What does it do?*

The new extention places a new objects that are called beacons in the simulation. We initalize a new drone to each beacon. Each drone can only move in the area covered in the assigned beacon. In the edge case, where the destination is not covered by any beacon, the robot will attempt to travel to the destination using an Astar strategy.

*Why is it significally interesting?*

This is significally interesting because the extenstion simulates an effective range for the drones. As such when a destination is not inrange, it will drop off the drone at the edge of the effective area towards the destination.

*How does it add to the existing work?*

Our project adds to the existing work by making it more realistic. Realistically automated vehicles do not have infinite range. This addition simulates their effective range. We added the beacons that simulate control towers. Each beacon notifies its drones when a new robot gets into its range. When robots are dropped outside the range of a beacon they will walk to their destination at a slower rate. For ease of visibility each beacon has radius markers that have a color unique to their beacon. When the drones are transporting robots they will change their color to that of their beacon. 

*Which design pattern did you choose to implement it and why?*

The observer pattern is used to create a way for the drones and beacons to communicate with each other. Drones needed  to be notified when robots entered their beacon's radius. Each beacon is a publisher and its drones are subscribers. Beacause both the beacon and the drones are children of IEntity, and adding a subscriber interface would mean that Drones would have to implement multiple inheritance, we do not have a subscriber interface. 

*Instruction to use this new feature* 

Our feature is not user interactable. In the simulation, the robot will be visibly picked up and dropped off between drones when traveling.

*Instruction to use this new feature if you are altering the code*
Our current set up has the 48 drones and 20 beacons. They cover the each have of campus with an uncovered strip in the middle. If you want to change the number of drones on line 198 of main.js there is a for loop that controls the number of drones in the simulation. If you want to change the layout of the beacons, the set up for them are lines 152 -162; The radius of the beacons can be found in in main.js on line 143.

## UML
TODO: *Add UML here*

## Credits
The beacon model was taken from https://sketchfab.com/3d-models/radio-tower-from-poly-by-google-268b4970a174419f8d621f469454be84#download
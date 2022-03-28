//
//  main.cpp
//  PA1/PA2-CS330
//  This is the PA2 assignments for CS 330 - Path Following / code can be rearranged using commented out code at the end for PA1 - movement behaviors
//  Created by on 2/5/22.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

#include "Character.hpp"
#include "SteeringOutput.hpp"
#include "Path.hpp"
#include "mathFunctions.hpp"

#define M_PI 3.141592653589793238

//Functions
void initPA2(Character &char1, Character &target);
void initPath(Path &path);
void initPathCoord (float xCoord[], float zCoord[]);
void printData (ofstream &outFile, double simTime, Character &charX);

// update function
Character update (Character &charX, SteeringOutput &steering, double timeStep);

// get steering functions
SteeringOutput dynamicGetSteeringContinue (Character &charX,  SteeringOutput &steering);
SteeringOutput dynamicGetSteeringFlee (Character &charX, Character &target, SteeringOutput &steering);
SteeringOutput dynamicGetSteeringSeek (Character &charX, Character &target, SteeringOutput &steering);
SteeringOutput dynamicGetSteeringArrive (Character &charX, Character &target, SteeringOutput &steering);

SteeringOutput dynamicGetSteeringFollowPath (Path &path, Character &charX, Character &target, SteeringOutput &steering, float xCoord[], float zCoord[]);

Path assemble (Path &path, float xCoord[], float zCoord[]);

using namespace std;

// start program
int main(int argc, const char * argv[]) {

    // create instances of characters
    Character char1;
    Character target;
    SteeringOutput steering;
    Path path;
    
    // create x and z coordinate array
    float xCoord[8];
    float zCoord[8];
    
    // intial values for simualtion time
    double timeStep = 0.5;
    double stopTime = 125;
    double simTime = 0;

    // variables for file input and output
    ifstream inFile; //file containing input for future
    ofstream outFile; //file containing output
    string inFileName; //input file external name for future
    string outFileName; //output file external name
   
    //open output file
    outFileName = "PA2-Output.txt";    // replace with your path -----
    outFile.open(outFileName.c_str());
    
    // initialize and create path
    initPathCoord (xCoord, zCoord);
    initPath(path);
    assemble(path, xCoord, zCoord);
    
    // initialize character and target
    initPA2 (char1, target);
    
    // print out initial character data to output file
    printData (outFile, simTime, char1);
    
    for (simTime = 0.5; simTime <= stopTime; simTime += timeStep)
    {
        // call get steering function, update values, print data
        dynamicGetSteeringFollowPath(path, char1, target, steering, xCoord, zCoord);
        update(char1, steering, timeStep);
        printData (outFile, simTime, char1);
    }
    
    // close output file
    outFile.close();
    
    return 0;
}


//
//Functions
//

// Function to get steeringing output to follow a path
SteeringOutput dynamicGetSteeringFollowPath (Path &path, Character &charX, Character &target, SteeringOutput &steering, float xCoord[], float zCoord[])
{
    // get the parameter for the right segment
    float param = path.GetParam(path, charX, xCoord, zCoord);
    
    // offset the parameter
    float targetParam = param + charX.pathOffset;
    
    // get the desired target position
    target.xPos = path.xGetPosition(path, targetParam, xCoord, zCoord);
    target.zPos = path.zGetPosition(path, targetParam, xCoord, zCoord);
    
    // call seek to follow it
    return dynamicGetSteeringSeek(charX, target, steering);
}


// Function to update the position of a character
Character update (Character &charX, SteeringOutput &steering, double timeStep)
{
    // update values of mover with respect to time/steering output
    charX.xPos += charX.xVel * timeStep;
    charX.zPos += charX.zVel * timeStep;

    // update orientation
    charX.orient += charX.rotation * timeStep;
    
    // update velocity
    charX.xVel += steering.xLinAcc * timeStep;
    charX.zVel += steering.zLinAcc * timeStep;
    
    // update rotation
    charX.rotation += steering.angular * timeStep;
    
    // update acceleration
    charX.xLinAcc = steering.xLinAcc;
    charX.zLinAcc = steering.zLinAcc;

    //update angle
    charX.angular = steering.angular;
   
    // prevent jitter
    if (mathFunctions::vectorVelLength(charX) < 0.02)
    {
        charX.xVel = 0.0;
        charX.zVel = 0.0;
    }

    // check if speed is too high
    if (mathFunctions::vectorVelLength(charX) > charX.maxVel)
    {
        if (mathFunctions::vectorVelLength(charX) != 0.0)
       {
           double temp = mathFunctions::vectorVelLength(charX);
           
            charX.xVel = charX.maxVel * (charX.xVel / temp);
            charX.zVel = charX.maxVel * (charX.zVel / temp);
        }
    }

    // prevent jitter
    if (mathFunctions::vectorLinAccLength(charX) < 0.02)
    {
        charX.xLinAcc = 0.0;
        charX.zLinAcc = 0.0;
    }

    // check if accel is too high
    if (mathFunctions::vectorLinAccLength(charX) > charX.maxAcc)
    {
        if (mathFunctions::vectorLinAccLength(charX) != 0.0)
        {
            double temp1 = mathFunctions::vectorLinAccLength(charX);
            
            charX.xLinAcc = charX.maxAcc * (charX.xLinAcc / temp1);
            charX.zLinAcc = charX.maxAcc * (charX.zLinAcc / temp1);
        }
    }
    
    // return character data
    return charX;
}


// Function to get the steering output for a continuing character
SteeringOutput dynamicGetSteeringContinue (Character &charX,  SteeringOutput &steering)
{
    // reset steering values
    steering.xLinAcc = 0.0;
    steering.zLinAcc = 0.0;
    steering.angular = 0.0;
    
    // set steering values to initial values
    steering.angular = charX.angular;
    steering.xLinAcc = charX.xLinAcc;
    steering.zLinAcc = charX.zLinAcc;
    
    // return angle and lin accel
    return steering;
}


// Function to get the steering output for a fleeing character
SteeringOutput dynamicGetSteeringFlee (Character &charX, Character &target, SteeringOutput &steering)
{
    // reset steering values
    steering.xLinAcc = 0.0;
    steering.zLinAcc = 0.0;
    steering.angular = 0.0;
    
    // get direction to target to flee
    steering.xLinAcc = charX.xPos - target.xPos;
    steering.zLinAcc = charX.zPos - target.zPos;
    
    double temp = mathFunctions::vectorLinAccLengthSteer (steering);
    
    // accelerate at maximum rate
    steering.xLinAcc /= temp;
    steering.zLinAcc /= temp;
    
    // normalize
    steering.xLinAcc *= charX.maxAcc;
    steering.zLinAcc *= charX.maxAcc;
    
    // set angle to 0
    steering.angular = 0.0;
    
    // return angle and lin accel
    return steering;
}


// Function to get the steering output for a seeking character
SteeringOutput dynamicGetSteeringSeek (Character &charX, Character &target, SteeringOutput &steering)
{
    // reset steering values
    steering.xLinAcc = 0.0;
    steering.zLinAcc = 0.0;
    steering.angular = 0.0;
    
    // get direction to target to seek
    steering.xLinAcc = target.xPos - charX.xPos;
    steering.zLinAcc = target.zPos - charX.zPos;

    // accelerate at maximum rate
    // normalize
    double temp = mathFunctions::vectorLinAccLengthSteer (steering);

    steering.xLinAcc /= temp;
    steering.zLinAcc /= temp;
 
    steering.xLinAcc *= charX.maxAcc;
    steering.zLinAcc *= charX.maxAcc;
    
    // set angle to 0
    steering.angular = 0.0;
    
    // return steering angle an lin accel
    return steering;
}


// Function to get the steering output for an arriving character
SteeringOutput dynamicGetSteeringArrive (Character &charX, Character &target,  SteeringOutput &steering)
{
    // reset steering values
    steering.xLinAcc = 0.0;
    steering.zLinAcc = 0.0;
    steering.angular = 0.0;
    
    // declare varaibles for arrive
    float xDir = 0.0;
    float zDir = 0.0;
    float distance = 0.0;
    float targetSpeed = 0.0;
    float xTargetVel = 0.0;
    float zTargetVel = 0.0;
    
    // find direction to target
    xDir = target.xPos - charX.xPos;
    zDir = target.zPos - charX.zPos;
    
    // find distance to target
    distance = sqrt(pow(xDir, 2) + pow(zDir, 2));
    
    // check which radius character is in
    // arrived
    if (distance < charX.arriveRad)
    {
        targetSpeed = 0.0;
    }
    // normal speed
    if (distance > charX.slowRad)
    {
        targetSpeed = charX.maxVel;
    }
    // slow down
    else
    {
        targetSpeed = charX.maxVel * distance / charX.slowRad;
    }
    
    // set velocity by combining speed and direction
    xTargetVel = xDir;
    zTargetVel = zDir;
    
    // normalize
    double temp = sqrt(pow(xTargetVel, 2) + pow(zTargetVel, 2));

    xTargetVel /= temp;
    zTargetVel /= temp;
    
    xTargetVel *= targetSpeed;
    zTargetVel *= targetSpeed;
    
    // accelerate to target velocity
    steering.xLinAcc = xTargetVel - charX.xVel;
    steering.zLinAcc = zTargetVel - charX.zVel;

    steering.xLinAcc = steering.xLinAcc / charX.timeToTar;
    steering.zLinAcc = steering.zLinAcc / charX.timeToTar;
    
    // test if acceleration is too fast
    if (mathFunctions::vectorLinAccLengthSteer (steering) > charX.maxAcc)
    {
        double temp1 = mathFunctions::vectorLinAccLengthSteer (steering);
        
        steering.xLinAcc /= temp1;
        steering.zLinAcc /= temp1;
        
        steering.xLinAcc *= charX.maxAcc;
        steering.zLinAcc *= charX.maxAcc;
    }
    
    // set steering angle to 0
    steering.angular = 0.0;
    
    // return lin accel and angle
    return steering;
}


// Funtion to print character data to output file
void printData (ofstream &outFile, double simTime, Character &charX)
{
    // print out data in desired order
    outFile << simTime << "," << charX.id << "," << charX.xPos << "," << charX.zPos << "," << charX.xVel << "," << charX.zVel << "," << charX.xLinAcc << "," << charX.zLinAcc << "," << charX.orient << "," << charX.steerCode << ",";
    
    // puts out true or false as text
    if (charX.collideStat == 0)
    {
        outFile << "FALSE" << endl;
    }
    else
    {
        outFile << "TRUE" << endl;
    }
}


//Funciton to initialze character and target for PA2
void initPA2 (Character &char1, Character &target)
{
    // character 1 - follow path
    char1.id = 2701;
    char1.xPos = 20.0;
    char1.zPos = 95.0;
    char1.xVel = 0.0;
    char1.zVel = 0.0;
    char1.xLinAcc = 0.0;
    char1.zLinAcc = 0.0;
    char1.steerCode = 11;
    char1.collideStat = false;
    char1.orient = 0;
    char1.maxVel = 4.0;
    char1.maxAcc = 2.0;
    char1.angular = 0;
    char1.rotation = 0;
    char1.followPath = 1.0;
    char1.pathOffset = 0.04;
    
    target.id = 0;
    target.xPos = 0.0;
    target.zPos = 0.0;
    target.xVel = 0.0;
    target.zVel = 0.0;
    target.xLinAcc = 0.0;
    target.zLinAcc = 0.0;
    target.steerCode = 0;
    target.collideStat = false;
    target.orient = 0;
    target.maxVel = 0.0;
    target.maxAcc = 0.0;
    target.angular = 0;
    target.rotation = 0;
    target.followPath = 0.0;
    target.pathOffset = 0.0;
}

// Function to set the (x,z) coordinates
void initPathCoord (float xCoord[], float zCoord[])
{
    xCoord[1] = 0;
    xCoord[2] = -20;
    xCoord[3] = 20;
    xCoord[4] = -40;
    xCoord[5] = 40;
    xCoord[6] = -60;
    xCoord[7] = 60;
    xCoord[8] = 0;
    xCoord[0] = 0;
    
    zCoord[1] = 90;
    zCoord[2] = 65;
    zCoord[3] = 40;
    zCoord[4] = 15;
    zCoord[5] = -10;
    zCoord[6] = -35;
    zCoord[7] = -60;
    zCoord[8] = -85;
    zCoord[0] = 0;
}


// Function to initialize a path
void initPath(Path &path)
{
    path.param[0] = 0;
    path.param[1] = 0;
    path.param[2] = 0;
    path.param[3] = 0;
    path.param[4] = 0;
    path.param[5] = 0;
    path.param[6] = 0;
    path.param[7] = 0;
    path.param[8] = 0;
    
    path.segments = 0;
    path.id = 1;
}


// Function to assemble a path
Path assemble (Path &path, float xCoord[], float zCoord[])
{
    // initialize number of segments
    path.segments = sizeof(*(&xCoord +1) - xCoord) - 1;

    // set distance to all to 0
    for (int i = 0; i <= (path.segments + 1); i++)
    {
        path.distance[i] = 0;
    }
    
    // find the distance between all points
    for (int i = 2; i <= (path.segments + 1); i++)
    {
        path.distance[i] = path.distance[i-1] + Path::distancePointToPoint(xCoord[i-1], zCoord[i-1], xCoord[i], zCoord[i]);
    }
    
    // set parameter of all to -
    for (int i = 0; i <= (path.segments + 1); i++)
    {
        path.param[i] = 0;
    }
    
    // set the parameter of each segment
    for (int i = 2; i <= (path.segments + 1); i++)
    {
        path.param[i] = path.distance[i] / Path::max(path.distance, 9);

    }

    return path;
}



// Below are the things needed to run for PA1


// inside main //

/* Comment out Program One
 void initPA1(Character &char1, Character &char2, Character &char3, Character &char4);

// fill in characters initial values
initPA1 (char1, char2, char3, char4);

// print out initial character data to output file
printData (outFile, simTime, char1);
printData (outFile, simTime, char2);
printData (outFile, simTime, char3);
printData (outFile, simTime, char4);

// incremment timestep and update each character
for (simTime = 0.5; simTime <= stopTime; simTime += timeStep)
{
    // call get steering function, update values, print data
    dynamicGetSteeringContinue(char1, steering);
    update(char1, steering, timeStep);
    printData (outFile, simTime, char1);
            
    dynamicGetSteeringFlee(char2, char1, steering);
    update (char2, steering, timeStep);
    printData (outFile, simTime, char2);
    
    dynamicGetSteeringSeek(char3, char1, steering);
    update (char3, steering, timeStep);
    printData (outFile, simTime, char3);
    
    dynamicGetSteeringArrive(char4, char1, steering);
    update (char4, steering, timeStep);
    printData (outFile, simTime, char4);
}
 
*/

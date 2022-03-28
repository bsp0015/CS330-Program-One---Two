//
//  mathFunctions.cpp
//  PA1-CS330
//
//  Created by on 2/18/22.
//

#include "mathFunctions.hpp"
#include "Character.hpp"
#include "SteeringOutput.hpp"
#include <cmath>

// Math functions

// Function that returns the Length of velocity vector
float mathFunctions::vectorVelLength (Character &charX)
{
    return sqrt(pow(charX.xVel, 2) + pow(charX.zVel, 2));
}


// Function that returns the length of linear acceleration vector
float mathFunctions::vectorLinAccLength (Character &charX)
{
    return sqrt(pow(charX.xLinAcc, 2) + pow(charX.zLinAcc, 2));
}


// Function that returns the length of steering linear acceleration vector
float mathFunctions::vectorLinAccLengthSteer (SteeringOutput &steering)
{
    return sqrt(pow(steering.xLinAcc, 2) + pow(steering.zLinAcc, 2));
}

// Function that returns the vector dot product
float mathFunctions::vectorDot (float xStart, float zStart, float xEnd, float zEnd)
{
    return (xStart * xEnd) + (zStart * zEnd);
};

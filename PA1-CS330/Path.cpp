//
//  Path.cpp
//  PA1-CS330
//
//  Created by Brandon Perry on 2/18/22.
//

#include "Path.hpp"
#include "Character.hpp"
#include <list>
#include <cmath>
#include <algorithm>
#include "mathFunctions.hpp"

// Function to get the path parameter of the point closest to the character
float Path::GetParam (Path &path, Character &charX, float xCoord[], float zCoord[])
{
    // initialize variables
    float closestDistance = INFINITY;
    int closestSegment = 0;
    float xClosest = 0;
    float zClosest = 0;
    
    // go through each segment
    for (int i = 0; i <= path.segments; i++)
    {
        // get start and end coordinate of the segment
        float xStart = xCoord[i];
        float zStart = zCoord[i];
 
        float xEnd = xCoord[i+1];
        float zEnd = zCoord[i+1];
        
        // find closest point on segment
        float xCheckPoint = xClosestPointOnSegment(charX.xPos, charX.zPos, xStart, zStart, xEnd, zEnd);
        float zCheckPoint = zClosestPointOnSegment(charX.xPos, charX.zPos, xStart, zStart, xEnd, zEnd);
        
        float checkDistance = distancePointToPoint(charX.xPos, charX.zPos, xCheckPoint, zCheckPoint);
        
        // get closest segment to character
        if (checkDistance < closestDistance)
        {
           xClosest = xCheckPoint;
           zClosest = zCheckPoint;
           closestDistance = checkDistance;
           closestSegment = i;
        }
    }
    
    // Get path paramater of closest point
    float xStart = xCoord[closestSegment];
    float zStart = zCoord[closestSegment];
    
    float zStartParam = path.param[closestSegment];
    
    float xEnd = xCoord[closestSegment + 1];
    float zEnd = zCoord[closestSegment + 1];
    
    float zEndParam = path.param[closestSegment + 1];

    float xC = xClosest;
    float zC = zClosest;
    
    float temp = (sqrt(pow((xC - xStart),2) + pow((zC - zStart),2))) / (sqrt(pow((xEnd - xStart),2) + pow((zEnd - zStart),2)));
    
    float cParam = zStartParam + (temp * (zEndParam - zStartParam));
    
    return cParam;
}


// Function to get the xPosition of the target point
float Path::xGetPosition (Path &path, float param, float xCoord[], float zCoord[])
{
    // intialize variables
    int segment = 0;
    
    // Go through segments
    for (int i = 0; i <= 8; i++)
    {
        // find max segment where target parameter is greater then segment parameter
        if (param > path.param[i])
        {
            segment = i;
        }
    }
    
    // calculate x position
    float xStart = xCoord[segment];
    
    float xEnd = xCoord[segment + 1];

    float temp = (param - path.param[segment]) / (path.param[segment + 1] - path.param[segment]);
    
    float xPos = xStart + (temp * (xEnd - xStart));

    return xPos;
}


//Function to get the z position of target point
float Path::zGetPosition (Path &path, float param, float xCoord[], float zCoord[])
{
    // initialize variable
    int segment = 0;
  
    // for each segment
    for (int i = 0; i < 8; i++)
    {
        // find max segment wehre target parameter is greater then segment parameter
        if (param > path.param[i])
        {
            segment = i;
        }
    
    }
    
    // calculate z position
    float zStart = zCoord[segment];
    
    float zEnd = zCoord[segment + 1];
    
    float temp = (param - path.param[segment]) / (path.param[segment + 1] - path.param[segment]);
    
    float zPos = zStart + (temp * (zEnd - zStart));
    
    return zPos;
}


// Funcution to return the x coordinate of the closest point on a line
float Path::xClosestPointOnLine (float xQuery, float zQuery, float xStart, float zStart, float xEnd, float zEnd)
{
    float temp1 = mathFunctions::vectorDot ((xQuery - xStart), (zQuery - zStart), (xEnd - xStart), (zEnd - zStart));
    float temp2 = mathFunctions::vectorDot ((xEnd - xStart), (zEnd - zStart), (xEnd - xStart), (zEnd - zStart));
    
    float temp3 = temp1 / temp2;
    
    int xTemp = (xEnd - xStart) * temp3;
    
    xTemp = xStart + xTemp;
    
    return (xTemp);
}


// Function to return the z cooridinate of the closest point on a line
float Path::zClosestPointOnLine (float xQuery, float zQuery, float xStart, float zStart, float xEnd, float zEnd)
{
    float temp1 = mathFunctions::vectorDot((xQuery - xStart), (zQuery - zStart), (xEnd - xStart), (zEnd - zStart));
    float temp2 = mathFunctions::vectorDot ((xEnd - xStart), (zEnd - zStart), (xEnd - xStart), (zEnd - zStart));
    
    float temp3 = temp1 / temp2;
    
    int zTemp = (zEnd - zStart) * temp3;
    
    zTemp = zStart + zTemp;
    
    return (zTemp);
}


// Function to return the x coordinate of the closest point on a line segment
float Path::xClosestPointOnSegment(float xQuery, float zQuery, float xStart, float zStart, float xEnd, float zEnd)
{
    float temp1 = mathFunctions::vectorDot((xQuery - xStart), (zQuery - zStart), (xEnd - xStart), (zEnd - zStart));
    float temp2 = mathFunctions::vectorDot ((xEnd - xStart), (zEnd - zStart), (xEnd - xStart), (zEnd - zStart));
    
    float temp3 = temp1 / temp2;
    
    if (temp3 <= 0)
    {
        return xStart;
    }
    else if (temp3 >= 1)
    {
        return xEnd;
    }
    else
    {
        float xTemp = (xStart + ((xEnd - xStart) * temp3));
        return xTemp;
    }
}


// Function to return the z coordinate of the closest point on a line segment
float Path::zClosestPointOnSegment(float xQuery, float zQuery, float xStart, float zStart, float xEnd, float zEnd)
{
    float temp1 = mathFunctions::vectorDot((xQuery - xStart), (zQuery - zStart), (xEnd - xStart), (zEnd - zStart));
    float temp2 = mathFunctions::vectorDot ((xEnd - xStart), (zEnd - zStart), (xEnd - xStart), (zEnd - zStart));
    
    float temp3 = temp1 / temp2;
    
    if (temp3 <= 0)
    {
        return zStart;
    }
    else if (temp3 >= 1)
    {
        return zEnd;
    }
    else
    {
        float zTemp = (zStart + ((zEnd - zStart) * temp3));
        
        return zTemp;
    }
}


// Function to find the distance between two points
float Path::distancePointToPoint (float xStart, float zStart, float xEnd, float zEnd)
{
    return (sqrt((pow((xEnd - xStart), 2)) + (pow((zEnd - zStart), 2))));
}


// Function to return the maximum parameter
float Path::max (float param[], int n)
{
    float max = param[0];
    
    for (int i = 0; i < n; i++)
    {
        if (param[i] > max)
        {
            max = param[i];
        }
    }
    
    return max;
}

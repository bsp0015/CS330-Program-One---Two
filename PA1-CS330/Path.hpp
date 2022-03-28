//
//  Path.hpp
//  PA1-CS330
//  Path is used to create, alter, and access a path
//  Created by on 2/18/22.
//

#ifndef Path_hpp
#define Path_hpp

#include <stdio.h>
#include <list>
#include <cmath>
#include "Character.hpp"

using namespace std;

class Path
{
public:
    float segments;
    float distance[9];
    float param[9];
    int id;
    
    float GetParam (Path &path, Character &charX, float xCoord[], float zCoord[]);
    float xGetPosition (Path &path, float param, float xCoord[], float zCoord[]);
    float zGetPosition (Path &path, float param, float xCoord[], float zCoord[]);
    float xClosestPointOnLine (float xQuery, float zQuery, float xStart, float zStart, float xEnd, float zEnd);
    float zClosestPointOnLine (float xQuery, float zQuery, float xStart, float zStart, float xEnd, float zEnd);
    float xClosestPointOnSegment (float xQuery, float zQuery, float xStart, float zStart, float xEnd, float zEnd);
    float zClosestPointOnSegment (float xQuery, float zQuery, float xStart, float zStart, float xEnd, float zEnd);
    
    static float distancePointToPoint (float xStart, float zStart, float xEnd, float zEnd);
    static float max (float param[], int n);
};

#endif /* Path_hpp */

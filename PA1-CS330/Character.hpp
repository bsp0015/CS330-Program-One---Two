//
//  Character.hpp
//  PA1-CS330
//
//  Created by  on 2/5/22.
//

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include <iostream>
#include "SteeringOutput.hpp"

using namespace std;

class Character {
public:
    int id;
    float xPos;
    float zPos;
    float xVel;
    float zVel;
    float xLinAcc;
    float zLinAcc;
    float orient;
    int steerCode;
    bool collideStat;
    float maxVel;
    float maxAcc;
    int arriveRad;
    int slowRad;
    float timeToTar;
    float angular;
    float rotation;
    int followPath;
    double pathOffset;
    

};


#endif /* Character_hpp */

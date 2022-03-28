//
//  mathFunctions.hpp
//  PA1-CS330
//  mathFunctions are used for vector operations
//  Created by on 2/18/22.
//

#ifndef mathFunctions_hpp
#define mathFunctions_hpp

#include <stdio.h>
#include "Character.hpp"
#include "SteeringOutput.hpp"

using namespace std;

class mathFunctions
{
public:
    static float vectorVelLength (Character &charX);
    static float vectorLinAccLength (Character &charX);
    static float vectorLinAccLengthSteer (SteeringOutput &steering);
    static float vectorDot (float xStart, float zStart, float xEnd, float zEnd);

};

#endif /* mathFunctions_hpp */

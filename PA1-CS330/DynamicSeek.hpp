//
//  DynamicSeek.hpp
//  PA1-CS330
//
//  Created by on 2/18/22.
//

#ifndef DynamicSeek_hpp
#define DynamicSeek_hpp

#include <stdio.h>
#include "Character.hpp"
#include "SteeringOutput.hpp"

using namespace std;

class DynamicSeek
{
public:
    SteeringOutput getSteering(Character &charX, Character &target);
};

#endif /* DynamicSeek_hpp */

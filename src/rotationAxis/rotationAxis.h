//
// Created by yossielman on 12/29/18.
//

#ifndef INC_3DFINALPROJECRT_ROTATIONAXIS_H
#define INC_3DFINALPROJECRT_ROTATIONAXIS_H

#include "../utils/Utils.h"
#include <cmath>

class rotationAxis {

public:
    static bool validateAxisFromUser(float axis[4][3] , int numOfAxis);

private:
    static bool isValidAxis(float axis[3]);
    static double calcDistance(RowVector3 q, RowVector3 p);

};


#endif //INC_3DFINALPROJECRT_ROTATIONAXIS_H

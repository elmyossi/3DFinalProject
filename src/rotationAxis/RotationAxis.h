//
// Created by yossielman on 12/29/18.
//

#ifndef INC_3DFINALPROJECRT_ROTATIONAXIS_H
#define INC_3DFINALPROJECRT_ROTATIONAXIS_H

#include "../utils/Utils.h"
#include <cmath>

class RotationAxis {

public:
    static bool validateAxisFromUser(float axis[MAX_NUMBER_OF_AXIS][3] , int numOfAxis);
    static bool handleAxisFromUser(float axisAngles[MAX_NUMBER_OF_AXIS][3] , float axisPosition[MAX_NUMBER_OF_AXIS][3], int numOfAxis);

private:
    static bool isValidAxis(float axis[3]);
    static double calcDistance(RowVector3 q, RowVector3 p);
    static void translateAxisAngleAndPositionToVector(float axisAngles[MAX_NUMBER_OF_AXIS][3], float axisPosition[MAX_NUMBER_OF_AXIS][3], RowVector3 translated[MAX_NUMBER_OF_AXIS], int numOfAxis);
    static bool validateEachRotationAxisHasCenterPiece(RowVector3 arrayOfRotationAxis[]);
};


#endif //INC_3DFINALPROJECRT_ROTATIONAXIS_H

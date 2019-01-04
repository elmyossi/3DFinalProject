//
// Created by yossielman on 12/29/18.
//

#include "RotationAxis.h"
#include "../JaapSphere/jaapSphere.h"

bool RotationAxis::validateAxisFromUser(float axis[MAX_NUMBER_OF_AXIS][3], int numOfAxis) {
    for (int i = 0; i < numOfAxis; i++) {
        if (isValidAxis(axis[i]) == false) {
            return false;
        }
    }
    return true;
}

bool RotationAxis::isValidAxis(float axis[3]) {
    RowVector3 core = jaapSphere::jaapSphereCore;
    double jaapSphereRadius = jaapSphere::jaapSphereRadius;
    double dist = calcDistance(RowVector3(axis[0], axis[1], axis[2]), core);
    if (dist > jaapSphereRadius) {
        return false;
    }
    return true;
}

double RotationAxis::calcDistance(RowVector3 q, RowVector3 p) {
    return sqrt(pow((q[0] - p[0]), 2) + pow((q[1] - p[1]), 2) + pow((q[2] - p[2]), 2));
}

void RotationAxis::translateAxisAngleAndPositionToVector(float axisAngles[MAX_NUMBER_OF_AXIS][3],
                                                         float axisPosition[MAX_NUMBER_OF_AXIS][3],
                                                         RowVector3 translated[MAX_NUMBER_OF_AXIS], int numOfAxis) {
    RowVector3 core = jaapSphere::jaapSphereCore;
    double jaapSphereRadius = jaapSphere::jaapSphereRadius;
    for (int i = 0; i < numOfAxis; i++) {
        double dist = calcDistance(RowVector3(axisPosition[i][0], axisPosition[i][1], axisPosition[i][2]), core);
        double alpha = dist / jaapSphereRadius;
        translated[i][0] = axisAngles[i][0] * alpha;
        translated[i][1] = axisAngles[i][1] * alpha;
        translated[i][2] = axisAngles[i][2] * alpha;
    }
}

bool
RotationAxis::handleAxisFromUser(float axisAngles[MAX_NUMBER_OF_AXIS][3], float axisPosition[MAX_NUMBER_OF_AXIS][3],
                                 int numOfAxis) {
    // 1. translate axis position and angles to 1 vector
    RowVector3 translated[MAX_NUMBER_OF_AXIS];
    translateAxisAngleAndPositionToVector(axisAngles, axisPosition, translated, numOfAxis);

    // 2. check if the axis are blocking
    return !validateEachRotationAxisHasCenterPiece(translated);
}

bool RotationAxis::validateEachRotationAxisHasCenterPiece(RowVector3 arrayOfRotationAxis[]) {
    for (int i = 0; i < MAX_NUMBER_OF_AXIS; i++) {
        RowVector3 currentVector = arrayOfRotationAxis[i];
        for (int j = 0; j < MAX_NUMBER_OF_AXIS; j++) {
            if (i == j) {
                continue;
            } else {
                RowVector3 toCheck = arrayOfRotationAxis[j];
                if (((currentVector - toCheck).dot(toCheck)) > 0) {
                    return false;
                }
            }
        }
    }
    return true;
}



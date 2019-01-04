//
// Created by yossielman on 12/29/18.
//

#include "rotationAxis.h"
#include "../JaapSphere/jaapSphere.h"


bool rotationAxis::validateAxisFromUser(float axis[4][3], int numOfAxis) {
    for (int i = 0; i < numOfAxis; i++) {
        if (isValidAxis(axis[i]) == false) {
            return false;
        }
    }
    return true;

}

bool rotationAxis::isValidAxis(float axis[3]) {
    RowVector3 core = jaapSphere::jaapSphereCore;
    double jaapSphereRadius = jaapSphere::jaapSphereRadius;
    double dist = calcDistance(RowVector3(axis[0], axis[1], axis[2]), core);
    if (dist > jaapSphereRadius) {
        return false;
    }
    return true;

}


double rotationAxis::calcDistance(RowVector3 q, RowVector3 p) {
    return sqrt(pow((q[0] - p[0]), 2) + pow((q[1] - p[1]), 2) + pow((q[2] - p[2]), 2));
}

void rotationAxis::translateAxisAngleAndPositionToVector(float axisAngles[4][3], float axisPosition[4][3], RowVector3 translated[4], int numOfAxis){
    RowVector3 core = jaapSphere::jaapSphereCore;
    double jaapSphereRadius = jaapSphere::jaapSphereRadius;
    for (int i =0; i< numOfAxis; i++ ){
        double dist = calcDistance(RowVector3(axisPosition[i][0], axisPosition[i][1], axisPosition[i][2]), core);
        double alpha = dist / jaapSphereRadius;
        translated[i][0] = axisAngles[i][0] * alpha;
        translated[i][1] = axisAngles[i][1] * alpha;
        translated[i][2] = axisAngles[i][2] * alpha;
    }
}

bool rotationAxis::handleAxisFromUser(float axisAngles[4][3], float axisPosition[4][3], int numOfAxis) {
    // 1. translate axis position and angles to 1 vector
    RowVector3 translated[5];
    translateAxisAngleAndPositionToVector(axisAngles, axisPosition, translated, numOfAxis);

    // 2. check if the axis are blocking
    //return checkIfAxisAreBlocking(translated);
}



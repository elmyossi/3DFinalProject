//
// Created by yossielman on 12/29/18.
//

#include "rotationAxis.h"
#include "../JaapSphere/jaapSphere.h"


bool rotationAxis::validateAxisFromUser(float axis[4][3], int numOfAxis) {
    for (int i =0; i<numOfAxis; i++){
        if (isValidAxis(axis[i]) == false){
            return false;
        }
    }
    return true;

}

bool rotationAxis::isValidAxis(float axis[3]) {
    RowVector3 core = jaapSphere::jaapSphereCore;
    double jaapSphereRadius = jaapSphere::jaapSphereRadius;
    double dist = calcDistance(RowVector3(axis[0], axis[1], axis[2]), core);
    if (dist > jaapSphereRadius){
        return false;
    }
    return true;

}


double rotationAxis::calcDistance(RowVector3 q, RowVector3 p) {
    return sqrt(pow((q[0] - p[0]), 2) + pow((q[1] - p[1]), 2) + pow((q[2] - p[2]), 2));
}


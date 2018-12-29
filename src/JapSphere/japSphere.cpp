//
// Created by michaelo on 12/28/18.
//

#include "japSphere.h"


double japSphere::getMinOutOfMesh(Eigen::MatrixXd meshPointsS, RowVector3 p) {
    RowVector3 argMin = meshPointsS.row(0);
    double minVal = calcDistance(argMin, p);
    double temp;
    for (int i = 1; i < meshPointsS.rows(); i++) {
        RowVector3 q = meshPointsS.row(i);
        temp = calcDistance(q, p);
        if (temp < minVal) {
            minVal = temp;
            argMin = q;
        }
    }
    return minVal;
}

double japSphere::calcDistance(RowVector3 q, RowVector3 p) {
    return sqrt(pow((q[0] - p[0]), 2) + pow((q[1] - p[1]), 2) + pow((q[2] - p[2]), 2));
}

RowVector3 japSphere::calculateCenterOfSphere(Eigen::MatrixXd meshPointsS, Eigen::MatrixXd meshPointsInnerS,
                                              int numberOfRowsInner) {
    RowVector3 argMax = meshPointsInnerS.row(0);
    double maxVal = getMinOutOfMesh(meshPointsS, argMax);
    double temp;
    for (int i = 1; i < numberOfRowsInner; i++) {
        RowVector3 p = meshPointsInnerS.row(i);
        temp = getMinOutOfMesh(meshPointsS, p);
        if (temp > maxVal) {
            argMax = p;
            maxVal = temp;
        }
    }
    return argMax;
}

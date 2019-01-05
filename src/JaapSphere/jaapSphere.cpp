//
// Created by michaelo on 12/28/18.
//

#include "jaapSphere.h"

RowVector3 jaapSphere::jaapSphereCore = RowVector3(0,0,0);
double jaapSphere::jaapSphereRadius = 0;
static const char *const innerPointsFilePath = "../points_bunny2.txt";

double jaapSphere::getMinOutOfMesh(Eigen::MatrixXd meshPointsS, RowVector3 p) {
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

double jaapSphere::calcDistance(RowVector3 q, RowVector3 p) {
    return sqrt(pow((q[0] - p[0]), 2) + pow((q[1] - p[1]), 2) + pow((q[2] - p[2]), 2));
}

RowVector3 jaapSphere::calculateCenterOfSphere(Eigen::MatrixXd meshPointsS, double& radiusSize) {

    ifstream inFile(innerPointsFilePath);
    long numberOfRowsInner = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');
    Eigen::MatrixXd meshPointsInnerS((numberOfRowsInner), 3);
    Utils::fillMeshInnerPoints(meshPointsInnerS, innerPointsFilePath);

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
    jaapSphere::jaapSphereRadius = maxVal;
    jaapSphere::jaapSphereCore = argMax;
    return argMax;
}



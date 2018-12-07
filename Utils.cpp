//
// Created by Yossi Elman on 2018-12-07.
//

#include "Utils.h"

RowVector3 Utils::calculateCenterOfMass(Eigen::MatrixXd V, Eigen::MatrixXi F) {
    RowVector3 massCenter = RowVector3(0, 0, 0);
    RowVector3 triangleCenter;
    double area;
    double mass = 0;
    for (int i = 0; i < F.rows(); i++)
    {
        RowVector3 v1 = V.row(F(i,0));
        RowVector3 v2 = V.row(F(i,1));
        RowVector3 v3 = V.row(F(i,2));
        triangleCenter = Utils::getCenterOfTriangle(v1, v2, v3);
        area = Utils::getAreaOfTriangle(v1, v2, v3);
        mass += area;
        massCenter[0] += area * triangleCenter[0];
        massCenter[1] += area * triangleCenter[1];
        massCenter[2] += area * triangleCenter[2];

    }
    massCenter[0] /= mass;
    massCenter[1] /= mass;
    massCenter[2] /= mass;
    return massCenter;

}


RowVector3 Utils::getCenterOfTriangle(RowVector3 v1, RowVector3 v2, RowVector3 v3)
{
    RowVector3 triangleCenter = RowVector3(0.0, 0.0, 0.0);
    triangleCenter[0] += v1[0];
    triangleCenter[0] += v2[0];
    triangleCenter[0] += v3[0];
    triangleCenter[1] += v1[1];
    triangleCenter[1] += v2[1];
    triangleCenter[1] += v3[1];
    triangleCenter[2] += v1[2];
    triangleCenter[2] += v2[2];
    triangleCenter[2] += v3[2];
    triangleCenter[0] /= 3;
    triangleCenter[1] /= 3;
    triangleCenter[2] /= 3;
    return triangleCenter;
}

double Utils::getAreaOfTriangle(RowVector3 v1, RowVector3 v2, RowVector3 v3) {
    double x1 = v1[0] - v2[0];
    double x2 = v1[1] - v2[1];
    double x3 = v1[2] - v2[2];
    double y1 = v1[0] - v3[0];
    double y2 = v1[1] - v3[1];
    double y3 = v1[2] - v3[2];
    return sqrt(pow(x2 * y3 - x3 * y2, 2) + pow(x3 * y1 - x1 * y3, 2) + pow(x1 * y2 - x2 * y1, 2) ) / 2.0;
}


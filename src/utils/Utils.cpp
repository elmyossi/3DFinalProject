//
// Created by Yossi Elman on 2018-12-07.
//

#include "Utils.h"

RowVector3 Utils::calculateCenterOfMassInside(Eigen::MatrixXd V, Eigen::MatrixXi F) {
    RowVector3 mg = RowVector3(0,0,0);
    RowVector3 O = RowVector3(0,0,0);
    double m =  0;
    for (int i = 0; i < F.rows(); i++)
    {
        RowVector3 v1 = V.row(F(i,0));
        RowVector3 v2 = V.row(F(i,1));
        RowVector3 v3 = V.row(F(i,2));
        double volume = Utils::SignedVolume(O, v1, v2, v3);
        m += volume;
        mg = mg + (volume * Utils::Centroid(O, v1, v2, v3));
    }
    return mg * 1.0/m;
}



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


RowVector3 Utils::Centroid(RowVector3 p1, RowVector3 p2, RowVector3 p3, RowVector3 p4)
{
    return 0.25*(p1+p2+p3+p4);
}

double Utils::SignedVolume(RowVector3 p1, RowVector3 p2, RowVector3 p3, RowVector3 p4)
{
    RowVector3 newP1 = RowVector3(p2[0]-p1[0], p2[1]-p1[1], p2[2]-p1[2]);
    RowVector3 newP2 = RowVector3(p3[0]-p1[0], p3[1]-p1[1], p3[2]-p1[2]);
    RowVector3 newP3 = RowVector3(p4[0]-p1[0], p4[1]-p1[1], p4[2]-p1[2]);
    RowVector3 cross = newP2.cross(newP3);
    double dot = newP1.dot(cross);
    return 1.0/6 * dot;
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


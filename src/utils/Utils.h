//
// Created by Yossi Elman on 2018-12-07.
//

#ifndef INC_3DFINALPROJECRT_UTIL_H
#define INC_3DFINALPROJECRT_UTIL_H

#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiTraits.h>
#include <iostream>
#include <cmath>

const double EulerConstant = std::exp(1.0);
typedef Eigen::Matrix<double, 1, 3> RowVector3;


class Utils {

public:
    static RowVector3 calculateCenterOfMass(Eigen::MatrixXd V, Eigen::MatrixXi F);
    static RowVector3 calculateCenterOfMassInside(Eigen::MatrixXd V, Eigen::MatrixXi F);


private:
    static RowVector3 getCenterOfTriangle(RowVector3 p1, RowVector3 p2, RowVector3 p3);
    static double getAreaOfTriangle(RowVector3 v1, RowVector3 v2, RowVector3 v3);
    static RowVector3 Centroid(RowVector3 p1, RowVector3 p2, RowVector3 p3, RowVector3 p4);
    static double SignedVolume(RowVector3 p1, RowVector3 p2, RowVector3 p3, RowVector3 p4);

};


#endif //INC_3DFINALPROJECRT_UTIL_H

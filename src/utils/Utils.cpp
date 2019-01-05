//
// Created by Yossi Elman on 2018-12-07.
//

#include "Utils.h"
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiTraits.h>
#include <igl/decimate.h>
#include <iostream>
#include "../../inc/slicing_plugin.h"
#include "../JaapSphere/jaapSphere.h"
#include <fstream>
#include <sstream>

RowVector3 Utils::calculateCenterOfMassInside(Eigen::MatrixXd V, Eigen::MatrixXi F) {
    RowVector3 mg = RowVector3(0, 0, 0);
    RowVector3 O = RowVector3(0, 0, 0);
    double m = 0;
    for (int i = 0; i < F.rows(); i++) {
        RowVector3 v1 = V.row(F(i, 0));
        RowVector3 v2 = V.row(F(i, 1));
        RowVector3 v3 = V.row(F(i, 2));
        double volume = Utils::SignedVolume(O, v1, v2, v3);
        m += volume;
        mg = mg + (volume * Utils::Centroid(O, v1, v2, v3));
    }
    return mg * 1.0 / m;
}


RowVector3 Utils::Centroid(RowVector3 p1, RowVector3 p2, RowVector3 p3, RowVector3 p4) {
    return 0.25 * (p1 + p2 + p3 + p4);
}

double Utils::SignedVolume(RowVector3 p1, RowVector3 p2, RowVector3 p3, RowVector3 p4) {
    RowVector3 newP1 = RowVector3(p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]);
    RowVector3 newP2 = RowVector3(p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2]);
    RowVector3 newP3 = RowVector3(p4[0] - p1[0], p4[1] - p1[1], p4[2] - p1[2]);
    RowVector3 cross = newP2.cross(newP3);
    double dot = newP1.dot(cross);
    return 1.0 / 6 * dot;
}


void Utils::fillMeshInnerPoints(Eigen::MatrixXd &meshInnerPoints, const char *innerPointsFilePath) {
    string line;
    ifstream meshInnerPointsFile;
    meshInnerPointsFile.open(innerPointsFilePath);
    int currentRow = 0;

    while (getline(meshInnerPointsFile, line)) {
        string lineWithoutBraces = line.substr(1, line.size() - 2);
        string arr[3];
        int i = 0;
        stringstream ssin(lineWithoutBraces);
        while (ssin.good() && i < 3) {
            ssin >> arr[i];
            ++i;
        }
        meshInnerPoints.row(currentRow)[0] = stof(arr[0]);
        meshInnerPoints.row(currentRow)[1] = stof(arr[1]);
        meshInnerPoints.row(currentRow)[2] = stof(arr[2]);
        currentRow++;
    }
}

void Utils::displayGUI(igl::opengl::glfw::Viewer viewer, Eigen::MatrixXd V, Eigen::MatrixXi F, RowVector3 core,
                       RowVector3 cm) {
    viewer.data().set_mesh(V, F);
    viewer.data().point_size = POINTS_DISPLAY_SIZE;
    viewer.data().add_points(core, RowVector3(255, 0, 0));
    viewer.data().add_points(cm, RowVector3(0, 255, 0));
    viewer.data().add_label(core, "Jaap Sphere Core");
    viewer.data().add_label(cm, "Center Mass");
    double jaapSphereRadius = jaapSphere::jaapSphereRadius;
    cout << "This is the radius:" << jaapSphereRadius << endl;

    SlicingPlugin menu;
    viewer.plugins.push_back(&menu);
    // Plot the mesh
    viewer.launch();
}

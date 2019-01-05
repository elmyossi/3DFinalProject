#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiTraits.h>
#include <igl/decimate.h>
#include <iostream>
#include "utils/Utils.h"
#include "JaapSphere/jaapSphere.h"
#include <fstream>
#include <sstream>


static const char *const innerPointsFilePath = "../points_bunny2.txt";
static const char *const objFilePath = "../goodBunny.obj";

using namespace std;

int main(int argc, char *argv[]) {

    ifstream inFile(innerPointsFilePath);
    long numberOfRows = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');

    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    Eigen::MatrixXd meshInnerPoints((numberOfRows), 3);

    // Load a mesh in OBJ format
    igl::readOBJ(objFilePath, V, F);

    // Attach a menu plugin
    igl::opengl::glfw::Viewer viewer;

    Utils::fillMeshInnerPoints(meshInnerPoints, innerPointsFilePath);

    double radiusSize;
    // Compute the optimal core position of the Jaap's sphere
    const RowVector3 &matrix = jaapSphere::calculateCenterOfSphere(V, meshInnerPoints, numberOfRows, radiusSize);

    RowVector3 cm = Utils::calculateCenterOfMassInside(V, F);

    RowVector3 core = RowVector3(matrix[0], matrix[1], matrix[2]);

    Utils::displayGUI(viewer, V, F, core, cm);

}


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
#include <stdio.h>
#include <stdlib.h>


static const char *const objFilePath = "../pre_processing/bunny.obj";

using namespace std;

void perform_pre_processing(){
    // the pre - processing stage is computational heavy, but need to be performed only once.
    // it performs:
    // 1. convert a given .stl file to obj
    // 2. calculates winding numbers on the .stl file
    system("../pre_processing/pre_proc.sh bunny");     //should be chmod +x
}

int main(int argc, char *argv[]) {

    // the program expects an .stl file to be located in the pre_processing folder
    perform_pre_processing();

    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    // Load a mesh in OBJ format
    igl::readOBJ(objFilePath, V, F);

    // Attach a menu plugin
    igl::opengl::glfw::Viewer viewer;

    double radiusSize;
    // Compute the optimal core position of the Jaap's sphere
    const RowVector3 &matrix = jaapSphere::calculateCenterOfSphere(V, radiusSize);

    RowVector3 cm = Utils::calculateCenterOfMassInside(V, F);

    RowVector3 core = RowVector3(matrix[0], matrix[1], matrix[2]);

    Utils::displayGUI(viewer, V, F, core, cm);

}


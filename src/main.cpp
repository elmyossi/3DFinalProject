#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiTraits.h>
#include <igl/decimate.h>
#include <iostream>
#include "utils/Utils.h"
#include "../inc/slicing_plugin.h"
#include "JaapSphere/jaapSphere.h"
#include <fstream>
#include <sstream>


static const char *const innerPointsFilePath = "../points_bunny2.txt";
static const char *const objFilePath = "../goodBunny.obj";

static int pointsDisplaySize = 10;
using namespace std;
string line;

bool DisplayInnerPoints = false;

int main(int argc, char *argv[]) {

    std::ifstream inFile(innerPointsFilePath);
    long numberOfRows = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');

    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    Eigen::MatrixXd meshInnerPoints((numberOfRows), 3);

    // Load a mesh in OBJ format
    igl::readOBJ(objFilePath, V, F);

    // Attach a menu plugin
    igl::opengl::glfw::Viewer viewer;

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

    double radiusSize;
    // Compute the optimal core position of the Jaap's sphere
    const RowVector3 &matrix = jaapSphere::calculateCenterOfSphere(V, meshInnerPoints,numberOfRows,radiusSize);

    std::cout << "This is x:" << matrix[0] << std::endl;
    std::cout << "This is y:" << matrix[1] << std::endl;
    std::cout << "This is z:" << matrix[2] << std::endl;

    RowVector3 cm = Utils::calculateCenterOfMassInside(V, F);
    RowVector3 zero = RowVector3(0,0,0);

    RowVector3 core = RowVector3(matrix[0], matrix[1], matrix[2]);

    viewer.data().set_mesh(V, F);
    viewer.data().point_size = pointsDisplaySize;
    viewer.data().add_points(core, RowVector3(0, 0, 0));
    viewer.data().add_points(cm, RowVector3(0, 0, 0));
    viewer.data().add_points(zero, RowVector3(0, 0, 0));
    if(DisplayInnerPoints){
        for(int i=0;i<numberOfRows;i++){
            viewer.data().add_points(meshInnerPoints.row(i), RowVector3(0, 0, 0));
        }
    }
    viewer.data().add_label(core, "THIS IS THE CORE");
    viewer.data().add_label(cm, "THIS IS THE Center Mass");
    viewer.data().add_label(zero, "THIS IS Zero");
    double jaapSphereRadius = jaapSphere::jaapSphereRadius;
    std::cout << "This is the radius:" << jaapSphereRadius << std::endl;

    SlicingPlugin menu;
    viewer.plugins.push_back(&menu);
    // Plot the mesh
    viewer.launch();
}

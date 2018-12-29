#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiTraits.h>
#include <iostream>
#include "utils/Utils.h"
#include "../inc/slicing_plugin.h"
#include "JapSphere/japSphere.h"
#include <fstream>
#include <sstream>


static const char *const innerPointsFilePath = "../points.txt";
using namespace std;
string line;

int main(int argc, char *argv[]) {

    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    Eigen::MatrixXd meshInnerPoints(2600, 3);

    // Load a mesh in OBJ format
    igl::readOBJ(argv[1], V, F);

    // Attach a menu plugin
    igl::opengl::glfw::Viewer viewer;

    ifstream meshInnerPointsFile;
    meshInnerPointsFile.open(innerPointsFilePath);
    int numberOfRows = 0;

    while (getline(meshInnerPointsFile, line)) {
        string lineWithoutBraces = line.substr(1, line.size() - 2);
        string arr[3];
        int i = 0;
        stringstream ssin(lineWithoutBraces);
        while (ssin.good() && i < 3) {
            ssin >> arr[i];
            ++i;
        }
        meshInnerPoints.row(numberOfRows)[0] = stof(arr[0]);
        meshInnerPoints.row(numberOfRows)[1] = stof(arr[1]);
        meshInnerPoints.row(numberOfRows)[2] = stof(arr[2]);
        numberOfRows++;
    }

    RowVector3 japCenter = japSphere::calculateCenterOfSphere(V, meshInnerPoints, numberOfRows);

    // Compute the optimal core position of the Jaap's sphere
    //TODO: add implementation
    const RowVector3 &matrix = japSphere::calculateCenterOfSphere(V, meshInnerPoints,numberOfRows);

    std::cout << "This is x:" << matrix[0] << std::endl;
    std::cout << "This is y:" << matrix[1] << std::endl;
    std::cout << "This is z:" << matrix[2] << std::endl;


    RowVector3 core = RowVector3(-0.0208036, 0.0858753, 0.010965);

    viewer.data().set_mesh(V, F);
    viewer.data().point_size = 100;
    viewer.data().add_points(core, RowVector3(0, 0, 0));

    viewer.data().add_label(core, "THIS IS THE CORE");

    SlicingPlugin menu;
    viewer.plugins.push_back(&menu);
    // Plot the mesh
    viewer.launch();
}

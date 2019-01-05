//
// Created by Yossi Elman on 2018-12-07.
//

#ifndef INC_3DFINALPROJECRT_UTIL_H
#define INC_3DFINALPROJECRT_UTIL_H
#include <functional>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiTraits.h>
#include <iostream>
#include <cmath>
#include <unordered_set>


#define POINTS_DISPLAY_SIZE 10;
#define MAX_NUMBER_OF_AXIS 3

using namespace std;
const double EulerConstant = std::exp(1.0);
typedef Eigen::Matrix<double, 1, 3> RowVector3;
typedef Eigen::Matrix<double, 1, 3> CylRowVector3;
typedef Eigen::Matrix<double, 1, 2> CylRowVector2;


namespace std {
    template <typename Scalar, int Rows, int Cols>
    struct hash<Eigen::Matrix<Scalar, Rows, Cols>> {
        // https://wjngkoh.wordpress.com/2015/03/04/c-hash-function-for-eigen-matrix-and-vector/
        size_t operator()(const Eigen::Matrix<Scalar, Rows, Cols>& matrix) const {
            size_t seed = 0;
            for (size_t i = 0; i < matrix.size(); ++i) {
                Scalar elem = *(matrix.data() + i);
                seed ^=
                        std::hash<Scalar>()(elem) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}



class Utils {

public:

    /*
     * this function calculates the center of mass given the mesh by (V,F)
     */
    static RowVector3 calculateCenterOfMassInside(Eigen::MatrixXd V, Eigen::MatrixXi F);

    /*
     * this fucntion receives the file with the points inside
     * the 3d-mesh and fills the MatrixXd with the points
     */
    static void fillMeshInnerPoints(Eigen::MatrixXd &meshInnerPoints, const char *innerPointsFilePath);

    /*
     * receives parameters from main function to display and displays them
     */
    static void
    displayGUI(igl::opengl::glfw::Viewer viewer, Eigen::MatrixXd V, Eigen::MatrixXi F, RowVector3 core, RowVector3 cm);

    /*
     * receives RowVector3 in cartesian coordinates (x,y,z)
     * and returns a RowVector in Cylindrical coordinates (z,r,theta)
     */
    static CylRowVector3 transformToCylindricalCoordinates(RowVector3 cartesian);

    /*
     * this function receives a list of CylRowVector3 and returns a set with all the points reduced
     * to dimension (z,r) only
     */
    static unordered_set<CylRowVector2> reduceThetaDim(list<CylRowVector3> &CylindricalPointsList);

private:

    static RowVector3 Centroid(RowVector3 p1, RowVector3 p2, RowVector3 p3, RowVector3 p4);

    static double SignedVolume(RowVector3 p1, RowVector3 p2, RowVector3 p3, RowVector3 p4);

    static CylRowVector2 reduceToCyl(CylRowVector3 &cyl);
};


#endif //INC_3DFINALPROJECRT_UTIL_H

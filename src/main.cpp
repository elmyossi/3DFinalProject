#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <igl/opengl/glfw/imgui/ImGuiTraits.h>
#include <iostream>
#include "utils/Utils.h"

int main(int argc, char *argv[])
{
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;

  // Load a mesh in OBJ format
  igl::readOBJ(argv[1], V, F);

  // Attach a menu plugin
  igl::opengl::glfw::imgui::ImGuiMenu menu;
  igl::opengl::glfw::Viewer viewer;

  // Compute the optimal core position of the Jaap's sphere
  //TODO: add implementation
  const RowVector3 &matrix = Utils::calculateCenterOfMassInside(V, F);

  std::cout << "This is x:" << matrix[0] << std::endl;
  std::cout << "This is y:" << matrix[1] << std::endl;
  std::cout << "This is z:" << matrix[2] << std::endl;


  viewer.plugins.push_back(&menu);
  // Add content to the default menu window
  menu.callback_draw_viewer_menu = [&]()
  {
      // Draw parent menu content
      menu.draw_viewer_menu();
  };
  // Plot the mesh
  viewer.data().set_mesh(V, F);
  viewer.launch();
}

#pragma once
////////////////////////////////////////////////////////////////////////////////
#include "../imguizmo/ImGuizmo.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <vector>
#include <Eigen/Dense>
#include "../src/rotationAxis/rotationAxis.h"
////////////////////////////////////////////////////////////////////////////////

namespace ImGuizmo {

void EditTransform(const float *cameraView, float *cameraProjection, float* matrix)
{
	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
	static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };

	// if (ImGui::IsKeyPressed(90))
	// 	mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	// if (ImGui::IsKeyPressed(69))
	// 	mCurrentGizmoOperation = ImGuizmo::ROTATE;
	// if (ImGui::IsKeyPressed(82)) // r Key
	// 	mCurrentGizmoOperation = ImGuizmo::SCALE;
	if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);
	ImGui::InputFloat3("Tr", matrixTranslation, 3);
	ImGui::InputFloat3("Rt", matrixRotation, 3);
	ImGui::InputFloat3("Sc", matrixScale, 3);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);

	if (mCurrentGizmoOperation != ImGuizmo::SCALE)
	{
		if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
			mCurrentGizmoMode = ImGuizmo::LOCAL;
		ImGui::SameLine();
		if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
			mCurrentGizmoMode = ImGuizmo::WORLD;
	}
	// if (ImGui::IsKeyPressed(83))
	// 	useSnap = !useSnap;
	// ImGui::Checkbox("##Snap", &useSnap);
	// ImGui::SameLine();

	// switch (mCurrentGizmoOperation)
	// {
	// case ImGuizmo::TRANSLATE:
	// 	ImGui::InputFloat3("Snap", &snap[0]);
	// 	break;
	// case ImGuizmo::ROTATE:
	// 	ImGui::InputFloat("Angle Snap", &snap[0]);
	// 	break;
	// case ImGuizmo::SCALE:
	// 	ImGui::InputFloat("Scale Snap", &snap[0]);
	// 	break;
	// }

	// Expose an enumeration type
	static int rotation_index = 0;
	static float axisAngles[4][3] = {0};
	static float axisPosition[4][3] = {0};

	ImGui::Combo("Axis index to set", (int *)(&rotation_index), "Axis 1\0Axis 2\0Axis 3\0Axis 4\0\0");

	if (ImGui::Button("Capture axis", ImVec2(-1,0)))
	{
		axisAngles[rotation_index][0] = matrixRotation[0];
		axisPosition[rotation_index][0] = matrixTranslation[0]-0.095f;
		axisAngles[rotation_index][1] = matrixRotation[1];
		axisPosition[rotation_index][1] = matrixTranslation[1]-0.508f;
		axisAngles[rotation_index][2] = matrixRotation[2];
		axisPosition[rotation_index][2] = matrixTranslation[2]-0.05f;
	}
	//static std::vector<std::string> axis;
	// each axis is 2d vector: axis[0] vector defines the direction, axis[1] defines the center
	ImGui::InputFloat3("Axis 1: direction", axisAngles[0], 3);
	ImGui::InputFloat3("Axis 1: center", axisPosition[0], 3);
	ImGui::InputFloat3("Axis 2: direction", axisAngles[1], 3);
	ImGui::InputFloat3("Axis 2: center", axisPosition[1], 3);
	ImGui::InputFloat3("Axis 3: direction", axisAngles[2], 3);
	ImGui::InputFloat3("Axis 3: center", axisPosition[2], 3);
	ImGui::InputFloat3("Axis 4: direction", axisAngles[3], 3);
	ImGui::InputFloat3("Axis 4: center", axisPosition[3], 3);

	if (ImGui::Button("Done", ImVec2(-1,0)))
	{
		// 1. validate that the Rotation Axis centers cut the Jaap sphere
		// we will have the core position and the maximal radius as parameters.
		// given the core position we will translate the rotation axis center like the core is the center
		// if the distance from the core to one of the center is bigger then the radius -> error
		// 2. we will represent each axis using 1 single vector:
		//			* its direction will be perpendicular to the vector connecting both centers.
		if (rotationAxis::validateAxisFromUser(axisPosition, 4) == false)
		{
			std::cout << "Axis NOT VALID"<< std::endl;
		}
		else {
			std::cout << "OK :)))))"<< std::endl;
		}
		//validateAxis(axis);


	}





	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL);
}

} // namespace ImGuizmo

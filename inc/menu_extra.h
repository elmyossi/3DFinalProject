#pragma once
////////////////////////////////////////////////////////////////////////////////
#include "../imguizmo/ImGuizmo.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <vector>
#include <Eigen/Dense>
#include "../src/rotationAxis/RotationAxis.h"
////////////////////////////////////////////////////////////////////////////////

namespace ImGuizmo {
	static const float ZPI = 3.14159265358979323846f;
	static const float RAD2DEG = (180.f / ZPI);
	static const float DEG2RAD = (ZPI / 180.f);

	const float screenRotateSize = 0.06f;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//template <typename T> T LERP(T x, T y, float z) { return (x + (y - x)*z); }
	template <typename T> T Clamp(T x, T y, T z) { return ((x<y) ? y : ((x>z) ? z : x)); }
	template <typename T> T max(T x, T y) { return (x > y) ? x : y; }
	template <typename T> T min(T x, T y) { return (x < y) ? x : y; }
	template <typename T> bool IsWithin(T x, T y, T z) { return (x>=y) && (x<=z); }

	struct matrix_t;
	struct vec_t
	{
	public:
		float x, y, z, w;

		void Lerp(const vec_t& v, float t)
		{
			x += (v.x - x) * t;
			y += (v.y - y) * t;
			z += (v.z - z) * t;
			w += (v.w - w) * t;
		}

		void Set(float v) { x = y = z = w = v; }
		void Set(float _x, float _y, float _z = 0.f, float _w = 0.f) { x = _x; y = _y; z = _z; w = _w; }

		vec_t& operator -= (const vec_t& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
		vec_t& operator += (const vec_t& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
		vec_t& operator *= (const vec_t& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
		vec_t& operator *= (float v) { x *= v;    y *= v;    z *= v;    w *= v;    return *this; }

		vec_t operator * (float f) const;
		vec_t operator - () const;
		vec_t operator - (const vec_t& v) const;
		vec_t operator + (const vec_t& v) const;
		vec_t operator * (const vec_t& v) const;

		const vec_t& operator + () const { return (*this); }
		float Length() const { return sqrtf(x*x + y*y + z*z); };
		float LengthSq() const { return (x*x + y*y + z*z); };
		vec_t Normalize() { (*this) *= (1.f / Length()); return (*this); }
		vec_t Normalize(const vec_t& v) { this->Set(v.x, v.y, v.z, v.w); this->Normalize(); return (*this); }
		vec_t Abs() const;


		float& operator [] (size_t index) { return ((float*)&x)[index]; }
		const float& operator [] (size_t index) const { return ((const float*)&x)[index]; }
	};


	struct matrix_t
	{
	public:

		union
		{
			float m[4][4];
			float m16[16];
			struct
			{
				vec_t right, up, dir, position;
			} v;
			vec_t component[4];
		};

		matrix_t(const matrix_t& other) { memcpy(&m16[0], &other.m16[0], sizeof(float) * 16); }
		matrix_t() {}

		operator float * () { return m16; }
		operator const float* () const { return m16; }
	};

void EditTransform(const float *cameraView, float *cameraProjection, float* matrix, Eigen::MatrixXd V)
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
	static float axisAngles[MAX_NUMBER_OF_AXIS][3] = {0};
	static float axisPosition[MAX_NUMBER_OF_AXIS][3] = {0};
	matrix_t& mat = *(matrix_t*)matrix;


	ImGui::Combo("Axis index to set", (int *)(&rotation_index), "Axis 1\0Axis 2\0Axis 3\0\0");

	if (ImGui::Button("Capture axis", ImVec2(-1,0)))
	{
	    float centerX = (V.row(0)[0] + V.row(1)[0] + V.row(2)[0] + V.row(3)[0] )/ 4.0;
        float centerY = (V.row(0)[1] + V.row(1)[1] + V.row(2)[1] + V.row(3)[1] )/ 4.0;
        float centerZ = (V.row(0)[2] + V.row(1)[2] + V.row(2)[2] + V.row(3)[2] )/ 4.0;
        axisAngles[rotation_index][0] = mat.v.dir[0];
		axisPosition[rotation_index][0] = centerX;
		axisAngles[rotation_index][1] = mat.v.dir[1];
		axisPosition[rotation_index][1] = centerY;
		axisAngles[rotation_index][2] = mat.v.dir[2];
		axisPosition[rotation_index][2] = centerZ;
	}
	//static std::vector<std::string> axis;
	// each axis is 2d vector: axis[0] vector defines the direction, axis[1] defines the center
	ImGui::InputFloat3("Axis 1: direction", axisAngles[0], 3);
	ImGui::InputFloat3("Axis 1: center", axisPosition[0], 3);
	ImGui::InputFloat3("Axis 2: direction", axisAngles[1], 3);
	ImGui::InputFloat3("Axis 2: center", axisPosition[1], 3);
	ImGui::InputFloat3("Axis 3: direction", axisAngles[2], 3);
	ImGui::InputFloat3("Axis 3: center", axisPosition[2], 3);
//	ImGui::InputFloat3("Axis 4: direction", axisAngles[3], 3);
//	ImGui::InputFloat3("Axis 4: center", axisPosition[3], 3);

	if (ImGui::Button("Done", ImVec2(-1,0)))
	{
		// 1. validate that the Rotation Axis centers cut the Jaap sphere
		// we will have the core position and the maximal radius as parameters.
		// if the distance from the core to one of the axis' center is bigger then the radius -> error
		// 2. we will represent each axis using 1 single vector:
		//			* its direction will be perpendicular to the vector connecting both centers.
		bool allAxisAreValid = RotationAxis::validateAxisFromUser(axisPosition, MAX_NUMBER_OF_AXIS);
		if (allAxisAreValid) {
            std::cout << "All axes are inside the sphere!"<< std::endl;
            bool puzzleIsBlocking = true;
			puzzleIsBlocking = RotationAxis::handleAxisFromUser(axisAngles, axisPosition, MAX_NUMBER_OF_AXIS);
			if (puzzleIsBlocking){
				std::cout << "Puzzle is Blocking!"<< std::endl;
			} else {
				std::cout << "Puzzle is not Blocking!"<< std::endl;
			}
        }
		else {
            std::cout << "At least one axis is outside the sphere"<< std::endl;
		}

	}

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL);
}

} // namespace ImGuizmo

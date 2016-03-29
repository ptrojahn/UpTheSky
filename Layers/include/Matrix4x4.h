#pragma once

#include <algorithm>

class Matrix4x4
{
public:
	Matrix4x4() {
		std::fill(values, values + 16, 0);
	}
	Matrix4x4(	float v0_0, float v1_0, float v2_0, float v3_0,
				float v0_1, float v1_1, float v2_1, float v3_1,
				float v0_2, float v1_2, float v2_2, float v3_2,
				float v0_3, float v1_3, float v2_3, float v3_3) {
		//The matrix needs to be transposed because opengl wants column major matrices
		values[0] = v0_0; values[1] = v0_1; values[2] = v0_2; values[3] = v0_3;
		values[4] = v1_0; values[5] = v1_1; values[6] = v1_2; values[7] = v1_3;
		values[8] = v2_0; values[9] = v2_1; values[10] = v2_2; values[11] = v2_3;
		values[12] = v3_0; values[13] = v3_1; values[14] = v3_2; values[15] = v3_3;
	}
	Matrix4x4 operator*(Matrix4x4 matrix) {
		return Matrix4x4(	values[0] * matrix.values[0] + values[4] * matrix.values[1] + values[8] * matrix.values[2] + values[12] * matrix.values[3],
							values[0] * matrix.values[4] + values[4] * matrix.values[5] + values[8] * matrix.values[6] + values[12] * matrix.values[7],
							values[0] * matrix.values[8] + values[4] * matrix.values[9] + values[8] * matrix.values[10] + values[12] * matrix.values[11],
							values[0] * matrix.values[12] + values[4] * matrix.values[13] + values[8] * matrix.values[14] + values[12] * matrix.values[15],
							values[1] * matrix.values[0] + values[5] * matrix.values[1] + values[9] * matrix.values[2] + values[13] * matrix.values[3],
							values[1] * matrix.values[4] + values[5] * matrix.values[5] + values[9] * matrix.values[6] + values[13] * matrix.values[7],
							values[1] * matrix.values[8] + values[5] * matrix.values[9] + values[9] * matrix.values[10] + values[13] * matrix.values[11],
							values[1] * matrix.values[12] + values[5] * matrix.values[13] + values[9] * matrix.values[14] + values[13] * matrix.values[15],
							values[2] * matrix.values[0] + values[6] * matrix.values[1] + values[10] * matrix.values[2] + values[14] * matrix.values[3],
							values[2] * matrix.values[4] + values[6] * matrix.values[5] + values[10] * matrix.values[6] + values[14] * matrix.values[7],
							values[2] * matrix.values[8] + values[6] * matrix.values[9] + values[10] * matrix.values[10] + values[14] * matrix.values[11],
							values[2] * matrix.values[12] + values[6] * matrix.values[13] + values[10] * matrix.values[14] + values[14] * matrix.values[15],
							values[3] * matrix.values[0] + values[7] * matrix.values[1] + values[11] * matrix.values[2] + values[15] * matrix.values[3],
							values[3] * matrix.values[4] + values[7] * matrix.values[5] + values[11] * matrix.values[6] + values[15] * matrix.values[7],
							values[3] * matrix.values[8] + values[7] * matrix.values[9] + values[11] * matrix.values[10] + values[15] * matrix.values[11],
							values[3] * matrix.values[12] + values[7] * matrix.values[13] + values[11] * matrix.values[14] + values[15] * matrix.values[15]);
	}

	float values[16];
};
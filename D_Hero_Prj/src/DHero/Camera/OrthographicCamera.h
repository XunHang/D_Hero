#pragma once

#include "DHero/Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DH {

	class DH_API OrthographicCamera {

	public:
		// 正交投影需要设置 Frustum
		OrthographicCamera(float left, float right, float bottom, float top, float n = -1.0f, float f = 1.0f);

		void ReCalculateMatrix(float left, float right, float bottom, float top, float n = -1.0f, float f = 1.0f);

		// 获取相机的位姿数据，计算 View 矩阵
		const glm::vec3& GetPosition() const { return m_Position; } // 返回类型是引用，前加 const
		float GetRotation() const { return m_Rotation; }

		void SetPosition(glm::vec3& position) { m_Position = position; ReCalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; ReCalculateViewMatrix(); }

		// 相机的核心就是 View 与 Projection 矩阵，留有返回三个矩阵的接口
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void ReCalculateViewMatrix();

	private:
		glm::vec3 m_Position;
		float m_Rotation;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};

}
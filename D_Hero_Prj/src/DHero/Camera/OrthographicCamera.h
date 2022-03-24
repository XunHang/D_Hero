#pragma once

#include "DHero/Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DH {

	class DH_API OrthographicCamera {

	public:
		// ����ͶӰ��Ҫ���� Frustum
		OrthographicCamera(float left, float right, float bottom, float top, float n = -1.0f, float f = 1.0f);

		void ReCalculateMatrix(float left, float right, float bottom, float top, float n = -1.0f, float f = 1.0f);

		// ��ȡ�����λ�����ݣ����� View ����
		const glm::vec3& GetPosition() const { return m_Position; } // �������������ã�ǰ�� const
		float GetRotation() const { return m_Rotation; }

		void SetPosition(glm::vec3& position) { m_Position = position; ReCalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; ReCalculateViewMatrix(); }

		// ����ĺ��ľ��� View �� Projection �������з�����������Ľӿ�
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
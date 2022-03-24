#include "dhpch.h"

#include "OrthographicCamera.h"

namespace DH {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float n, float f)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, n, f)), m_ViewMatrix(1.0f){

		//m_ViewProjectionMatrix = m_ProjectionMatrix* m_ViewMatrix;
		m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
	}
	
	void OrthographicCamera::ReCalculateMatrix(float left, float right, float bottom, float top, float n, float f) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, n, f);
		//m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
	}

	void OrthographicCamera::ReCalculateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		// 相机移动，相当于所有物体反向移动
		m_ViewMatrix = glm::inverse(transform);
		//m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
	}
}
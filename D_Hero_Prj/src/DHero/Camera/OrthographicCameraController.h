#pragma once
#include "DHero/Core/Core.h"
#include "DHero/Camera/OrthographicCamera.h"
#include "DHero/Core/TimeStep.h"
#include "DHero/Events/Event.h"


namespace DH {

	class DH_API OrthographicCameraController {
	public:
		OrthographicCameraController();
		OrthographicCameraController(float aspectRatio, float zoom);

		void OnUpdate(const TimeStep& step);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }


	private:
		void OnZoomCamera(float scrollOffset);

	private:
		float m_ZoomMax = 3.0f;
		float m_ZoomMin = 0.15f;
		float m_Aspect = 4.0f / 3.0f;
		float m_Zoom = 1.0f;

		float m_RotateSpeed = 10.0f;
		float m_MoveSpeed = 1.0f;
		bool m_Rotatable = true;

		OrthographicCamera m_Camera;	
	};

}
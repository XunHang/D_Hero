#include "dhpch.h"

#include "OrthographicCameraController.h"
#include "DHero/Core/Input.h"
#include "DHero/Core/KeyCodes.h"
#include "DHero/Events/MouseEvent.h"

namespace DH {
	OrthographicCameraController::OrthographicCameraController()
		:m_Camera(-m_Aspect * m_Zoom, m_Aspect* m_Zoom, -m_Zoom, m_Zoom, -1, 1){
	}
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float zoom)
		:m_Camera(-aspectRatio * zoom, aspectRatio* zoom, -zoom, zoom, -1, 1) {
	}

	void OrthographicCameraController::OnUpdate(const TimeStep& step) {
		auto cameraPosition = m_Camera.GetPosition();

		if (Input::IsKeyPressed(Key::A))
			cameraPosition.x += step * m_MoveSpeed;
		else if (Input::IsKeyPressed(Key::D))
			cameraPosition.x -= step * m_MoveSpeed;

		if (Input::IsKeyPressed(Key::W))
			cameraPosition.y += step * m_MoveSpeed;
		else if(Input::IsKeyPressed(Key::S))
			cameraPosition.y -= step * m_MoveSpeed;

		if (m_Rotatable) {
			auto cameraRotation = m_Camera.GetRotation();
			if (Input::IsKeyPressed(Key::Q))
				cameraRotation += step * m_RotateSpeed;
			else if (Input::IsKeyPressed(Key::E))
				cameraRotation -= step * m_RotateSpeed;

			m_Camera.SetRotation(cameraRotation);
		}
		m_Camera.SetPosition(cameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e) {
		if (e.GetEventType() == EventType::MouseScrolled) {
			MouseScrolledEvent* ep = dynamic_cast<MouseScrolledEvent*>(&e);
			OnZoomCamera(ep->GetYOffset());
		}
	}

	void OrthographicCameraController::OnZoomCamera(float scrollOffset) {
		m_Zoom -= scrollOffset*0.2;
		m_Zoom = std::clamp(m_Zoom, m_ZoomMin, m_ZoomMax);
		m_Camera.ReCalculateMatrix(-m_Aspect * m_Zoom, m_Aspect * m_Zoom, -m_Zoom, m_Zoom, -1, 1);
	}

}
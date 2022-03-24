#pragma once

#include "DHero/Core/Core.h"

#include "RenderCommand.h"
#include "Shader.h"

#include "DHero/Camera/OrthographicCamera.h"

/*
* Renderer Ӧ���ܹ���
* 1. ���û��������Ϣ��
* 2. ���ܱ���Ⱦ�����������ݣ����㡢���ʡ�shader �ȣ�
* 3. ��Ⱦ���壨���� DrawCall��
* 4. ��������ͬ���ʵ�����һ����Ⱦ���Ż����ܣ�
*/
namespace DH {

	// Renderer �ӿ�����׼����Ⱦ����Ҫ������
	class DH_API Renderer {
	public:
		inline static RendererAPI::Type GetAPI() { return RendererAPI::GetAPI(); }

		static void Init();

		// ������Ⱦ��������Ҫ�� camera��lighting �Ȳ���
		static void BeginScene(OrthographicCamera& camera);

		static void EndScene();

		// ͨ�� RenderCommand �� VAO ��Ϣ���ݸ� RenderCommandQueue
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>&, const glm::mat4&);


	protected:

	private:
		struct SceneData
		{
			glm::mat4 View;
			glm::mat4 Projection;
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}

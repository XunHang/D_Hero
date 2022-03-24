#pragma once

#include "DHero/Core/Core.h"

#include "RenderCommand.h"
#include "Shader.h"

#include "DHero/Camera/OrthographicCamera.h"

/*
* Renderer 应该能够：
* 1. 设置环境相关信息；
* 2. 接受被渲染物体的相关数据（顶点、材质、shader 等）
* 3. 渲染物体（调用 DrawCall）
* 4. 批处理（相同材质的物体一起渲染以优化性能）
*/
namespace DH {

	// Renderer 接口用于准备渲染所需要的数据
	class DH_API Renderer {
	public:
		inline static RendererAPI::Type GetAPI() { return RendererAPI::GetAPI(); }

		static void Init();

		// 配置渲染场景所需要的 camera、lighting 等参数
		static void BeginScene(OrthographicCamera& camera);

		static void EndScene();

		// 通过 RenderCommand 把 VAO 信息传递给 RenderCommandQueue
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

#pragma once

#include "DHero/Core.h"
#include "Layer.h"


namespace DH {

	/*
	* 将 层栈 中的 “层” 分为普通层与覆盖层两种；
	* push 与 pop 操作普通层时，通过 insert 迭代器跟踪其位置
	* 而 覆盖层 overlay 的操作实现方式，保证了 overlay 总是在所有普通层的最后	
	*/
	class DH_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex;

	};
}


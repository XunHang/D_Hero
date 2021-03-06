#include "dhpch.h"
#include "LayerStack.h"


namespace DH {
	LayerStack::LayerStack() {
		m_LayerInsertIndex = 0;
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		// 因为覆盖层与普通层是分割开的，不知能否使用下面这种写法？
		// auto it = std::find(m_Layers.begin(), m_LayerInsert, layer);		

		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}

	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		// 因为覆盖层与普通层是分割开的，不知能否使用下面这种写法？
		// auto it = std::find(m_LayerInsert, m_Layers.end(), layer);

		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}

	}
}
#pragma once

#include "DHero/Core.h"
#include "Layer.h"


namespace DH {

	/*
	* �� ��ջ �е� ���㡱 ��Ϊ��ͨ���븲�ǲ����֣�
	* push �� pop ������ͨ��ʱ��ͨ�� insert ������������λ��
	* �� ���ǲ� overlay �Ĳ���ʵ�ַ�ʽ����֤�� overlay ������������ͨ������	
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


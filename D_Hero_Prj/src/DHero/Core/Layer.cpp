#include "dhpch.h"
#include "Layer.h"


namespace DH {
	Layer::Layer(const std::string& name)
		:m_debugName(name) {}

	Layer::~Layer()  {}
}
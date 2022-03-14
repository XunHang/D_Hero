#include "dhpch.h"
#include <DHero.h>

class SandBox :public DH::Application {
public:
	SandBox() {

	}
	~SandBox() {

	}
};

DH::Application* DH::CreaterApplication() {
	return new SandBox();
}

//void main() {
//	SandBox* sandBox = new SandBox();
//	sandBox->Run();
//	delete sandBox;
//}
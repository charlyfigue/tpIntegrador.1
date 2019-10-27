#include <iostream>
#include "imguiAcces.h"
#include "ImGuiController.h"

int main() {
	imguiAcces imguiWidgets;
	if (imguiWidgets.imguiBegin())
	{
		Model modelo;
		//View interface(modelo);
		ImGuiController Controller(&imguiWidgets, modelo);
		//modelo.attach(&interface);
		//modelo.attach(&Controller);

		while (!Controller.isOver()) {
			Controller.cycle();
		}

		imguiWidgets.imguiDestroy();
	}
	return 0;
}
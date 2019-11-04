#include <iostream>
#include "imguiAcces.h"
#include "ImGuiController.h"
#include "View.h"

int main() {
	imguiAcces imguiWidgets;
	if (imguiWidgets.imguiBegin())
	{
		Model modelo;
		View interface(modelo);
		ImGuiController Control(&imguiWidgets, modelo);
		modelo.attach(&interface);
		modelo.attach(&Control);
		while (!Control.isOver()) {
			Control.cycle();
		}

		imguiWidgets.imguiDestroy();
	}
	return 0;
}
#include <iostream>
#include "ImGuiController.h"
#include <boost/filesystem.hpp>
#include <string> 
#include <vector>

using namespace boost::filesystem;

ImGuiController::ImGuiController(imguiAcces* imguiInterfaz, Model& modelo) : Controller(modelo) {
	lookProperties = false;
	isError = true;
	isFinished = false;
	shouldQuit = false;
	oldVelocidad = 1;
	queueEmpty = false;
	velocidad = 1;
	oldCantidadTuits = 0;
	cantidadTuits = 0;
	stateOfScroll = false;
	display = imguiInterfaz->getDisplay();
	eventQueue = imguiInterfaz->getEventQueue();
	if (eventQueue != NULL)
	{
		al_register_event_source(eventQueue, al_get_keyboard_event_source());
		al_register_event_source(eventQueue, al_get_mouse_event_source());
		al_register_event_source(eventQueue, al_get_display_event_source(display));
		isError = false;
	}
	else
		std::cout << "Error en la inicializacion del controler" << std::endl;
}

void ImGuiController::update(void* objeto) {
	//printf("Pantalla actualizada\n");
}

bool ImGuiController::isOver() {
	return isFinished;
}

void ImGuiController::cycle() {
	getEvent();
	dispatch();
}

void ImGuiController::getEvent() {
	if (!al_get_next_event(eventQueue, &ev))
		queueEmpty = true;
	else
		queueEmpty = false;
}

void ImGuiController::dispatch() {
	if (!queueEmpty) {
		ImGui_ImplAllegro5_ProcessEvent(&ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			isFinished = true;
	}
	else {
		ImGui_ImplAllegro5_NewFrame();
		ImGui::NewFrame();

		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("EDA Encoder");

		static char newpath[256] = {};
		bool windows[1000];
		int i = 0;
		std::string labels[1000];
		std::vector<ALLEGRO_BITMAP*> vbitmap;
		if (!lookProperties) {
			ImGui::InputText("Ingresar Directorio", newpath, sizeof(newpath));
			ImGui::Separator();


			std::string fileName(newpath);
			m.getFilesFromFolder(fileName);

			for (int j = 0; j < m.getCantOfFiles(); j++) {
				ImGui::Checkbox(((m.getPathnames())->at(j)).c_str(), &(m.getLabel())[j]);
				if ((m.getLabel())[j]) {
					ImGui::SameLine();
					ImGui::Text("      ");
					ImGui::SameLine();
					if (ImGui::Button("Propiedades"))
						lookProperties = true;
					m.fileChoosen(j);
				}
			}
		}
		else {
			if (ImGui::Button("Volver")) {
				m.reInitSearchFileFromFolder();
				lookProperties = false;
			}
		}

		ImGui::End();

		// Rendering
		ImGui::Render();
		al_clear_to_color(al_map_rgba_f(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
		ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
		al_flip_display();
	}
}

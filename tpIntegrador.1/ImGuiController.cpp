#include <iostream>
#include "ImGuiController.h"
#include <boost/filesystem.hpp>
#include <string> 
#include <vector>

using namespace boost::filesystem;

ImGuiController::ImGuiController(imguiAcces* imguiInterfaz, Model& modelo) : Controller(modelo) {
	watchingOutput = false;
	lookProperties = false;
	lookBlocksProperties = false;
	calculateMerkleRoot = false;
	validateMerkleRoot = false;
	watchMerkleRoot = false;
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
				ImGui::Checkbox(((m.getPathnames())->at(j)).c_str(), &(m.getPathLabel())[j]);
				if ((m.getPathLabel())[j]) {
					ImGui::SameLine();
					ImGui::Text("      ");
					ImGui::SameLine();
					if (ImGui::Button("Propiedades")) {
						m.setFileChoseen(j);
						m.findNumberOfBlocks();
						lookProperties = true;
					}
					m.fileChoosen(j);
				}
			}
			
			ImGui::NewLine();
			ImGui::NewLine();
			if (ImGui::Button("Salir")) {
				isFinished = true;
			}
		}
		else {
			if ((!lookBlocksProperties) && (!calculateMerkleRoot) && (!validateMerkleRoot) && (!watchMerkleRoot)) {
				for (int j = 0; j < m.getNumberOfBlocks(); j++) {
					ImGui::Checkbox(((m.getBlockNames())->at(j)).c_str(), &(m.getBlocksLabel())[j]);
					if ((m.getBlocksLabel())[j]) {
						ImGui::SameLine();
						ImGui::Text("      ");
						ImGui::SameLine();
						ImGui::Columns(3, "Acciones posibles", false);
						ImGui::NextColumn();
						if (ImGui::Button("Propiedades"))
							lookBlocksProperties = true;
						if (ImGui::Button("Calcular Merkle root"))
							calculateMerkleRoot = true;
						if (ImGui::Button("Validar Merkle root"))
							validateMerkleRoot = true;
						if (ImGui::Button("Ver Merkle root"))
							watchMerkleRoot = true;
						ImGui::Columns();
						m.blockChoosen(j);
					}
				}

				ImGui::NewLine();
				ImGui::NewLine();

				if (ImGui::Button("Volver")) {
					m.reInitSearchFileFromFolder();
					lookProperties = false;
				}
			}
			else {
				if (lookBlocksProperties) {
					if (!watchingOutput) {
						m.viewInformation();
						watchingOutput = true;
					}
				}
				else if (calculateMerkleRoot) {
					if (!watchingOutput) {
						m.calculateMerkle();
						watchingOutput = true;
					}
				}
				else if (validateMerkleRoot) {
					if (!watchingOutput) {
						m.validateMerkle();
						watchingOutput = true;
					}
				}
				else {
					if (!watchingOutput) {
						m.watchMerkle();
						watchingOutput = true;
					}
				}
				ImGui::NewLine();
				ImGui::NewLine();
				if (ImGui::Button("Volver")) {
					m.reInitSearchBlockFromFile();
					watchingOutput = false;
					if (lookBlocksProperties)
						lookBlocksProperties = false;
					if (calculateMerkleRoot)
						calculateMerkleRoot = false;
					if (validateMerkleRoot)
						validateMerkleRoot = false;
					if (watchMerkleRoot)
						watchMerkleRoot = false;
				}
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

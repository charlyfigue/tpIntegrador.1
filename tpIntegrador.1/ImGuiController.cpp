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

		ImGui::Begin("EDA TP Integrador");
		
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
						m.setFileChosen(j);
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
			for (int j = 0; j < m.getNumberOfBlocks(); j++) {
				ImGui::Checkbox((m.getBlockOfGroup(j)->getBlockName().c_str()), &(m.getBlocksLabel())[j]);//ImGui::Checkbox(((m.getBlockNames())->at(j)).c_str(), &(m.getBlocksLabel())[j]);
				if ((m.getBlocksLabel())[j]) {
					ImGui::End();
					ImGui::Begin((m.getBlockOfGroup(j)->getBlockName().c_str()));//ImGui::Begin(((m.getBlockNames())->at(j)).c_str());
					printBlocksProperties(j);
					ImGui::End();
					ImGui::Begin("EDA TP Integrador");
				}
			}

			ImGui::NewLine();
			ImGui::NewLine();

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

void ImGuiController::printBlocksProperties(int j){
	if((!m.getBlockOfGroup(j)->getLookProperties()) && (!m.getBlockOfGroup(j)->getCalculatedMerkle())
		&& (!m.getBlockOfGroup(j)->getValidatedMerkle()) && (!m.getBlockOfGroup(j)->getWatchMerkle())){
		ImGui::NewLine();
		if (ImGui::Button("Propiedades"))
			m.getBlockOfGroup(j)->setLookProperties(true);
		if (ImGui::Button("Calcular Merkle root"))
			m.getBlockOfGroup(j)->setCalculatedMerkle(true);
		if (ImGui::Button("Validar Merkle root"))
			m.getBlockOfGroup(j)->setValidatedMerkle(true);
		if (ImGui::Button("Ver Merkle root"))
			m.getBlockOfGroup(j)->setWatchMerkle(true);
		m.blockChoosen(j);
		ImGui::NewLine();
		if (ImGui::Button("Cerrar")) {
			m.noShowBlock(j);
		}
	}
	else {
		if (m.getBlockOfGroup(j)->getLookProperties()) {
			if (!watchingOutput) {
				m.viewInformation();
				watchingOutput = true;
			}
			ImGui::NewLine();
			ImGui::Text((m.getInformationMessage()).c_str());
		}
		else if (m.getBlockOfGroup(j)->getCalculatedMerkle()) {
			if (!watchingOutput) {
				m.serMerkle(m.calculateMerkle());
				watchingOutput = true;
			}
			ImGui::NewLine();
			ImGui::Text((m.getMerkle()).c_str());
		}
		else if (m.getBlockOfGroup(j)->getValidatedMerkle()) {
			if (!watchingOutput) {
				m.validateMerkle();
				watchingOutput = true;
			}
			ImGui::NewLine();
			ImGui::Text((m.getValidMessage()).c_str());
		}
		else {
			if (!watchingOutput) {
				m.watchMerkle();
				watchingOutput = true;
			}
			ImGui::NewLine();
			ImVec2 sizeImag = ImVec2(500.0f, 300.0f);
			ImGui::Image(m.getOutputImage(), sizeImag);
		}
		ImGui::NewLine();
		ImGui::NewLine();
		if (ImGui::Button("Volver")) {
			watchingOutput = false;
			if (m.getBlockOfGroup(j)->getLookProperties())
				m.getBlockOfGroup(j)->setLookProperties(false);
			if (m.getBlockOfGroup(j)->getCalculatedMerkle())
				m.getBlockOfGroup(j)->setCalculatedMerkle(false);
			if (m.getBlockOfGroup(j)->getValidatedMerkle())
				m.getBlockOfGroup(j)->setValidatedMerkle(false);
			if (m.getBlockOfGroup(j)->getWatchMerkle())
				m.getBlockOfGroup(j)->setWatchMerkle(false);
		}
	}
}
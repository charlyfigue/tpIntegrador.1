/*#include <iostream>
#include "ImGuiController.h"
#include <string> 

ImGuiController::ImGuiController(ALLEGRO_DISPLAY** disp, Model& modelo) : Controller(modelo) {
	isError = true;
	shouldQuit = false;
	oldVelocidad = 1;
	queueEmpty = false;
	velocidad = 1;
	oldCantidadTuits = 0;
	cantidadTuits = 0;
	stateOfScroll = false;
	display = (*disp);
	eventQueue = al_create_event_queue();
	if (eventQueue != NULL)
	{
		al_register_event_source(eventQueue, al_get_keyboard_event_source());
		al_register_event_source(eventQueue, al_get_mouse_event_source());
		al_register_event_source(eventQueue, al_get_display_event_source(display));
		isError = false;
	}
}

ImGuiController::~ImGuiController()
{
	al_unregister_event_source(eventQueue, al_get_display_event_source(display));
	al_destroy_event_queue(eventQueue);
}

void ImGuiController::update(void* objeto) {
	//printf("Pantalla actualizada\n");
}

void ImGuiController::run() {
	while (ev.type != FIN_IMGUI) {
		cycle();
	}
}

void ImGuiController::cycle() {
	if (al_get_next_event(eventQueue, &ev)) {
		queueEmpty = false;
		//if (!(ev.type == NO_EVENT) && !(ev.type == FIN_IMGUI)) {
		dispatch();
		//}
	}
	else {
		queueEmpty = true;
		dispatch();
	}
}

void ImGuiController::getEvent() {
	if (!al_get_next_event(eventQueue, &ev))
		ev.type = NO_EVENT;
}

void ImGuiController::dispatch() {
	if (!queueEmpty) {
		ImGui_ImplAllegro5_ProcessEvent(&ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			shouldQuit = true;
			ev.type = FIN_IMGUI;
			return;
		}
	}
	else {
		ImGui_ImplAllegro5_NewFrame();
		ImGui::NewFrame();
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("EDA Twitter");

		static char user[50] = {};

		ImGui::Text("Puede conocer los tuits publicados por otra persona.");
		ImGui::Text("Ingrese el usuario abajo y la cantidad de tuits que solicita.");
		ImGui::Text("De no enviar esta ultima, se tomara el valor default de Twitter.");
		ImGui::NewLine();
		ImGui::InputText("Usuario a buscar", user, sizeof(user));
		ImGui::NewLine();
		ImGui::Checkbox("Especificar cantidad", &isCantidad);
		if (!m.getInProcess()) {
			if (isCantidad) {
				ImGui::SliderInt("Numero de tweets", &cantidadTuits, 0, 100);
				if ((!stateOfScroll) || (oldCantidadTuits != cantidadTuits)) {
					m.changeTweetAmount(cantidadTuits);
					oldCantidadTuits = cantidadTuits;
				}
				stateOfScroll = true;
			}
			else {
				if (stateOfScroll)
					m.changeTweetAmount(0);
				stateOfScroll = false;
			}
		}
		ImGui::NewLine();
		bool startDownload = ImGui::Button("Comenzar operacion");
		if (startDownload) {

			if (m.getInProcess() == false) {
				if (tweethand.startFetchingTweets(user, cantidadTuits)) {
					m.setUser(user);
					m.manageOutputWhile();
					m.startDownload();
					isCantidad = false;
				}
				else {
					vector<string> errors;
					errors.push_back("No se pudo iniciar la obtencion de tweets");
					m.setErrors(errors);
				}
			}
		}
		if (m.getInProcess()) {

			ImGui::NewLine();
			ImGui::Text("Descargando archivos...");
			ImGui::SameLine();
			bool cancel = ImGui::Button("Cancelar descarga");
			if (cancel || tweethand.performFetch()) {
				m.setErrors(tweethand.cleanupFetch());
				m.setTweets(tweethand.getTweets());
				m.setTweetsDates(tweethand.getDates());
				m.manageOutputDo();
				m.finishDownload();
			}
			else {
				m.sendWhileOutput();
			}
		}
		if (m.isFinished()) {
			ImGui::Text("Tweets descargados: %d", m.getTweetAmount());
			ImGui::Text("Mostrando en pantalla: Tuit%d", m.getCurrentTweetIndex());
			ImGui::NewLine();
			bool pre = ImGui::Button("Tweet anterior");
			ImGui::SameLine();
			bool reset = ImGui::Button("Repetir Tweet");
			ImGui::SameLine();
			bool pos = ImGui::Button("Tweet posterior");
			ImGui::SliderInt("Velocidad", &velocidad, 1, 8);
			ImGui::NewLine();
			bool reInit = ImGui::Button("Reiniciar la busqueda");
			if (pre)
				m.showPreviousTweet();
			if (pos)
				m.showNextTweet();
			if (reset)
				m.resetTweet();
			if (oldVelocidad != velocidad) {
				m.changeSpeed(velocidad);
				oldVelocidad = velocidad;
			}
			if (reInit)
				m.readyForDownload();
			m.displayTuits();
			bool salir = ImGui::Button("Salir");
			if (salir) {
				ev.type = FIN_IMGUI;
				return;
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
*/
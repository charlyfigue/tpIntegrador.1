#pragma once
#include "Controller.h"
#include "Model.h"
#include "imguiAcces.h"

#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define FIN_IMGUI ALLEGRO_EVENT_DISPLAY_CLOSE
#define NO_EVENT ALLEGRO_EVENT_MOUSE_BUTTON_UP

typedef ALLEGRO_EVENT Evento;
typedef ALLEGRO_EVENT_QUEUE * ColaDeEvento;
typedef ALLEGRO_DISPLAY* Display;

class ImGuiController :public Controller {
public:
	ImGuiController(imguiAcces* imguiInterfaz, Model& modelo);
	void update(void*);
	void run(void);
	void cycle(void);
	bool getLookProperties() { return lookProperties; }
	bool isOver(void);

private:
	void getEvent(void);
	void dispatch(void);
	void printBlocksProperties(int);
	Evento ev;
	ColaDeEvento eventQueue;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* tempBitmap;
	bool lookProperties;
	bool lookBlocksProperties;
	bool calculateMerkleRoot;
	bool validateMerkleRoot;
	bool watchMerkleRoot;
	bool isFinished;
	bool queueEmpty;
	bool isError;
	bool shouldQuit;
	bool isCantidad;
	bool stateOfScroll;
	bool watchingOutput;
	int oldCantidadTuits;
	int cantidadTuits;
	int velocidad;
	int oldVelocidad;
};
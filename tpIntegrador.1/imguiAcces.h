#pragma once
#include <iostream>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define ALLEGRO_STATICLINK
#define FIN_IMGUI ALLEGRO_EVENT_DISPLAY_CLOSE
#define NO_EVENT ALLEGRO_EVENT_MOUSE_BUTTON_UP

typedef ALLEGRO_EVENT Evento;
typedef ALLEGRO_EVENT_QUEUE * ColaDeEvento;
typedef ALLEGRO_DISPLAY* Display;

#define LIGHT_GRAY al_map_rgb(195,195,195)

class imguiAcces{
public:
	bool imguiBegin(void);
	void imguiDestroy(void);
	Display getDisplay(void);
	ColaDeEvento getEventQueue(void);
protected:
	Evento ev;
	ColaDeEvento eventQueue;
	Display display;
};
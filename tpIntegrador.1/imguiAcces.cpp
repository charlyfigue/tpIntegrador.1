#include "imguiAcces.h"
#include <iostream>

bool imguiAcces::imguiBegin(){
	if (al_init())
	{
		if (al_init_primitives_addon())
		{
			if (al_install_keyboard())
			{
				if (al_install_mouse())
				{
					if (al_init_font_addon())
					{
						if (al_init_ttf_addon())
						{
							display = al_create_display(800, 600);
							if (display != NULL)
							{
								eventQueue = al_create_event_queue();
								if (eventQueue != NULL)
								{
									al_register_event_source(eventQueue, al_get_keyboard_event_source());
									al_register_event_source(eventQueue, al_get_mouse_event_source());
									al_register_event_source(eventQueue, al_get_display_event_source(display));
									al_set_window_title(display, "EDA Encoder");
									IMGUI_CHECKVERSION();
									ImGui::CreateContext();
									ImGuiIO& io = ImGui::GetIO(); (void)io;
									//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
									ImGui::StyleColorsDark();
									ImGui_ImplAllegro5_Init(display);
									std::cout << "Initialization has been finished" << std::endl;
									return true;
								}
							}
							else
								std::cout << "Unable to create display" << std::endl;
							al_shutdown_ttf_addon();
						}
						else
							std::cout << "Unable to init ttf font addon" << std::endl;
						al_shutdown_font_addon();
					}
					else
						std::cout << "Unable to init font addon" << std::endl;
					al_uninstall_mouse();
				}
				else
					std::cout << "Unable to install mouse" << std::endl;
				al_uninstall_keyboard();
			}
			else
				std::cout << "Unable to install keyboard" << std::endl;
			al_shutdown_primitives_addon();
		}
		else
			std::cout << "Unable to init primitives addon" << std::endl;
	}
	else
		std::cout << "Unable to init Allegro" << std::endl;
	return false;
}

void imguiAcces::imguiDestroy() {
	ImGui_ImplAllegro5_Shutdown();
	ImGui::DestroyContext();
	al_destroy_display(display);
	al_shutdown_font_addon();
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_shutdown_primitives_addon();
	al_unregister_event_source(eventQueue, al_get_display_event_source(display));
	al_destroy_event_queue(eventQueue);
}

Display imguiAcces::getDisplay() {
	return display;
}

ColaDeEvento imguiAcces::getEventQueue() {
	return eventQueue;
}
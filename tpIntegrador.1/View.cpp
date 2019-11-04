#include "View.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"

void View::update(void*) {
	std::vector<std::string> merkle = m.getMerkleVector();
	ALLEGRO_BITMAP* actual = al_get_target_bitmap();
	ALLEGRO_BITMAP* tempBitmap = al_create_bitmap(500, 300);
	al_set_target_bitmap(tempBitmap);
	int cont = 0;
	int posX = 0;
	int posY = 0;
	int floors = 0;
	if (merkle.size() > 1) {
		std::string target = merkle[0];
		while (((cont) < (merkle.size()))) {
			while ((target != SEPARADOR) && (cont < (merkle.size()))) {
				std::cout << target.c_str() << std::endl;
				al_draw_filled_rectangle(posX + 30, posY + 220, posX + 100, posY + 250, al_map_rgb(255, 255, 0));
				al_draw_textf(al_load_ttf_font("disney.ttf", 12, 0), al_map_rgb(0, 0, 0), posX + 65, posY + 230, ALLEGRO_ALIGN_CENTRE, target.c_str());
				if (cont == (merkle.size() - 1))
					break;
				cont++;
				posX += 130 * (floors + 1);
				target = merkle[cont];
			}
			floors++;
			posY -= 60;
			posX = 60 + ((floors - 1) * 130);
			if (cont == (merkle.size() - 1))
				break;
			cont++;
			target = merkle[cont];
		}
	}
	else {
		al_draw_filled_rectangle(160, 135, 340, 165, al_map_rgb(255, 255, 0));
		al_draw_textf(al_load_ttf_font("disney.ttf", 12, 0), al_map_rgb(0, 0, 0), 250, 140, ALLEGRO_ALIGN_CENTRE, (merkle[0]).c_str());
	}
	al_set_target_bitmap(actual);
	m.setOutputImage(tempBitmap);
	//return tempBitmap;
}
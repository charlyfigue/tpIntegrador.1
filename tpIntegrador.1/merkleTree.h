#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>

#define SEPARADOR "separador2345"
#define NO_TRANSACTION "No hay transaccion"

class MerkleTree {
public:
	MerkleTree();
	void viewInformation(void);
	std::string calculateMerkle(std::vector<std::string>, int);
	std::vector<std::string> getMerkleVector() { return merkle; }

private:
	std::string separator;
	std::vector<std::string> leafs;
	std::vector<std::string> merkle;
	std::vector<std::string> recursiveTree(std::vector<std::string>);
	int numberOfLeafs;
	int cantOfSeparators;
	ALLEGRO_BITMAP* outBitmap;
};
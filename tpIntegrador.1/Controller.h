#pragma once
#define ALLEGRO_STATICLINK
#include "Observer.h"
#include "Model.h"
//#include <allegro5\allegro.h>

class Controller : public observer
{
public:
	//Controller() {}
	Controller(Model& mod) :m(mod) {}
	virtual void update(void*) = 0;
	virtual void cycle(void) = 0;
	Model* getModel() { return &m; }
protected:
	virtual void getEvent(void) = 0;
	virtual void dispatch(void) = 0;
	Model& m;
};

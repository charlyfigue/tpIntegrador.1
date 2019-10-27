#pragma once
//#define ALLEGRO_STATICLINK
#include "Observer.h"
#include "Model.h"

class Controller : public observer
{
public:
	Controller(Model& mod) :m(mod) {}
	virtual void update(void*) = 0;
	virtual void cycle(void) = 0;
	Model* getModel() { return &m; }
protected:
	virtual void getEvent(void) = 0;
	virtual void dispatch(void) = 0;
	Model& m;
};

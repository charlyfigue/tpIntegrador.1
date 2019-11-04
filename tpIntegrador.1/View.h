#pragma once
#include <iostream>
#include "Observer.h"
#include "Model.h"

class View : public observer {
public:
	View(Model& modelo) :m(modelo){}
	void update(void*);
private:
	Model& m;
};
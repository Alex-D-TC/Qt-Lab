#pragma once
#include "UndoAction.h"
#include <vector>

class UndoRem : public UndoAction<Medicament> {
private:

	Repository &container;
	Medicament obj;

public:

	UndoRem(Repository &container, Medicament obj) :
		obj(obj),
		container(container) {}

	UndoRem(Repository &container) :
		obj(Medicament{}),
		container(container) {}

	void doUndo() {
		container.addElement(obj);
	}

	void operator=(UndoRem rhs) {
		this->obj = rhs.obj;
		this->container = rhs.container;
	}
};

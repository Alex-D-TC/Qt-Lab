#pragma once
#include "UndoAction.h"
#include <vector>

class UndoMod : public UndoAction<Medicament> {
private:
	Repository &container;
	Medicament obj;

public:

	UndoMod(Repository &container, Medicament obj) :
		obj(obj),
		container(container)
	{}

	UndoMod(Repository &container) :
		obj(Medicament{}),
		container(container)
	{}

	void doUndo() {
		container.updateElement(obj);
	}

};
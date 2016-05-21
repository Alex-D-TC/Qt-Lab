#pragma once
#include "UndoAction.h"
#include "Repository.h"
#include <vector>
#include <algorithm>
#include <iterator>

class UndoAdd : public UndoAction<Medicament> {

	Medicament obj;
	Repository &container;

public:

	UndoAdd(Repository &container) : 
		obj(Medicament{}),
		container(container) {}

	UndoAdd(Repository &container, Medicament obj) :
		obj(obj),
		container(container) {}

	void doUndo() {
		container.removeElement(obj);
	}

	void operator=(UndoAdd rhs) {
		this->obj = rhs.obj;
		this->container = rhs.container;
	}
};
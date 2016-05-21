#pragma once
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include "Repository.h"
#include "ControlConstants.h"
#include "UndoAdd.h"
#include "UndoAction.h"
#include "UndoMod.h"
#include "UndoRem.h"

class Controller {
private:
	Repository& repo;
	vector<Medicament> shpCart;
	vector<std::shared_ptr<UndoAction<Medicament>>> stateVector;
	typedef bool(*compF)(Medicament a, Medicament b);
	typedef bool(*filterF)(Medicament med, string value);

	/*
		Determines the compare method to use when sorting
	*/
	compF Controller::determineMethod(int order, int type);

	/*
		Determines the method used for the filtering algorithm
	*/
	filterF determineMethodF(string type);

public:

	// CONSTRUCTORS | DESTRUCTORS
	/*
		Base constructor
	*/
	Controller(Repository& repo) :
		repo(repo),
		shpCart(vector<Medicament>{})
	{}

	/*
		Copy constructor
	*/
	Controller(const Controller& rhs) = delete;

	// CORE LOGIC

	/*
		Gets the shopping cart
	*/
	vector<Medicament> getShpCart() {
		return shpCart;
	}

	/*
		Adds a new medicine to the shopping cart
	*/
	vector<Medicament> addToCart(Medicament med) {
		shpCart.push_back(med);
		return shpCart;
	}

	/*
		Saves the shopping cart to a CSV or HTML file
	*/
	void saveToFile(string choice, string filename);
	
	/*
		Executes the undo function
		Throws invalid_argument if the undo list is empty
	*/
	void undo() {
		if (stateVector.size() == 0)
			throw invalid_argument("Cannot undo!");
		std::shared_ptr<UndoAction<Medicament>> act = stateVector.at(stateVector.size() - 1);
		act->doUndo();
		stateVector.pop_back();
	}

	/*
		Adds an UndoAdd UndoAction to the undo stack
	*/
	void saveUndoAdd(Medicament med) {
		stateVector.push_back(
			std::shared_ptr<UndoAdd>{ new UndoAdd{ repo, med } });
	}

	/*
		Adds an UndoRem UndoAction to the undo stack
	*/
	void saveUndoRem(Medicament med) {
		stateVector.push_back(
			std::shared_ptr<UndoRem>{new UndoRem{ repo, med }});
	}

	/*
		Adds an UndoMod UndoAction to the undo stack
	*/
	void saveUndoMod(Medicament med) {
		stateVector.push_back(
			std::shared_ptr<UndoMod>{new UndoMod{ repo, med }});
	}

	/*
		Generates a random shopping cart of a given size
	*/
	vector<Medicament> generate(int size);

	/*
		Empties the shopping cart
	*/
	vector<Medicament> emptyShpCart() {
		shpCart = vector<Medicament>{};
		return shpCart;
	}

	/*
		Adds an element to the repository
	*/
	void addElement(string denumire, int pret, string producator, string substActiva) {
		Medicament med{ denumire, pret, producator, substActiva };
		repo.addElement(med);
		saveUndoAdd(med);
	}

	/*
		Removes an element from the repository
	*/
	Medicament removeElement(string denumire, string producator) {
		Medicament med = repo.removeElement(Medicament{ denumire, 10, producator, "" });
		saveUndoRem(med);
		return med;
	}

	/*
		Gets all elements similar to the one requested
		The equivalence class is defined through the name and producer
	*/
	vector<Medicament>
		Controller::getSimElemes(string denumire, string producator);

	/*
		Updates an element in the repository
	*/
	void updateElement(string denumire, int pret, string producator, string substActiva) {
		vector<Medicament> vect = repo.getAll();
		Medicament med{ denumire, pret, producator, substActiva };
		vector<Medicament>::iterator it = find_if(vect.begin(), vect.end(), [&med](Medicament medicament) {
			return med == medicament;
		});
		repo.updateElement(med);
		saveUndoMod(*it);
	}

	/*
		Returns an iterator for all items in the repository
	*/
	vector<Medicament> getAll() {
		return repo.getAll();
	}

	/*
		Returns a sorted vector of elements
		OBS: The returned pointer must be destroyed after use
	*/
	vector<Medicament> get_sorted(string order ,string type, vector<Medicament> *list = nullptr);

	/*
			Returns a dynamic vector containing all elements, filtered
		by a given type - value pair
		OBS: The vector must be destroyed after usage
	*/
	vector<Medicament> filter(string type, string value);
};
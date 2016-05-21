#pragma once
#include "Medicament.h"
#include <vector>
#include <algorithm>

class Repository {
private:
	vector<Medicament> list;
public:
		
	// CONSTRUCTORS | DESTRUCTORS
	
	/*
		Base constructor
	*/
	Repository() : list{ vector<Medicament>{} } {}

	/*
		Copy constructor
	*/
	Repository(const Repository& rhs) : list(rhs.list) {}

	void operator=(const Repository& rhs) {
		this->list = rhs.list;
	}

	/*
		Destructor
	*/
	~Repository() = default;

	// CORE LOGIC

	/*
		Adds an element to the repository
		Raises exception if the element already exists
	*/
	virtual void addElement(Medicament med) {
		vector<Medicament>::iterator res = find(list.begin(), list.end(), med);
		if (res != list.end())
			throw invalid_argument{ "Medicine already exists!" };
		list.push_back(med);
	}

	/*
		Removes an element from the repository
		Raises exception if the element is not found
	*/
	virtual Medicament removeElement(Medicament element) {
		vector<Medicament>::iterator result = find(list.begin(), list.end(), element);
		if (result == list.end())
			throw invalid_argument{"Medicamentul nu a fost gasit"};
		Medicament retV = *result;
		list.erase(result);
		return retV;
	}

	/*
		Modifies an element from the repository
	*/
	virtual void updateElement(Medicament element) {
		vector<Medicament>::iterator result = find(list.begin(), list.end(), element);
		if (result == list.end())
			throw invalid_argument{ "Medicamentul nu a fost gasit" };
		for_each(list.begin(), list.end(), [&element](Medicament &med) {
			if (element == med) {
				med.setPret(element.getPret());
				med.setSubstActiva(element.getSubstActiva());
			}
		});
	}

	/*
		Returns a copy of the entire repository
	*/
	vector<Medicament> getAll() {
		return list;
	}
};
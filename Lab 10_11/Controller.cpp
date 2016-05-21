#include "Controller.h"
#include "FSaver.h"
#include "CSVFSaver.h"
#include "HTMLFSaver.h"
#include <iterator>
#include <algorithm>

vector<Medicament> Controller::generate(int size) {
	vector<Medicament> list = repo.getAll();
	emptyShpCart();
	if (list.size() == 0)
		throw invalid_argument("No medicine!");
	while (shpCart.size() < size) {
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(list.begin(), list.end(), std::default_random_engine(seed));
		shpCart.push_back(list.at(0));
	}
	return shpCart;
}

vector<Medicament>
	Controller::getSimElemes(string denumire, string producator) {
	vector<Medicament> vect = this->repo.getAll();
	vector<Medicament> newV;
	copy_if(vect.begin(), vect.end(), back_inserter(newV), [&denumire, &producator](Medicament med) {
		return med.getDenumire() == denumire
			&& med.getProducator() == producator;
	});
	if (newV.size() == 0) {
		throw invalid_argument("Nici un medicament nu a fost gasit ");
	}
	return newV;
}

void Controller::saveToFile(string choice, string filename) {
	FSaver<Medicament> *saver;
	if (shpCart.size() == 0)
		throw invalid_argument("Shopping cart is invalid!");
	if (choice == "CSV") {
		saver = new CSVFSaver<Medicament>{};
	}
	else if (choice == "HTML") {
		saver = new HTMLFSaver<Medicament>{};
	}
	else {
		saver = new HTMLFSaver<Medicament>{ new CSVFSaver<Medicament>{} };
	}
	saver->saveToFile(shpCart, filename);
	delete saver;
}

vector<Medicament> Controller::get_sorted(string order, string type, vector<Medicament> *list) {
	int iOrder, iType;
	transform(order.begin(), order.end(), order.begin(), ::tolower);
	transform(type.begin(), type.end(), type.begin(), ::tolower);

	if (order == "crescator")
		iOrder = CRESCATOR;
	else if (order == "descrescator")
		iOrder = DESCRESCATOR;
	else
		throw invalid_argument("Ordinea este invalida! ");
	
	if (type == "producator")
		iType = PRODUCATOR;
	else if (type == "pret")
		iType = PRET;
	else if (type == "denumire")
		iType = DENUMIRE;
	else if (type == "substanta activa")
		iType = SUBST_ACTIVA;
	else throw invalid_argument("Tipul introdus este invalid! ");

	compF comp = determineMethod(iOrder, iType);

	if (list == nullptr) {
		vector<Medicament> v = repo.getAll();
		sort(v.begin(), v.end(), comp);
		return v;
	}
	sort(list->begin(), list->end(), comp);
	return *list;
}

// PRICE SORTING FUNCTIONS

bool compMedicineAscendingPret(Medicament a, Medicament b) {
	return a.getPret() > b.getPret();
}

bool compMedicineDescendingPret(Medicament a, Medicament b) {
	return a.getPret() < b.getPret();
}

// NAME SORTING FUNCTIONS

bool compMedicineAscendingDenumire(Medicament a, Medicament b) {
	return a.getDenumire() > b.getDenumire();
}

bool compMedicineDescendingDenumire(Medicament a, Medicament b) {
	return a.getDenumire() < b.getDenumire();
}

// PRODUCER SORTING FUNCTIONS

bool compMedicineAscendingProducator(Medicament a, Medicament b) {
	return a.getProducator() > b.getProducator();
}

bool compMedicineDescendingProducator(Medicament a, Medicament b) {
	return a.getProducator() < b.getProducator();
}

// ACTIVE SUBSTANCE SORTING FUNCTIONS

bool compMedicineAscendingASub(Medicament a, Medicament b) {
	return a.getSubstActiva() > b.getSubstActiva();
}

bool compMedicineDescendingASub(Medicament a, Medicament b) {
	return a.getSubstActiva() < b.getSubstActiva();
}

Controller::compF Controller::determineMethod(int order, int type) {
	if (type == PRET) {
		if (order == CRESCATOR)
			return compMedicineAscendingPret;
		return compMedicineDescendingPret;
	}
	if (type == DENUMIRE) {
		if (order == CRESCATOR)
			return compMedicineAscendingDenumire;
		return compMedicineDescendingDenumire;
	}
	if (type == PRODUCATOR) {
		if (order == CRESCATOR)
			return compMedicineAscendingProducator;
		return compMedicineDescendingProducator;
	}
	if (type == SUBST_ACTIVA) {
		if (order == CRESCATOR)
			return compMedicineAscendingASub;
		return compMedicineDescendingASub;
	}
}

bool filterMedicineName(Medicament a, string value) {
	return strstr(a.getDenumire().c_str(), value.c_str()) == nullptr;
}

bool filterMedicinePret(Medicament a, string value) {
	int val = stoi(value);
	return a.getPret() >= val;
}

bool filterMedicineSAct(Medicament a, string value) {
	return a.getSubstActiva() == value;
}

bool filterMedicineProducer(Medicament a, string value) {
	return a.getProducator() == value;
}

Controller::filterF Controller::determineMethodF(string type) {
	if (type == "denumire")
		return filterMedicineName;
	if (type == "pret")
		return filterMedicinePret;
	if (type == "producator")
		return filterMedicineProducer;
	if (type == "substanta activa")
		return filterMedicineSAct;
	throw invalid_argument("Tip invalid introdus! ");
}

vector<Medicament> Controller::filter(string type, string value) {
	transform(type.begin(), type.end(), type.begin(), ::tolower);
	filterF func = determineMethodF(type);
	vector<Medicament> resultVector;
	vector<Medicament> vector = repo.getAll();

	copy_if(vector.begin(), vector.end(), back_inserter(resultVector), [&func, &value](Medicament med) {
		return func(med, value);
	});

	return resultVector;
}

#pragma once
#include <string>

using namespace std;

class Medicament {
private:
	string denumire;
	int pret;
	string producator;
	string substActiva;
	friend ostream& operator<<(ostream& os, const Medicament& ob);

public:

	// CONSTRUCTORS | DESTRUCTORS
	/*
		Empty constructor
	*/
	Medicament() :
		denumire(""),
		pret(0),
		producator(""),
		substActiva("")
	{}

	/*
		Standard constructor
	*/
	Medicament(string denumire, int pret, string producator, string substActiva) {
		this->denumire = denumire;
		this->pret = pret;
		this->producator = producator;
		this->substActiva = substActiva ;
	}

	/*
		Copy constructor
	*/
	Medicament(const Medicament& other) {
		this->denumire = other.denumire;
		this->pret = other.pret;
		this->producator = other.producator;
		this->substActiva = other.substActiva;
	
	}

	/*
		Destructor
	*/
	~Medicament() = default;

	// GETTERS
	/*
		Gets the name
	*/
	string getDenumire() const {
		return this->denumire;
	}

	/*
		Gets the price
	*/
	int getPret() const {
		return this->pret;
	}

	/*
		Gets the producer
	*/
	string getProducator() const {
		return this->producator;
	}

	/*
		Gets the active substance
	*/
	string getSubstActiva() const {
		return this->substActiva;
	}

	// SETTERS
	/*
		Sets the name
	*/
	void setDenumire(const string newDenumire) {
		this->denumire = newDenumire;
	}

	/*
		Sets the price
	*/
	void setPret(const int newPret) {
		this->pret = newPret;
	}

	/*
		Sets the producer
	*/
	void setProducator(const string newProducator) {
		this->producator = newProducator;
	}

	/*
		Sets the active substance
	*/
	void setSubstActiva(const string newSubstActiva) {
		this->substActiva = newSubstActiva;
	}

	bool operator==(const Medicament &other) const {
		return this->denumire == other.denumire &&
			this->producator == other.producator;
	}

};
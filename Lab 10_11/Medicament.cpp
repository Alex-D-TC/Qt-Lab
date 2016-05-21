#include "stdafx.h"
#include "Medicament.h"

ostream& operator<<(ostream &os, const Medicament &other) {
	return os << other.denumire << ";" <<
		other.pret << ";" <<
		other.producator << ";" <<
		other.substActiva;
}
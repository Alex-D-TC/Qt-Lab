#pragma once
#include "FSaver.h"
#include <fstream>

template<typename T>
class CSVFSaver : public FSaver<T>{
public:

	/*
		Saves the list to the CSV file
	*/
	void saveToFile(const vector<T>& vect, string output) {
		ofstream g{ output + ".csv" };
		for_each(vect.begin(), vect.end(), [&g](Medicament med) {
			g << med << endl;
		});
		if (next != nullptr) {
			next->saveToFile(vect, output);
		}
	}

	// CONSTRUCTORS | DESTRUCTORS

	CSVFSaver() = default;

	CSVFSaver(FSaver<T>* next) { 
		FSaver<T>::next = next;
	}

	CSVFSaver(const CSVFSaver& rhs) = default;

	~CSVFSaver() = default;

};
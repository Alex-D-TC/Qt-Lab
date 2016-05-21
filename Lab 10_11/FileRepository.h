#pragma once
#include <fstream>
#include "Repository.h"
#include "FSaver.h"
#include "CSVFSaver.h"

class FileRepository : public Repository {
private:
	string filename;


	/*
		Reads all the data from a CSV file
	*/
	void readAll() {
		char line[1000];
		char* s;
		const char* delimiter = ";";
		string fname = filename;
		fname.append(".csv");
		ifstream f{fname};

		// denumire ; pret ; producator ; substanta activa
		while (!f.eof()) {
			string denumire, producator, substActiva;
			int pret;
			f.getline(line, 1000, '\n');
			s = strtok(line, delimiter);
			if (strlen(line) == 0)
				break;
			denumire.append(s);
			s = strtok(nullptr, delimiter);
			pret = atoi(s);
			s = strtok(nullptr, delimiter);
			producator.append(s);
			s = strtok(nullptr, delimiter);
			substActiva.append(s);
			Repository::addElement(Medicament{ denumire, pret, producator, substActiva });
		}

		f.close();
	}

public:

	void addElement(Medicament element) {
		Repository::addElement(element);
		CSVFSaver<Medicament> saver{};
		saver.saveToFile(getAll(), filename);
	}

	Medicament removeElement(Medicament element) {
		Medicament med = Repository::removeElement(element);
		CSVFSaver<Medicament> saver{};
		saver.saveToFile(getAll(), filename);
		return med;
	}

	void updateElement(Medicament element) {
		Repository::updateElement(element);
		CSVFSaver<Medicament> saver{};
		saver.saveToFile(getAll(), filename);
	}

	FileRepository(string nume) : 
		filename{ nume }
	{
		readAll();
	}

	~FileRepository() = default;

	FileRepository(const FileRepository& rhs) = default;

};
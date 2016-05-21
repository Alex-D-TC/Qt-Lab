#pragma once
#include "FSaver.h"
#include <fstream>

template<typename T>
class HTMLFSaver : public FSaver<T> {
public:

	/*
		Save the list to a html file
	*/
	void saveToFile(const vector<T>& vect, string output) {
		ofstream g{ output + ".html" };
		g << "<table>\n";
		g << "\t<tr>\n\
\t\t<td> Denumire </td>\n\
\t\t<td> Pret </td>\n\
\t\t<td> Producator </td>\n\
\t\t<td> Substanta activa </td>\n\
\t</tr>" << endl;
		for_each(vect.begin(), vect.end(), [&g](Medicament med) {
			g << "\t<tr>\n\
\t\t<td> " << med.getDenumire() << " </td>\n\
\t\t<td> " << med.getPret() << " </td>\n\
\t\t<td> " << med.getProducator() << " </td>\n\
\t\t<td> " << med.getSubstActiva() << " </td>\n\
\t</tr>" << endl;
		});
		g << "</table>";
		if (next != nullptr) {
			next->saveToFile(vect, output);
		}
	}

	// CONSTRUCTORS | DESTRUCTORS

	HTMLFSaver() = default;

	HTMLFSaver(FSaver<T>* next) {
		FSaver<T>::next = next;
	}

	HTMLFSaver(const HTMLFSaver& rhs) = default;

	~HTMLFSaver() = default;

};
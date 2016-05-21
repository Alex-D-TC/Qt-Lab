#pragma once

template<typename T>
class FSaver {
protected:
	FSaver<T>* next = nullptr;
public:
	virtual void saveToFile(const vector<T>& vect, string output) = 0;

	virtual ~FSaver() {
		if (next != nullptr)
			delete next;
	}
};
#pragma once
#include "Controller.h"

class Console {
private:
	Controller& controller;

	/*
		Prints shopping cart menu
	*/
	void printShpCart();

	/*
		Shopping cart loop
	*/
	void shpCartLoop();

	/*
	Prints all elements of an iterator
	*/
	void printElems(vector<Medicament>::iterator &begin, vector<Medicament>::iterator &end);

	/*
	Executes a function based on the given input
	*/
	void executeFunction(int result);

	/*
		Adds an element to the cart
	*/
	vector<Medicament> addToCart();

	/*
		Saves the shopping cart in a CSV or HTML file
	*/
	void saveToFile();

	/*
		Esxecutes a shopping cart function based on the given input
	*/
	vector<Medicament> executeFunctionShpCart(int result);

	/*
	Receives the command input from the keyboard
	*/
	int getInput();

	/*
	Displays the menu
	*/
	void printMenu();

	/*
	Receives the input for a new element and adds it to the repo
	*/
	void addItem();

	/*
	Receives the input for an element and removes it from the repo
	*/
	void removeItem();

	/*
	Receives the input for an element and updates it in the repo
	*/
	void updateItem();

	/*
		Reads an integer from the standard input
		message - The message to print before accepting input
		maxValue - The maximum value
		emptyFlag - A flag that signifies empty-string behaviour
				- If it's 0, inputting an empty string is an error
				- It it's not 0, inputting an empty string returns -1
	*/
	int readInt(string message, int maxValue, int emptyFlag = 0);

	/*
		Reads a string from the standard input
		message - The message to print before accepting input
		emptyFlat - A flag that signifies empty-string behaviour
				- If it's 0, inputting an empty string is an error
				- If it's not 0, inputting an empty string returns the empty string
	*/
	string readString(string message, int emptyFlag = 0);

	/*
		Displays all elements from the repository
	*/
	void printAll();

	/*
		Searches for an element in the repository
		Prints all similar elements to the screen
	*/
	void search();

	/*
			Prints to the screen the elements of the repository sorted
		by different criteria
	*/
	void sort();

	/*
			Prints the elements filtered by a given condition and value to
		the screen
	*/
	void filter();

	/*
		Generates an empty shopping cart
	*/
	vector<Medicament> empty() {
		return controller.emptyShpCart();
	}

	/*
		Gets and shows the receipt
	*/
	vector<Medicament> showReceipt() {
		return controller.getShpCart();
	}

	/*
		Reads the size at which to generate the shopping cart
	*/
	vector<Medicament> generate() {
		int size;
		size = readInt("Input number: ", 5000);
		return controller.generate(size);
	}

public:

	// CONSTRUCTORS | DESTRUCTORS

	/*
		Default constructor
	*/
	Console(Controller& controller):
		controller(controller)
	{}

	/*
		Copy constructor
	*/
	Console(const Console& other) = delete;

	/*
		Destructor
	*/
	~Console() = default;

	// CORE LOGIC

	/*
		Main GUI loop
	*/
	void start();
};
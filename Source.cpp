#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());
	

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// *********************************************************************** End of Starter Code **********************************************************************

// Displays menu options
void DisplayMenu() { 
	cout << "Menu" << endl;
	cout << "1: Items and Quantities list" << endl;
	cout << "2: Item purchase information" << endl;
	cout << "3: List Histogram" << endl;
	cout << "4: Exit" << endl;
}

// Takes itemName, calls python function to return item frequency
void PrintItemCount(string itemName) {
	int numCount = callIntFunc("ItemFrequency", itemName);
	cout << numCount << " " << itemName << "(s) were sold today." << endl;
}

// Builds a text based histogram
void GenerateHistogram() {
	string currLine;
	CallProcedure("BuildHistogram");
	ifstream inFS;  // Opens file stream
	inFS.open("frequency.dat");
	while (!inFS.eof()) {
		getline(inFS, currLine);
		int numLoc = currLine.find(' ') + 1; // gets the location of the quantity
		string currItem = currLine.substr(0, numLoc); // creates substring of item name and trailing space
		string currCount = currLine.substr(numLoc, numLoc + 1); // creates substring of the quantity
		int num = stoi(currCount);								// converts the string to int
		cout << currItem;
		for (int i = 0; i < num; ++i) {							// adds a star for every item sold
			cout << "*";
		}
		cout << endl;
	}
	inFS.close();  // Close file for reading to avoid memory leak

}

void main()
{
	string item = "";
	int userInput = -1;

	while (userInput != 4) {
		DisplayMenu();
		cin >> userInput;
		if (userInput == 1) {
			CallProcedure("CountItems");
		}
		if (userInput == 2) {
			cout << "Which item were you looking to count?" << endl;
			cin >> item;
			PrintItemCount(item);
		}
		if (userInput == 3) {
			GenerateHistogram();
		}
		if (userInput == 4) {
			break;
		}
	}
	// KEPT IN FOR REFERENCE
	// CallProcedure("printsomething");
	// cout << callIntFunc("PrintMe", "House") << endl;
	// cout << callIntFunc("SquareValue", 2);
}
#include <iostream>
#include <cmath>
using namespace std;

int variablesNo; //number of variables
int minTerms = 0;
int sigma[65536];
bool domain[65536][16], valuesF[65536]; //domain
char complements[65536][16];
char variables[16]; // actual variables (symbols)

void createSigma(); 
void fillDomainMatrix(int values);

int main()
{
	//USER INPUT
	cout << "Number of variables: "; cin >> variablesNo; //getting the nubmer of variables
	int values = pow(2, variablesNo);
	cout << "\n" << "Function values (" << values <<"): ";
	for (int i = 0; i < values; i++) { //geting the f values;
		cin >> valuesF[i];
	}
	//-------

	//getting variable symbols
	for (int i = 0; i < variablesNo; i++) {
		variables[i] = (char)(65 + i);
	}

	//filling the domain matrix by creating all binary numbers till 2^variables - 1
	fillDomainMatrix(values);

	//check for complements using the minterm method and creting sigma
	createSigma(values);

	//PRINTING STUFF
	//printing truth table
	cout << "\n" << "truth table";
	for (int i = 0; i < values; i++) { 
		cout << "\n";
		for (int j = 0; j < variablesNo; j++) {
			cout << domain[i][j] << " ";
		}
		cout <<"| " << valuesF[i];
	}
	
	//printing sigma
	cout << "\n\n" << "sigma" << "\n";
	for (int i = 0; i < minTerms; i++) {
		cout << sigma[i] << " ";
	}

	//printing complements
	cout << "\n\n" << "complements";
	for (int i = 0; i < minTerms; i++) { 
		cout << "\n";
		for (int j = 0; j < variablesNo; j++) {
			cout << complements[i][j] << " ";
		}
	}

	//printing F
	cout << "\n\n" << "F = ";
	for (int i = 0; i < minTerms; i++) {
		for (int j = 0; j < variablesNo; j++) {
			if (complements[i][j] == '!') cout << variables[j] << "'";
			else cout << variables[j];
		}
		if(i < minTerms - 1) cout << " + ";
	}
}

//FUNCTIONS

void fillDomainMatrix(int values) {
	for (int i = 0; i < values; i++) {
		int n = i;
		for (int j = variablesNo - 1; j >= 0; j--) {
			domain[i][j] = n % 2;
			n /= 2;
		}
	}
}

//check for complements using the minterm method and creting sigma
void createSigma(int values) {
	for (int i = 0; i < values; i++) {
		if (valuesF[i] == 1) {
			sigma[minTerms] = i;
			minTerms++;
		}
		for (int j = 0; j < variablesNo; j++) {
			if (valuesF[i] == 1) {
				if (domain[i][j] == 0) {
					complements[minTerms - 1][j] = '!';
				}
				else {
					complements[minTerms - 1][j] = '_';
				}
			}
		}
	}
}
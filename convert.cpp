#include <iostream>
#include <iomanip>

using namespace std;

void printMatrix(double** matrix, double** identity, int rows, int columns);
void inputMatrix(double** matrix, int rows, int columns);
void ReducedEchelon(double** matrix, double** identity, int rows, int columns);
bool isEchelon(double** matrix, int rows, int columns);

int main()
{
	int rows, columns;
	double **matrix, **identity;

	/*Taking input of rows and columns from user*/

	cout << "Enter Rows: ";
	cin >> rows;
	cout << "Enter Columns: ";
	cin >> columns;

	/*Checking if given rows & columns are equal or not. If not, asking user to
	input again*/

	while (rows != columns) {
		system("cls");
		cout << "Error!" << endl
			<< "Rows and columns have to be equal in order to find inverse!" << endl << endl;
		cout << "Enter Rows: ";
		cin >> rows;
		cout << "Enter Columns: ";
		cin >> columns;
	}

	/*Dynamically allocating memory for matrix & identity of that matrix*/

	matrix = new double*[rows];
	identity = new double*[rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new double[columns];
		identity[i] = new double[columns];
	}

	/*Forming identity*/

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == j) 
				identity[i][j] = 1;
			else 
				identity[i][j] = 0;
		}
	}

	inputMatrix(matrix, rows, columns);					// This function inputs matrix from user

	printMatrix(matrix, identity, rows, columns);		// This function prints the given matrix

	ReducedEchelon(matrix, identity, rows, columns);	// This function converts the given matrix to reduced echelon
	
	if (isEchelon(matrix, rows, columns)) {				// isEchelon function checks if converted matrix is in echelon form or not
		cout << endl << "Inverse of the given matrix is: " << endl << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				cout << setprecision(2) << identity[i][j] << '\t';
			}
			cout << endl;
		}
	}
	else {
		cout << "Inverse of the given matrix is not possible." << endl;
	}

	/*De-allocating memory for matrix & identity*/

	for (int i = 0; i < rows; i++) {
		delete[]matrix[i];
		delete[]identity[i];
	}
	delete[]matrix;
	delete[]identity;

	system("pause");
}

void printMatrix(double** matrix, double** identity, int rows, int columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << setprecision(2) << matrix[i][j] << '\t';
		}
		cout << " |\t";
		for (int j = 0; j < columns; j++) {
			cout << setprecision(2) << identity[i][j] << '\t';
		}
		cout << endl;
	}
}

void inputMatrix(double** matrix, int rows, int columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cin >> matrix[i][j];
		}
	}
}

void ReducedEchelon(double** matrix, double** identity, int rows, int columns)
{
	double lead = 0, div = 0;
	int rowX = 0, columnY = 0;
	if (matrix[0][0] == 0) {
		cout << endl << "Interchanging R1 and R2." << endl << endl;
		for (int i = 0; i < columns; i++) {
			double temp = 0;
			temp = matrix[0][i];
			matrix[0][i] = matrix[1][i];
			matrix[1][i] = temp;
			temp = identity[0][i];
			identity[0][i] = identity[1][i];
			identity[1][i] = temp;
		}
		printMatrix(matrix, identity, rows, columns);
	}
	while (rowX < rows && columnY < columns) {
		lead = matrix[rowX][columnY];
		if (lead != 0 && lead != 1) {
			cout << endl << "Expanding R" << rowX + 1 << " by (1/" << lead << ")R" << rowX + 1 << endl << endl;
			for (int i = columnY; i < columns; i++) {
				matrix[rowX][i] /= lead;
				identity[rowX][i] /= lead;
			}
			printMatrix(matrix, identity, rows, columns);
		}

		/*This loop will make zeroes beneath the leading entry*/

		for (int i = rowX + 1, j = columnY; i < rows; i++) {
			div = matrix[i][j];
			cout << endl << "Replace R" << i + 1 << " By R" << i + 1 << " - (" << div << ")" << "R" << rowX + 1 << endl << endl;
			for (int j = columnY; j < columns; j++) {
				matrix[i][j] = matrix[i][j] - (div * matrix[rowX][j]);
				identity[i][j] = identity[i][j] - (div * identity[rowX][j]);
			}
			printMatrix(matrix, identity, rows, columns);
		}

		/*This loop will make zeroes above the leading entry*/

		for (int i = rowX - 1, j = columnY; i >= 0; i--) {
			div = matrix[i][j];
			cout << endl << "Replace R" << i + 1 << " By R" << i + 1 << " - (" << div << ")" << "R" << rowX + 1 << endl << endl;
			for (int j = columnY; j < columns; j++) {
				matrix[i][j] = matrix[i][j] - (div * matrix[rowX][j]);
				identity[i][j] = identity[i][j] - (div * identity[rowX][j]);
			}
			printMatrix(matrix, identity, rows, columns);
		}
		rowX++; columnY++;
	}
}

bool isEchelon(double** matrix, int rows, int columns)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == j) {
				if (matrix[i][j] != 1) {
					return false;
				}
			}
			else if (matrix[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}
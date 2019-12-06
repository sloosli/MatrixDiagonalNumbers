#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string INPUT_FILENAME = "input.txt";
string OUTPUT_FILENAME = "output.txt";

char** InputMatrix(string filename, int &size)
{
	ifstream file(filename, ios::in);
	file >> size;

	char** matrix = new char* [size];

	for (size_t i = 0; i < size; i++)
	{
		matrix[i] = new char[size];
		for (size_t j = 0; j < size; j++)
		{
			int temp;
			file >> temp;
			matrix[i][j] = temp + '0';
		}
	}

	file.close();

	return matrix;
}

void AddDigit(string &number, char digit)
{
	if (number.length() == 0 && digit == '0')
		return;
	number += digit;
}

string* GetNumbers(char** matrix, int size, int index)
{
	string* numbers = new string[4];

	for (int i = 0; i < size - index; i++)
	{
		AddDigit(numbers[0], matrix[i + index][i]);							// Гл. диаг. ниже
		AddDigit(numbers[1], matrix[size - 1 - i - index][i]);	// Побоч. диаг. выше
		AddDigit(numbers[2], matrix[i][i + index]);							// Гл. диаг. веше
		AddDigit(numbers[3], matrix[size - 1 - i][i + index]);	// Побоч. диаг. ниже
	}

	int n = index == 0 ? 2 : 4;

	string* result = new string[n];
	for (size_t i = 0; i < n; i++)
	{
		result[i] = numbers[i];
	}

	return result;
}

string Min(string n1, string n2)
{
	if (n1 == "Нет")
		return n2;
	if (n2 == "Нет")
		return n1;

	if (n1.length() < n2.length())
		return n1;
	if (n2.length() < n1.length())
		return n2;

	for (size_t i = 0; i < n1.length(); i++)
	{
		if (n1[i] < n2[i])
			return n1;
		if (n2[i] < n1[i])
			return n2;
	}
	return n1;
}

string MinimalDiagonalNumbers(char** matrix, int size)
{
	string* numbers = new string[size * 4 - 2];
	int count = 0;

	string min = "Нет";

	string* temp = GetNumbers(matrix, size, 0);
	numbers[count++] = temp[0];
	numbers[count++] = temp[1];

	if (temp[0] == temp[1]) min = temp[0];

	for (int i = 1; i < size; i++)
	{
		temp = GetNumbers(matrix, size, i);
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < count; k++)
			{
				if (temp[j] == numbers[k])
				{
					min = Min(min, temp[j]);
				}
			}
			numbers[count++] = temp[j];
		}
	}
	return min == "" ? "0" : min;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	string inputFilename;
	string outputFilename;

	if(argc == 1)
		inputFilename = INPUT_FILENAME;
	else
	{
		inputFilename = argv[1];
		if(argc == 3)
			outputFilename = argv[2];
		else
			outputFilename = OUTPUT_FILENAME;
	}

	int size;
	char** matrix = InputMatrix(inputFilename, size);

	string min = MinimalDiagonalNumbers(matrix, size);

	ofstream outFile(outputFilename);

	outFile << min;

	outFile.close();

	return 0;
}

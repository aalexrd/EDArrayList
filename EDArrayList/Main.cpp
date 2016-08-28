#include "ArrayList.h"
#include <iostream>

std::string getString();
int getInt();

int main()
{
	ArrayList<int> array(2);
	while (true)
	{
		std::cout << "Ingrese un numero: ";
		array.add(getInt());
		std::cout << "Desea agregar mas, Si o No?: ";
		if (tolower(getString()[0]) == 'n')
			break;
	}
	std::cout << "Estos son los numeros que ingresaste: \n";
	std::cout << array.toString();
	std::cin.get();
}

std::string getString()
{
	std::string line;
	while (true)
	{
		getline(std::cin, line);
		if (line.empty())
			continue;
		return line;
	}
}

int getInt()
{
	std::string number = getString();
	std::string n;
	if (number[0] == 45)
		n.push_back(number[0]);
	for (unsigned int i = 0; i < number.length(); i++)
		if (number[i] > 47 && number[i] < 58)
			n.push_back(number[i]);
	return n.empty() ? getInt() : atoi(n.c_str());
}

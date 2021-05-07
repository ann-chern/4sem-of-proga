#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

int main()
{
	int n;
	std::fstream fin("7_2.txt", std::ios::in);
	std::string text;
	std::getline(fin, text);

	int size = text.size() + 2;

	std::cout << "enter the number of string:" << std::endl;
	std::cin >> n;

	fin.seekg((n - 1) * size, std::ios::beg);
	std::getline(fin, text);
	std::cout << text << std::endl;

	return 0;
}
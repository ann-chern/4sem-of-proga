#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

int main()
{
	int number = 0;
	int beg = 0;

	std::fstream fin("test_1.txt", std::ios::in);
	std::string text(std::istreambuf_iterator <char>{fin}, std::istreambuf_iterator <char>{});
	fin.close();
	int i = 0;

	while (i < text.size())
	{
		if ((text[i] == '"') and (text[i - 1] != '\\'))
		{
			i++;
			while ((text[i] != '"') || ((text[i] == '"') and (text[i - 1] == '\\')))
			{
				i++;
			}
		}
		if (text[i] == '/')
		{
			if (text[i + 1] == '/')
			{
				beg = i;
				while (text[i] != '\n')
				{
					i++;
					number++;
				}
				text.erase(beg, number);
				i = beg - 1;
				number = 0;
			}
			else if (text[i + 1] == '*')
			{
				beg = i;
				i++;
				i++;
				while ((text[i] != '*') || ((text[i] == '*') and (text[i - 1] == '\\')))
				{
					i++;
					number++;
				}
				text.erase(beg, number + 4);
				i = beg - 1;
				number = 0;
			}
		}
		else
		{
			i++;
		}
	}

	std::fstream fout("test_2.txt", std::ios::out | std::ios::trunc);
	fout << text;
	fout.close();

	return 0;
}
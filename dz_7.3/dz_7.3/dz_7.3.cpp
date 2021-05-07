#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>


template <typename TP>
std::time_t to_time_t(TP tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

void view_directory(const std::filesystem::path& path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			auto file_name = entry.path().filename().string();

			auto time = std::filesystem::last_write_time(entry);

			std::time_t cftime = to_time_t(time);

			std::cout << "File write time is " << std::asctime(std::localtime(&cftime)) << std::endl;

			std::cout << file_name << std::endl;
		}
	}
}


int main()
{
	system("chcp 1251");
	std::filesystem::path path;
	std::cout << "enter the directoty: ";
	std::cin >> path;
	view_directory(path);

	return 0;
}
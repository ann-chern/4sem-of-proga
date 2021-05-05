#include <chrono>
#include <random>
#include <set>
#include <string>
#include <functional>
#include <iostream>
#include <unordered_set>

std::set < std::string > make_random_words(std::size_t N, std::size_t length) // length = 10 - good enough
{
	std::uniform_int_distribution <> letter(97, 122);
	std::default_random_engine e(static_cast <std::size_t> (
		std::chrono::system_clock::now().time_since_epoch().count()));

	std::set < std::string > words;

	for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
		for (auto& c : s)
			c = letter(e);

	return words;
}

template < typename T >
void hash_combine(std::size_t& seed, const T& value) noexcept
{
	seed ^= std::hash < T >()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t& seed, const T& value) noexcept
{
	hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t& seed, const T& value, const Types& ... args) noexcept
{
	hash_combine(seed, value);
	hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types& ... args) noexcept
{
	std::size_t seed = 0;
	hash_value(seed, args...);
	return seed % 128;
}

int main()
{
	std::size_t N = 1000;
	unsigned int num = 0;
	std::set <std::size_t> codes;
	std::set<std::size_t> hash;
	for (auto i = 0U; i < N; i++)
	{
		std::set < std::string > names = make_random_words(1, 10);
		std::size_t a = rand() % 10000;
		char b = rand() % 128;
		codes.insert(hash_value(*names.begin(), a, b));
		auto res = hash.insert(hash_value(*names.begin(), a, b));

		if (res.second == 0)
		{
			num++;
			std::cout << num << std::endl;
		}
	}
	for (auto i : hash)
	{
		std::cout << i << std::endl;
	}
	std::cout << "number of collisions = " << num << std::endl;

	return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>
#include <iterator>

int main()
{
	// ¹1
	std::cout << "   1" << std::endl;
	std::vector <int> v1(10);
	int i = 1;
	std::generate(std::begin(v1), std::end(v1), [&i]() mutable {return i++; });

	std::cout << "v1 : ";
	std::for_each(std::begin(v1), std::end(v1), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	// ¹2
	v1.resize(13);
	std::cout << "   2" << std::endl;
	std::cout << "enter 3 numbers : ";
	//std::copy(
	//	std::istream_iterator < int >(std::cin),
	//	std::istream_iterator < int >(),
	//	std::back_inserter(v1));
	int t;
	std::generate(std::next(std::begin(v1), 10), std::end(v1), [&t]()mutable {std::cin >> t;
	return t;
		});

	std::cout << "v1 : ";
	std::for_each(std::begin(v1), std::end(v1), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//¹3
	std::cout << "   3" << std::endl;
	std::default_random_engine dre(std::chrono::system_clock().now().time_since_epoch().count());
	//std::mt19937 mt(dre);
	std::shuffle(std::begin(v1), std::end(v1), dre);

	std::cout << "v1 : ";
	std::for_each(std::begin(v1), std::end(v1), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//// ¹4
	//std::cout << "   4" << std::endl;
	//std::sort(std::begin(v1), std::end(v1));
	//auto result = std::unique(std::begin(v1), std::end(v1));
	//v1.erase(result, std::end(v1));

	std::cout << "v1 : ";
	std::for_each(std::begin(v1), std::end(v1), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	// ¹5
	std::cout << "   5" << std::endl;
	int odd = std::count_if(std::begin(v1), std::end(v1), [](auto x) {return x % 2 == 1; });
	std::cout << odd << " odd numbers" << std::endl;

	// ¹6
	std::cout << "   6" << std::endl;
	auto [min1, max1] = std::minmax_element(std::begin(v1), std::end(v1));
	std::cout << "min = " << *min1 << "; max = " << *max1 << std::endl;

	//¹7
	std::cout << "   7" << std::endl;
	std::vector <int> temp(static_cast <int> (std::sqrt(*max1)));
	i = 2;
	std::generate(std::begin(temp), std::end(temp), [&i]() mutable {return i++; });
	auto c = std::find_if(std::begin(v1), std::end(v1), [temp](auto x) {
		auto c1 = std::count_if(std::begin(temp), std::end(temp), [x](auto y) {
			if (x == 0)
			{
				return 0;
			}
			else if (x != y)
			{
				if (x % y == 0)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
			});
		if (c1 == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		});
	if (c != std::end(v1))
	{
		std::cout << "first prime number is " << *c << std::endl;
	}
	else
	{
		std::cout << "no prime numbers" << std::endl;
	}


	// ¹8
	std::cout << "   8" << std::endl;
	std::transform(std::begin(v1), std::end(v1), std::begin(v1), [](auto x) {return x * x; });


	for (auto element : v1)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;

	// ¹9
	std::cout << "   9" << std::endl;
	std::vector <int> v2(std::size(v1));
	std::uniform_int_distribution <> uid(0, 15);
	std::generate(std::begin(v2), std::end(v2), [&dre, &uid]() {return uid(dre); });


	for (auto element : v2)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;

	// ¹10
	std::cout << "   10" << std::endl;
	int sum2 = std::accumulate(std::begin(v2), std::end(v2), 0);
	std::cout << "sum2 = " << sum2 << std::endl;

	// ¹11
	std::cout << "   11" << std::endl;
	std::fill_n(std::begin(v2), 4, 1);

	std::cout << "v2 : ";
	std::for_each(std::begin(v2), std::end(v2), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//¹12
	std::cout << "   12" << std::endl;
	std::vector <int> v3(std::size(v1));
	std::copy(std::begin(v1), std::end(v1), std::begin(v3));
	std::transform(std::begin(v1), std::end(v1), std::begin(v2), std::begin(v3), std::minus <>());

	std::cout << "v3 : ";
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//¹13
	std::cout << "   13" << std::endl;
	std::replace_if(std::begin(v3), std::end(v3), [](auto x) {return x < 0; }, 0);

	std::cout << "v3 : ";
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//¹14
	std::cout << "   14" << std::endl;
	v3.erase(std::remove_if(std::begin(v3), std::end(v3), [](auto x) {return x == 0; }));

	std::cout << "v3 : ";
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//¹15
	std::cout << "   15" << std::endl;
	std::reverse(std::begin(v3), std::end(v3));

	std::cout << "v3 : ";
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//¹16
	std::cout << "   16" << std::endl;
	std::vector <int> max(4);
	std::copy(std::begin(v3), std::next(std::begin(v3), 3), std::begin(max));
	std::sort(std::begin(max), std::end(max));
	std::for_each(std::next(std::begin(v3), 3), std::end(v3), [&max](auto y)mutable {
		if (y > * std::max_element(std::begin(max), std::next(std::begin(max), 3)))
		{
			max[3] = y;
			std::nth_element(std::begin(max), std::next(std::begin(max), 3), std::end(max), [](auto a, auto b) {return a > b; });
			//std::sort(std::begin(max), std::end(max));
		}
		});
	std::cout << "max : ";
	std::for_each(std::begin(max), std::next(std::begin(max), 3), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//¹17
	std::cout << "   17" << std::endl;
	std::sort(std::begin(v1), std::end(v1));
	std::sort(std::begin(v2), std::end(v2));

	std::cout << "v1 : ";
	std::for_each(std::begin(v1), std::end(v1), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;
	std::cout << "v2 : ";
	std::for_each(std::begin(v2), std::end(v2), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//¹18
	std::cout << "   18" << std::endl;
	std::vector <int> v4(2 * std::size(v1));
	std::copy(std::begin(v1), std::end(v1), std::begin(v4));
	std::copy(std::begin(v2), std::end(v2), std::next(std::begin(v4), std::size(v1)));

	std::cout << "v4 : ";
	std::for_each(std::begin(v4), std::end(v4), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	//¹19
	std::cout << "   19" << std::endl;
	std::sort(std::begin(v4), std::end(v4));
	auto a = std::lower_bound(std::begin(v4), std::end(v4), 1);
	auto b = std::upper_bound(std::begin(v4), std::end(v4), 1);
	if (a == std::end(v4))
	{
		std::cout << "1 is the first element" << std::endl;
	}
	else if (b == std::end(v4))
	{
		std::cout << "1 is the last element" << std::endl;
	}
	else
	{
		std::cout << "1 is between " << *a << " and " << *b << std::endl;
	}

	//¹20
	std::cout << "   20" << std::endl;
	std::cout << "v1 : ";
	std::for_each(std::begin(v1), std::end(v1), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;
	std::cout << "v2 : ";
	std::for_each(std::begin(v2), std::end(v2), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;
	std::cout << "v3 : ";
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;
	std::cout << "v4 : ";
	std::for_each(std::begin(v4), std::end(v4), [](auto x) {std::cout << x << ' '; });
	std::cout << std::endl;

	return 0;
}
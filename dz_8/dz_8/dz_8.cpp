#include <iostream>
#include <iterator>
#include <thread>
#include <future>
#include <random>
#include <algorithm>
#include <numeric>
#include <chrono>

class Timer
{
public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;
    void pause()
    {
        dur = std::chrono::duration_cast <std::chrono::microseconds>(clock_t::now() - m_begin);
        paused = true;
    }
    void cont()
    {
        m_begin = clock_t::now() - dur;
        paused = false;
    }
    Timer() : m_begin(clock_t::now()), dur(std::chrono::duration_cast <std::chrono::microseconds>(clock_t::now() - clock_t::now())), paused(false) {}
    ~Timer()
    {
        if (!paused) {
            dur = std::chrono::duration_cast <std::chrono::microseconds>(clock_t::now() - m_begin);
        }
        m_begin = clock_t::now() - dur;
        auto end = clock_t::now();
        std::cout << "microseconds: " << std::chrono::duration_cast <std::chrono::microseconds> (end - m_begin).count() << std::endl;
    }
private:
    time_point_t m_begin;
    std::chrono::microseconds dur;
    bool paused;
};

void find_m(int n, double& result)
{
    double x, y;
    double m = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (int i = 0; i < n; ++i)
    {
        x = dis(gen);
        y = dis(gen);
        if ((x * x + y * y) < 1.0)
        {
            result++;
        }
    }
}

int main()
{
    std::cout << "with 1 thread:" << std::endl;
    //with one thread
    {
        Timer t1;
        double x, y;
        double m = 0; double n = 1000000;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        for (int i = 0; i < n; ++i)
        {
            x = dis(gen);
            y = dis(gen);
            //std::cout << x << " " << y << std::endl;
            if ((x * x + y * y) < 1.0)
            {
                m++;
                //std::cout << m << std::endl;
            }
        }
        //std::cout << "m = " << m << std::endl;
        double result = 4 * (m / n);
        std::cout << "pi1 = " << result << std::endl;
    }
    std::cout << std::endl;
    //-------------------------------------------------------------------------------------
    //with threads
    std::cout << "with threads:" << std::endl;
    {
        Timer t2;
        int num_all = 1000000;

        const std::size_t hardware_threads =
            std::thread::hardware_concurrency();
        std::vector < std::thread > threads(hardware_threads - 1);
        std::vector < double >      m_results(hardware_threads, 0);
        for (std::size_t i = 0; i < (hardware_threads - 1); ++i)
        {
            threads[i] = std::thread(find_m, num_all / hardware_threads, std::ref(m_results[i]));
        }
        std::for_each(threads.begin(), threads.end(),
            std::mem_fn(&std::thread::join));
        find_m(num_all - (num_all / hardware_threads) * (hardware_threads - 1), m_results[hardware_threads - 1]);
        double m_result = std::accumulate(std::begin(m_results), std::end(m_results), 0.0);
        std::cout << "pi2 = " << 4 * (m_result / num_all) << std::endl;
    }
}
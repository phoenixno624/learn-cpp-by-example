#include <iostream>
#include <chrono>
#include <ratio>
#include <concepts>

template<typename T>
concept Quacks = requires(T t)
{
    t.Quack();
};

template<typename T>
requires Quacks<T>
void must_be_a_duck(T x)
{
    x.Quack();
}
void also_must_be_a_duck(Quacks auto x)
{
    x.Quack();
}

void duration_to_end_of_year()
{
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    std::chrono::time_point now = std::chrono::system_clock::now();
    auto new_years_eve = 2024y / December / 31;
    auto event = std::chrono::sys_days(new_years_eve);
    std::chrono::duration dur = event - now;
    std::cout << dur << " until event\n";
}
void durations()
{
    using namespace std::chrono;

    auto nearly_a_day = hours{23};
    days a_day = duration_cast<days>(nearly_a_day);
    hours round_trip = a_day;
    std::cout << nearly_a_day << " cast to " << a_day
              << " and cast back to " << round_trip << '\n';
}
void defining_a_duration()
{
    using namespace std::chrono;
    using centuries = duration<long long,
                               std::ratio_multiply<years::period, std::hecto>>;
    centuries two_hundred_years = centuries(2);
    seconds sec = two_hundred_years;
    hours hrs = two_hundred_years;
    days day_count = duration_cast<days>(two_hundred_years);

    std::cout << "Two centuries is approximately " << day_count << '\n';
}

int main()
{
    durations();
    defining_a_duration();
    duration_to_end_of_year();
}
#include <iostream>
#include <string>
#include <numeric>
#include <sstream>
#include <optional>
#include <functional>
#include <format>
#include <concepts>
#include <random>

constexpr bool is_prime(int n)
{
    if (n == 2 || n == 3)
    {
        return true;
    }
    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    for (int i = 5; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

unsigned some_const_number()
{
    return 42;
}
int some_random_number()
{
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    return dist(engine);
}
int some_prime_number()
{
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> dist{1, 99999};
    int n{};

    while (!is_prime(n))
    {
        n = dist(engine);
    }

    return n;
}

unsigned input()
{
    unsigned number;
    while (!(std::cin >> number))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a number.\n";
    }
    return number;
}
std::optional<int> read_number(std::istream &in)
{
    int result{};
    if (in >> result)
    {
        return result;
    }
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return {};
}

void guess_number(unsigned number)
{
    std::cout << "Guess the number.\n >";
    unsigned guess = input();
    while (guess != number)
    {
        std::cout << guess << " is wrong. Try again\n >";
        guess = input();
    }
    std::cout << "Well done.\n";
}
void guess_number_or_give_up(int number)
{
    std::cout << "Guess the number.\n >";
    std::optional<int> guess;
    while (guess = read_number(std::cin))
    {
        if (guess.value() == number)
        {
            std::cout << "Well done.\n";
            return;
        }
        std::cout << guess.value() << " is wrong. Try again\n >";
    }
    std::cout << "The number was " << number << "\n";
}
void guess_number_with_clues(unsigned number,
                             std::invocable<int, int> auto message)
{
    std::cout << "Guess the number.\n >";
    std::optional<int> guess;
    while (guess = read_number(std::cin))
    {
        if (guess.value() == number)
        {
            std::cout << "Well done.\n";
            return;
        }
        std::cout << message(number, guess.value());
        std::cout << ">";
    }
    std::cout << std::format("The number was {}\n", number);
}

void check_properties()
{
    static_assert(is_prime(2));
}

int main()
{
    check_properties();

    unsigned number = some_prime_number();
    auto make_message = [](int number, int guess)
    {
        return std::format("Your guess was too {}\n",
                           (guess < number ? "small" : "big"));
    };
    guess_number_with_clues(number, make_message);
}
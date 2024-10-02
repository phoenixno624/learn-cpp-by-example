#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>
#include <compare>
#include <random>
#include <variant>

namespace cards
{
    enum class Suit
    {
        Hearts,
        Diamonds,
        Clubs,
        Spades
    };
    class FaceValue
    {
    private:
        int value_;

    public:
        explicit FaceValue(int value);
        int value() const;
        auto operator<=>(const FaceValue &) const = default;
    };
    class Card
    {
    private:
        FaceValue value_{1};
        Suit suit_{};

    public:
        Card() = default;
        Card(FaceValue value, Suit suit);
        FaceValue value() const;
        Suit suit() const;
        auto operator<=>(const Card &) const = default;
    };
    struct Joker
    {
    };
    std::ostream &operator<<(std::ostream &os, const Card &card);
    std::ostream &operator<<(std::ostream &os, const std::variant<Card, Joker> &card);
    std::string to_string(const Suit &suit);
    std::string to_string(const FaceValue &value);
    std::array<Card, 52> create_deck();
    std::array<std::variant<Card, Joker>, 54> create_extended_deck();
    Suit &operator++(Suit &suit);
    template <typename T, int n>
    void shuffle_deck(std::array<T, n> &deck);
    void higher_lower();
    void higher_lower_with_jokers();
    bool is_guess_correct(char guess, const Card &current, const Card &next);
    bool is_guess_correct(char guess,
                          const std::variant<Card, Joker> &current,
                          const std::variant<Card, Joker> &next);
}
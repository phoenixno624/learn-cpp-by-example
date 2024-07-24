#pragma once

#include <iostream>
#include <stdexcept>

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
    };
    std::ostream &operator<<(std::ostream &os, const Card &card);
}
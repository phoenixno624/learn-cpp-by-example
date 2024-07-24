#include "playing_cards.hpp"

namespace cards
{
    FaceValue::FaceValue(int value) : value_(value)
    {
        if (value_ < 1 || value_ > 13)
        {
            throw std::invalid_argument("Face value invalid.");
        }
    }
    int FaceValue::value() const
    {
        return value_;
    }
    
    Card::Card(FaceValue value, Suit suit) : value_(value),
                                             suit_(suit)
    {
    }
    FaceValue Card::value() const { return value_; };
    Suit Card::suit() const { return suit_; };

    std::ostream &operator<<(std::ostream &os, const Card &card)
    {
        os << card.value().value()
           << " of " << static_cast<int>(card.suit());
        return os;
    }
}
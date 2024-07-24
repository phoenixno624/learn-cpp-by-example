#include "playing_cards.hpp"

using namespace cards;

int main()
{
    Card card{FaceValue(2), Suit::Clubs};

    std::cout << card << std::endl;
}
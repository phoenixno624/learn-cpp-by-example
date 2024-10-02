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
        os << to_string(card.value())
           << " of " << to_string(card.suit());
        return os;
    }
    std::ostream &operator<<(std::ostream &os, const std::variant<Card, Joker> &card)
    {
        if (std::holds_alternative<Joker>(card))
        {
            os << "JOKER";
        }
        else
        {
            os << std::get<Card>(card);
        }

        return os;
    }
    std::string to_string(const Suit &suit)
    {
        using namespace std::literals;
        switch (suit)
        {
        case Suit::Hearts:
            return "Hearts"s;
        case Suit::Diamonds:
            return "Diamonds"s;
        case Suit::Clubs:
            return "Clubs"s;
        case Suit::Spades:
            return "Spades"s;
        default:
            return "?"s;
        }
    }
    std::string to_string(const FaceValue &value)
    {
        using namespace std::literals;
        switch (value.value())
        {
        case 1:
            return "Ace"s;
        case 11:
            return "Jack"s;
        case 12:
            return "Queen"s;
        case 13:
            return "King"s;
        default:
            return std::to_string(value.value());
        }
    }
    std::array<Card, 52> create_deck()
    {
        std::array<Card, 52> deck;
        int value = 1;
        Suit suit = Suit::Hearts;
        std::ranges::generate(deck, [&value, &suit]()
                              {
            if (value > 13)
            {
                value = 1;
                ++suit;
            }
            return Card{FaceValue(value++), suit}; });
        return deck;
    }
    std::array<std::variant<Card, Joker>, 54> create_extended_deck()
    {
        std::array<std::variant<Card, Joker>, 54> deck{Joker{}, Joker{}};
        std::array<Card, 52> cards = create_deck();
        std::ranges::copy(cards, deck.begin() + 2);

        return deck;
    }
    Suit &operator++(Suit &suit)
    {
        using IntType = typename std::underlying_type<Suit>::type;
        if (suit == Suit::Spades)
        {
            suit = Suit::Hearts;
        }
        else
        {
            suit = static_cast<Suit>(static_cast<IntType>(suit) + 1);
        }
        return suit;
    }
    template <typename T, int n>
    void shuffle_deck(std::array<T, n> &deck)
    {
        std::random_device rd;
        std::mt19937 gen{rd()};
        std::ranges::shuffle(deck, gen);
    };
    void higher_lower()
    {
        auto deck = create_deck();
        shuffle_deck<Card, 52>(deck);

        size_t index = 0;
        while (index + 1 < deck.size())
        {
            std::cout << deck[index] << ": Next card higher (h) or lower (l)?\n";

            char c;
            std::cin >> c;

            bool ok = is_guess_correct(c, deck[index], deck[index + 1]);
            if (!ok)
            {
                std::cout << "Next card was " << deck[index + 1] << '\n';
                break;
            }
            ++index;
        }
        std::cout << "You got " << index << " correct\n";
    }
    void higher_lower_with_jokers()
    {
        auto deck = create_extended_deck();
        shuffle_deck<std::variant<Card, Joker>, 54>(deck);

        size_t index = 0;
        while (index + 1 < deck.size())
        {
            std::cout << deck[index] << ": Next card higher (h) or lower (l)?\n";

            char c;
            std::cin >> c;

            bool ok = is_guess_correct(c, deck[index], deck[index + 1]);
            if (!ok)
            {
                std::cout << "Next card was " << deck[index + 1] << '\n';
                break;
            }
            ++index;
        }
        std::cout << "You got " << index << " correct\n";
    }
    bool is_guess_correct(char guess, const Card &current, const Card &next)
    {
        if (guess == 'h' && next > current)
        {
            return true;
        }
        if (guess == 'l' && next < current)
        {
            return true;
        }
        return false;
    }
    bool is_guess_correct(char guess,
                          const std::variant<Card, Joker> &current,
                          const std::variant<Card, Joker> &next)
    {
        if (std::holds_alternative<Joker>(current))
        {
            return true;
        }
        if (std::holds_alternative<Joker>(next))
        {
            return true;
        }

        Card current_card = std::get<Card>(current);
        Card next_card = std::get<Card>(next);

        return is_guess_correct(guess, current_card, next_card);
    }
}
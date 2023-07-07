#ifndef CARD
#define CARD

#include <string>

class Card {
 private:
  int raw_value{};

 public:
  Card(int raw) {
    raw_value = raw;
  }
  Card() {
    raw_value = -1;
  }

  void setCard(int raw) {
    raw_value = raw;
  }
  int getRaw() {
    return raw_value;
  }

  int getRank() {
    return (raw_value / 4);
  }
  int getSuit() {
    return (raw_value % 4);
  }

  bool operator==(const Card &rhs) const noexcept {
    if (raw_value / 4 == rhs.raw_value / 4) {
      return true;
    }
    return false;
  }
  bool operator!=(const Card &rhs) const noexcept {
    if (raw_value / 4 != rhs.raw_value / 4) {
      return true;
    }
    return false;
  }
  bool operator<=(const Card &rhs) const noexcept {
    if (raw_value / 4 <= rhs.raw_value / 4) {
      return true;
    }
    return false;
  }
  bool operator>=(const Card &rhs) const noexcept {
    if (raw_value / 4 >= rhs.raw_value / 4) {
      return true;
    }
    return false;
  }
  bool operator<(const Card &rhs) const noexcept {
    if (raw_value / 4 < rhs.raw_value / 4) {
      return true;
    }
    return false;
  }
  bool operator>(const Card &rhs) const noexcept {
    if (raw_value / 4 > rhs.raw_value / 4) {
      return true;
    }
    return false;
  }

  std::string getCardString() {
    // quotient of 0 indicates rank of 2
    // quotient of 1 indicates rank of 3
    // quotient of 12 indicates rank of Ace
    std::string str{};
    switch (raw_value / 4) {
      case 0:
        str = "2 of ";
        break;
      case 1:
        str = "3 of ";
        break;
      case 2:
        str = "4 of ";
        break;
      case 3:
        str = "5 of ";
        break;
      case 4:
        str = "6 of ";
        break;
      case 5:
        str = "7 of ";
        break;
      case 6:
        str = "8 of ";
        break;
      case 7:
        str = "9 of ";
        break;
      case 8:
        str = "10 of ";
        break;
      case 9:
        str = "J of ";
        break;
      case 10:
        str = "Q of ";
        break;
      case 11:
        str = "K of ";
        break;
      case 12:
        str = "A of ";
        break;
      default:
        str = "GetCardString-rank-error";
        break;
    }
    // 0 = clubs, 1 = diamonds, 2 = hearts, 3 = spades
    switch (raw_value % 4) {
      case 0:
        str += "clubs";
        break;
      case 1:
        str += "diamonds";
        break;
      case 2:
        str += "hearts";
        break;
      case 3:
        str += "spades";
        break;
      default:
        str += "GetCardString-suit-error";
    }
    return str;
  }

  std::string getRankString() {
    switch (getRank()) {
      case 0:
        return "2";
        break;
      case 1:
        return "3";
        break;
      case 2:
        return "4";
        break;
      case 3:
        return "5";
        break;
      case 4:
        return "6";
        break;
      case 5:
        return "7";
        break;
      case 6:
        return "8";
        break;
      case 7:
        return "9";
        break;
      case 8:
        return "10";
        break;
      case 9:
        return "Jack";
        break;
      case 10:
        return "Queen";
        break;
      case 11:
        return "King";
        break;
      case 12:
        return "Ace";
        break;
      default:
        return "GetRankString-error";
        break;
    }
  }
};
#endif
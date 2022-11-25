#ifndef FIGURETYPE_H
#define FIGURETYPE_H

#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_set>

class FigureType {
public:
    FigureType() {
        this->value = "no type";
    }

    FigureType(std::string value) {
        this->value = value;
    }

    std::string getValue() const {
        return this->value;
    }

    bool operator==(const FigureType& type) const {
        return type.getValue() == this->getValue();
    }

    bool operator!=(const FigureType& type) const {
        return type.getValue() != this->getValue();
    }


    static std::unordered_set<std::string> all;

private:
    std::string value;
};


namespace std {
  template <>
  struct hash<FigureType> {
    std::size_t operator()(const FigureType& k) const {
      return std::hash<std::string>()(k.getValue());
    }
  };

}

#endif // FIGURETYPE_H

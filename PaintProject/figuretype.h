#ifndef FIGURETYPE_H
#define FIGURETYPE_H

#include <string>
#include <vector>
#include <stdexcept>

enum class FigureType {
    line = 1,
    rectangle = 2,
    ellipse = 3,
    polyline = 4,
    polygon = 5
};

class FigureTypeConverter {
public:
    static FigureType FromStr(const std::string& str) {
        if (str == "line") {
            return FigureType::line;
        }

        if (str == "rectangle") {
            return FigureType::rectangle;
        }

        if (str == "ellipse") {
            return FigureType::ellipse;
        }

        if (str == "polyline") {
            return FigureType::polyline;
        }

        if (str == "polygon") {
            return FigureType::polygon;
        }
        throw std::invalid_argument("No Figure type with name " + str);
    }

    static std::string ToStr(const FigureType& type) {
        switch (type) {
        case FigureType::line: {
            return "line";
        }
        case FigureType::ellipse: {
            return "ellipse";
        }

        case FigureType::rectangle: {
            return "rectangle";
        }
        case FigureType::polyline: {
            return "polyline";
        }
        case FigureType::polygon: {
            return "polygon";
        }
        }
        throw std::invalid_argument("Can't convert figure type to string");
    }

    const static std::vector<FigureType> all;
};

#endif // FIGURETYPE_H

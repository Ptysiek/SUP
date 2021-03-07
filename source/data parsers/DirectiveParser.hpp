#pragma once

#include "../Tools"
#include "../DataStructures"


namespace DataParsers {
class DirectiveParser {
protected:
    using Converter = Tools::Converter;
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;

    DirectiveParser() {}


public:
    static Data removeDirectives(Data data) {
        for (auto& line : data) {
            auto tmp = Converter::removeWhitespaces(line);
            if (tmp.empty()) {
                continue;
            }
            if (tmp[0] == '#') {
                line = "";
            }
        }
        return data;
    }
};
} // namespace DataParsers



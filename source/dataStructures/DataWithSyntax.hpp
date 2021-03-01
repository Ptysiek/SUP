#pragma once

#include "BaseStructures"


class DataWithSyntax {
    using Line = BaseStructures::Line;

    const std::string type_;
    const Line data_;

public:
    DataWithSyntax(const std::string& type, const Line& line):
        type_(type),
        data_(line)
    {}



};


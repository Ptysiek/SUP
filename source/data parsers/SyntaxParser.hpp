#pragma once

#include "../DataStructures"


class SyntaxParser {
    using Converter = Tools::Converter;
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;
    using Syntax = DataStructures::Syntax;
    
    Data data_;
    Syntax product_;

public:
    SyntaxParser(const Data& data):
        data_(data),
        product_()
    {}

    Data getData() const { return data_; }
    Syntax getProduct() const { return product_; }

protected:


};





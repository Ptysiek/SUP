#pragma once

#include <string>

#include "iSyntax.hpp"


class Class : public iSyntax {

    std::string header_;
    std::vector<std::shared_ptr<iSyntax>> subElements_;


public:
    Class(const std::string& data): 
        header_(data),
        subElements_()
    {}
    //enum Type { Instruction, Function, Operation, Class, Structure };
    //enum Memory { Global, Component, Static }; 

    std::string getResult() const override {
        return header_;
    }
    
    void push_back(const std::shared_ptr<iSyntax>& subElement) {
        subElements_.push_back(subElement);
    }

    Type getSyntaxType() const override { return Type::Class; }
    //Memory getMemoryType() const override { return Memory::  ; } 
};

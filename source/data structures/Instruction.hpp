#pragma once

#include <string>

#include "iSyntax.hpp"


class Instruction : public iSyntax {

    std::string rawData_;
    
public:
    Instruction(const std::string& data): rawData_(data) {}

    std::string getResult() const override {
        return rawData_;   
    }
    
    //enum Type { Instruction, Function, Operation, Class, Structure };
    //enum Memory { Global, Component, Static }; 

    Type getSyntaxType() const override { return Type::Instruction; }
    //Memory getMemoryType() const override { return Memory::  ; } 
};

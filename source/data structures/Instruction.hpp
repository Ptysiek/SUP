#pragma once

#include <string>

#include "iSyntax.hpp"


class Instruction : public iSyntax {

    std::string rawData_;

    


public:
    //enum Type { Instruction, Function, Operation, Class, Structure };
    //enum Memory { Global, Component, Static }; 

    Type getSyntaxType() const override { return Type::Instruction; }
    //Memory getMemoryType() const override { return Memory::  ; } 
};

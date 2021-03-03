#pragma once

#include <string>

#include "iSyntax.hpp"


class Class : public iSyntax {

    std::string rawData_;

    
    std::vector<std::shared_ptr<iSyntax>> subElements_;


public:
    //enum Type { Instruction, Function, Operation, Class, Structure };
    //enum Memory { Global, Component, Static }; 

    Type getSyntaxType() const override { return Type::Class; }
    //Memory getMemoryType() const override { return Memory::  ; } 
};

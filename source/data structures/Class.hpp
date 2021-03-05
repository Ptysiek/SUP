#pragma once

#include <numeric>
#include <string>

#include "Block.hpp"
#include "iSyntax.hpp"


class Class : public Block {


public:
    Class(const std::string& temp, const std::string& data): 
        Block(temp, data)
    {}
    //enum Type { Instruction, Function, Operation, Class, Structure };
    //enum Memory { Global, Component, Static }; 

    std::string getResult() const override {
        return Block::getResult();
    }
    
    Type getSyntaxType() const override { return Type::Class; }
    //Memory getMemoryType() const override { return Memory::  ; } 
private:


};

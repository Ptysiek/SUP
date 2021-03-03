#pragma once



class iSyntax {


public:
    enum Type { Instruction, Function, Operation, Class, Structure };
    enum Memory { Global, Component, Static }; 

    virtual ~iSyntax() = 0;

    virtual Type getSyntaxType() const = 0;    
    // virtual Memory getMemoryType() const = 0;
};

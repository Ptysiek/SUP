#pragma once



class iSyntax {
public:
    enum Type { Instruction, Function, Operation, Class, Structure };
    enum Memory { Global, Component, Static }; 

    //virtual Type getSyntaxType() = 0;    
    //virtual Memory getMemoryType() = 0;

};

#pragma once

#include "SyntaxTypes"


class iSyntax {
protected:
    using Type = SyntaxTypes::Type;

public:

    virtual ~iSyntax() {};

    virtual std::string getResult(size_t = 0) const = 0;

    virtual Type getSyntaxType() const = 0;    
    // virtual Memory getMemoryType() const = 0;
};

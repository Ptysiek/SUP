#pragma once

#include "SyntaxTypes"


class iSyntax {
protected:
    using Type = SyntaxTypes::Type;
    using Access = SyntaxTypes::Access;

public:
    virtual ~iSyntax() {};

    virtual Type getSyntaxType() const = 0;    
    virtual Access getSyntaxAccess() const = 0;    

    virtual std::string getResult(size_t = 0) const = 0;
};



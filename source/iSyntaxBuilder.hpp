#pragma once

#include <memory>

#include "DataStructures"
#include "Tools"


class iSyntaxBuilder {
    using Converter = Tools::Converter;
    using Syntax = DataStructures::Syntax;
    using BlockSyntax = DataStructures::BlockSyntax;


public:

    static BlockSyntax buildBlock(std::string syntaxData) {
        auto temp = CutOutTemplate(syntaxData);      

        return std::make_shared<Block>(temp, syntaxData);
    }

    static Syntax buildInstruction(const std::string& syntaxData) {
        return std::make_shared<Instruction>(syntaxData);
    }

private:

    static std::string CutOutTemplate(std::string& syntaxData) {
        auto begin = syntaxData.find("template");
        if (begin == std::string::npos) {
            return std::string();
        }
        auto end =  syntaxData.find(">", begin);
        if (end == std::string::npos) {
            return std::string();
        }
        std::string result = syntaxData.substr(begin, end - begin);
        std::string tmp = syntaxData.substr(end + 1);
        syntaxData = syntaxData.substr(0, begin) + " " + tmp; 
        Converter::removeWhitespaces(result);
        Converter::removeWhitespaces(syntaxData);
        return result;
    }


};


#pragma once

#include <numeric>
#include <string>
#include <sstream>

#include "Block.hpp"
#include "iSyntax.hpp"
#include "../Tools"


class Class : public Block {
    using Converter = Tools::Converter;
    std::string className_;

public:
    Class(const std::string& templateData, const std::string& headerData): 
        Block(templateData, headerData),
        className_(BuildClassName(headerData))
    {}
    //enum Type { Instruction, Function, Operation, Class, Structure };
    //enum Memory { Global, Component, Static }; 

    std::string getResult() const override {
        return getResult(0);
    }
    std::string getResult(size_t tabs) const override {
        std::stringstream result;
        const std::string tab = std::string(tabs, '\t');
        
        result << tab << "Class `" << className_ << "` {";
        //result << std::string(tabs, '\t') << header_ << "  " << className_;
        //result << "\n" << std::string(tabs + 1, '\t') + "Has " + std::to_string(CountInstructions()) + " instructions"
        //result << "\n" << std::string(tabs + 1, '\t') + "Has " + std::to_string(CountClasses()) + " classes"
        //result << "\n" << std::string(tabs + 1, '\t') + "Has " + std::to_string(CountBlocks()) + " blocks";
        
        result << "\n" << tab << '\t' << "Class Fields:";
        result << BuildFields(tab + "\t\t");
        result << "\n\n" << tab << '\t' << "Class Operations:";
        result << BuildOperations(tab + "\t\t");

        result << "\n" << tab << "};";

        /*
        if (!subClasses_.empty()) {
            result += "\n\n";
        }
        for (const auto& element : subOperations_) {
            result += '\t' + element->getResult() + "\n";
        }
        for (const auto& element : subClasses_) {
            result += '\t' + element->getResult() + "\n\n";
        }
        */
        return result.str();
    }
    
    Type getSyntaxType() const override { return Type::Class; }
    //Memory getMemoryType() const override { return Memory::  ; } 
private:
    std::string BuildClassName(std::string header) const {
        if (auto i = header.find('{'); i != std::string::npos) {
            header = header.substr(0, i);
        }
        if (auto i = header.find("class"); i != std::string::npos) {
            header = header.substr(i + 5);
        }
        return Converter::removeWhitespaces(header);
    }

    std::string BuildFields(const std::string& tab) const {
        std::stringstream result;
        size_t count = 0;
        for (const auto& element : fields_) {
            std::string data = RemoveLabel(element->getResult());
            if (data.find("using") != std::string::npos) {
                continue;
            }
            if (data.find("};") != std::string::npos) {
                continue;
            }
            data = Converter::removeWhitespaces(data);
            result << "\n" << tab << ++count << "] " << data;
        }
        if (count == 0) {
            result << "\n" << tab << "This class has no Fields";
        }
        return result.str();
    }

    std::string BuildOperations(const std::string& tab) const {
        std::stringstream result;
        size_t count = 0;
        for (const auto& element : subOperations_) {
            result << "\n" << tab << ++count << "] " << BuildOperation(element->getResult());
        }
        return result.str();
    }

    std::string BuildOperation(std::string data) const {
        data = RemoveLabel(data);
        if (auto i = data.find(')'); i != std::string::npos) {
            data = data.substr(0, i + 1);
        }
        return Converter::removeWhitespaces(data);
    }

    std::string RemoveLabel(std::string data) const {
        if (auto i = data.find("public:"); i != std::string::npos) {
            data = data.substr(i + 7);
        }
        if (auto i = data.find("private:"); i != std::string::npos) {
            data = data.substr(i + 8);
        }
        if (auto i = data.find("protected:"); i != std::string::npos) {
            data = data.substr(i + 10);
        }
        return data;
    }

};

#pragma once

#include <map>


/*
class FileParserSyntax {
protected:
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;
    using SyntaxedData = DataStructures::SyntaxedData;
    
    FileParserSyntax() {}


public:
    static SyntaxedData generateSyntax(const Data& data) {
        return Generate(data);
    }


protected:
    static SyntaxedData Generate(const Data& data) {
        SyntaxedData result;
        std::string spareLines;
        for (const auto& line : data) {
            if (HasSemicolon(line)) {
                result.push_back({"instruction", spareLines + line});
                spareLines = CutoutSpareLines(line); 
            }
            else {
                spareLines += line + "\n";
            }
        }
        return result;
    }

    static bool HasSemicolon(const Line& line) {
        return (line.find(';') != std::string::npos); 
    }

    static Line CutoutSpareLines(const Line& line) {
        const auto i = line.find(';');
        return (i < line.size() - 1)? line.substr(i) : ""; 
    }


    //_______________________________________________________________________________________________________
    //-------------------------------------------------------------------------------------------------------
    static std::map<size_t, char> CreateTagMap(const Data& data) {
        std::map<size_t, char> result;
        
        for (size_t i = 0; i < data.size(); ++i) {
            auto open = data[i].find("{");
            auto close = data[i].find("}");
            auto key = GenerateKey(open, close);
            if (key != 'n') {
                result[i] = key;
            }
        }
        return result;
    }

    static char GenerateKey(const size_t open, const size_t close) {
        if (open == std::string::npos) {
            if (close == std::string::npos) {
                return 'n'; // none
            }
            return 'c'; // close
        }
        if (close == std::string::npos) {
            return 'o'; // open
        }
        return 'b'; // both
    }

};
*/

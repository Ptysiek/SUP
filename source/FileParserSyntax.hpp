#pragma once

#include <map>

#include "DataStructures"


class FileParserSyntax {
protected:
    using Data = DataStructures::Data;
    using Line = DataStructures::Line;
    
    FileParserSyntax() {}


public:
    static std::map<size_t, char> tagData(const Data& data) {
        return CreateTagMap(data);
    }


protected:
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


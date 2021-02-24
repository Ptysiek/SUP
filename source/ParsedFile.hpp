#pragma once

#include <string>
#include <vector>

#include "File.hpp"


class ParsedFile : public File {


public:
    explicit ParsedFile(const File& base):
        File(base)
    {}



};


#pragma once

#include <string>
#include <vector>

#include "File.hpp"
#include "PathInitializer.hpp"



class FileBuilder {
    const PathInitializer target_;
    const File product_;

public:
    FileBuilder(const PathInitializer& target, std::vector<File>& subFiles):
        target_(target),
        product_(buildProduct(subFiles))
    {}

    File getProduct() const { return product_; }
    
private:
    File buildProduct(std::vector<File>& subFiles) {
        return File(target_, subFiles);
    }
};


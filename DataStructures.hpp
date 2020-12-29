#pragma once

#include <vector>


struct File {
    explicit File(std::string& name): name_(name) {}
    
    const std::string name_;
    virtual bool ifCatalog() const { return false; }
};


struct Catalog : public File {
    explicit Catalog(std::string& name, std::vector<std::shared_ptr<File>>& files):
        File(name), files_(files) {}

    std::vector<std::shared_ptr<File>> files_;
    bool ifCatalog() const override { return true; }
};


using FilePtr = std::shared_ptr<File>;


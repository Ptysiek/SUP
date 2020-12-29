#pragma once

#include <vector>


struct File {
    explicit File(std::string& name): name_(name) {}
    
    const std::string name_;
    virtual bool isCatalog() const { return false; }
    virtual std::vector<std::shared_ptr<File>> getFiles() { 
        return std::vector<std::shared_ptr<File>>(); }
};


struct Catalog : public File {
    explicit Catalog(std::string& name, std::vector<std::shared_ptr<File>>& files):
        File(name), files_(files) {}

    std::vector<std::shared_ptr<File>> files_;
    bool isCatalog() const override { return true; }
    std::vector<std::shared_ptr<File>> getFiles() override { return files_; }
};


using FilePtr = std::shared_ptr<File>;


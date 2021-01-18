#pragma once 

#include "DirectoriesReader.hpp"
#include "File.hpp"



class DirectoriesReader_test : public DirectoriesReader {
public:
    std::string conditionalSlashAppend(const std::string& startpath) {
        return DirectoriesReader::ConditionalSlashAppend(startpath);
    }

    std::string removeSlashOnEnd (const std::string& dirname) {
        return DirectoriesReader::RemoveSlashOnEnd(dirname);
    }

    bool ignoreListContains(const std::string& data) {
        return IgnoreListContains(data);
    }

    void setIgnoreList(const std::initializer_list<std::string>& data) {
        DirectoriesReader::ignoreDirectories_ = data;
    }
    
    size_t getIgnoreListSize() const { return DirectoriesReader::ignoreDirectories_.size(); }
    const std::set<std::string>& getIgnoreList() const { return DirectoriesReader::ignoreDirectories_; }

    File makeFile(const std::string& dirName, const std::string& startpath) {
        return DirectoriesReader::MakeFile(dirName, startpath);
    }

    std::vector<File> makeFiles(
            const std::vector<std::string>& directoryNames, 
            const std::string& startpath) 
    {
        return DirectoriesReader::MakeFiles(directoryNames, startpath);
    }
};



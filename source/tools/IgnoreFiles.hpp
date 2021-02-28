#pragma once 

#include <algorithm>
#include <set>
#include <string>
#include <vector>


namespace Tools {
class IgnoreFiles {
    const static std::string filename_;
    const static std::set<std::string> alwaysIgnores_;
    const static std::set<std::string> formatIgnores_;
    static std::set<std::string> defaultIgnores_;
    static std::set<std::string> ignored_;

    explicit IgnoreFiles() { }


public:
    static void setIgnoreFiles(const std::set<std::string>& data) { defaultIgnores_ = data; }
    
    static std::string getIgnoreFileName() { return filename_; }

    static std::set<std::string> getDefaultIgnoreFiles() { return defaultIgnores_; }

    static bool isAlwaysIgnored(const std::string& value) {
        return (alwaysIgnores_.find(value) != alwaysIgnores_.end());
    }
    static bool isFormatIgnored(const std::string& format) {
        return (formatIgnores_.find(format) != formatIgnores_.end());
    }
    static bool isIgnored(const std::string& value) {
        if (isAlwaysIgnored(value)) {
            return true;
        }
        if (isFormatIgnored(value)) {
            return true;
        }
        return (defaultIgnores_.find(value) != defaultIgnores_.end());
    }
    static std::vector<std::string> pickoutAlwaysIgnored(const std::vector<std::string>& vctr) {
        std::vector<std::string> result;
        result.resize(vctr.size());
        std::copy_if(vctr.begin(), vctr.end(), result.begin(), [](auto val){return !isAlwaysIgnored(val);});
        return result;
    }
};
} // namespace Tools




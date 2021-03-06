#pragma once

#include <chrono>
#include <sstream>

#include "Tools"
#include "DataStructures"


class GeneratorTxt {
    const std::string separator_;
    const std::string targetPath_;
    std::vector<File> data_;


public:
    explicit GeneratorTxt(const std::string& targetPath, const std::vector<File>& data):
        separator_("############################################################################\n"),
        targetPath_(targetPath),
        data_(data)
    {}

    std::string buildFile() {
        std::stringstream result;       
        
        result << BuildHeader();
        result << "File generation date:  " << BuildDate();
        result << "\n\n";
        result << BuildTableOfContents();
        result << "\n\n\n\n";

        for (const auto& file : data_) {
            if (file.isCatalog()) {
                continue;
            }
            result << BuildFile(file) << "\n\n\n\n";
        }
        return result.str();
    }


private:
    std::string BuildHeader() {
        return "Author of SUP-SeeYourPoint: Kacu Kacper Kaleta [https://github.com/Ptysiek]\n";
    }

    std::string BuildDate() {
        using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
        TimePoint thisPoint = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(thisPoint);
        std::string date = std::ctime(&t);
        return date;
    }

    std::string BuildTableOfContents() {
        std::stringstream result;       

        result << BuildSeparator("### Table Of Contents: ");
        for (size_t f = 1; f < data_.size(); ++f) {
            const auto& file = data_[f];

            if (file.isCatalog()) {
                result << "\n";
            }
            for (size_t i = 0; i < file.getDepth(); ++i) {
                result << "\t";
            }
            if (file.isCatalog()) {
                result << "[" << file.getPath() << file.getName() << "]\n";
            }
            else {
                result << file.getName() << file.getFormat() << "\n"; 
            }
        }
        return result.str();
    }

    std::string BuildFile(const File& file) {
        std::stringstream result;       

        result << BuildSeparator("### " + file.getFile() + " ");
        result << BuildFileSummary(file);
        result << "\n\n";
        result << BuildFileContent(file);

        return result.str();
    }
 
    std::string BuildFileContent(const File& file) {
        std::stringstream result;       
        result << "File content:\n";
        for (const auto& ptr : file.getData().getData()) {
            if (ptr->getSyntaxType() == SyntaxTypes::Type::Instruction) {
                continue;
            }
            
            result << ptr->getResult(1) << "\n";
        }
        return result.str();
    }

    std::string BuildFileSummary(const File& file) {
        std::stringstream result;       
        result << "File includes:";
        if (!file.getData().getLibIncludes().empty()) {
            result << "\n\tLibraries included:  [" << file.getData().getLibIncludes().size() << "]\n";;
            size_t count = 0;
            for (const auto& line : file.getData().getLibIncludes()) {
                result << "\t\t " << ++count << "] <" << line << ">\n"; 
            }
        }
        if (!file.getData().getProjIncludes().empty()) {
            result << "\n\tFiles included:  [" << file.getData().getProjIncludes().size() << "]\n";
            size_t count = 0;
            for (const auto& line : file.getData().getProjIncludes()) {
                result << "\t\t " << ++count << "] " << line << "\n";
            }
        }
        return result.str();
    }

    std::string BuildSeparator(const std::string& title) {
        std::stringstream result;       
        result << title;
        if (title.size() < separator_.size()) {
            result << separator_.substr(title.size());
        }
        result << separator_;
        return result.str();
    }
};


#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string path = "D:\\Academics\\2-1\\Previous Year Questions";
    for(const auto & entry : fs::recursive_directory_iterator(path)) {
        fs::path p = entry.path();
        if(fs::is_directory(p)) continue;
        std::cout << p.filename().string() << std::endl;
    }
    return 0;
}

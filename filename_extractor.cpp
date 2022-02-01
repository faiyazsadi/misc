#include <iostream>
#include <string>
#include <filesystem>

int main() {
    std::string path = "D:\\Academics\\2-1\\Previous Year Questions";
    for(const auto & entry : std::filesystem::directory_iterator(path)) {
        std::filesystem::path p = entry.path();
        std::cout << p.filename().string() << std::endl;
    }
    return 0;
}

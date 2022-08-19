#include "File.h"
#include "GameObjectParser.h"
#include <cassert>

using namespace engine;
using namespace parser;

std::vector<std::shared_ptr<core::GameObject>> File::Load() const {
    std::fstream file(file_name_);
    assert(file.is_open());
    std::string str;
    std::string obj_info;
    std::vector<std::shared_ptr<core::GameObject>> objects;
    while (file >> str) {
        if (str.substr(0, 4) == "type" && !obj_info.empty()) {
            std::stringstream ss;
            ss << obj_info;
            objects.push_back(GameObjectParser::Parse(ss));
            obj_info.clear();
        }
        obj_info += str + "\n";
    }
    if (!obj_info.empty()) {
        std::stringstream ss;
        ss << obj_info;
        objects.push_back(GameObjectParser::Parse(ss));
    }
    file.close();
    return objects;
}

void File::Save(const std::vector<std::shared_ptr<core::GameObject>> &objects) {
    std::ofstream file(file_name_);
    assert(file.is_open());
    for (const auto &obj : objects) {
        if (!obj) continue;
        file << obj->GetString();
    }
    file.close();
}

#include "File.h"
#include "GameObjectParser.h"

std::vector<std::shared_ptr<engine::GameObject>> engine::File::Load() const
{
    std::fstream file(file_name_);
    if (!file) throw std::runtime_error("File does not exist");
    std::string str;
    std::string obj_info;
    std::vector<std::shared_ptr<GameObject>> objects;
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

void engine::File::Save(const std::vector<std::shared_ptr<GameObject>>& objects)
{
    std::ofstream file(file_name_);
    if (!file) throw std::runtime_error("Can't create or open file");
    for (const auto& obj : objects) {
        if (!obj) continue;
        file << obj->GetString();
    }
    file.close();
}

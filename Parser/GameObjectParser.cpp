#include "GameObjectParser.h"

using namespace engine;
using namespace parser;

std::shared_ptr<core::GameObject> GameObjectParser::Parse(std::stringstream &stream) {
    std::string type;
    stream >> type;
    type = Split(type)[1];
    std::shared_ptr<core::GameObject> object = nullptr;
    if (type == "point") {
        object = std::make_shared<core::Point>(core::Vector2f());
    } else if (type == "line") {
        object = std::make_shared<core::Line>(core::Vector2f(), core::Vector2f());
    } else if (type == "rectangle") {
        object = std::make_shared<core::Rectangle>(core::Vector2f(), core::Vector2f());
    } else if (type == "circle") {
        object = std::make_shared<core::Circle>(core::Vector2f(), 0.0f);
    } else if (type == "triangle") {
        object = std::make_shared<core::Triangle>(core::Vector2f(), core::Vector2f(), core::Vector2f(),
                                                  core::Vector2f(), core::Vector2f());
    } else if (type == "polygon") {
        object = std::make_shared<core::Polygon>(core::Vector2f(), core::Vector2f(), std::vector<core::Vector2f>{});
    }
    if (!object) return nullptr;
    object->StringToObject(stream);
    return object;
}

std::vector<std::string> GameObjectParser::Split(const std::string &str) {
    std::vector<std::string> words;
    std::string word;

    for (char ch : str) {
        if (ch == ',' || ch == '=') {
            words.push_back(word);
            word.clear();
        } else word += ch;
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

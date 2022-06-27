#include "GameObjectParser.h"

std::shared_ptr<engine::GameObject> engine::GameObjectParser::Parse(std::stringstream& stream)
{
    std::string type;
    stream >> type;
    type = Split(type)[1];
    std::shared_ptr<GameObject> object = nullptr;
    if (type == "point") {
        object = std::make_shared<Point>(Vector2f());
    }
    else if (type == "line") {
        object = std::make_shared<Line>(Vector2f(), Vector2f());
    }
    else if (type == "rectangle") {
        object = std::make_shared<Rectangle>(Vector2f(), Vector2f());
    }
    else if (type == "circle") {
        object = std::make_shared<Circle>(Vector2f(), 0.0f);
    }
    else if (type == "triangle") {
        object = std::make_shared<Triangle>(Vector2f(), Vector2f(), Vector2f(), Vector2f(), Vector2f());
    }
    else if (type == "polygon") {
        object = std::make_shared<Polygon>(Vector2f(), Vector2f(), std::vector<Vector2f>{});
    }
    if (!object) return nullptr;
    object->StringToObject(stream);
    return object;
}

std::vector<std::string> engine::GameObjectParser::Split(const std::string& str)
{
    std::vector<std::string> words;
    std::string word;

    for (char ch : str) {
        if (ch == ',' || ch == '=') {
            words.push_back(word);
            word.clear();
        }
        else word += ch;
    }
    if (!word.empty()) words.push_back(word);
    return words;
}

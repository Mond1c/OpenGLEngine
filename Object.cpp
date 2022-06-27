#include "Object.h"
#include "GameObjectParser.h"
#include <stdexcept>
#include <stdio.h>
#include <cmath>
using namespace engine;

#define DEFAULT_SCALE 1
#define PI 3.1415926535897932384626433

Vector2f GameObject::GetPosition() const {
    return transform_->Position;
}

Vector2f GameObject::GetSize() const {
    return transform_->Scale;
}

Color GameObject::GetColor() const {
    return color_;
}

std::shared_ptr<Transform>& engine::GameObject::GetTransform()
{
    return transform_;
}   

void GameObject::SetPosition(const Vector2f& position) {
    transform_->Position = ToScreenPoint(position);
}

void GameObject::SetScale(const Vector2f& scale) {
    transform_->Scale = scale;
}

void GameObject::SetColor(const Color& color) {
    color_ = color;
}

void engine::GameObject::AddComponent(std::shared_ptr<IComponent> component)
{
    components_.push_back(component);
}

void engine::GameObject::Update()
{
    for (auto& component : components_) component->Update();
}

void Rectangle::Draw() const {
    glBegin(GL_QUADS);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(transform_->Position.x - DEFAULT_SCALE * transform_->Scale.x,
        transform_->Position.y + DEFAULT_SCALE * transform_->Scale.y);
    glVertex2f(transform_->Position.x + DEFAULT_SCALE * transform_->Scale.x,
        transform_->Position.y + DEFAULT_SCALE * transform_->Scale.y);
    glVertex2f(transform_->Position.x + DEFAULT_SCALE * transform_->Scale.x,
        transform_->Position.y - DEFAULT_SCALE * transform_->Scale.y);
    glVertex2f(transform_->Position.x - DEFAULT_SCALE * transform_->Scale.x,
        transform_->Position.y - DEFAULT_SCALE * transform_->Scale.y);
    glEnd();
}

void engine::Rectangle::StringToObject(std::stringstream& ss)
{
    std::string str;
    while (ss >> str) {
        std::vector<std::string> elements = GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
        else if (elements[1] == "scale") SetScale(ParseVector2f(elements[1], elements[2]));
    }
}

std::string engine::Rectangle::GetString() const
{
    Vector2f scale = transform_->Scale;
    return "type=rectangle\nposition=" + Vector2fToString(transform_->Position) + "\n"
        + "scale=" + std::to_string(scale.x) + "," + std::to_string(scale.y) + "\n";
}

std::array<Vector2f, 3> engine::Triangle::GetPoints() const
{
    return points_;
}

void Triangle::SetPoints(const std::array<Vector2f, 3>& points)
{
    points_ = points;
}

void Triangle::Draw() const {
    glBegin(GL_TRIANGLES);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(transform_->Position.x + points_[0].x * DEFAULT_SCALE * transform_->Scale.x,
        transform_->Position.y + points_[0].y * DEFAULT_SCALE * transform_->Scale.y);
    glVertex2f(transform_->Position.x + points_[1].x * DEFAULT_SCALE * transform_->Scale.x,
        transform_->Position.y + points_[1].y * DEFAULT_SCALE * transform_->Scale.y);
    glVertex2f(transform_->Position.x + points_[2].x * DEFAULT_SCALE * transform_->Scale.x,
        transform_->Position.y + points_[2].y * DEFAULT_SCALE * transform_->Scale.y);
    glEnd();
}

void engine::Triangle::StringToObject(std::stringstream& ss)
{
    std::string str;
    int point = 0;
    while (ss >> str) {
        std::vector<std::string> elements = GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "scale") SetScale(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "vertex") points_[point++] = ToScreenPoint(ParseVector2f(elements[1], elements[2]));
    }
}

std::string engine::Triangle::GetString() const
{
    Vector2f scale = transform_->Scale;
    return "type=triangle\nposition=" + Vector2fToString(transform_->Position) + "\n"
        + "scale=" + std::to_string(scale.x) + "," + std::to_string(scale.y) + "\n"
        + "vertex=" + Vector2fToString(points_[0]) + "\n"
        + "vertex=" + Vector2fToString(points_[1]) + "\n"
        + "vertex=" + Vector2fToString(points_[2]) + "\n";
}

void Point::SetScale(const Vector2f& scale)
{
    printf("You can't use this method with point (SetSize)");
    throw std::runtime_error("You can't use this method with point");
}

void Point::Draw() const
{
    glBegin(GL_POINT);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(transform_->Position.x, transform_->Position.y);
    glEnd();
}

void engine::Point::StringToObject(std::stringstream& ss)
{
    std::string str;
    while (ss >> str) {
        std::vector<std::string> elements = GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
    }
}

std::string engine::Point::GetString() const
{
    Vector2f position = ToWorldPoint(transform_->Position);
    return "type=point\nposition=" + std::to_string(position.x) + "," + std::to_string(position.y) + "\n";
}

void engine::Line::SetScale(const Vector2f& size)
{
    printf("You can't use this method with line (SetSize)");
    throw std::runtime_error("You can't use this method with line");
}

void engine::Line::Draw() const
{
    glBegin(GL_LINE);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(transform_->Position.x, transform_->Position.y);
    glVertex2f(point_.x, point_.y);
    glEnd();
}

void engine::Line::StringToObject(std::stringstream& ss)
{
    std::string str;
    bool isItFirstPoint = true;
    while (ss >> str) {
        std::vector<std::string> elements = GameObjectParser::Split(str);
        if (elements[0] == "position") {
            if (isItFirstPoint) SetPosition(ParseVector2f(elements[1], elements[2]));
            else point_ = ToScreenPoint(ParseVector2f(elements[1], elements[2]));
            isItFirstPoint = false;
        }
    }
}

std::string engine::Line::GetString() const
{
    return "type=line\nposition=" + Vector2fToString(transform_->Position) + "\n"
        + "position=" + Vector2fToString(point_) + "\n";
}

void engine::Polygon::UpdateVertices()
{
    for (auto& vertex : vertices_) {
        vertex.x = transform_->Position.x + vertex.x * DEFAULT_SCALE * transform_->Scale.x;
        vertex.y = transform_->Position.y + vertex.y * DEFAULT_SCALE * transform_->Scale.x;
    }
}

void engine::Polygon::Draw() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertexPointer(2, GL_FLOAT, 0, vertices_.data());
    glDrawArrays(GL_POLYGON, 0, vertices_.size());
    glDisableClientState(GL_VERTEX_ARRAY);
}

void engine::Polygon::StringToObject(std::stringstream& ss)
{
    std::string str;
    while (ss >> str) {
        std::vector<std::string> elements = GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "scale") SetScale(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "vertex") vertices_.push_back(ToScreenPoint(ParseVector2f(elements[1], elements[2])));
    }
}

std::string engine::Polygon::GetString() const
{
    std::string ans = "type=polygon";
    for (auto vertex : vertices_) {
        ans += "\nposition=" + Vector2fToString(vertex);
    }
    return ans;
}

void engine::Circle::Draw() const
{
    float radius = transform_->Scale.x;
    int i;
    int triangleAmount = 40;
    glBegin(GL_TRIANGLE_FAN);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    for (i = 0; i <= triangleAmount; ++i) {
        glVertex2f(
            transform_->Position.x + (radius * cos(i * 2 * PI / triangleAmount)),
            transform_->Position.y + (radius * sin(i * 2 * PI / triangleAmount))
        );
    }
    glEnd();
}

void engine::Circle::StringToObject(std::stringstream& ss)
{
    std::string str;
    while (ss >> str) {
        std::vector<std::string> elements = GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "radius") SetScale(ToScreenPoint(Vector2f(std::stof(elements[1]), std::stof(elements[1]))));
    }
}

std::string engine::Circle::GetString() const
{
    return "type=circle\nposition=" + Vector2fToString(transform_->Position)
        + "radius=" + std::to_string(ToWorldPoint(transform_->Scale).x) + "\n";
}

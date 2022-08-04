#include "GameObject.h"
#include "GameObjectParser.h"
#include <stdexcept>
#include <stdio.h>
#include <cmath>
using namespace engine;
using namespace core;

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

std::shared_ptr<Transform>& GameObject::GetTransform()
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

void GameObject::AddComponent(std::shared_ptr<IComponent> component)
{
    components_.push_back(component);
}

void GameObject::Update()
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

void Rectangle::StringToObject(std::stringstream& ss)
{
    std::string str;
    while (ss >> str) {
        std::vector<std::string> elements = parser::GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "scale") SetScale(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "color") SetColor(ParseColor(elements[1], elements[2], elements[3], elements[4]));
    }
}

std::string Rectangle::GetString() const
{
    Vector2f scale = transform_->Scale;
    return "type=rectangle\nposition=" + Vector2fToString(transform_->Position) + "\n"
        + "scale=" + std::to_string(scale.x) + "," + std::to_string(scale.y) + "\n"
        + "color=" + ColorToString(color_) + "\n";
}

std::array<Vector2f, 3> Triangle::GetPoints() const
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

void Triangle::StringToObject(std::stringstream& ss)
{
    std::string str;
    int point = 0;
    while (ss >> str) {
        std::vector<std::string> elements = parser::GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "scale") SetScale(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "vertex") points_[point++] = ToScreenPoint(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "color") SetColor(ParseColor(elements[1], elements[2], elements[3], elements[4]));
    }
}

std::string Triangle::GetString() const
{
    Vector2f scale = transform_->Scale;
    return "type=triangle\nposition=" + Vector2fToString(transform_->Position) + "\n"
        + "scale=" + std::to_string(scale.x) + "," + std::to_string(scale.y) + "\n"
        + "vertex=" + Vector2fToString(points_[0]) + "\n"
        + "vertex=" + Vector2fToString(points_[1]) + "\n"
        + "vertex=" + Vector2fToString(points_[2]) + "\n"
        + "color=" + ColorToString(color_) + "\n";
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

void Point::StringToObject(std::stringstream& ss)
{
    std::string str;
    while (ss >> str) {
        std::vector<std::string> elements = parser::GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "color") SetColor(ParseColor(elements[1], elements[2], elements[3], elements[4]));
    }
}

std::string Point::GetString() const
{
    Vector2f position = ToWorldPoint(transform_->Position);
    return "type=point\nposition=" + std::to_string(position.x) + "," + std::to_string(position.y) + "\n"
        + "color=" + ColorToString(color_) + "\n";
}

void Line::SetScale(const Vector2f& size)
{
    printf("You can't use this method with line (SetSize)");
    throw std::runtime_error("You can't use this method with line");
}

void Line::Draw() const
{
    glBegin(GL_LINE);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(transform_->Position.x, transform_->Position.y);
    glVertex2f(point_.x, point_.y);
    glEnd();
}

void Line::StringToObject(std::stringstream& ss)
{
    std::string str;
    bool isItFirstPoint = true;
    while (ss >> str) {
        std::vector<std::string> elements = parser::GameObjectParser::Split(str);
        if (elements[0] == "position") {
            if (isItFirstPoint) SetPosition(ParseVector2f(elements[1], elements[2]));
            else point_ = ToScreenPoint(ParseVector2f(elements[1], elements[2]));
            isItFirstPoint = false;
        }
        else if (elements[0] == "color") SetColor(ParseColor(elements[1], elements[2], elements[3], elements[4]));
    }
}

std::string Line::GetString() const
{
    return "type=line\nposition=" + Vector2fToString(transform_->Position) + "\n"
        + "position=" + Vector2fToString(point_) + "\n"
        + "color=" + ColorToString(color_) + "\n";
}

std::vector<Vector2f> Polygon::GetVertices() const
{
    std::vector<Vector2f> ans(vertices_.size());
    for (const auto& vertex : vertices_) {
        ans.push_back(Vector2f(transform_->Position.x + vertex.x * DEFAULT_SCALE * transform_->Scale.x,
                transform_->Position.y + vertex.y * DEFAULT_SCALE * transform_->Scale.x));
    }
    return ans;
}

void Polygon::Draw() const
{
    std::vector<Vector2f> vertices = GetVertices();
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertexPointer(2, GL_FLOAT, 0, vertices.data());
    glDrawArrays(GL_POLYGON, 0, vertices.size());
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Polygon::StringToObject(std::stringstream& ss)
{
    std::string str;
    while (ss >> str) {
        std::vector<std::string> elements = parser::GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "scale") SetScale(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "vertex") vertices_.push_back(ToScreenPoint(ParseVector2f(elements[1], elements[2])));
        else if (elements[0] == "color") SetColor(ParseColor(elements[1], elements[2], elements[3], elements[4]));
    }
}

std::string Polygon::GetString() const
{
    std::string ans = "type=polygon\nposition=" + Vector2fToString(transform_->Position) 
        + "\nscale=" + std::to_string(transform_->Scale.x) + "," + std::to_string(transform_->Scale.y);
    for (auto vertex : vertices_) {
        ans += "\nvertex=" + Vector2fToString(vertex);
    }
    ans += "\ncolor=" + ColorToString(color_) + "\n";
    return ans;
}

void Circle::Draw() const
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

void Circle::StringToObject(std::stringstream& ss)
{
    std::string str;
    while (ss >> str) {
        std::vector<std::string> elements = parser::GameObjectParser::Split(str);
        if (elements[0] == "position") SetPosition(ParseVector2f(elements[1], elements[2]));
        else if (elements[0] == "radius") SetScale(ToScreenPoint(Vector2f(std::stof(elements[1]), std::stof(elements[1]))));
        else if (elements[0] == "color") SetColor(ParseColor(elements[1], elements[2], elements[3], elements[4]));
    }
}

std::string Circle::GetString() const
{
    return "type=circle\nposition=" + Vector2fToString(transform_->Position) + "\n"
        + "radius=" + std::to_string(ToWorldPoint(transform_->Scale).x) + "\n"
        + "color=" + ColorToString(color_) + "\n";
}

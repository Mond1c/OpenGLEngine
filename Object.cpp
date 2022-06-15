#include "Object.h"
#include <stdexcept>
#include <stdio.h>
using namespace engine;

Vector2f Object::GetPosition() const {
    return position_;
}

Vector2f Object::GetSize() const {
    return size_;
}

Color Object::GetColor() const {
    return color_;
}

void Object::SetPosition(Vector2f&& position) {
    position_ = std::move(position);
}

void Object::SetSize(Vector2f&& size) {
    size_ = std::move(size);
}

void Object::SetColor(Color&& color) {
    color_ = std::move(color);
}

void Rectangle::Draw() const {
    glBegin(GL_QUADS);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(position_.x, position_.y);
    glVertex2f(position_.x + size_.x, position_.y);
    glVertex2f(position_.x + size_.x, position_.y - size_.y);
    glVertex2f(position_.x, position_.y - size_.y);
    glEnd();
}

std::array<Vector2f, 3> engine::Triangle::GetPoints() const
{
    return points_;
}

Vector2f engine::Triangle::GetPosition() const
{
    printf("You can't use this method with triangle (GetPosition)");
    throw std::runtime_error("You can't use this method with triangle");
}

Vector2f engine::Triangle::GetSize() const
{
    printf("You can't use this method with triangle (GetSize)");
    throw std::runtime_error("You can't use this method with triangle");
}

void engine::Triangle::SetPoints(std::array<Vector2f, 3>&& points)
{
    points_ = std::move(points);
}

void engine::Triangle::SetPosition(Vector2f&& position)
{
    printf("You can't use this method with triangle (SetPosition)");
    throw std::runtime_error("You can't use this method with triangle");
}

void engine::Triangle::SetSize(Vector2f&& size)
{
    printf("You can't use this method with triangle (SetSize)");
    throw std::runtime_error("You can't use this method with triangle");
}

void Triangle::Draw() const {
    glBegin(GL_TRIANGLES);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(points_[0].x, points_[0].y);
    glVertex2f(points_[1].x, points_[1].y);
    glVertex2f(points_[2].x, points_[2].y);
    glEnd();
}
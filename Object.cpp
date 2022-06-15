#include "Object.h"
#include <stdexcept>
#include <stdio.h>
using namespace engine;

#define DEFAULT_SCALE 1

Vector2f Object::GetPosition() const {
    return position_;
}

Vector2f Object::GetSize() const {
    return scale_;
}

Color Object::GetColor() const {
    return color_;
}

void Object::SetPosition(Vector2f&& position) {
    position_ = std::move(position);
}

void Object::SetScale(Vector2f&& scale) {
    scale_ = std::move(scale);
}

void Object::SetColor(Color&& color) {
    color_ = std::move(color);
}

void Rectangle::Draw() const {
    glBegin(GL_QUADS);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(position_.x - DEFAULT_SCALE * scale_.x, position_.y + DEFAULT_SCALE * scale_.y);
    glVertex2f(position_.x + DEFAULT_SCALE * scale_.x, position_.y + DEFAULT_SCALE * scale_.y);
    glVertex2f(position_.x + DEFAULT_SCALE * scale_.x, position_.y - DEFAULT_SCALE * scale_.y);
    glVertex2f(position_.x - DEFAULT_SCALE * scale_.x, position_.y - DEFAULT_SCALE * scale_.y);
    glEnd();
}

std::array<Vector2f, 3> engine::Triangle::GetPoints() const
{
    return points_;
}

void Triangle::SetPoints(std::array<Vector2f, 3>&& points)
{
    points_ = std::move(points);
}

void Triangle::Draw() const {
    glBegin(GL_TRIANGLES);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(position_.x + points_[0].x * DEFAULT_SCALE * scale_.x,
        position_.y + points_[0].y * DEFAULT_SCALE * scale_.y);
    glVertex2f(position_.x + points_[1].x * DEFAULT_SCALE * scale_.x,
        position_.y + points_[1].y * DEFAULT_SCALE * scale_.y);
    glVertex2f(position_.x + points_[2].x * DEFAULT_SCALE * scale_.x,
        position_.y + points_[2].y * DEFAULT_SCALE * scale_.y);
    glEnd();
}

void Point::SetScale(Vector2f&& scale)
{
    printf("You can't use this method with triangle (SetSize)");
    throw std::runtime_error("You can't use this method with point");
}

void Point::Draw() const
{
    glBegin(GL_POINT);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(position_.x, position_.y);
    glEnd();
}

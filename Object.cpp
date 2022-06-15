#include "Object.h"
#include <stdexcept>
#include <stdio.h>
#include <cmath>
using namespace engine;

#define DEFAULT_SCALE 1
#define PI 3.1415926535897932384626433

Vector2f Object::GetPosition() const {
    return transform_.Position;
}

Vector2f Object::GetSize() const {
    return transform_.Scale;
}

Color Object::GetColor() const {
    return color_;
}

void Object::SetPosition(Vector2f&& position) {
    transform_.Position = std::move(position);
}

void Object::SetScale(Vector2f&& scale) {
    transform_.Scale = std::move(scale);
}

void Object::SetColor(Color&& color) {
    color_ = std::move(color);
}

void Rectangle::Draw() const {
    glBegin(GL_QUADS);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(transform_.Position.x - DEFAULT_SCALE * transform_.Scale.x,
        transform_.Position.y + DEFAULT_SCALE * transform_.Scale.y);
    glVertex2f(transform_.Position.x + DEFAULT_SCALE * transform_.Scale.x,
        transform_.Position.y + DEFAULT_SCALE * transform_.Scale.y);
    glVertex2f(transform_.Position.x + DEFAULT_SCALE * transform_.Scale.x,
        transform_.Position.y - DEFAULT_SCALE * transform_.Scale.y);
    glVertex2f(transform_.Position.x - DEFAULT_SCALE * transform_.Scale.x,
        transform_.Position.y - DEFAULT_SCALE * transform_.Scale.y);
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
    glVertex2f(transform_.Position.x + points_[0].x * DEFAULT_SCALE * transform_.Scale.x,
        transform_.Position.y + points_[0].y * DEFAULT_SCALE * transform_.Scale.y);
    glVertex2f(transform_.Position.x + points_[1].x * DEFAULT_SCALE * transform_.Scale.x,
        transform_.Position.y + points_[1].y * DEFAULT_SCALE * transform_.Scale.y);
    glVertex2f(transform_.Position.x + points_[2].x * DEFAULT_SCALE * transform_.Scale.x,
        transform_.Position.y + points_[2].y * DEFAULT_SCALE * transform_.Scale.y);
    glEnd();
}

void Point::SetScale(Vector2f&& scale)
{
    printf("You can't use this method with point (SetSize)");
    throw std::runtime_error("You can't use this method with point");
}

void Point::Draw() const
{
    glBegin(GL_POINT);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(transform_.Position.x, transform_.Position.y);
    glEnd();
}

void engine::Line::SetScale(Vector2f&& size)
{
    printf("You can't use this method with line (SetSize)");
    throw std::runtime_error("You can't use this method with line");
}

void engine::Line::Draw() const
{
    glBegin(GL_LINE);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertex2f(transform_.Position.x, transform_.Position.y);
    glVertex2f(point_.x, point_.y);
    glEnd();
}

void engine::Polygon::UpdateVertixes()
{
    for (auto& vertix : vertixes_) {
        vertix.x = transform_.Position.x + vertix.x * DEFAULT_SCALE * transform_.Scale.x;
        vertix.y = transform_.Position.y + vertix.y * DEFAULT_SCALE * transform_.Scale.x;
        vertix = ToScreenPoint(vertix);
    }
}

void engine::Polygon::Draw() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    glVertexPointer(2, GL_FLOAT, 0, vertixes_.data());
    glDrawArrays(GL_POLYGON, 0, vertixes_.size());
    glDisableClientState(GL_VERTEX_ARRAY);
}

void engine::Circle::Draw() const
{
    float radius = transform_.Scale.x;
    int i;
    int triangleAmount = 40;
    glBegin(GL_TRIANGLE_FAN);
    glColor4ub(color_.r, color_.g, color_.b, color_.a);
    for (i = 0; i <= triangleAmount; ++i) {
        glVertex2f(
            transform_.Position.x + (radius * cos(i * 2 * PI / triangleAmount)),
            transform_.Position.y + (radius * sin(i * 2 * PI / triangleAmount))
        );
    }
    glEnd();
}

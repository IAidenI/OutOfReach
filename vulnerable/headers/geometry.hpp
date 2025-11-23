#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <raylib.h>
#include <raymath.h>
using namespace std;

using Frame = Rectangle;
using Size2D = Vector2;
using Size3D = Vector3;
using Position2D = Vector2;
using Position3D = Vector3;

// ---- Padding ----
struct Spacing {
    float x;
    float y;
};
using Padding = Spacing;
using Margins = Spacing;

#endif // GEOMETRY_HPP

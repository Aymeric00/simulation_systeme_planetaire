#include "vec2.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

/// Create a 2d vector.
/// @param x_ The first component.
/// @param y_ The second component.
/// @return The newly created vector.
vec2 vec2_create(double x_, double y_)
{
    vec2 v;
    v.x = x_;
    v.y = y_;
    return v;
}

/// Create a zero 2d vector.
/// @return The newly created zero vector.
vec2 vec2_create_zero()
{
    return vec2_create(0.0, 0.0);
}

/// Add two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The sum in a new vector.
vec2 vec2_add(vec2 lhs, vec2 rhs)
{
    vec2 v;
    v.x = lhs.x + rhs.x;
    v.y = lhs.y + rhs.y;

    return v;
}

/// Substract two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The difference in a new vector.
vec2 vec2_sub(vec2 lhs, vec2 rhs)
{
    vec2 v;
    v.x = lhs.x - rhs.x;
    v.y = lhs.y - rhs.y;

    return v;
}

/// Multiply a vector by a scalar.
/// @param scalar The left operand, a scalar.
/// @param rhs The right operand, a vector.
/// @return The product in a new vector.
vec2 vec2_mul(double scalar, vec2 rhs)
{
    vec2 v;
    v.x = rhs.x * scalar;
    v.y = rhs.y * scalar;

    return v;
}

/// Compute the dot product (scalar product) between two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The dot product.
double vec2_dot(vec2 lhs, vec2 rhs)
{
    double x;
    double y;
    x = lhs.x * rhs.x;
    y = lhs.y * rhs.y;

    return (x + y);
}

/// Compute the square of the euclidean norm of a given vector.
/// @param v The vector.
/// @return The square of the norm.
double vec2_norm_sqr(vec2 v)
{
    return (v.x * v.x) + (v.y * v.y);
}

/// Compute the euclidean norm of a given vector.
/// @param v The vector.
/// @return The norm.
double vec2_norm(vec2 v)
{
    return sqrt(vec2_norm_sqr(v));
}

/// Compute the normalization of a given vector.
/// @param v The vector.
/// @return The new normalized vector.
vec2 vec2_normalize(vec2 v)
{
    vec2 v2;
    v2.x = v.x / vec2_norm(v);
    v2.y = v.y / vec2_norm(v);

    return v2;
}

/// Check whether two vectors are approximately equals within a given tolerance.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @param eps The tolerance.
/// @return true if vector are approximately equal, false otherwise.
bool vec2_is_approx_equal(vec2 lhs, vec2 rhs, double eps)
{
    if (rhs.x - eps <= lhs.x && lhs.x <= rhs.x + eps && rhs.y - eps <= lhs.y && lhs.y <= rhs.y + eps){
        return true;
    }
    else{
        return false;
    }
}

/// Compute the coordinates of a 2d vector (with components between -1 and 1)
/// in a given screen matrix.
/// @param v The 2d vector.
/// @param width The screen width.
/// @param height The screen height.
/// @return The coordinates (row, column).
coordinates vec2_to_coordinates(vec2 v, uint32_t width, uint32_t height)
{
    // param [-1, 1] return pixel coord
    // if x = 0.5 return width/2
    // width -1 because the first pixel is 0
    coordinates result;
    result.row = (uint32_t)((v.y / 2 + 0.5) * (height - 1) + 0.5);
    result.column = (uint32_t)((v.x / 2 + 0.5) * (width - 1) + 0.5);

    return result;
}

/// Print a vector in the standard output.
/// @param v The vector.
void vec2_print(vec2 v)
{
    printf("x = %g, y = %g\n", v.x, v.y);
}

/// Divide the vecteur with a scalar.
/// @param vec The vector.
/// @param scalar The scalar.
vec2 vec2_div(vec2 vec, double scalar)
{
    vec2 result;
    result.x = -1 * vec.x / scalar; //Inverser la direction (force d'attraction)
    result.y = -1 * vec.y / scalar; //Inverser la direction (force d'attraction)
    return result;
}

vec2 vec_to_position_display(vec2 pos, long f) {
    return vec2_mul(1.0 / f, pos);
}

/// @param c coordonnée 1
/// @param c2 coordonnée 1
/// @return vrai ou faux
bool comp_coords(coordinates c, coordinates c2){
    return c.column == c2.column && c.row == c2.row;
}
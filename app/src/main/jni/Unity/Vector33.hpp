#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>


struct Vector33
{
    union
    {
        struct
        {
            float X;
            float Y;
            float Z;
        };
        float data[3];
    };


    /**
     * Constructors.
     */
    inline Vector33();
    inline Vector33(float data[]);
    inline Vector33(float value);
    inline Vector33(float x, float y);
    inline Vector33(float x, float y, float z);


    /**
     * Constants for common vectors.
     */
    static inline Vector33 Zero();
    static inline Vector33 One();
    static inline Vector33 Right();
    static inline Vector33 Left();
    static inline Vector33 Up();
    static inline Vector33 Down();
    static inline Vector33 Forward();
    static inline Vector33 Backward();


    /**
     * Returns the angle between two vectors in radians.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A scalar value.
     */
    static inline float Angle(Vector33 a, Vector33 b);

    /**
     * Retorna um vetor com sua magnitude fixada em maxLength.
     * @param vector: O vetor de destino.
     * @param maxLength: O comprimento máximo do vetor de retorno.
     * @return: Um novo vetor.
     */

    static inline Vector33 ClampMagnitude(Vector33 vector, float maxLength);

    /**
     * Returns the component of a in the direction of b (scalar projection).
     * @param a: The target vector.
     * @param b: The vector being compared against.
     * @return: A scalar value.
     */
    static inline float Component(Vector33 a, Vector33 b);

    /**
     * Returns the cross product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A new vector.
     */
    static inline Vector33 Cross(Vector33 lhs, Vector33 rhs);

    /**
     * Returns the distance between a and b.
     * @param a: The first point.
     * @param b: The second point.
     * @return: A scalar value.
     */
    static inline float Distance(Vector33 a, Vector33 b);

    static inline char ToChar(Vector33 a);

    /**
     * Returns the dot product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(Vector33 lhs, Vector33 rhs);

    /**
     * Converts a spherical representation of a vector into cartesian
     * coordinates.
     * This uses the ISO convention (radius r, inclination theta, azimuth phi).
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the XY plane from the X axis.
     * @param phi: The angle from the positive Z axis to the vector.
     * @return: A new vector.
     */
    static inline Vector33 FromSpherical(float rad, float theta, float phi);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line. The vector is clamped to never go beyond the end points.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1].
     * @return: A new vector.
     */
    static inline Vector33 Lerp(Vector33 a, Vector33 b, float t);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1] (no actual bounds).
     * @return: A new vector.
     */
    static inline Vector33 LerpUnclamped(Vector33 a, Vector33 b, float t);

    /**
     * Returns the magnitude of a vector.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float Magnitude(Vector33 v);

    /**
     * Returns a vector made from the largest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector33 Max(Vector33 a, Vector33 b);

    /**
     * Returns a vector made from the smallest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector33 Min(Vector33 a, Vector33 b);

    /**
     * Returns a vector "maxDistanceDelta" units closer to the target. This
     * interpolation is in a straight line, and will not overshoot.
     * @param current: The current position.
     * @param target: The destination position.
     * @param maxDistanceDelta: The maximum distance to move.
     * @return: A new vector.
     */
    static inline Vector33 MoveTowards(Vector33 current, Vector33 target,
                                      float maxDistanceDelta);

    /**
     * Returns a new vector with magnitude of one.
     * @param v: The vector in question.
     * @return: A new vector.
     */
    static inline Vector33 Normalized(Vector33 v);

    /**
     * Returns an arbitrary vector orthogonal to the input.
     * This vector is not normalized.
     * @param v: The input vector.
     * @return: A new vector.
     */
    static inline Vector33 Orthogonal(Vector33 v);

    /**
     * Creates a new coordinate system out of the three vectors.
     * Normalizes "normal", normalizes "tangent" and makes it orthogonal to
     * "normal" and normalizes "binormal" and makes it orthogonal to both
     * "normal" and "tangent".
     * @param normal: A reference to the first axis vector.
     * @param tangent: A reference to the second axis vector.
     * @param binormal: A reference to the third axis vector.
     */
    static inline void OrthoNormalize(Vector33 &normal, Vector33 &tangent,
                                      Vector33 &binormal);

    /**
     * Returns the vector projection of a onto b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector33 Project(Vector33 a, Vector33 b);

    /**
     * Returns a vector projected onto a plane orthogonal to "planeNormal".
     * This can be visualized as the shadow of the vector onto the plane, if
     * the light source were in the direction of the plane normal.
     * @param vector: The vector to project.
     * @param planeNormal: The normal of the plane onto which to project.
     * @param: A new vector.
     */
    static inline Vector33 ProjectOnPlane(Vector33 vector, Vector33 planeNormal);

    /**
     * Returns a vector reflected off the plane orthogonal to the normal.
     * The input vector is pointed inward, at the plane, and the return vector
     * is pointed outward from the plane, like a beam of light hitting and then
     * reflecting off a mirror.
     * @param vector: The vector traveling inward at the plane.
     * @param planeNormal: The normal of the plane off of which to reflect.
     * @return: A new vector pointing outward from the plane.
     */
    static inline Vector33 Reflect(Vector33 vector, Vector33 planeNormal);

    /**
     * Returns the vector rejection of a on b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector33 Reject(Vector33 a, Vector33 b);

    /**
     * Rotates vector "current" towards vector "target" by "maxRadiansDelta".
     * This treats the vectors as directions and will linearly interpolate
     * between their magnitudes by "maxMagnitudeDelta". This function does not
     * overshoot. If a negative delta is supplied, it will rotate away from
     * "target" until it is pointing the opposite direction, but will not
     * overshoot that either.
     * @param current: The starting direction.
     * @param target: The destination direction.
     * @param maxRadiansDelta: The maximum number of radians to rotate.
     * @param maxMagnitudeDelta: The maximum delta for magnitude interpolation.
     * @return: A new vector.
     */
    static inline Vector33 RotateTowards(Vector33 current, Vector33 target,
                                        float maxRadiansDelta,
                                        float maxMagnitudeDelta);

    /**
     * Multiplies two vectors element-wise.
     * @param a: The lhs of the multiplication.
     * @param b: The rhs of the multiplication.
     * @return: A new vector.
     */
    static inline Vector33 Scale(Vector33 a, Vector33 b);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is clamped to 0 <= t <= 1.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector33 Slerp(Vector33 a, Vector33 b, float t);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is unclamped.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector33 SlerpUnclamped(Vector33 a, Vector33 b, float t);

    /**
     * Returns the squared magnitude of a vector.
     * This is useful when comparing relative lengths, where the exact length
     * is not important, and much time can be saved by not calculating the
     * square root.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float SqrMagnitude(Vector33 v);

    /**
     * Calculates the spherical coordinate space representation of a vector.
     * This uses the ISO convention (radius r, inclination theta, azimuth phi).
     * @param vector: The vector to convert.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the XY plane from the X axis.
     * @param phi: The angle from the positive Z axis to the vector.
     */
    static inline void ToSpherical(Vector33 vector, float &rad, float &theta,
                                   float &phi);


    /**
     * Operator overloading.
     */
    inline struct Vector33& operator+=(const float rhs);
    inline struct Vector33& operator-=(const float rhs);
    inline struct Vector33& operator*=(const float rhs);
    inline struct Vector33& operator/=(const float rhs);
    inline struct Vector33& operator+=(const Vector33 rhs);
    inline struct Vector33& operator-=(const Vector33 rhs);
};

inline Vector33 operator-(Vector33 rhs);
inline Vector33 operator+(Vector33 lhs, const float rhs);
inline Vector33 operator-(Vector33 lhs, const float rhs);
inline Vector33 operator*(Vector33 lhs, const float rhs);
inline Vector33 operator/(Vector33 lhs, const float rhs);
inline Vector33 operator+(const float lhs, Vector33 rhs);
inline Vector33 operator-(const float lhs, Vector33 rhs);
inline Vector33 operator*(const float lhs, Vector33 rhs);
inline Vector33 operator/(const float lhs, Vector33 rhs);
inline Vector33 operator+(Vector33 lhs, const Vector33 rhs);
inline Vector33 operator-(Vector33 lhs, const Vector33 rhs);
inline bool operator==(const Vector33 lhs, const Vector33 rhs);
inline bool operator!=(const Vector33 lhs, const Vector33 rhs);



/*******************************************************************************
 * Implementation
 */

Vector33::Vector33() : X(0), Y(0), Z(0) {}
Vector33::Vector33(float data[]) : X(data[0]), Y(data[1]), Z(data[2]) {}
Vector33::Vector33(float value) : X(value), Y(value), Z(value) {}
Vector33::Vector33(float x, float y) : X(x), Y(y), Z(0) {}
Vector33::Vector33(float x, float y, float z) : X(x), Y(y), Z(z) {}


Vector33 Vector33::Zero() { return Vector33(0, 0, 0); }
Vector33 Vector33::One() { return Vector33(1, 1, 1); }
Vector33 Vector33::Right() { return Vector33(1, 0, 0); }
Vector33 Vector33::Left() { return Vector33(-1, 0, 0); }
Vector33 Vector33::Up() { return Vector33(0, 1, 0); }
Vector33 Vector33::Down() { return Vector33(0, -1, 0); }
Vector33 Vector33::Forward() { return Vector33(0, 0, 1); }
Vector33 Vector33::Backward() { return Vector33(0, 0, -1); }


float Vector33::Angle(Vector33 a, Vector33 b)
{
    float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

Vector33 Vector33::ClampMagnitude(Vector33 vector, float maxLength)
{
    float length = Magnitude(vector);
    if (length > maxLength)
        vector *= maxLength / length;
    return vector;
}

float Vector33::Component(Vector33 a, Vector33 b)
{
    return Dot(a, b) / Magnitude(b);
}

Vector33 Vector33::Cross(Vector33 lhs, Vector33 rhs)
{
    float x = lhs.Y * rhs.Z - lhs.Z * rhs.Y;
    float y = lhs.Z * rhs.X - lhs.X * rhs.Z;
    float z = lhs.X * rhs.Y - lhs.Y * rhs.X;
    return Vector33(x, y, z);
}

float Vector33::Distance(Vector33 a, Vector33 b)
{
    return Vector33::Magnitude(a - b);
}

float Vector33::Dot(Vector33 lhs, Vector33 rhs)
{
    return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
}

Vector33 Vector33::FromSpherical(float rad, float theta, float phi)
{
    Vector33 v;
    v.X = rad * sin(theta) * cos(phi);
    v.Y = rad * sin(theta) * sin(phi);
    v.Z = rad * cos(theta);
    return v;
}

Vector33 Vector33::Lerp(Vector33 a, Vector33 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

Vector33 Vector33::LerpUnclamped(Vector33 a, Vector33 b, float t)
{
    return (b - a) * t + a;
}

float Vector33::Magnitude(Vector33 v)
{
    return sqrt(SqrMagnitude(v));
}

Vector33 Vector33::Max(Vector33 a, Vector33 b)
{
    float x = a.X > b.X ? a.X : b.X;
    float y = a.Y > b.Y ? a.Y : b.Y;
    float z = a.Z > b.Z ? a.Z : b.Z;
    return Vector33(x, y, z);
}

Vector33 Vector33::Min(Vector33 a, Vector33 b)
{
    float x = a.X > b.X ? b.X : a.X;
    float y = a.Y > b.Y ? b.Y : a.Y;
    float z = a.Z > b.Z ? b.Z : a.Z;
    return Vector33(x, y, z);
}

Vector33 Vector33::MoveTowards(Vector33 current, Vector33 target,
                             float maxDistanceDelta)
{
    Vector33 d = target - current;
    float m = Magnitude(d);
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

Vector33 Vector33::Normalized(Vector33 v)
{
    float mag = Magnitude(v);
    if (mag == 0)
        return Vector33::Zero();
    return v / mag;
}

Vector33 Vector33::Orthogonal(Vector33 v)
{
    return v.Z < v.X ? Vector33(v.Y, -v.X, 0) : Vector33(0, -v.Z, v.Y);
}

void Vector33::OrthoNormalize(Vector33 &normal, Vector33 &tangent,
                             Vector33 &binormal)
{
    normal = Normalized(normal);
    tangent = ProjectOnPlane(tangent, normal);
    tangent = Normalized(tangent);
    binormal = ProjectOnPlane(binormal, tangent);
    binormal = ProjectOnPlane(binormal, normal);
    binormal = Normalized(binormal);
}

Vector33 Vector33::Project(Vector33 a, Vector33 b)
{
    float m = Magnitude(b);
    return Dot(a, b) / (m * m) * b;
}

Vector33 Vector33::ProjectOnPlane(Vector33 vector, Vector33 planeNormal)
{
    return Reject(vector, planeNormal);
}

Vector33 Vector33::Reflect(Vector33 vector, Vector33 planeNormal)
{
    return vector - 2 * Project(vector, planeNormal);
}

Vector33 Vector33::Reject(Vector33 a, Vector33 b)
{
    return a - Project(a, b);
}

Vector33 Vector33::RotateTowards(Vector33 current, Vector33 target,
                               float maxRadiansDelta,
                               float maxMagnitudeDelta)
{
    float magCur = Magnitude(current);
    float magTar = Magnitude(target);
    float newMag = magCur + maxMagnitudeDelta *
                            ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));

    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0)
        return Normalized(target) * newMag;
    else if (totalAngle >= M_PI)
        return Normalized(-target) * newMag;

    Vector33 axis = Cross(current, target);
    float magAxis = Magnitude(axis);
    if (magAxis == 0)
        axis = Normalized(Cross(current, current + Vector33(3.95, 5.32, -4.24)));
    else
        axis /= magAxis;
    current = Normalized(current);
    Vector33 newVector = current * cos(maxRadiansDelta) +
                        Cross(axis, current) * sin(maxRadiansDelta);
    return newVector * newMag;
}

Vector33 Vector33::Scale(Vector33 a, Vector33 b)
{
    return Vector33(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
}

Vector33 Vector33::Slerp(Vector33 a, Vector33 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

Vector33 Vector33::SlerpUnclamped(Vector33 a, Vector33 b, float t)
{
    float magA = Magnitude(a);
    float magB = Magnitude(b);
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    Vector33 relativeVec = Normalized(b - a * dot);
    Vector33 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

float Vector33::SqrMagnitude(Vector33 v)
{
    return v.X * v.X + v.Y * v.Y + v.Z * v.Z;
}

void Vector33::ToSpherical(Vector33 vector, float &rad, float &theta,
                          float &phi)
{
    rad = Magnitude(vector);
    float v = vector.Z / rad;
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    theta = acos(v);
    phi = atan2(vector.Y, vector.X);
}


struct Vector33& Vector33::operator+=(const float rhs)
{
    X += rhs;
    Y += rhs;
    Z += rhs;
    return *this;
}

struct Vector33& Vector33::operator-=(const float rhs)
{
    X -= rhs;
    Y -= rhs;
    Z -= rhs;
    return *this;
}

struct Vector33& Vector33::operator*=(const float rhs)
{
    X *= rhs;
    Y *= rhs;
    Z *= rhs;
    return *this;
}

struct Vector33& Vector33::operator/=(const float rhs)
{
    X /= rhs;
    Y /= rhs;
    Z /= rhs;
    return *this;
}

struct Vector33& Vector33::operator+=(const Vector33 rhs)
{
    X += rhs.X;
    Y += rhs.Y;
    Z += rhs.Z;
    return *this;
}

struct Vector33& Vector33::operator-=(const Vector33 rhs)
{
    X -= rhs.X;
    Y -= rhs.Y;
    Z -= rhs.Z;
    return *this;
}

char Vector33::ToChar(Vector33 a) {
    const char* x = (const char*)(int)a.X;
    const char* y = (const char*)(int)a.Y;
    const char* z = (const char*)(int)a.Z;
    char buffer[25];
    strncpy(buffer, x, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, y, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, z, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    return buffer[24];
}

Vector33 operator-(Vector33 rhs) { return rhs * -1; }
Vector33 operator+(Vector33 lhs, const float rhs) { return lhs += rhs; }
Vector33 operator-(Vector33 lhs, const float rhs) { return lhs -= rhs; }
Vector33 operator*(Vector33 lhs, const float rhs) { return lhs *= rhs; }
Vector33 operator/(Vector33 lhs, const float rhs) { return lhs /= rhs; }
Vector33 operator+(const float lhs, Vector33 rhs) { return rhs += lhs; }
Vector33 operator-(const float lhs, Vector33 rhs) { return rhs -= lhs; }
Vector33 operator*(const float lhs, Vector33 rhs) { return rhs *= lhs; }
Vector33 operator/(const float lhs, Vector33 rhs) { return rhs /= lhs; }
Vector33 operator+(Vector33 lhs, const Vector33 rhs) { return lhs += rhs; }
Vector33 operator-(Vector33 lhs, const Vector33 rhs) { return lhs -= rhs; }

bool operator==(const Vector33 lhs, const Vector33 rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
}

bool operator!=(const Vector33 lhs, const Vector33 rhs)
{
    return !(lhs == rhs);
}

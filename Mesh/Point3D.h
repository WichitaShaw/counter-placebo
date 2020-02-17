#pragma once

namespace Math_NS
{
  class Point3D
  {
  private:
    double x;
    double y;
    double z;

  public:
    Point3D() = default;
    Point3D(const double i_x, const double i_y, const double i_z);

    // equals
    bool operator==(const Point3D& rhs) const;

    // addition
    Point3D operator+(const Point3D& rhs) const;

    // subtraction
    Point3D operator-(const Point3D& rhs) const;

    // scaling
    Point3D operator*(const double rhs) const;
    friend Point3D operator*(const double lhs, const Point3D& rhs);

    // dot product
    double operator*(const Point3D& rhs) const;

    // cross product
    Point3D operator^(const Point3D& rhs) const;

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    void setX(const double i_x) { x = i_x; }
    void setY(const double i_y) { y = i_y; }
    void setZ(const double i_z) { z = i_z; }

    double getLengthSqr() const;
    double getLength() const;
    Point3D getUnitVector() const;
    void makeUnitVector();

    static Point3D zero();
    static Point3D one();

  };

}
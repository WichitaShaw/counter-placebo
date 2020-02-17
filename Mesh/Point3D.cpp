#include "Point3D.h"

#include <cmath>
#include <limits>

namespace Math_NS
{
  
  Point3D::Point3D(const double i_x, 
                   const double i_y,
                   const double i_z)
    : x(i_x), y(i_y), z(i_z) {}

  bool Point3D::operator==(const Point3D& rhs) const
  {
    auto eps = std::numeric_limits<double>::epsilon();
    return (x - rhs.getX()) < eps
      && (y - rhs.getY()) < eps
      && (z - rhs.getZ()) < eps;
  }

  Point3D Point3D::operator*(const double rhs) const
  {
    return Point3D(x * rhs, y * rhs, z * rhs);
  }
  Point3D operator*(const double lhs, const Point3D& rhs)
  {
    return rhs * lhs;
  }

  Point3D Point3D::operator+(const Point3D& rhs) const
  {
    return Point3D(x + rhs.getX(), y + rhs.getY(), z + rhs.getZ());
  }

  Point3D Point3D::operator-(const Point3D& rhs) const
  {
    return *this + -1 * rhs;
  }

  double Point3D::operator*(const Point3D& rhs) const
  {
    return x * rhs.getX() + y * rhs.getY() + z * rhs.getZ();
  }

  Point3D Point3D::operator^(const Point3D& rhs) const
  {
    const auto& rx = rhs.getX();
    const auto& ry = rhs.getY();
    const auto& rz = rhs.getZ();

    auto nx = y * rz - z * ry;
    auto ny = z * rx - x * rz;
    auto nz = x * ry - y * rx;

    return Point3D(nx, ny, nz);
  }

  double Point3D::getLengthSqr() const
  {
    return x*x + y*y + z*z;
  }

  double Point3D::getLength() const
  {
    return sqrt(getLengthSqr());
  }

  // will return 0 vector if vector length is 0
  Point3D Point3D::getUnitVector() const
  {
    const double len = getLength();
    if (len < std::numeric_limits<double>::min())
      return Point3D::zero();
    return Point3D(x / len, y / len, z / len);
  }

  void Point3D::makeUnitVector()
  {
    *this = getUnitVector();
  }


  Point3D Point3D::zero()
  {
    return Point3D(0, 0, 0);
  }

  Point3D Point3D::one()
  {
    return Point3D(1, 1, 1);
  }
}
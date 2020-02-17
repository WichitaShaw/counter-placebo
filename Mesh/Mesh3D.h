#pragma once

#include "Point3D.h"
#include "VoxelArray.h"

#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

namespace Mesh_NS
{

  // hash function for Math_NS::Point3D
  struct hashP3D
  {
    auto operator()(const Math_NS::Point3D& p) const
    {
      return std::hash<double>()(p.getX()) ^ std::hash<double>()(p.getY()) ^ std::hash<double>()(p.getZ());
    }
  };


  using PointSet = std::unordered_set<Math_NS::Point3D, hashP3D>;
  struct Triangle
  {
    Math_NS::Point3D vertices[3];
    Math_NS::Point3D norm;
  };

  
  // 
  class Mesh3D
  {
    std::vector<Triangle> triangles;
    PointSet points;

  private:
    void addPointToMesh(const Math_NS::Point3D& i_p);

  public:
    Mesh3D() = default;
    Mesh3D(const Voxel_NS::VoxelArray<bool>& voxelArray, const double voxelSize);

    void addTriangle(const Triangle& i_tri);
    void addTriangle(const Math_NS::Point3D& i_a, 
                     const Math_NS::Point3D& i_b,
                     const Math_NS::Point3D& i_c,
                     const Math_NS::Point3D& i_n);

    // returns true if point is in points array
    // bool pointInMesh(const Math_NS::Point3D& i_p) const;

    // returns std::vector of Point3D in mesh
    std::vector<Math_NS::Point3D> getVecOfVerts() const;

    // saves as ASCII STL
    bool saveAsASCIISTL(const std::string& i_fileName) const;

    // saves as binary STL
    bool saveAsSTL(const std::string& i_fileName) const;
  };


  static const Math_NS::Point3D VertexPointTable[8] = 
  {
    Math_NS::Point3D(0, 0, 0),
    Math_NS::Point3D(1, 0, 0),
    Math_NS::Point3D(1, 1, 0),
    Math_NS::Point3D(0, 1, 0),
    Math_NS::Point3D(0, 0, 1),
    Math_NS::Point3D(1, 0, 1),
    Math_NS::Point3D(1, 1, 1),
    Math_NS::Point3D(0, 1, 1)
  };

  static const Math_NS::Point3D EdgePointTable[12] =
  {
    Math_NS::Point3D(0.5, 0, 0),
    Math_NS::Point3D(1, 0, 0.5),
    Math_NS::Point3D(0.5, 0, 1),
    Math_NS::Point3D(0, 0, 0.5),
    Math_NS::Point3D(0.5, 1, 0),
    Math_NS::Point3D(1, 1, 0.5),
    Math_NS::Point3D(0.5, 1, 1),
    Math_NS::Point3D(0, 1, 0.5),
    Math_NS::Point3D(0, 0.5, 0),
    Math_NS::Point3D(1, 0.5, 0),
    Math_NS::Point3D(0, 0.5, 1),
    Math_NS::Point3D(1, 0.5, 1)
  };

}
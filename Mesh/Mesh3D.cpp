#include "Mesh3D.h"

#include "MarchingCubes.h"

#include <assert.h>
#include <fstream>
#include <iostream>

namespace Mesh_NS
{

  void Mesh3D::addPointToMesh(const Math_NS::Point3D& i_p)
  {
    points.insert(i_p);
  }


  Mesh3D::Mesh3D(const Voxel_NS::VoxelArray<bool>& voxelArray, const double voxelSize)
  {
    const auto arraySize = voxelArray.getSize();

    Math_NS::Point3D currentOrigin(0, 0, 0);

    for (auto z = 0; z != arraySize - 1; ++z)
    {
      currentOrigin.setY(0);
      for (auto y = 0; y != arraySize - 1; ++y)
      {
        currentOrigin.setX(0);
        for (auto x = 0; x != arraySize - 1; ++x)
        {
          VertexIndex c = { 0 };
          c.b += (voxelArray.get(x, y, z) ? V(0) : 0);
          c.b += (voxelArray.get(x + 1, y, z) ? V(1) : 0);
          c.b += (voxelArray.get(x + 1, y + 1, z) ? V(2) : 0);
          c.b += (voxelArray.get(x, y + 1, z) ? V(3) : 0);
          c.b += (voxelArray.get(x, y, z + 1) ? V(4) : 0);
          c.b += (voxelArray.get(x + 1, y, z + 1) ? V(5) : 0);
          c.b += (voxelArray.get(x + 1, y + 1, z + 1) ? V(6) : 0);
          c.b += (voxelArray.get(x, y + 1, z + 1) ? V(7) : 0);


          auto findEdgePoint = [&currentOrigin, c](const int i_edge)
          {
            auto firstVert = edgeVertMap.at(i_edge).first;
            auto secondVert = edgeVertMap.at(i_edge).second;
            
            auto point = 0.5 * (VertexPointTable[firstVert] + VertexPointTable[secondVert]) + currentOrigin;
            auto gradient = VertexPointTable[firstVert] - VertexPointTable[secondVert];

            auto pointAway = VOUT((c.b & V(firstVert)), firstVert) ? -1 : 1;
            gradient = gradient * pointAway;

            return std::make_pair(point, gradient);
          };
          
          auto edgeIndex = edgeFromVertex(c);

          int tableIndex = 0;
          for (auto i = 0; i!=256; ++i)
          {
            if (aCases[i] ==  edgeIndex.b)
            {
              tableIndex = i; 
              break;
            }
          }

          auto* topology = triTable[tableIndex];
          for (auto i = 0; i != 16; i+=3 )
          {
            if (topology[i] == -1 || topology[i + 1] == -1 || topology[i + 2] == -1)
              break;
            auto a = findEdgePoint(topology[i]);
            auto b = findEdgePoint(topology[i+1]);
            auto c = findEdgePoint(topology[i+2]);
            auto n = (a.second + b.second + c.second).getUnitVector();
            addTriangle(a.first, b.first, c.first, n);
          }

          currentOrigin = currentOrigin + Math_NS::Point3D(voxelSize, 0, 0);
        }
        currentOrigin = currentOrigin + Math_NS::Point3D(0, voxelSize, 0);
      }
      currentOrigin = currentOrigin + Math_NS::Point3D(0, 0, voxelSize);
    }

  }


  void Mesh3D::addTriangle(const Triangle& i_tri)
  {
    auto* currentVertex = i_tri.vertices;
    for (auto i = 0; i != 3; ++i)
      points.insert(*(currentVertex + i));
    triangles.push_back(i_tri);
  }


  void Mesh3D::addTriangle(const Math_NS::Point3D& i_a,
                           const Math_NS::Point3D& i_b,
                           const Math_NS::Point3D& i_c,
                           const Math_NS::Point3D& i_n)
  {
    // vertices stored counterclockwise
    bool rightorder = ((i_b - i_a) ^ (i_c - i_b)) * i_n > 0;

    Triangle tri;
    tri.vertices[0] = i_a;
    tri.vertices[1] = rightorder ? i_b : i_c;
    tri.vertices[2] = rightorder ? i_c : i_b;
    tri.norm = i_n;
    addTriangle(tri);
  }


  std::vector<Math_NS::Point3D> Mesh3D::getVecOfVerts() const
  {
    std::vector<Math_NS::Point3D> result;
    for (auto pSetItr = points.begin(); pSetItr != points.end(); ++pSetItr)
      result.emplace_back(*pSetItr);
    return result;
  }


  bool Mesh3D::saveAsASCIISTL(const std::string& i_fileName) const
  {
    std::ofstream result;
    result.open(i_fileName);
    if (result.is_open())
    {
      result << "solid test" << '\n';
      for (auto i = 0; i != triangles.size(); ++i)
      {
        auto ct = triangles[i];
        result << '\t' << "facet normal " << ct.norm.getX() << " " << ct.norm.getY() << " "
          << ct.norm.getZ() << '\n';
        result << '\t' << '\t' << "outer loop" << '\n';
        result << '\t' << '\t' << '\t' << "vertex " << ct.vertices[0].getX() << " "
          << ct.vertices[0].getY() << " " << ct.vertices[0].getZ() << '\n';
        result << '\t' << '\t' << '\t' << "vertex " << ct.vertices[1].getX() << " "
          << ct.vertices[1].getY() << " " << ct.vertices[1].getZ() << '\n';
        result << '\t' << '\t' << '\t' << "vertex " << ct.vertices[2].getX() << " "
          << ct.vertices[2].getY() << " " << ct.vertices[2].getZ() << '\n';
        result << '\t' << '\t' << "endloop" << '\n';
        result << '\t' << "endfacet" << '\n';
      }
      result << "endsolid";
      result.close();
      return true;
    }
    return false;
  }


  bool Mesh3D::saveAsSTL(const std::string& i_fileName) const
  {
    std::ofstream result;
    result.open(i_fileName.c_str(), std::ios::out | std::ios::binary);
    if (result.is_open())
    {
      // header uint8[80]
      char header[80] = "";
      result.write(header, 80);

      // number of triangles uint32
      uint32_t numTriangles = triangles.size();
      result.write((char*)&numTriangles, 4);
      
      // triangle data real32[3] x4, uint16
      for (auto i = 0; i != triangles.size(); ++i)
      {
        auto streamPoint3DAsFloat = [](const Math_NS::Point3D& i_pt, std::ofstream& io_os) 
        {
          float xf = i_pt.getX();
          io_os.write((char*)&xf, sizeof(float));

          float yf = i_pt.getY();
          io_os.write((char*)&yf, sizeof(float));

          float zf = i_pt.getZ();
          io_os.write((char*)&zf, sizeof(float));
        };

        streamPoint3DAsFloat(triangles[i].norm, result);
        for (auto v = 0; v != 3; ++v)
          streamPoint3DAsFloat(triangles[i].vertices[v], result);
        uint16_t attr = 0;
        result.write((char*)&attr, 2);
      }

      result.close();
      return true;
    }
    return false;
  }

}
#include "VoxelArray.h"

#include <exception>

using namespace std;

namespace Voxel_NS
{
  // Voxel<bool> member definitions

  std::ostream& operator<<(std::ostream& os, const Voxel<bool>& vx)
  {
    os << vx.value ? 1 : 0;
    return os;
  }


  ///////////////////////////////////////////////////////////

  // VoxelArray<bool> member definitions

  VoxelArray<bool>::VoxelArray(const int i_sz) : size(i_sz)
  {
    if (size < 0 || size > 200)
      throw out_of_range("invalid voxel array size: must be 0-200");

    vector<Voxel<bool>> row(size, 0);
    vector<vector<Voxel<bool>>> slice(size, row);
    vector<vector<vector<Voxel<bool>>>> volume(size, slice);
    data.clear();
    data.swap(volume);
  }


  void VoxelArray<bool>::printCoronalSlice(const int i_x) const
  {
    for (auto xySlice : data)
    {
      for (auto xArray : xySlice)
        std::cout << xArray[i_x] << ' ';
      std::cout << '\n';
    }
  }


  void VoxelArray<bool>::printSagittalSlice(const int i_y) const
  {
    for (auto xySlice : data)
    {
      for (auto xValue : xySlice[i_y])
        std::cout << xValue << ' ';
      std::cout << '\n';
    }
  }


  void VoxelArray<bool>::printAxialSlice(const int i_z) const
  {
    for (auto xySlice : data[i_z])
    {
      for (auto xValue : xySlice)
        std::cout << xValue << ' ';
      std::cout << '\n';
    }
  }

}
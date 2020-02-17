#pragma once

#include <iostream>
#include <vector>

// 3-bit unsigned integer for voxel array data type
//struct int8bit
//{
//  unsigned int w : 3;
//};

///////////////////////////////////////////

namespace Voxel_NS
{
  // plain wrapper for data type
  // could be expanded to include more information
  template <class T>
  struct Voxel
  {
    T value;

    Voxel() {}
    Voxel(const T i_val) : value(i_val)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Voxel& vx);
  };


  template <class T>
  class VoxelArray
  {
    const int size;
    std::vector<std::vector<std::vector<Voxel<T>>>> data;
  
  public:
    VoxelArray(const int i_sz);

    int getSize() const
    {
      return size;
    }

    // set voxel value
    // throws out_of_range error if i_x, i_y, or i_z > size
    void set(const int i_x, const int i_y, const int i_z, const T i_val)
    {
      data[i_z][i_y][i_x].value = i_val;
    }

    // retrieve voxel value
    // throws out_of_range error if i_x, i_y, or i_z > size
    T get(const int i_x, const int i_y, const int i_z) const
    {
      return data[i_z][i_y][i_x].value;
    }

    // YZ-slice viewer
    void printCoronalSlice(const int i_x) const;

    // XZ-slice viewer
    void printSagittalSlice(const int i_y) const;

    // XY-slice viewer
    void printAxialSlice(const int i_z) const;
  };

}
#include "ground_segmentation/bin.h"

#include <limits>

Bin::Bin() : min_z(std::numeric_limits<double>::max()), has_point_(false) {}

Bin::Bin(const Bin &bin) : min_z(std::numeric_limits<double>::max()),
                           has_point_(false) {}

// note that d isn't stored in class, we only store min of d
void Bin::addPoint(const pcl::PointXYZ &point)
{
  const double d = sqrt(point.x * point.x + point.y * point.y);
  addPoint(d, point.z);
}

/*添加点*/
void Bin::addPoint(const double &d, const double &z)
{
  has_point_ = true;
  if (z < min_z)
  {
    min_z       = z;
    min_z_range = d;
  }
}

/*判断是否有点，如果有点存在的话，将我们之前算好的min_z和min_z_range传入到point之中*/
Bin::MinZPoint Bin::getMinZPoint()
{
  MinZPoint point;

  if (has_point_)
  {
    point.z = min_z;
    point.d = min_z_range;
  }

  return point;
}

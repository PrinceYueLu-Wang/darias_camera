// Generated by gencpp from file darias_intelcamera/maplist.msg
// DO NOT EDIT!


#ifndef DARIAS_INTELCAMERA_MESSAGE_MAPLIST_H
#define DARIAS_INTELCAMERA_MESSAGE_MAPLIST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace darias_intelcamera
{
template <class ContainerAllocator>
struct maplist_
{
  typedef maplist_<ContainerAllocator> Type;

  maplist_()
    : center_x()
    , center_y()
    , center_z()
    , sphere_radius(0.0)
    , cube_number(0)  {
    }
  maplist_(const ContainerAllocator& _alloc)
    : center_x(_alloc)
    , center_y(_alloc)
    , center_z(_alloc)
    , sphere_radius(0.0)
    , cube_number(0)  {
  (void)_alloc;
    }



   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _center_x_type;
  _center_x_type center_x;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _center_y_type;
  _center_y_type center_y;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _center_z_type;
  _center_z_type center_z;

   typedef double _sphere_radius_type;
  _sphere_radius_type sphere_radius;

   typedef int64_t _cube_number_type;
  _cube_number_type cube_number;





  typedef boost::shared_ptr< ::darias_intelcamera::maplist_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::darias_intelcamera::maplist_<ContainerAllocator> const> ConstPtr;

}; // struct maplist_

typedef ::darias_intelcamera::maplist_<std::allocator<void> > maplist;

typedef boost::shared_ptr< ::darias_intelcamera::maplist > maplistPtr;
typedef boost::shared_ptr< ::darias_intelcamera::maplist const> maplistConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::darias_intelcamera::maplist_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::darias_intelcamera::maplist_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::darias_intelcamera::maplist_<ContainerAllocator1> & lhs, const ::darias_intelcamera::maplist_<ContainerAllocator2> & rhs)
{
  return lhs.center_x == rhs.center_x &&
    lhs.center_y == rhs.center_y &&
    lhs.center_z == rhs.center_z &&
    lhs.sphere_radius == rhs.sphere_radius &&
    lhs.cube_number == rhs.cube_number;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::darias_intelcamera::maplist_<ContainerAllocator1> & lhs, const ::darias_intelcamera::maplist_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace darias_intelcamera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::darias_intelcamera::maplist_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::darias_intelcamera::maplist_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::darias_intelcamera::maplist_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::darias_intelcamera::maplist_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::darias_intelcamera::maplist_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::darias_intelcamera::maplist_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::darias_intelcamera::maplist_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a13af0fc5407b2a8448e9cb9d1e85a83";
  }

  static const char* value(const ::darias_intelcamera::maplist_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa13af0fc5407b2a8ULL;
  static const uint64_t static_value2 = 0x448e9cb9d1e85a83ULL;
};

template<class ContainerAllocator>
struct DataType< ::darias_intelcamera::maplist_<ContainerAllocator> >
{
  static const char* value()
  {
    return "darias_intelcamera/maplist";
  }

  static const char* value(const ::darias_intelcamera::maplist_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::darias_intelcamera::maplist_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64[] center_x\n"
"float64[] center_y\n"
"float64[] center_z\n"
"\n"
"float64 sphere_radius\n"
"\n"
"int64 cube_number\n"
"\n"
"\n"
;
  }

  static const char* value(const ::darias_intelcamera::maplist_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::darias_intelcamera::maplist_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.center_x);
      stream.next(m.center_y);
      stream.next(m.center_z);
      stream.next(m.sphere_radius);
      stream.next(m.cube_number);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct maplist_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::darias_intelcamera::maplist_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::darias_intelcamera::maplist_<ContainerAllocator>& v)
  {
    s << indent << "center_x[]" << std::endl;
    for (size_t i = 0; i < v.center_x.size(); ++i)
    {
      s << indent << "  center_x[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.center_x[i]);
    }
    s << indent << "center_y[]" << std::endl;
    for (size_t i = 0; i < v.center_y.size(); ++i)
    {
      s << indent << "  center_y[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.center_y[i]);
    }
    s << indent << "center_z[]" << std::endl;
    for (size_t i = 0; i < v.center_z.size(); ++i)
    {
      s << indent << "  center_z[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.center_z[i]);
    }
    s << indent << "sphere_radius: ";
    Printer<double>::stream(s, indent + "  ", v.sphere_radius);
    s << indent << "cube_number: ";
    Printer<int64_t>::stream(s, indent + "  ", v.cube_number);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DARIAS_INTELCAMERA_MESSAGE_MAPLIST_H

// Generated by gencpp from file darias_intelcamera/joystick.msg
// DO NOT EDIT!


#ifndef DARIAS_INTELCAMERA_MESSAGE_JOYSTICK_H
#define DARIAS_INTELCAMERA_MESSAGE_JOYSTICK_H


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
struct joystick_
{
  typedef joystick_<ContainerAllocator> Type;

  joystick_()
    : rh_axisX(0.0)
    , rh_axisY(0.0)
    , lh_axisX(0.0)
    , lh_axisY(0.0)
    , button_up(0.0)
    , button_down(0.0)
    , button_left(0.0)
    , button_right(0.0)
    , button_axisZ(0.0)  {
    }
  joystick_(const ContainerAllocator& _alloc)
    : rh_axisX(0.0)
    , rh_axisY(0.0)
    , lh_axisX(0.0)
    , lh_axisY(0.0)
    , button_up(0.0)
    , button_down(0.0)
    , button_left(0.0)
    , button_right(0.0)
    , button_axisZ(0.0)  {
  (void)_alloc;
    }



   typedef double _rh_axisX_type;
  _rh_axisX_type rh_axisX;

   typedef double _rh_axisY_type;
  _rh_axisY_type rh_axisY;

   typedef double _lh_axisX_type;
  _lh_axisX_type lh_axisX;

   typedef double _lh_axisY_type;
  _lh_axisY_type lh_axisY;

   typedef double _button_up_type;
  _button_up_type button_up;

   typedef double _button_down_type;
  _button_down_type button_down;

   typedef double _button_left_type;
  _button_left_type button_left;

   typedef double _button_right_type;
  _button_right_type button_right;

   typedef double _button_axisZ_type;
  _button_axisZ_type button_axisZ;





  typedef boost::shared_ptr< ::darias_intelcamera::joystick_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::darias_intelcamera::joystick_<ContainerAllocator> const> ConstPtr;

}; // struct joystick_

typedef ::darias_intelcamera::joystick_<std::allocator<void> > joystick;

typedef boost::shared_ptr< ::darias_intelcamera::joystick > joystickPtr;
typedef boost::shared_ptr< ::darias_intelcamera::joystick const> joystickConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::darias_intelcamera::joystick_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::darias_intelcamera::joystick_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::darias_intelcamera::joystick_<ContainerAllocator1> & lhs, const ::darias_intelcamera::joystick_<ContainerAllocator2> & rhs)
{
  return lhs.rh_axisX == rhs.rh_axisX &&
    lhs.rh_axisY == rhs.rh_axisY &&
    lhs.lh_axisX == rhs.lh_axisX &&
    lhs.lh_axisY == rhs.lh_axisY &&
    lhs.button_up == rhs.button_up &&
    lhs.button_down == rhs.button_down &&
    lhs.button_left == rhs.button_left &&
    lhs.button_right == rhs.button_right &&
    lhs.button_axisZ == rhs.button_axisZ;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::darias_intelcamera::joystick_<ContainerAllocator1> & lhs, const ::darias_intelcamera::joystick_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace darias_intelcamera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::darias_intelcamera::joystick_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::darias_intelcamera::joystick_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::darias_intelcamera::joystick_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::darias_intelcamera::joystick_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::darias_intelcamera::joystick_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::darias_intelcamera::joystick_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::darias_intelcamera::joystick_<ContainerAllocator> >
{
  static const char* value()
  {
    return "38359861987deff7a4f782a03f0a4d54";
  }

  static const char* value(const ::darias_intelcamera::joystick_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x38359861987deff7ULL;
  static const uint64_t static_value2 = 0xa4f782a03f0a4d54ULL;
};

template<class ContainerAllocator>
struct DataType< ::darias_intelcamera::joystick_<ContainerAllocator> >
{
  static const char* value()
  {
    return "darias_intelcamera/joystick";
  }

  static const char* value(const ::darias_intelcamera::joystick_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::darias_intelcamera::joystick_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 rh_axisX\n"
"float64 rh_axisY\n"
"\n"
"float64 lh_axisX\n"
"float64 lh_axisY\n"
"\n"
"float64 button_up\n"
"float64 button_down\n"
"\n"
"float64 button_left\n"
"float64 button_right\n"
"\n"
"float64 button_axisZ\n"
;
  }

  static const char* value(const ::darias_intelcamera::joystick_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::darias_intelcamera::joystick_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.rh_axisX);
      stream.next(m.rh_axisY);
      stream.next(m.lh_axisX);
      stream.next(m.lh_axisY);
      stream.next(m.button_up);
      stream.next(m.button_down);
      stream.next(m.button_left);
      stream.next(m.button_right);
      stream.next(m.button_axisZ);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct joystick_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::darias_intelcamera::joystick_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::darias_intelcamera::joystick_<ContainerAllocator>& v)
  {
    s << indent << "rh_axisX: ";
    Printer<double>::stream(s, indent + "  ", v.rh_axisX);
    s << indent << "rh_axisY: ";
    Printer<double>::stream(s, indent + "  ", v.rh_axisY);
    s << indent << "lh_axisX: ";
    Printer<double>::stream(s, indent + "  ", v.lh_axisX);
    s << indent << "lh_axisY: ";
    Printer<double>::stream(s, indent + "  ", v.lh_axisY);
    s << indent << "button_up: ";
    Printer<double>::stream(s, indent + "  ", v.button_up);
    s << indent << "button_down: ";
    Printer<double>::stream(s, indent + "  ", v.button_down);
    s << indent << "button_left: ";
    Printer<double>::stream(s, indent + "  ", v.button_left);
    s << indent << "button_right: ";
    Printer<double>::stream(s, indent + "  ", v.button_right);
    s << indent << "button_axisZ: ";
    Printer<double>::stream(s, indent + "  ", v.button_axisZ);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DARIAS_INTELCAMERA_MESSAGE_JOYSTICK_H

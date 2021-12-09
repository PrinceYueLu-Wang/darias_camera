# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from darias_intelcamera/maplist.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class maplist(genpy.Message):
  _md5sum = "a13af0fc5407b2a8448e9cb9d1e85a83"
  _type = "darias_intelcamera/maplist"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """float64[] center_x
float64[] center_y
float64[] center_z

float64 sphere_radius

int64 cube_number


"""
  __slots__ = ['center_x','center_y','center_z','sphere_radius','cube_number']
  _slot_types = ['float64[]','float64[]','float64[]','float64','int64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       center_x,center_y,center_z,sphere_radius,cube_number

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(maplist, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.center_x is None:
        self.center_x = []
      if self.center_y is None:
        self.center_y = []
      if self.center_z is None:
        self.center_z = []
      if self.sphere_radius is None:
        self.sphere_radius = 0.
      if self.cube_number is None:
        self.cube_number = 0
    else:
      self.center_x = []
      self.center_y = []
      self.center_z = []
      self.sphere_radius = 0.
      self.cube_number = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      length = len(self.center_x)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.Struct(pattern).pack(*self.center_x))
      length = len(self.center_y)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.Struct(pattern).pack(*self.center_y))
      length = len(self.center_z)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.Struct(pattern).pack(*self.center_z))
      _x = self
      buff.write(_get_struct_dq().pack(_x.sphere_radius, _x.cube_number))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.center_x = s.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.center_y = s.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.center_z = s.unpack(str[start:end])
      _x = self
      start = end
      end += 16
      (_x.sphere_radius, _x.cube_number,) = _get_struct_dq().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      length = len(self.center_x)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.center_x.tostring())
      length = len(self.center_y)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.center_y.tostring())
      length = len(self.center_z)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.center_z.tostring())
      _x = self
      buff.write(_get_struct_dq().pack(_x.sphere_radius, _x.cube_number))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.center_x = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.center_y = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.center_z = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      _x = self
      start = end
      end += 16
      (_x.sphere_radius, _x.cube_number,) = _get_struct_dq().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_dq = None
def _get_struct_dq():
    global _struct_dq
    if _struct_dq is None:
        _struct_dq = struct.Struct("<dq")
    return _struct_dq
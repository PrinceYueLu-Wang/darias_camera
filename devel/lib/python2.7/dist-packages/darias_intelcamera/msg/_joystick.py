# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from darias_intelcamera/joystick.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class joystick(genpy.Message):
  _md5sum = "38359861987deff7a4f782a03f0a4d54"
  _type = "darias_intelcamera/joystick"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """float64 rh_axisX
float64 rh_axisY

float64 lh_axisX
float64 lh_axisY

float64 button_up
float64 button_down

float64 button_left
float64 button_right

float64 button_axisZ"""
  __slots__ = ['rh_axisX','rh_axisY','lh_axisX','lh_axisY','button_up','button_down','button_left','button_right','button_axisZ']
  _slot_types = ['float64','float64','float64','float64','float64','float64','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       rh_axisX,rh_axisY,lh_axisX,lh_axisY,button_up,button_down,button_left,button_right,button_axisZ

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(joystick, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.rh_axisX is None:
        self.rh_axisX = 0.
      if self.rh_axisY is None:
        self.rh_axisY = 0.
      if self.lh_axisX is None:
        self.lh_axisX = 0.
      if self.lh_axisY is None:
        self.lh_axisY = 0.
      if self.button_up is None:
        self.button_up = 0.
      if self.button_down is None:
        self.button_down = 0.
      if self.button_left is None:
        self.button_left = 0.
      if self.button_right is None:
        self.button_right = 0.
      if self.button_axisZ is None:
        self.button_axisZ = 0.
    else:
      self.rh_axisX = 0.
      self.rh_axisY = 0.
      self.lh_axisX = 0.
      self.lh_axisY = 0.
      self.button_up = 0.
      self.button_down = 0.
      self.button_left = 0.
      self.button_right = 0.
      self.button_axisZ = 0.

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
      _x = self
      buff.write(_get_struct_9d().pack(_x.rh_axisX, _x.rh_axisY, _x.lh_axisX, _x.lh_axisY, _x.button_up, _x.button_down, _x.button_left, _x.button_right, _x.button_axisZ))
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
      _x = self
      start = end
      end += 72
      (_x.rh_axisX, _x.rh_axisY, _x.lh_axisX, _x.lh_axisY, _x.button_up, _x.button_down, _x.button_left, _x.button_right, _x.button_axisZ,) = _get_struct_9d().unpack(str[start:end])
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
      _x = self
      buff.write(_get_struct_9d().pack(_x.rh_axisX, _x.rh_axisY, _x.lh_axisX, _x.lh_axisY, _x.button_up, _x.button_down, _x.button_left, _x.button_right, _x.button_axisZ))
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
      _x = self
      start = end
      end += 72
      (_x.rh_axisX, _x.rh_axisY, _x.lh_axisX, _x.lh_axisY, _x.button_up, _x.button_down, _x.button_left, _x.button_right, _x.button_axisZ,) = _get_struct_9d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_9d = None
def _get_struct_9d():
    global _struct_9d
    if _struct_9d is None:
        _struct_9d = struct.Struct("<9d")
    return _struct_9d

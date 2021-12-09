// Auto-generated. Do not edit!

// (in-package darias_intelcamera.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class maplist {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.center_x = null;
      this.center_y = null;
      this.center_z = null;
      this.sphere_radius = null;
      this.cube_number = null;
    }
    else {
      if (initObj.hasOwnProperty('center_x')) {
        this.center_x = initObj.center_x
      }
      else {
        this.center_x = [];
      }
      if (initObj.hasOwnProperty('center_y')) {
        this.center_y = initObj.center_y
      }
      else {
        this.center_y = [];
      }
      if (initObj.hasOwnProperty('center_z')) {
        this.center_z = initObj.center_z
      }
      else {
        this.center_z = [];
      }
      if (initObj.hasOwnProperty('sphere_radius')) {
        this.sphere_radius = initObj.sphere_radius
      }
      else {
        this.sphere_radius = 0.0;
      }
      if (initObj.hasOwnProperty('cube_number')) {
        this.cube_number = initObj.cube_number
      }
      else {
        this.cube_number = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type maplist
    // Serialize message field [center_x]
    bufferOffset = _arraySerializer.float64(obj.center_x, buffer, bufferOffset, null);
    // Serialize message field [center_y]
    bufferOffset = _arraySerializer.float64(obj.center_y, buffer, bufferOffset, null);
    // Serialize message field [center_z]
    bufferOffset = _arraySerializer.float64(obj.center_z, buffer, bufferOffset, null);
    // Serialize message field [sphere_radius]
    bufferOffset = _serializer.float64(obj.sphere_radius, buffer, bufferOffset);
    // Serialize message field [cube_number]
    bufferOffset = _serializer.int64(obj.cube_number, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type maplist
    let len;
    let data = new maplist(null);
    // Deserialize message field [center_x]
    data.center_x = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [center_y]
    data.center_y = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [center_z]
    data.center_z = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [sphere_radius]
    data.sphere_radius = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [cube_number]
    data.cube_number = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.center_x.length;
    length += 8 * object.center_y.length;
    length += 8 * object.center_z.length;
    return length + 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'darias_intelcamera/maplist';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a13af0fc5407b2a8448e9cb9d1e85a83';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64[] center_x
    float64[] center_y
    float64[] center_z
    
    float64 sphere_radius
    
    int64 cube_number
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new maplist(null);
    if (msg.center_x !== undefined) {
      resolved.center_x = msg.center_x;
    }
    else {
      resolved.center_x = []
    }

    if (msg.center_y !== undefined) {
      resolved.center_y = msg.center_y;
    }
    else {
      resolved.center_y = []
    }

    if (msg.center_z !== undefined) {
      resolved.center_z = msg.center_z;
    }
    else {
      resolved.center_z = []
    }

    if (msg.sphere_radius !== undefined) {
      resolved.sphere_radius = msg.sphere_radius;
    }
    else {
      resolved.sphere_radius = 0.0
    }

    if (msg.cube_number !== undefined) {
      resolved.cube_number = msg.cube_number;
    }
    else {
      resolved.cube_number = 0
    }

    return resolved;
    }
};

module.exports = maplist;

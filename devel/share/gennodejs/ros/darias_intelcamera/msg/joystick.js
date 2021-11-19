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

class joystick {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.rh_axisX = null;
      this.rh_axisY = null;
      this.lh_axisX = null;
      this.lh_axisY = null;
      this.button_up = null;
      this.button_down = null;
      this.button_left = null;
      this.button_right = null;
    }
    else {
      if (initObj.hasOwnProperty('rh_axisX')) {
        this.rh_axisX = initObj.rh_axisX
      }
      else {
        this.rh_axisX = 0.0;
      }
      if (initObj.hasOwnProperty('rh_axisY')) {
        this.rh_axisY = initObj.rh_axisY
      }
      else {
        this.rh_axisY = 0.0;
      }
      if (initObj.hasOwnProperty('lh_axisX')) {
        this.lh_axisX = initObj.lh_axisX
      }
      else {
        this.lh_axisX = 0.0;
      }
      if (initObj.hasOwnProperty('lh_axisY')) {
        this.lh_axisY = initObj.lh_axisY
      }
      else {
        this.lh_axisY = 0.0;
      }
      if (initObj.hasOwnProperty('button_up')) {
        this.button_up = initObj.button_up
      }
      else {
        this.button_up = 0.0;
      }
      if (initObj.hasOwnProperty('button_down')) {
        this.button_down = initObj.button_down
      }
      else {
        this.button_down = 0.0;
      }
      if (initObj.hasOwnProperty('button_left')) {
        this.button_left = initObj.button_left
      }
      else {
        this.button_left = 0.0;
      }
      if (initObj.hasOwnProperty('button_right')) {
        this.button_right = initObj.button_right
      }
      else {
        this.button_right = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type joystick
    // Serialize message field [rh_axisX]
    bufferOffset = _serializer.float64(obj.rh_axisX, buffer, bufferOffset);
    // Serialize message field [rh_axisY]
    bufferOffset = _serializer.float64(obj.rh_axisY, buffer, bufferOffset);
    // Serialize message field [lh_axisX]
    bufferOffset = _serializer.float64(obj.lh_axisX, buffer, bufferOffset);
    // Serialize message field [lh_axisY]
    bufferOffset = _serializer.float64(obj.lh_axisY, buffer, bufferOffset);
    // Serialize message field [button_up]
    bufferOffset = _serializer.float64(obj.button_up, buffer, bufferOffset);
    // Serialize message field [button_down]
    bufferOffset = _serializer.float64(obj.button_down, buffer, bufferOffset);
    // Serialize message field [button_left]
    bufferOffset = _serializer.float64(obj.button_left, buffer, bufferOffset);
    // Serialize message field [button_right]
    bufferOffset = _serializer.float64(obj.button_right, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type joystick
    let len;
    let data = new joystick(null);
    // Deserialize message field [rh_axisX]
    data.rh_axisX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rh_axisY]
    data.rh_axisY = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [lh_axisX]
    data.lh_axisX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [lh_axisY]
    data.lh_axisY = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [button_up]
    data.button_up = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [button_down]
    data.button_down = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [button_left]
    data.button_left = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [button_right]
    data.button_right = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 64;
  }

  static datatype() {
    // Returns string type for a message object
    return 'darias_intelcamera/joystick';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '71f51f585b7d21a17e5851f8e46a743b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 rh_axisX
    float64 rh_axisY
    
    float64 lh_axisX
    float64 lh_axisY
    
    float64 button_up
    float64 button_down
    
    float64 button_left
    float64 button_right
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new joystick(null);
    if (msg.rh_axisX !== undefined) {
      resolved.rh_axisX = msg.rh_axisX;
    }
    else {
      resolved.rh_axisX = 0.0
    }

    if (msg.rh_axisY !== undefined) {
      resolved.rh_axisY = msg.rh_axisY;
    }
    else {
      resolved.rh_axisY = 0.0
    }

    if (msg.lh_axisX !== undefined) {
      resolved.lh_axisX = msg.lh_axisX;
    }
    else {
      resolved.lh_axisX = 0.0
    }

    if (msg.lh_axisY !== undefined) {
      resolved.lh_axisY = msg.lh_axisY;
    }
    else {
      resolved.lh_axisY = 0.0
    }

    if (msg.button_up !== undefined) {
      resolved.button_up = msg.button_up;
    }
    else {
      resolved.button_up = 0.0
    }

    if (msg.button_down !== undefined) {
      resolved.button_down = msg.button_down;
    }
    else {
      resolved.button_down = 0.0
    }

    if (msg.button_left !== undefined) {
      resolved.button_left = msg.button_left;
    }
    else {
      resolved.button_left = 0.0
    }

    if (msg.button_right !== undefined) {
      resolved.button_right = msg.button_right;
    }
    else {
      resolved.button_right = 0.0
    }

    return resolved;
    }
};

module.exports = joystick;

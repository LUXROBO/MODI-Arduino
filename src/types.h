/*
    Type.h

    Author : Luxrobo Arduino Team
    Edited : Tuna (Tuna@luxrobo.com)
*/

#ifndef MODI_TYPES_H_
#define MODI_TYPES_H_

#include <Arduino.h>
#include <inttypes.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef int Direction;
enum
{
    DIRECTION_UNKNOWN = -1,
    DIRECTION_RIGHT,
    DIRECTION_TOP, 
    DIRECTION_LEFT,
    DIRECTION_BOTTOM,
    DIRECTION_WIRLESS_OFFSET,
};

typedef uint16_t ModuleKey;
typedef uint16_t ModuleVersion;
typedef uint16_t ModuleType;

enum
{
    MODULE_TYPE_NETWORK     = 0x0000,
    MODULE_TYPE_INPUT       = 0x2000,
    MODULE_TYPE_OUTPUT      = 0x4000,

    MODULE_USB              = (0x00) | MODULE_TYPE_NETWORK,
    MODULE_ESP              = (0x10) | MODULE_TYPE_NETWORK,
    //MODULE_ARDUINO          = (0x20) | MODULE_TYPE_NETWORK, // To Be Defined
    MODULE_ENVIORNMENT      = (0x00) | MODULE_TYPE_INPUT,
    MODULE_GYRO             = (0x10) | MODULE_TYPE_INPUT,
    MODULE_MIC              = (0x20) | MODULE_TYPE_INPUT,
    MODULE_BUTTON           = (0x30) | MODULE_TYPE_INPUT,
    MODULE_DIAL             = (0x40) | MODULE_TYPE_INPUT,
    MODULE_ULTRASONIC       = (0x50) | MODULE_TYPE_INPUT,
    MODULE_IR               = (0x60) | MODULE_TYPE_INPUT,
    MODULE_DISPLAY          = (0x10) | MODULE_TYPE_OUTPUT,
    MODULE_MOTOR            = (0x20) | MODULE_TYPE_OUTPUT,
    MODULE_LED              = (0x30) | MODULE_TYPE_OUTPUT,
    MODULE_SPEAKER          = (0x40) | MODULE_TYPE_OUTPUT,
};

template <typename T=void>
bool isValidKey(ModuleKey key)
{
    return !(key & 0xF000);
}

enum
{
    // FIRST                   = 0x00,
    CMD_HEALTH              = 0x00,
    CMD_ECHO                = 0x01,
    CMD_MODULE_INFO         = 0x02,
    CMD_REQUEST_PP          = 0x03,
    CMD_SET_PP              = 0x04,
    CMD_ASSIGN_ID           = 0x05,
    CMD_ASSIGN_ACTION       = 0x06,
    CMD_TOPOLOGY            = 0x07,
    CMD_FIND_ID             = 0x08,
    CMD_SET_STATE           = 0x09,
    CMD_WARNING             = 0x0A,
    CMD_FIRMWARE_DATA       = 0x0B,
    CMD_FIRMWARE_STATE      = 0x0C,
    CMD_FIRMWARE_COMMAND    = 0x0D,
    CMD_SAVE                = 0x0E,
    CMD_STREAM_DATA         = 0x10,
    CMD_STREAM_STATE        = 0x11,
    CMD_STREAM_COMMAND      = 0x12,
    CMD_MONITOR             = 0x13,
    CMD_BATTERY             = 0x14,
    CMD_VARIABLE            = 0x1C,
    CMD_SYNC                = 0x1D,
    CMD_EVENT               = 0x1E,
    CMD_CHANNEL             = 0x1F,
    CMD_EXT_REMODED         = 0x20,
    // LAST                    = 0xFF,
}modi_cmd_type_t;

enum
{
    DATA_F64                = 0x00,
    DATA_F32                = 0x01,
    DATA_F32_F32            = 0x02,
    DATA_U64                = 0x03,
    DATA_I64                = 0x04,
    DATA_U32                = 0x05,
    DATA_U32_U32            = 0x06,
    DATA_I32                = 0x07,
    DATA_I32_I32            = 0x08,
    DATA_U16                = 0x09,
    DATA_U16_U16            = 0x0A,
    DATA_U16_U16_U16        = 0x0B,
    DATA_U16_U16_U16_U16    = 0x0C,
    DATA_I16                = 0x0C,
    DATA_I16_I16            = 0x0D,
    DATA_I16_I16_I16        = 0x0E,
    DATA_I16_I16_I16_I16    = 0x0F,
}modi_data_type_t;

typedef struct
{
    uint64_t value[20];
}modi_property_t;

struct Frame
{
    uint16_t cmd;
    uint16_t sid;
    uint16_t did;
    uint16_t len;
    uint8_t  data[8];
};


class Message
{
public:
    Message(){}
    Message(const Frame& frame): m_frame(frame){}
    Message(int cmd, int sid, int did, const uint8_t* data, int len)
    {
        m_frame.cmd = (uint16_t)cmd;
        m_frame.sid = (uint16_t)sid;
        m_frame.did = (uint16_t)did;
        m_frame.len = (uint16_t)len;
        memset (m_frame.data, 0, sizeof(m_frame.data));
        for (int i = 0; i < len; i ++)
            m_frame.data[i] = data[i];
    }

public:
    uint16_t        cmd()     { return m_frame.cmd; }
    uint16_t        sid()     { return m_frame.sid; }
    uint16_t        did()     { return m_frame.did; }
    uint16_t        len()     { return m_frame.len; }
    uint8_t*       data()     { return m_frame.data;}

private:
    Frame m_frame;
};

typedef int32_t AppMode;

enum
{
    APP_MODE_NONE   = -1,
    APP_MODE_PNP    = 2,
    APP_MODE_USER   = 3,
};


typedef union
{
    uint8_t     u8[4];
    uint16_t    u16[2];
    uint32_t    u32;
    int8_t      i8[4];
    int16_t     i16[2];
    int32_t     i32;
    float       f32;
}size32_val_t;

typedef union
{
    uint8_t     u8[8];
    uint16_t    u16[4];
    uint32_t    u32[2];
    uint64_t    u64;
    int8_t      i8[8];
    int16_t     i16[4];
    int32_t     i32[2];
    int64_t     i64;

    float       f32[2];
    double      f64;
}size64_val_t;

#endif // MODI_TYPES_H_

/* End of File */

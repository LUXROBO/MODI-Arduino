/*
    MODI.h

    Author : Luxrobo Arduino Team
    Edtied : Tuna (Tuna@luxrobo.com)

*/

#ifndef MODI_H_
#define MODI_H_

#include <Arduino.h>
#include <inttypes.h>

#include "mcp_can.h"

#include "MODI_Interface.h"
#include "MODI_property.h"
#include "types.h"

/* change to 1 if you want to print information */
#define MODI_DEBUG_MODE 1

/* */
#define MODI_MAX_MODULE_NUM 2

/* Pin out for Arduino MKR Series */
#if defined(ARDUINO_ARCH_SAMD)
    #define MODI_INT_PIN    7
    #define MODI_CS_PIN     3
    #define MODI_DIR_PIN    2
#endif

/* Pin out for Arduino UNO  */
 #if defined(ARDUINO_ARCH_AVR)
    #define MODI_INT_PIN    2
    #define MODI_CS_PIN     10
    #define MODI_DIR_PIN    3
 #endif

#if MODI_DEBUG_MODE
    #if defined(ARDUINO_ARCH_AVR)
        #define MODI_PRINT(X,...)       Serial.print(X,##__VA_ARGS__)
        #define MODI_PRINTLN(X,...)     Serial.println(X,##__VA_ARGS__)
        #define MODI_PRINT_F(X,...)     Serial.print(F(X),##__VA_ARGS__)
    #elif defined(ARDUINO_ARCH_SAMD)
        #define MODI_PRINT(X,...)       Serial.print(X,##__VA_ARGS__)
        #define MODI_PRINTLN(X,...)     Serial.println(X,##__VA_ARGS__)
        #define MODI_PRINT_F(X,...)     Serial.print(X,##__VA_ARGS__)
    #endif
#else
    #define MODI_PRINT(...) 
    #define MODI_PRINTLN(...)
    #define MODI_PRINT_F(...)
#endif

class Module
{
    private:
    uint64_t m_uuid;
    AppMode m_app_mode;

    public:
    Module();
    Module(const uint64_t& uuid);

    uint32_t        uuid(void)      const;
    ModuleKey       key(void)       const;
    ModuleType      type(void)      const;
    AppMode         mode(void)      const;
    ModuleVersion   version(void)   const;
    
    void            writeUUID(uint32_t uuid);
    void            writeID(uint16_t ID);
    
    void begin(void);
};

class MODI_Manager
{
public : 
    void findModule(void);
    bool updateModule(uint16_t ID);
    bool setModulePnP(uint16_t module_id, uint8_t state);
    uint16_t findModuleIndex(uint16_t ID);
    void updatePropterty(uint16_t module_id, uint8_t pNum, uint8_t data[]);
    typedef enum
    {
        MODI_CAN     = 0x00,
        MODI_SERIAL  = 0x01,
        MODI_WIFI    = 0x02,
        MODI_BLE     = 0x03
    }MODI_Connect_Apapter_t;

public : 
    MODI_Manager();
    void begin(void);
    void begin(MODI_Connect_Apapter_t adapter);

    modi_property_t property[MODI_MAX_MODULE_NUM];
private :
    
    uint16_t moduleID[MODI_MAX_MODULE_NUM];
    uint16_t modulecnt;
    
};

/* 0. Network Module */
class Network :public Module, public PropertySender
{
    private:
    
    public:
    Network();
    Network(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);
    
    void addRequest(uint8_t property);

    void writeState(uint8_t state);

    uint32_t readData(void);
    uint32_t readEvent(void);
    uint32_t readSlider_Left(void);
    uint32_t readSlider_Right(void);
    uint32_t readDialTurn(void);
    uint32_t readTimeout(void);

    void writeData(int32_t data);
    void writeEvent(int32_t data);
    void writeCamera(int32_t data);
};

/* 1. Environment Module */

class Environment : public Module,public PropertySender
{
    private:

    public:
    Environment();
    Environment(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);
    
    void writeState(uint8_t state);

    float readIlluminance(void);
    float readRed(void);
    float readGreen(void);
    float readBlue(void);
    float readTemperature(void);
    float readHumidity(void);
};

/* 2. Gyro Module */
class Gyro : public Module, public PropertySender
{
    private:
    public:
    Gyro();
    Gyro (const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);
    
    void writeState(uint8_t state);

    float readRoll(void);
    float readPitch(void);
    float readYaw(void);
    float readGyro_X(void);
    float readGyro_Y(void);
    float readGyro_Z(void);
    float readAccel_X(void);
    float readAccel_Y(void);
    float readAccel_Z(void);
    float readVibration(void);
};


/* 3. Mic Module */
class Mic :public Module, public PropertySender
{
    private:
    public:
    Mic();
    Mic(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);
    
    void writeState(uint8_t state);

    float readVolume(void);
    float readFreq(void);

};

/* 4. Button Module */
class Button :public Module, public PropertySender
{
    private:
    public:
    Button();
    Button(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);
    
    void writeState(uint8_t state);
    
    float readClick(void);
    float readDoubleClick(void);
    float readPushState(void);
    float readToggle(void);
    void writeToggle(int16_t value);
};


/* 5. Dial Module */
class Dial :public Module, public PropertySender
{
    private:
    public:
    Dial();
    Dial(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);
    
    void writeState(uint8_t state);

    float readDegree(void);
    float readTurnSpeed(void);
};

/* 6. Ultrasonic Module */
class Ultrasonic :public Module, public PropertySender
{
    private:
    public:
    Ultrasonic();  
    Ultrasonic(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);

    void writeState(uint8_t state);

    float readDistance(void);
};


/* 7. Infrared Module */
class Ir :public Module, public PropertySender
{
    private:
    public:
    Ir();
    Ir(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);
    
    void writeState(uint8_t state);

    float readProximity(void);
    float readIntensity(void);
    float readRemote(void);
};


/* 8. Display Module */
class Display :public Module, public PropertySender
{
    private:
    uint16_t usingVarPropertyNum;
    public: 
    Display();
    Display(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);
    
    void writeState(uint8_t state);

    void writePosition(int16_t X, int16_t Y);
    void writeText(char text[]);
    void writeDots(char dots[]);
    void writePicture(char keyword[]);
    void resetDisplay(void);
    void writeVariable(int16_t X, int16_t Y, float var);
    void writeHorizontal(int16_t val);
    void writeVertical(int16_t val);

};

/* 9. Motor Module */
class Motor :public Module, public PropertySender
{
    private:
    public:
    Motor();
    Motor(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);
    
    void writeState(uint8_t state);
    
    float readTorque_Upper(void);
    float readTorque_Bottom(void);
    float readSpeed_Upper(void);
    float readSpeed_Bottom(void);
    float readAngle_Upper(void);
    float readAngle_Bottom(void);
    float readSenseSpeed_Upper(void);
    float readSenseSpeed_Bottom(void);
    float readSenseAngle_Upper(void);
    float readSenseAngle_Bottom(void);

    void writeTorque_Upper(float torque);
    void writeTorque_Bottom(float torque);
    void writeSpeed_Upper(float speed);
    void writeSpeed_Bottom(float speed);
    void writeAngle_Upper(float angle);
    void writeAngle_Bottom(float angle);

    void writeTorque(int16_t UpperTorque, int16_t BottomTorque);
    void writeSpeed(int16_t UpperSpeed, int16_t BottomSpeed);
    void writeAngle(int16_t UpperSpeed, int16_t BottomSpeed);

};

/* 10. LED Module */
class LED :public Module, public PropertySender
{
    private:
    public:
    LED();
    LED(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);
    
    void writeState(uint8_t state);

    float readRed(void);
    float readGreen(void);
    float readBlue(void);

    void writeRed(float R);
    void writeGreen(float G);
    void writeBlue(float B);

    void writeRGB(int16_t R, int16_t G, int16_t B);
};


/* 11. Speaker Module */
class Speaker :public Module, public PropertySender
{
    private:
    public:
    Speaker();
    Speaker(const uint64_t& assign_data);

    uint8_t begin(void);
    uint8_t begin(uint16_t uuid);

    void addRequest(uint8_t property);
    
    void writeState(uint8_t state);

    float readVolume(void);
    float readFreq(void);

    void writeVolume(float volume);
    void writeFreq(float m_freq);
    void writeTune(float freq, float volume);
    void writeSoundEffect(float sound, float volume);
    void writeMelody(float melody, float volume);
};


namespace modi
{
    extern MCP_CAN CAN;
}
extern MODI_Manager MODI;

#endif // MODI_H_

/* End of File */

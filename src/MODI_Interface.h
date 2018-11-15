/*
    MODI_Interface.h

    Author : Luxrobo Arduino Team
    Edited : Tuna (Tuna@luxrobo.com)
*/

#ifndef MODI_INTERFACE_H_
#define MODI_INTERFACE_H_

#include <Arduino.h>
#include <inttypes.h>

#include "types.h"

class PropertySender
{
private:
public:
    uint32_t getTxID(uint16_t destID, uint16_t pNum, uint16_t datatype, uint16_t cmd_Property);
    
    void requestPropterty(uint16_t destID,uint8_t pNum, uint16_t period); 

    void setState(uint16_t destID,uint8_t state);

    void setProperty64(uint16_t destID, uint16_t pNum, uint64_t value);
    void setProperty(uint16_t destID, uint16_t pNum, float value);
    void setProperty(uint16_t destID, uint16_t pNum, uint8_t value[]);
    void setPropertyString(uint16_t destID, uint16_t pNum, char * value);
    void setPropertyFunction(uint16_t destID, uint16_t pNum, uint64_t value);
    void setDisplay48(uint16_t destID, uint16_t pNum, char * value);
    int32_t getPropertyInt(uint16_t destID, uint16_t pNum);
    float getProperty(uint16_t destID, uint16_t pNum);
protected:
    typedef int PropertyNum;
protected:
    int32_t displayDrawAddress;
};

#endif // MODI_INTERFACE_H

/* End of File */

/*
    MODI_Interface.c

    Author : Luxrobo Arduino Team
    Edited : Tuna (Tuna@luxrobo.com)
*/

#include "MODI_Interface.h"
#include "MODI.h"

/* * * * * Part of PropertySender * * * * */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint32_t PropertySender::getTxID(uint16_t destID, uint16_t pNum, uint16_t datatype, uint16_t cmd_Property)
{
    uint32_t txID = (cmd_Property & 0x1F);
             txID = (txID << 4) | datatype;
             txID = (txID << 8) | pNum;
             txID = (txID << 12)| destID;
    return txID;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void PropertySender::requestPropterty(uint16_t destID,uint8_t pNum, uint16_t period)
{
    uint32_t txID = (CMD_REQUEST_PP & 0x1F);
             txID = (txID << 24) | destID ;
    uint8_t val[8] = {0,};
            val[0] = pNum;
            val[2] = period;

    modi::CAN.sendMsgBuf(txID,1,8,val);  // (ID, extended flag, data length, data)

    return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void PropertySender::setState(uint16_t destID,uint8_t state)
{
    uint32_t txID = (CMD_SET_STATE & 0x1F);
             txID = (txID << 24) | destID;
    
    uint8_t module_state = state;

    modi::CAN.sendMsgBuf(txID,1,1,&module_state);
    return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void PropertySender::setProperty64(uint16_t destID, uint16_t pNum, uint64_t value)
{
    uint8_t data[8] = {0,};
    data[0] = ((value >> 0) & 0xFF);
    data[1] = ((value >> 8) & 0xFF);
    data[2] = ((value >> 16) & 0xFF);
    data[3] = ((value >> 24) & 0xFF);
    data[4] = ((value >> 32) & 0xFF);
    data[5] = ((value >> 40) & 0xFF);
    data[6] = ((value >> 48) & 0xFF);
    data[7] = ((value >> 56) & 0xFF);
	uint32_t txID = getTxID(destID,pNum,DATA_F64,CMD_SET_PP);

    modi::CAN.sendMsgBuf(txID, 1, 8, data);//(ID, extended flag, data length, data)

    return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void PropertySender::setProperty(uint16_t destID, uint16_t pNum, float value)
{
    size32_val_t data;
    data.f32 = value;
    uint32_t txID = getTxID(destID,pNum,DATA_F32,CMD_SET_PP);

    modi::CAN.sendMsgBuf(txID, 1, 8, data.u8);//(ID, extended flag, data length, data)
    return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void PropertySender::setProperty(uint16_t destID, uint16_t pNum, uint8_t* value)
{

    uint32_t txID = getTxID(destID,pNum,DATA_I16_I16,CMD_SET_PP);

    modi::CAN.sendMsgBuf(txID, 1, 8, value);//(ID, extended flag, data length, data)
    return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void PropertySender::setPropertyString(uint16_t destID, uint16_t pNum, char * value)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void PropertySender::setPropertyFunction(uint16_t destID, uint16_t pNum, uint64_t value)
{

}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void PropertySender::setDisplay48(uint16_t destID, uint16_t pNum, char value[])
{
    uint8_t display_1line[8] = {0,};
    for(int i = 0; i < 48; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            display_1line[j] = value[j + (i*8)];
        }
        setProperty64(destID,pNum,display_1line);
        delay(1);
    }
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
int32_t PropertySender::getPropertyInt(uint16_t destID, uint16_t pNum)
{
    uint16_t index = MODI.findModuleIndex(destID);
    size64_val_t value;
    value.u64 = MODI.property[index].value[pNum];
    return value.i32[0];
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float PropertySender::getProperty(uint16_t destID, uint16_t pNum)
{
    uint16_t index = MODI.findModuleIndex(destID);
    size64_val_t value;
    value.u64 = MODI.property[index].value[pNum];
    return value.f32[0];
}

/* End of File */
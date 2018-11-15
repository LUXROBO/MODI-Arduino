/*
    MODI.c	

    Author : Luxrobo Arduino Team
    Edited : Tuna (Tuna@luxrobo.com)
*/

#include "MODI.h"


static void MODI_Message_Handler(void);			// CAN Message Handler

MODI_Manager MODI;

namespace modi
{
    MCP_CAN CAN(MODI_CS_PIN);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
MODI_Manager::MODI_Manager()
{
	modulecnt = 0;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void MODI_Manager::begin(void)
{
    /* CAN INIT */

    modi::CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ);
    modi::CAN.setMode(MCP_NORMAL);
    /* Set SPI INT EXTI */
    pinMode(MODI_INT_PIN,INPUT_PULLUP);
	
	attachInterrupt(digitalPinToInterrupt(MODI_INT_PIN),MODI_Message_Handler,LOW);

	randomSeed(random(0,0xFFFF));
	/* find module */
	MODI.findModule();
	/* PnP off */
	for(uint16_t cnt = 0; cnt < MODI.modulecnt; cnt++)
	{
		setModulePnP(MODI.moduleID[cnt],MODULE_PNP_OFF);
	}
	/* Set Direction pin as input */
	pinMode(MODI_DIR_PIN,INPUT);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void MODI_Manager::begin(MODI_Connect_Apapter_t adapter)
{

	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void MODI_Manager::findModule(void)
{
	Frame pkt;
	pkt.cmd	= CMD_FIND_ID;
	pkt.sid = 0x000;
	pkt.did = 0xFFF;
	pkt.len = 0x07;
	pkt.data[0] = 0xFF;
	pkt.data[1] = 0x0F;
	pkt.data[2] = 0x00;
	pkt.data[3] = 0x00;
	pkt.data[4] = 0x00;
	pkt.data[5] = 0x00;
	pkt.data[6] = 0x00;
	pkt.data[7] = 0x00;

	uint32_t txID = pkt.cmd;
			 txID = (txID << 12) | pkt.sid;
			 txID = (txID << 12) | pkt.did;

	modi::CAN.sendMsgBuf(txID,1,pkt.len,pkt.data);	

	return;
}

/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
bool MODI_Manager::updateModule(uint16_t ID)
{
	uint16_t cnt = 0;

	/* search connected module */
	for(cnt = 0; cnt < modulecnt; cnt++)
	{
		/* already conencted module */
		if(moduleID[cnt] == ID)
		{
			break;
		}
	}
	/* add connected module */
	moduleID[modulecnt] = ID;
	modulecnt = modulecnt + 0x01;

	/* turn off PnP */
	setModulePnP(moduleID[cnt],MODULE_PNP_OFF);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void MODI_Manager::updatePropterty(uint16_t module_id,uint8_t pNum, uint8_t data[])
{
	for(uint8_t cnt = 0; cnt < modulecnt; cnt++)
	{
		if(moduleID[cnt] == module_id)
		{
			property[cnt].value[pNum] = 0;
			size64_val_t value;

			for(uint8_t i = 0 ; i < 8 ; i++)
			{
				//property[cnt].value[pNum] = (property[cnt].value[pNum] << (8 * i)) | (uint64_t)data[i];
				value.u8[i] = data[i];
			}
			property[cnt].value[pNum] = value.u64;
		}
	}

	return;
}
uint16_t MODI_Manager::findModuleIndex(uint16_t ID)
{
	uint16_t index;
	for(uint8_t cnt = 0; cnt < modulecnt; cnt++)
	{
		if(moduleID[cnt] == ID)
		{
			index = cnt;
			return index;
		}
	}
	return -1;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
bool MODI_Manager::setModulePnP(uint16_t module_id, uint8_t state)
{
	/* 
		How to control pnp 
		----------------------------------
		1. Send property Set state
		2. Set length 2
		3. set byte[1] to 1 = turn on  pnp
		   set byte[1] to 0 = turn off pnp
	*/

	uint32_t txID = (CMD_SET_STATE & 0x1F);
			 txID = (txID << 24) | module_id;
	uint8_t data[2] = {0,};
			data[0] = 0x00U; /* Run */	
	/* turn off PnP*/
	if(state = 0)
	{
		data[1] = 0x01U; /* turn off PNP */
    	modi::CAN.sendMsgBuf(txID,1,2,data);
		return true;
	}
	/* turn on PnP */
	else if(state = 1)
	{
		data[1] = 0x02U; /* turn on PNP */
    	modi::CAN.sendMsgBuf(txID,1,2,data);
		return true;
	}
	/* invaild value */
	else
	{
		return false;
	}
	return false;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Module::Module()
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Module::Module(const uint64_t& uuid) : m_uuid(uuid)
{

}
/*
 *  @Func  :
 *  @Brief : 
 *  @Param :
 *  @RetVal:
 */ 
void Module::begin()
{

}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Module::writeUUID(uint32_t uuid)
{
	m_uuid = uuid;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Module::writeID(uint16_t ID)
{
	m_uuid = (m_uuid & 0xFFFFFFFFFFFFF000) | (ID & 0x0FFF);
	return;
}

namespace math 
{
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
    uint32_t getRandom(uint32_t min, uint32_t max)
    {
        int32_t dif = max - min, temp;
        if(dif < 0 ) return 0;

		return random(min,max+1);
    }
}

/* * * * * Part of Module * * * * */

/* 0. Network Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Network::Network(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Network::Network(const uint64_t& assign_data) : Module(assign_data)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Network::begin(void)
{
}

/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Network::begin(uint16_t ID)
{
    writeID(ID);
	MODI.updateModule(ID);
}

/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Network::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint32_t Network::readData(void)
{
    return getPropertyInt(key(),PROP_NETWORK_DATA);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint32_t Network::readEvent(void)
{
	return getPropertyInt(key(),PROP_NETWORK_EVENT);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Network::writeData(int32_t data)
{
	setProperty(key(), PROP_NETWORK_DATA, data);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Network::writeEvent(int32_t data)
{
	setProperty64(key(),PROP_NETWORK_EVENT,data);
	return;
}

/* 1. Environment Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Environment::Environment()
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Environment::Environment(const uint64_t& assign_data) : Module(assign_data)
{

}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Environment::begin(void)
{
    // idx = modulecnt++;
    // module[idx].uuid = modi::MODULE_ENVIORNMENT;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Environment::begin(uint16_t ID)
{
	writeID(ID);
	MODI.updateModule(ID);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Environment::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Environment::readIlluminance(void)
{
    return getProperty(key(),PROP_ENV_ILLUMINANCE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Environment::readRed(void)
{
    return getProperty(key(),PROP_ENV_RED);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Environment::readGreen(void)
{
    return getProperty(key(),PROP_ENV_GREEN);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Environment::readBlue(void)
{
    return getProperty(key(),PROP_ENV_BLUE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Environment::readTemperature(void)
{
    return getProperty(key(),PROP_ENV_TEMPERATURE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Environment::readHumidity(void)
{
    return getProperty(key(),PROP_ENV_HUMIDITY);
}

/* 2. Gyro Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Gyro::Gyro(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Gyro::Gyro(const uint64_t& assign_data) : Module(assign_data)
{
	
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Gyro::begin(void)
{
    // idx = modulecnt++;
    // module[idx].uuid = modi::MODULE_GYRO;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Gyro::begin(uint16_t ID)
{
    writeID(ID);
	MODI.updateModule(ID);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Gyro::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readRoll(void)
{
    return getProperty(key(), PROP_GYRO_ROLL);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readPitch(void)
{
    return getProperty(key(), PROP_GYRO_PITCH);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readYaw(void)
{
    return getProperty(key(), PROP_GYRO_YAW);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readGyro_X(void)
{
    return getProperty(key(), PROP_GYRO_GYRO_X);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readGyro_Y(void)
{   
    return getProperty(key(), PROP_GYRO_GYRO_Y);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readGyro_Z(void)
{
    return getProperty(key(), PROP_GYRO_GYRO_Z);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readAccel_X(void)
{
    return getProperty(key(), PROP_GYRO_ACCEL_X);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readAccel_Y(void)
{
    return getProperty(key(), PROP_GYRO_ACCEL_Y);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readAccel_Z(void)
{
    return getProperty(key(), PROP_GYRO_ACCEL_Z);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Gyro::readVibration(void)
{
    return getProperty(key(), PROP_GYRO_VIBRATION);
}

/* 3. Mic Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Mic::Mic(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Mic::Mic(const uint64_t& assign_data) : Module(assign_data)
{
	
}

/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Mic::begin(void)
{
    // idx = modulecnt++;
    // module[idx].uuid = modi::MODULE_MIC;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Mic::begin(uint16_t ID)
{
    writeID(ID);
	MODI.updateModule(ID);
}  
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Mic::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */ 
float Mic::readVolume(void)
{
    return getProperty(key(), PROP_MIC_VOLUME);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Mic::readFreq(void)
{
    return getProperty(key(), PROP_MIC_FREQUENCY);
}

/* 4. Button Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Button::Button(void)
{

}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Button::Button(const uint64_t& assign_data) : Module(assign_data)
{
	
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Button::begin(void)
{
    // idx = modulecnt++;
    // module[idx].uuid = modi::MODULE_BUTTON;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Button::begin(uint16_t ID)
{   
    writeID(ID);
	MODI.updateModule(ID);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Button::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Button::readClick(void)
{
    return getProperty(key(), PROP_BUTTON_CLICK);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Button::readDoubleClick(void)
{
    return getProperty(key(), PROP_BUTTON_DOUBLE_CLICK);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Button::readPushState(void)
{
    return getProperty(key(), PROP_BUTTON_PUSH_STATE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Button::readToggle(void)
{
    return getProperty(key(), PROP_BUTTON_TOGGLE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Button::writeToggle(int16_t value)
{
	return setProperty(key(),PROP_BUTTON_TOGGLE,(float)value);
}

/* 5. Dial Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Dial::Dial(void)
{

}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Dial::Dial(const uint64_t& assign_data) : Module(assign_data)
{
	
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Dial::begin(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Dial::begin(uint16_t ID)
{
    writeID(ID);
	MODI.updateModule(ID);
}

/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Dial::addRequest(uint8_t property)
{
    requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}

/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Dial::readDegree(void)
{
    return getProperty(key(), PROP_DIAL_TURN);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Dial::readTurnSpeed(void)
{
    return getProperty(key(), PROP_DIAL_TURN_SPEED);
}

/* 6. Ultrasonic Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Ultrasonic::Ultrasonic(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Ultrasonic::Ultrasonic(const uint64_t& assign_data) : Module(assign_data)
{

}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Ultrasonic::begin(void)
{
    // idx = modulecnt++;
    // module[idx].uuid = modi::MODULE_ULTRASONIC;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Ultrasonic::begin(uint16_t ID)
{
    writeID(ID);    
	MODI.updateModule(ID);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Ultrasonic::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Ultrasonic::readDistance(void)
{
	return getProperty(key(), PROP_ULTRASONIC_DISTANCE);
}

/* 7. Infrared Module */

/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Ir::Ir(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Ir::Ir(const uint64_t& assign_data) : Module(assign_data)
{
	
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Ir::begin(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Ir::begin(uint16_t ID)
{
    writeID(ID);
	MODI.updateModule(ID);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Ir::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Ir::readProximity(void)
{
	return getProperty(key(), PROP_IR_DISTANCE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Ir::readIntensity(void)
{
	return getProperty(key(), PROP_IR_INTENSITY);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Ir::readRemote(void)
{
	return getProperty(key(), PROP_IR_REMOTE);
}

/* 8. Display Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Display::Display(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Display::Display(const uint64_t& assign_data) : Module(assign_data)
{
	
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Display::begin(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Display::begin(uint16_t ID)
{
    writeID(ID);
	MODI.updateModule(ID);
	usingVarPropertyNum = 0;
}
void Display::writeState(uint8_t state)
{
	setState(key(),state);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Display::writePosition(int16_t X, int16_t Y)
{
	uint8_t data[8];
	data[0] = ((X >> 0x00FFU) >> 0);
	data[1] = ((X >> 0xFF00U) >> 8);
	data[2] = ((Y >> 0x00FFU) >> 0);
	data[3] = ((Y >> 0xFF00U) >> 8);
	setProperty64(key(),PROP_DISPLAY_RESET,data);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Display::writeText(char text[])
{
	setPropertyString(key(),PROP_DISPLAY_TEXT, text);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Display::writeDots(char dots[])
{	
	resetDisplay();
	delay(10);
	setDisplay48(key(),PROP_DISPLAY_DRAW_DATA, dots);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Display::writePicture(char keyword[])
{
	uint8_t value[8] = {0};
	for(uint8_t i = 0; i < 8; i++)
	{
		if(keyword[i] != 0)
		{
			value[i] = keyword[i];
		}
		else
		{
			break;
		}
	}
	setProperty64(key(),PROP_DISPLAY_DRAW_VARIABLE,value);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Display::resetDisplay(void)
{
	displayDrawAddress = 0;
	setProperty64(key(),PROP_DISPLAY_RESET,0);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Display::writeVariable(int16_t X, int16_t Y, float var)
{
	size64_val_t data;
	data.u16[0] = X;
	data.u16[1] = Y;
	data.f32[1] = var;

	setProperty64(key(),PROP_DISPLAY_VARIABLE(usingVarPropertyNum),data.u64);
	usingVarPropertyNum++;
	if(usingVarPropertyNum > 2)
	{
		usingVarPropertyNum = 0;
	}
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Display::writeHorizontal(int16_t val)
{
	uint8_t data[4] = {0};
	data[0] = ((val & 0x00FFU) >> 0);
	data[1] = ((val & 0xFF00U) >> 8);

	displayDrawAddress = 0;
	setProperty(key(),PROP_DISPLAY_HORIZONTAL,data);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Display::writeVertical(int16_t val)
{
	uint8_t data[4] = {0};
	data[0] = ((val & 0x00FFU) >> 0);
	data[1] = ((val & 0xFF00U) >> 8);
	displayDrawAddress = 0;
	setProperty(key(),PROP_DISPLAY_VERTICAL,data);
	return;
}

/* 9. Motor Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Motor::Motor(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Motor::Motor(const uint64_t& assign_data) : Module(assign_data)
{
	
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Motor::begin(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Motor::begin(uint16_t ID)
{
	writeID(ID);
	MODI.updateModule(ID);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readTorque_Upper(void)
{
	return getProperty(key(), PROP_MOTOR_UTORQUE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readTorque_Bottom(void)
{
	return getProperty(key(), PROP_MOTOR_BTORQUE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readSpeed_Upper(void)
{
	return getProperty(key(), PROP_MOTOR_USPEED);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readSpeed_Bottom(void)
{
	return getProperty(key(), PROP_MOTOR_BSPEED);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readAngle_Upper(void)
{
	return getProperty(key(), PROP_MOTOR_UANGLE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readAngle_Bottom(void)
{
	return getProperty(key(), PROP_MOTOR_BANGLE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readSenseSpeed_Upper(void)
{
	return getProperty(key(), PROP_MOTOR_USPEED_S);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readSenseSpeed_Bottom(void)
{
	return getProperty(key(), PROP_MOTOR_BSPEED_S);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readSenseAngle_Upper(void)
{
	return getProperty(key(), PROP_MOTOR_UANGLE_S);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Motor::readSenseAngle_Bottom(void)
{
	return getProperty(key(), PROP_MOTOR_BANGLE_S);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::writeTorque_Upper(float torque)
{
    setProperty(key(),PROP_MOTOR_UTORQUE,torque);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::writeTorque_Bottom(float torque)
{
    setProperty(key(),PROP_MOTOR_BTORQUE,torque);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::writeSpeed_Upper(float speed)
{
    setProperty(key(),PROP_MOTOR_USPEED,speed);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::writeSpeed_Bottom(float speed)
{
    setProperty(key(),PROP_MOTOR_BSPEED,speed);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::writeAngle_Upper(float angle)
{
    setProperty(key(),PROP_MOTOR_UANGLE,angle);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::writeAngle_Bottom(float angle)
{
    setProperty(key(),PROP_MOTOR_BANGLE,angle);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::writeTorque(int16_t UpperTorque, int16_t BottomTorque)
{
	uint8_t val[4] = {0,};
	val[0] = ((UpperTorque & 0x00FFU) >> 0);
	val[1] = ((UpperTorque & 0xFF00U) >> 8);
	val[2] = ((BottomTorque & 0x00FFU) >> 0);
	val[3] = ((BottomTorque & 0xFF00U) >> 8);
    setProperty(key(),PROP_MOTOR_TORQUE,val);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::writeSpeed(int16_t UpperSpeed, int16_t BottomSpeed)
{
	size64_val_t value;
	value.i16[0] = UpperSpeed;
	value.i16[1] = BottomSpeed;
	value.i16[2] = 0;
    
	setProperty64(key(),PROP_MOTOR_SPEED,value.u64);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Motor::writeAngle(int16_t UpperAngle, int16_t BottomAngle)
{
	uint8_t val[4] = {0,};
	val[0] = ((UpperAngle & 0x00FFU) >> 0);
	val[1] = ((UpperAngle & 0xFF00U) >> 8);
	val[2] = ((BottomAngle & 0x00FFU) >> 0);
	val[3] = ((BottomAngle & 0xFF00U) >> 8);
    setProperty(key(),PROP_MOTOR_ANGLE,val);
	return;
}

/* 10. LED Module */

/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
LED::LED(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
LED::LED(const uint64_t& assign_data) : Module(assign_data)
{
	
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t LED::begin(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t LED::begin(uint16_t ID)
{
	writeID(ID);
	MODI.updateModule(ID);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void LED::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float LED::readRed(void)
{
	return getProperty(key(), PROP_LED_RED);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float LED::readGreen(void)
{
	return getProperty(key(), PROP_LED_GREEN);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float LED::readBlue(void)
{
	return getProperty(key(), PROP_LED_BLUE);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void LED::writeRed(float R)
{
	setProperty(key(),PROP_LED_RED,R);
	return;
}

/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void LED::writeGreen(float G)
{
	setProperty(key(),PROP_LED_GREEN,G);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void LED::writeBlue(float B)
{
	setProperty(key(),PROP_LED_BLUE,B);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void LED::writeRGB(int16_t R, int16_t G, int16_t B)
{
	uint64_t RGB;
	RGB = B;
	RGB = (RGB << 16) | G;
	RGB = (RGB << 16) | R;
	
	setProperty64(key(),PROP_LED_RGB,RGB);
	return;
}

/* 11. Speaker Module */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Speaker::Speaker(void)
{
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
Speaker::Speaker(const uint64_t& assign_data) : Module(assign_data)
{
	
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Speaker::begin(void)
{
    // idx = modulecnt++;
    // module[idx].uuid = modi::MODULE_SPEAKER;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint8_t Speaker::begin(uint16_t ID)
{
	writeID(ID);
	MODI.updateModule(ID);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Speaker::addRequest(uint8_t property)
{
	requestPropterty(key(),property,0x60); // period : to be updated;
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Speaker::readVolume(void)
{
	return getProperty(key(), PROP_SPEAKER_VOLUME);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
float Speaker::readFreq(void)
{
	return getProperty(key(), PROP_SPEAKER_FREQUENCY);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Speaker::writeVolume(float volume)
{
	setProperty(key(),PROP_SPEAKER_VOLUME,volume);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Speaker::writeFreq(float freq)
{
	setProperty(key(),PROP_SPEAKER_FREQUENCY,freq);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Speaker::writeTune(float freq, float volume)
{
	size64_val_t val;
	val.f32[0] = freq;
	val.f32[1] = volume;
	setProperty64(key(),PROP_SPEAKER_TUNE,val.u64);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Speaker::writeSoundEffect(float sound, float volume)
{
	size64_val_t val;
	val.f32[0] = sound;
	val.f32[1] = volume;
	setProperty64(key(),PROP_SPEAKER_EFFECT,val.u64);
	return;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
void Speaker::writeMelody(float melody, float volume)
{
	size64_val_t val;
	val.f32[0] = melody;
	val.f32[1] = volume;
	setProperty64(key(),PROP_SPEAKER_MELODY,val.u64);
	return;
}

/* * * * * Part of Module * * * * */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
uint32_t Module::uuid(void) const
{
	return ((m_uuid & 0x00000000FFFFFFFF) >> 32);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
ModuleKey Module::key(void) const
{
	uint32_t key = (uint32_t)(m_uuid & 0x0000000000000FFF);
	return (ModuleKey)key;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
ModuleType Module::type(void) const
{
	return (ModuleType)((m_uuid & 0x0000FFFF00000000) >> 32);
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
AppMode Module::mode(void) const
{
	return m_app_mode;
}
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
ModuleVersion Module::version(void) const
{
	return (ModuleVersion)(m_uuid & 0xFFFF000000000000 >> 48);
}


/* * * * * Part of Interrupt * * * * */

/* CAN Interrupt */
/*
 *  @Func  :
 *  @Brief :
 *  @Param :
 *  @RetVal:
 */
static void MODI_Message_Handler(void)
{
    /* Read Message from CAN */
	
	uint32_t rxId = 0;
	uint32_t  ModuleID;
	uint8_t	len = 0;
	Frame pkt;

	modi::CAN.readMsgBuf(&rxId, &len, pkt.data);

	rxId = rxId & 0x1FFFFFFF; // 29 bit MASK
	pkt.cmd = rxId >> 24;
	pkt.sid = (rxId & 0x00FFF000) >> 12;
	pkt.did = rxId & 0x00000FFF;
	pkt.len = len;

	uint8_t datatype = 0;
	uint16_t propertyNum = 0;
	

	/* message */
	switch(pkt.cmd)
	{
		case 0x00: // case Health
			return;
		break;
		
		case 0x05: // case Assign ID
			ModuleID = pkt.data[5];
			ModuleID = ModuleID << 8;
			ModuleID = ModuleID | pkt.data[4];

			if (ModuleID == 0x0000) MODI_PRINT_F("AssignID received. Module Network - ID: 0x");//case Network
			else if (ModuleID == 0x2000) MODI_PRINT_F("AssignID received. Module Environment - ID: 0x");//case Environment
			else if (ModuleID == 0x2010) MODI_PRINT_F("AssignID received. Module Gyroscope - ID: 0x");//case Gyroscope
			else if (ModuleID == 0x2020) MODI_PRINT_F("AssignID received. Module Mic - ID: 0x");//case Mic
			else if (ModuleID == 0x2030) MODI_PRINT_F("AssignID received. Module Button - ID: 0x");//case Button
			else if (ModuleID == 0x2040) MODI_PRINT_F("AssignID received. Module Dial - ID: 0x");//case Dial
			else if (ModuleID == 0x2050) MODI_PRINT_F("AssignID received. Module Ultrasonic - ID: 0x");//case Ultrasonic
			else if (ModuleID == 0x2060) MODI_PRINT_F("AssignID received. Module IR - ID: 0x");//case IR
			else if (ModuleID == 0x4000) MODI_PRINT_F("AssignID received. Module Display - ID: 0x");//case Display
			else if (ModuleID == 0x4010) MODI_PRINT_F("AssignID received. Module Motor - ID: 0x");//case Motor
			else if (ModuleID == 0x4020) MODI_PRINT_F("AssignID received. Module LED - ID: 0x");//case LED
			else if (ModuleID == 0x4030) MODI_PRINT_F("AssignID received. Module Speaker - ID: 0x");//case Speaker

			MODI_PRINTLN(pkt.sid, HEX);

			/* Module Update */

			return ;
		break;

		case 0x1F: // case ChannelProperty
			datatype 	=  (pkt.did & 0x0F00) >> 8;
			propertyNum =  (pkt.did & 0x00FF) >> 0;
			MODI.updatePropterty(pkt.sid,propertyNum,pkt.data);
		break;

	}
	return;
}

/* End of File */

#ifndef ROBOT_H
#define ROBOT_H

#include "Motor.h"

#define MOTOR_SET(x) 	(((x) << 4) & 0x30)
#define CMD_SET(x)		((x) & 0x0F)
#define MOTOR_NUM(x) 	(((x) >> 4) & 0x03)
#define CMD_GET(x)		((x) & 0x0F)

#ifndef uint16_t
typedef unsigned int uint16_t;
#endif
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif


enum MOTOR {
	MOTOR1 = 0x01, 
	MOTOR2 = 0x02
	};

enum CONTROL {
	FORWARD = 0x09,
	REVERSE	= 0x06,
	FREE1 	= 0x00,
	BRAKE1	= 0x05,
	BRAKE2	= 0x0A
};
	
typedef struct move_cmd_s {
		uint8_t action1;
		uint8_t speed1;
		uint8_t action2;
		uint8_t speed2;
}move_cmd_t;

class Robot {
private:
	Motor *m_pM1;
	Motor *m_pM2;
	void Decode(uint8_t action, uint8_t speed);
public:
	Robot(void);
	~Robot(void);
	void Init(uint8_t nPinForward1, uint8_t nPinBackward1, uint8_t nPinEnable1, 
				uint8_t nPinForward2, uint8_t nPinBackward2, uint8_t nPinEnable2);
	void Move(move_cmd_t * cmds);
	void Stop(void);
	
	static void Packet(move_cmd_t * cmd, uint8_t speed_m1, uint8_t speed_m2);
	static uint16_t Abs(int number);
};
#endif

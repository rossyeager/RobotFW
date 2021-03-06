#include "MotorStepper.h"
#include "Arduino.h"

MotorStepper::MotorStepper() : Motor() {
}

//Only using 2 pins to control forward and backward and one enable pin
//MotorStepper driver based off of L298n Dual H-Bridge
MotorStepper::MotorStepper(uint8_t nPinForward, uint8_t nPinBackward, uint8_t nPinEnable) 
		: Motor(nPinForward, nPinBackward, nPinEnable){
}

void MotorStepper::Init(uint8_t nPinForward, uint8_t nPinBackward, uint8_t nPinEnable){
	m_nSpeed = 0;
	m_nPin1 = nPinForward;
	m_nPin2 = nPinBackward;
	m_nPinEnable = nPinEnable;
	m_nStatus = 0;
	digitalWrite(LOW, m_nPinEnable);
}

void MotorStepper::Forward(long nSpeed){
	if(nSpeed > PWM_HIGH)
		nSpeed = PWM_HIGH;
	m_nSpeed = nSpeed;
	digitalWrite(HIGH, m_nPinEnable);
	analogWrite((uint8_t) m_nSpeed, m_nPin1);
	analogWrite(PWM_LOW, m_nPin2);
}

void MotorStepper::Reverse(long nSpeed){
	if(nSpeed > PWM_HIGH)
		nSpeed = PWM_HIGH;
	m_nSpeed = nSpeed;
	digitalWrite(HIGH, m_nPinEnable);
	analogWrite(PWM_LOW, m_nPin1);
	analogWrite((uint8_t) m_nSpeed, m_nPin2);
}

void MotorStepper::Brake(){
	m_nSpeed = 0;
	digitalWrite(HIGH, m_nPinEnable);
	digitalWrite(LOW, m_nPin1);
	digitalWrite(LOW, m_nPin2);
}

void MotorStepper::Free(void){
	m_nSpeed = 0;
	digitalWrite(LOW, m_nPinEnable);
	analogWrite(PWM_LOW, m_nPin1);
	analogWrite(PWM_LOW, m_nPin2);
}

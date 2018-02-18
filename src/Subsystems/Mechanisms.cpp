#include "Mechanisms.h"

#include "../Commands/AuxiliaryMotors.h"

#include "../RobotMap.h"
#include <math.h>

#include "WPILib.h"
<<<<<<< HEAD
=======
#include "CommandBase.h"
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5

#include "ctre/Phoenix.h"

#define MAXRPM 534
#define LARGE_AMOUNT_OF_CURRENT 50
#define SQUISH_SPEED .1
#define PEAK_CLAW_CURRENT 5

Mechanisms::Mechanisms() :
		Subsystem("AuxiliaryMotors") {

	winchA = new WPI_TalonSRX(5);
	winchB = new WPI_TalonSRX(6);
	claw = new WPI_TalonSRX(7);
	elevatorWinch = new WPI_TalonSRX(8);
	elevatorClaw = new WPI_TalonSRX(9);

	winchB->Follow(*winchA);

<<<<<<< HEAD
	claw->ConfigPeakCurrentLimit(PEAK_CLAW_CURRENT,
			CommandBase::robotDrive->kTimeoutMs);
	claw->ConfigPeakCurrentDuration(200, 0);
	claw->EnableCurrentLimit(true);

	elevatorClaw->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,
				CommandBase::robotDrive->kTimeoutMs);
	claw->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,
				CommandBase::robotDrive->kTimeoutMs);
//	claw->ConfigForwardLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_RemoteTalonSRX,
//			LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 5);
//	claw->ConfigReverseLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_RemoteTalonSRX,
//			LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 5);
=======
//	claw->ConfigPeakCurrentLimit(PEAK_CLAW_CURRENT,
//			CommandBase::robotDrive->kTimeoutMs);
//	claw->ConfigPeakCurrentDuration(200, 0);
//	claw->EnableCurrentLimit(true);

	elevatorWinch->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,
			CommandBase::robotDrive->kTimeoutMs);
	InitDefaultCommand();
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
}

void Mechanisms::InitDefaultCommand() {
	SetDefaultCommand(new AuxiliaryMotors());
//	elevatorWinch->Config_kF(CommandBase::robotDrive->kPIDLoopIdx,	//ID (0), data, timeout
//			CommandBase::robotDrive->prefs->GetFloat("ElevatorClaw F",
//					CommandBase::robotDrive->defaultF),
//			CommandBase::robotDrive->kTimeoutMs);
//
//	elevatorWinch->Config_kP(CommandBase::robotDrive->kPIDLoopIdx,	//ID (0), data, timeout
//			CommandBase::robotDrive->prefs->GetFloat("ElevatorClaw P",
//					CommandBase::robotDrive->defaultP),
//			CommandBase::robotDrive->kTimeoutMs);
//
//	elevatorWinch->Config_kI(CommandBase::robotDrive->kPIDLoopIdx,	//ID (0), data, timeout
//			CommandBase::robotDrive->prefs->GetFloat("ElevatorClaw I",
//					CommandBase::robotDrive->defaultI),
//			CommandBase::robotDrive->kTimeoutMs);
//
//	elevatorWinch->Config_kD(CommandBase::robotDrive->kPIDLoopIdx,	//ID (0), data, timeout
//			CommandBase::robotDrive->prefs->GetFloat("ElevatorClaw D",
//					CommandBase::robotDrive->defaultD),
//			CommandBase::robotDrive->kTimeoutMs);
<<<<<<< HEAD
=======

	maxClawCurrent = CommandBase::prefs->GetFloat("Claw Max Current",
			LARGE_AMOUNT_OF_CURRENT);
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
}

void Mechanisms::Winch(float speed) {
	winchA->Set(speed);
<<<<<<< HEAD
	SmartDashboard::PutNumber("Winch speed",speed);
}

void Mechanisms::Claw(float speed) {
	float clawCurrent = claw->GetOutputCurrent();

	claw->Set(speed);
	SmartDashboard::PutNumber("Claw Current", claw->GetOutputCurrent());
	SmartDashboard::PutNumber("Claw Position",
			claw->GetSensorCollection().GetQuadraturePosition());

}

//NAMING CONVENTION REFORM
void Mechanisms::ClimbVertical(float speed) {
	//elevatorWinch->Set(ControlMode::Velocity, (speed * MAXRPM * 4096 * 600 );
	elevatorWinch->Set(speed);
//	SmartDashboard::PutNumber("Elevator winch speed",speed);
	SmartDashboard::PutNumber("Winch Current", elevatorWinch->GetOutputCurrent());
=======
//	SmartDashboard::PutNumber("Winch(es) speed",speed);
}

bool Mechanisms::Claw(float speed) {
	bool stop = ClawCurrent() > maxClawCurrent;
	if (!stop)
		claw->Set(speed);
	return stop;
}

void Mechanisms::ElevatorWinch(float speed) {
	//elevatorWinch->Set(ControlMode::Velocity, (speed * MAXRPM * 4096 * 600 );
	elevatorWinch->Set(speed);
	SmartDashboard::PutNumber("Elevator Winch Encoder",
			elevatorWinch->GetSensorCollection().GetQuadraturePosition());
//	SmartDashboard::PutNumber("Elevator winch speed",speed);
	SmartDashboard::PutNumber("Winch Current",
			elevatorWinch->GetOutputCurrent());
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
}

void Mechanisms::ElevatorClaw(float speed) {
	elevatorClaw->Set(speed);
	SmartDashboard::PutNumber("Elevator Claw Current",
			elevatorClaw->GetOutputCurrent());
//	SmartDashboard::PutNumber("Elevator claw speed",speed);
<<<<<<< HEAD
	SmartDashboard::PutNumber("Elevator Claw Position",
			elevatorClaw->GetSensorCollection().GetQuadraturePosition());
}

bool Mechanisms::ClawForwardLimit() {
	int raw = elevatorClaw->GetSensorCollection().IsFwdLimitSwitchClosed();
	SmartDashboard::PutBoolean("Lower Limit", (bool) raw);
	if (raw == 0)
		return false;
	return true;
}

//FAKE ERRORS REEEEEEEEEE
bool Mechanisms::ClawReverseLimit() {
	int raw = elevatorClaw->GetSensorCollection().IsRevLimitSwitchClosed();
	SmartDashboard::PutBoolean("Reverse Limit", (bool) raw);
	if (raw == 0)
		return false;
	return true;
}

float Mechanisms::ClawCurrent() {
	return claw->GetOutputCurrent();
=======
}

float Mechanisms::ClawCurrent() {
	float raw = claw->GetOutputCurrent();
	SmartDashboard::PutNumber("Claw Current", raw);
	return raw;
>>>>>>> ecad1213e55ff161c02ea4b138f0a2b43dc4b2f5
}
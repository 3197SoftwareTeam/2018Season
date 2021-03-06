#ifndef SWERVE_SCALE_OPP_H
#define SWERVE_SCALE_OPP_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include "AutoCalls.h"

class SwerveScaleOpp: public CommandBase
{
private:
	Timer timer;
	int state;
	bool finished;

	float eleTime;

	float eleSpeedUp;
	float eleSpeedDown;

	float baseSpeed;
	float backupSpeed;
	float extraSpeed;
	float extraExtraSpeed;

	float driveOverTime;
	float backupTime;

	float straightDistance;
	float straightAcrossDistance;

	float swerveAngle;
	float swerveBackAngle;

	enum states {
		StraightToScale,
		SwerveIn,
		StraightAcross,
		SwerveTowardScale,
		RaiseFully,
		DriveOverScale,
		Drop,
		Backup,
		Lower
	};

	AutoCalls* claw = new AutoCalls();
	void IncrementState();

public:
	SwerveScaleOpp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void Drive(float l, float r);
};

#endif

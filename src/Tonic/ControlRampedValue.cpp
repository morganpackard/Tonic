
#include "ControlRampedValue.h"

Tonic::Tonic_::ControlRampedValue_::ControlRampedValue_() : 	
	finished_(true),
	count_(0),
	len_(0),
	target_(0),
	last_(0),
	inc_(0)
{

}

Tonic::ControlTrigger Tonic::Tonic_::ControlRampedValue_::getFinishedTrigger()
{
	return finishedTrigger_;
}

bool Tonic::Tonic_::ControlRampedValue_::isFinished()
{
	return finished_;
}

Tonic::ControlTrigger Tonic::ControlRampedValue::getFinishedTrigger()
{
	return gen()->getFinishedTrigger();
}

bool Tonic::ControlRampedValue::isFinished()
{
	return gen()->isFinished();
}
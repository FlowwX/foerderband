
#include "States.h"

HightChecker::HightChecker(){
    state  = new Idle();
    sensor = new HightSensorStub();
    result_ = false;

    sensor->readValuesFromFile(SENSOR_FILE_1);
};

void HightChecker::setState(HcState* hc){
    state = hc;
}

void HightChecker::setResult(bool res){
    result_ = res;
}

bool HightChecker::result(){
   	return result_;
}

HcState* HightChecker::getState(){
    return state;
}

Signal HightChecker::toState(int height){
	if(height>=3765 && height<=3780){
		return GROUND;
	}
	else if(height>=3000 && height<=3150){
		return HIGH;
	}
	else if(height>=3330 && height<=3480){
		return MID;
	}
	else if(height>=3650 && height<=3750){
		return LOW;
	}
	return UNDEFINED;
}

int HightChecker::getHeight(){
	return sensor->nextValue();
}

void HightChecker::setSensor(HightSensorStub* stub){
	sensor = stub;
}

void HightChecker::evalCycle(){
		int index = 0;

		int h = getHeight();
		Signal sig = toState(h);
		switch(sig){
			case GROUND:
				state->onGroundSignal(this);
				break;
			case HIGH:
				state->onHighSignal(this);
				break;
			case MID:
				state->onMidSignal(this);
				break;
			case LOW:
				state->onLowSignal(this);
				break;
			case UNDEFINED:
				throw "Undefiniertes Signal.";
				break;

		index++;
		std::cout << index << ":" << state->getName() << std::endl;
		#ifdef DEBUG_

		#endif

	}
}

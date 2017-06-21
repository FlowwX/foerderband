#include "States.h"

void Error::onGroundSignal(HightChecker* hc){
     hc->setState(new Idle());
}

void Error::onHighSignal(HightChecker* hc){
	//keep in error sate
}

void Error::onLowSignal(HightChecker* hc){
	//keep in error sate
}

void Error::onMidSignal(HightChecker* hc){
	//keep in error sate
}

std::string Error::getName(){
	return "ERROR";
}

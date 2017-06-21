#include "States.h"

void Idle::onGroundSignal(HightChecker* hc){
    //do nothing
}

void Idle::onHighSignal(HightChecker* hc){
    hc->setState(new Error());
}

void Idle::onLowSignal(HightChecker* hc){
    hc->setState(new Error());
}

void Idle::onMidSignal(HightChecker* hc){
    hc->setState(new Z1());
}

std::string Idle::getName(){
	return "IDLE";
}

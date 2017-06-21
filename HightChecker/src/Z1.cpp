#include "States.h"

void Z1::onGroundSignal(HightChecker* hc){
	hc->setState(new Error());
}

void Z1::onHighSignal(HightChecker* hc){
	hc->setState(new Error());
}

void Z1::onLowSignal(HightChecker* hc){
	hc->setState(new Z2());
}

void Z1::onMidSignal(HightChecker* hc){
	//do nothing
}

std::string Z1::getName(){
	return "Z1";
}

#include "States.h"

void Z2::onGroundSignal(HightChecker* hc){
	hc->setState(new Error());
}

void Z2::onHighSignal(HightChecker* hc){
	hc->setState(new Error());
}

void Z2::onLowSignal(HightChecker* hc){
	//do nothing
}

void Z2::onMidSignal(HightChecker* hc){
	hc->setState(new Z3());
}

std::string Z2::getName(){
	return "Z2";
}

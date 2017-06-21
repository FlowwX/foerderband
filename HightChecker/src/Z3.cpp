#include "States.h"

void Z3::onGroundSignal(HightChecker* hc){
	hc->setState(new Error());
}

void Z3::onHighSignal(HightChecker* hc){
	hc->setState(new Accept());
	hc->setResult(true);
}

void Z3::onLowSignal(HightChecker* hc){
	hc->setState(new Error());
}

void Z3::onMidSignal(HightChecker* hc){
	//do nothing
}

std::string Z3::getName(){
	return "Z3";
}

#include "States.h"

void Accept::onGroundSignal(HightChecker* hc){
     hc->setState(new Idle());

}

void Accept::onHighSignal(HightChecker* hc){
    //do nothing
}

void Accept::onLowSignal(HightChecker* hc){
    hc->setState(new Error());
}

void Accept::onMidSignal(HightChecker* hc){
    hc->setState(new Error());
}

std::string Accept::getName(){
	return "ACCEPT";
}

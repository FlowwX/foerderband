/** 
 * File:   fsm.cpp
 *
 * Class contains the controlling FSM for sorting out metal contaminated parts.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-01
 */

#include "fsm.h"
#include "../HightChecker.h"
#include "../States.h"

FSM::FSM(FestoProcessAccess *process, Plugin* plugin = 0) {
    this->process = process;
    currentState = Start;
    this->plugin = plugin;
}

FSM::~FSM() {
    delete plugin;
    delete process;
}

void FSM::eval() {
    process->updateInputs();
    if (plugin != NULL) {
        plugin->evalCycle();
    }
    evalEvents();
    evalState();
    process->applyOutput();
}

void FSM::evalEvents() {
    switch (currentState) {
        case Start:
            currentState = Standby;
            break;
        case Standby:
            if (process->isButtonStartNegativeEdge()) {
                currentState = Ready;
            }
            break;
        case Ready:
            if (process->isButtonStartNegativeEdge()) {
                currentState = Standby;
            }
            if (process->isItemAtBeginning()&& !process->isItemAtEnd()) {
                currentState = Transport;
            }
            if (process->isItemAtHightSensor() || process->isItemAtMetalDetector()) {
                currentState = Error;
            }
            break;
        case Transport:
            if (process->isItemAtMetalDetector()) {
                currentState = MetalDetection;
            }
            if (process->isItemAtEnd()) {
                currentState = Error;
            }
            break;
        case MetalDetection:
            if (process->isMetalDetected()) {
                currentState = Metalic;
            } else {
                currentState = NonMetalic;
            }
            break;
        case NonMetalic:
            if (process->isItemAtHightSensor()) {
                currentState = ProfilDetection;
            }
            break;
        case EndReached:
            if (process->isButtonStartNegativeEdge()) {
                currentState = Standby;
            }
            if (!(process->isItemAtEnd())) {
                currentState = Ready;
            }
            if (process->isItemAtMetalDetector() || process->isItemAtHightSensor()) {
                currentState = Error;
            }
            break;
        case Metalic:
            if (process->hasItemPassedSlide()) {
                currentState = SlideReached;
            }
            if (process->isItemAtBeginning() || process->isItemAtHightSensor()) {
                currentState = Error;
            }
            break;
        case SlideReached:
            if (process->isButtonStartNegativeEdge()) {
                currentState = Standby;
            }
            if (process->isItemAtBeginning()) {
                currentState = Transport;
            }
            if (process->isItemAtEnd() || process->isItemAtHightSensor()) {
                currentState = Error;
            }
            break;
        case Error:
            if (process->isButtonStartNegativeEdge()) {
                currentState = Standby;
            }
            break;
        case ProfilDetection:
        	if( plugin->result() && ( (HightChecker*) plugin)->getState()->getName() == "ACCEPT" ){
        		currentState = ProfilOK;
        	}

        	if( plugin->result() && ( (HightChecker*) plugin)->getState()->getName() == "ERROR" ){
        		currentState = ProfilNotOK;
        	}

        	break;
        case ProfilNotOK:
        	if(process->isItemAtBeginning()){
        		currentState = Ready;
        	}
        	break;
        case ProfilOK:
        	if(process->isItemAtEnd()){
        		currentState = EndReached;

        	}
        	break;
        default:
            currentState = Start;
    }
}

void FSM::evalState() {
    switch (currentState) {
        case Start:
        case Standby:
            process->driveStop();
            process->lightGreenOff();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDQ1Off();
            process->turnLEDQ2Off();
            process->turnLEDResetOff();
            process->turnLEDStartOn();

            printf("Standby\n");

            break;
        case Ready:
            process->driveStop();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOn();

            printf("Ready\n");

            break;
        case Transport:
            process->driveRight();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOff();

            printf("Transport\n");

            break;
        case MetalDetection:
            process->driveStop();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();

            printf("MetalDetection\n");

            break;
        case NonMetalic:

            process->driveRight();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOff();
            process->openJunction();

            printf("NonMetalic\n");

            break;
        case EndReached:
            process->driveStop();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOff();
            process->closeJunction();
            process->turnLEDStartOn();
            blinkGreen();

            printf("EndReached\n");

            break;
        case Metalic:
            process->driveRight();
            process->lightGreenOff();
            process->lightRedOff();
            process->lightYellowOn();

            printf("Metalic\n");

            break;
        case SlideReached:
            process->driveStop();
            process->lightGreenOn();
            process->lightRedOff();
            process->lightYellowOff();
            process->turnLEDStartOn();

            printf("SlideReached\n");

            break;
        case Error:
            process->driveStop();
            process->lightGreenOff();
            process->lightYellowOff();
            process->turnLEDStartOn();
            process->closeJunction();
            blinkRed();

            printf("Error\n");

        case ProfilDetection:
        	 printf("ProfilDetection\n");
            break;

        case ProfilNotOK:
        	 printf("ProfilNotOK\n");
            break;

        case ProfilOK:
        	 printf("ProfilOK\n");
            break;

    }
}

void FSM::blinkRed() {
    if (process->timeCounter1s() & 0x01) {
        process->lightRedOn();
    } else {
        process->lightRedOff();
    }
}

void FSM::blinkGreen() {
    if (process->timeCounter1s() & 0x01) {
        process->lightGreenOn();
    } else {
        process->lightGreenOff();
    }
}

FestoProcessAccess* FSM::getProcess(){
	return process;
}

fsm_states FSM::getState() {

	return currentState;
}

Plugin* FSM::getPlugin() {

	return plugin;
}

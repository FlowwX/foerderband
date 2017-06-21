/* 
 * File:   main.cpp
 * Author: Lehmann
 *
 * Created on 8. November 2013, 16:24
 */

#include <cstdlib>
#include <cstdio>
#include "factory.h"
#include "../HightChecker.h"


using namespace std;


int main(int argc, char** argv) {

    FSMFactory factory;

    FSM* fsm = factory.createFSM();

    FestoProcessAccess* fpa = fsm->getProcess();

//Testsequenz 1: Korrekter Baustein

    //get into standby
    fsm->eval();

    //get into Ready
    fpa->setButtonPressed();
    fsm->eval();

    //get into Transport
    fpa->setItemAtBeginning();
    fpa->setItemNotAtEnd();
    fpa->setItemNotAtHightSensor();
    fpa->setItemNotAtMetallDetector();
    fsm->eval();

    //get into Metaldetection
    fpa->setItemAtMetallDetector();
    fpa->setItemNotAtEnd();
    fsm->eval();

    //get into NonMetalic
    fsm->eval();

    //get into HightDetection
    fpa->setItemAtHightSensor();
    fsm->eval();

    //check until detection gets ready
    while ( fsm->getState() == ProfilDetection ) {

    	fsm->eval();
    }

    //get into Endreached
    fpa->setItemAtEnd();
    fsm->eval();

    //get into Ready
    fpa->setItemNotAtEnd();
    fpa->setItemNotAtHightSensor();
    fpa->setItemNotAtMetallDetector();
    fsm->eval();

    printf("\n\n\n\n\n\n----------------------------\n\n\n\n\n\n");

//Testsequenz 2: Fehlerhafter Baustein

    HightChecker* hc_plugin = (HightChecker*) fsm->getPlugin();
    HightSensorStub* stub = new HightSensorStub();
    stub->readValuesFromFile(SENSOR_FILE_2);

    hc_plugin->setSensor(stub);

    //get into Transport
    fpa->setItemAtBeginning();
    fpa->setItemNotAtEnd();
    fpa->setItemNotAtHightSensor();
    fpa->setItemNotAtMetallDetector();
    fsm->eval();

    //get into Metaldetection
    fpa->setItemAtMetallDetector();
    fpa->setItemNotAtEnd();
    fsm->eval();

    //get into NonMetalic
    fsm->eval();

    //get into HightDetection
    fpa->setItemAtHightSensor();
    fsm->eval();

    //check until detection gets ready
    while ( fsm->getState() == ProfilDetection ) {

    	fsm->eval();
    }

    //get into Ready
    fpa->setItemAtBeginning();
    fsm->eval();


    delete fsm;

    return 0;
}

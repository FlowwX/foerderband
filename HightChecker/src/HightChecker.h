#ifndef HIGHT_CHECKER_H
#define HIGHT_CHECKER_H

#include "HightSensorStub.h"
#include "Sources_orig/plugin.h"


class HcState;

/**
 * 	Signaltypen
 */
enum Signal{LOW, MID, HIGH, GROUND, UNDEFINED};

/**
 * Klasse überprüft einkommende Signale
 * und bildet den Kontext im GoF State-Pattern
 */
class HightChecker: public Plugin
{
    private:

		/**
		 * Aktueller Status der FSM
		 */
        HcState *state;

        /**
         * Sensor Stub
         */
        HightSensorStub *sensor;

        /**
         * Ergebins der Überprüfung
         */
        bool result_;

    public:


        void setSensor(HightSensorStub*);

        /**
         *
         */
        HightChecker(void);

        /**
         * Methode setzt den Zustand
         */
        void setState(HcState*);

        /**
         * Methode setzt das Ergebinis
         */
        void setResult(bool);



        /**
         * Methode liefert Status
         */
        HcState* getState();

        /**
         * Sensorwerte in Signal wandeln
         */
        Signal toState(int);


        /**
         *	Höhe vom sensor auslesen
         */
        int getHeight(void);


        virtual void evalCycle();
        virtual bool result();

};

#endif //HIGHT_CHECKER_H

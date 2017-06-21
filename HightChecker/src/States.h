#ifndef STATES_H
#define STATES_H

#include <iostream>
#include "HightChecker.h"

class HcState {


	public:
		virtual void onHighSignal(HightChecker*) = 0;

		virtual void onLowSignal(HightChecker*) = 0;

		virtual void onMidSignal(HightChecker*) = 0;

		virtual void onGroundSignal(HightChecker*) = 0;

		virtual std::string getName() = 0;

};

class Idle: public HcState{


    public:
        virtual void onHighSignal(HightChecker*);

        virtual void onLowSignal(HightChecker*);

        virtual void onMidSignal(HightChecker*);

        virtual void onGroundSignal(HightChecker*);

        virtual std::string getName();

};



class Accept: public HcState{
    public:
        void onHighSignal(HightChecker*);

        void onLowSignal(HightChecker*);

        void onMidSignal(HightChecker*);

        void onGroundSignal(HightChecker*);

        virtual std::string getName();

};

class Error: public HcState{
    public:
        virtual void onHighSignal(HightChecker*);

        virtual void onLowSignal(HightChecker*);

        virtual void onMidSignal(HightChecker*);

        virtual void onGroundSignal(HightChecker*);

        virtual std::string getName();

};

class Z1: public HcState{
    public:
        virtual void onHighSignal(HightChecker*);

        virtual void onLowSignal(HightChecker*);

        virtual void onMidSignal(HightChecker*);

        virtual void onGroundSignal(HightChecker*);

        virtual std::string getName();

};

class Z2: public HcState{
    public:
        virtual void onHighSignal(HightChecker*);

        virtual void onLowSignal(HightChecker*);

        virtual void onMidSignal(HightChecker*);

        virtual void onGroundSignal(HightChecker*);

        virtual std::string getName();


};

class Z3: public HcState{
    public:
        virtual void onHighSignal(HightChecker*);

        virtual void onLowSignal(HightChecker*);

        virtual void onMidSignal(HightChecker*);

        virtual void onGroundSignal(HightChecker*);

        virtual std::string getName();

};

#endif //STATES_H

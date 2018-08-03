#include "instrument.h"
#include "instruments/bell8.h"
#include "instruments/bell.h"
#include "instruments/organ.h"
#include "instruments/harmonica.h"
#include "instruments/debug.h"

Instrument::Instrument(std::string sLabel){
    this->sLabel = sLabel;
}

Instrument::~Instrument() {
}

Instrument *Instrument::Create() {
    // Instrument selection
    int siUserInstrument = -1;
    bool bChooseAgain = true;

    while (bChooseAgain) {
        std::wcout << "\nSelect a instrument [" <<
            INS_BELL << "-BELL | " <<
            INS_BELL8 << "-BELL8 | " <<
            INS_HARMONICA << "-HARMONICA | " <<
            INS_ORGAN << "-ORGAN | " <<
            INS_DEBUG << "-DEBUG | " <<
            INS_NONE << "-EXIT]: ";

        std::cin >> siUserInstrument;
        bChooseAgain = false;

        if (siUserInstrument == INS_BELL) {
            std::cout << "BELL has been selected." << std::endl;
            return new Bell();
        }
        else if (siUserInstrument == INS_BELL8) {
            std::cout << "BELL8 has been selected." << std::endl;
            return new Bell8();
        }
        else if (siUserInstrument == INS_HARMONICA) {
            std::cout << "HARMONICA has been selected." << std::endl;
            return new Harmonica();
        }
        else if (siUserInstrument == INS_ORGAN) {
            std::cout << "ORGAN has been selected." << std::endl;
            return new Organ();
        }
        else if (siUserInstrument == INS_DEBUG) {
            std::cout << "DEBUG has been selected." << std::endl;
            return new Debug();
        }
        else if (siUserInstrument == INS_NONE) {
            return NULL;
        }
        else {
            std::cout << "Not available instrument." << std::endl;
            bChooseAgain = true;
        }
    }

    return NULL;
}


ChooseInstrument::ChooseInstrument() {
    this->pobInstrument = Instrument::Create();
}

ChooseInstrument::~ChooseInstrument() {
    if (this->pobInstrument) {
        delete[] this->pobInstrument;
        this->pobInstrument = NULL;
    }
}

Instrument* ChooseInstrument::getInstrument() {
    return this->pobInstrument;
}



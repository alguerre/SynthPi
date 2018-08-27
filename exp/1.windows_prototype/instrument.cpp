#include "instrument.h"
#include "instruments/bell8.h"
#include "instruments/bell.h"
#include "instruments/organ.h"
#include "instruments/harmonica.h"
#include "instruments/debug.h"
#include "drums/kick.h"
#include "drums/hihat.h"
#include "drums/snare.h"


Instrument::Instrument(std::string sLabel ){
    this->sLabel = sLabel;
}


Instrument::~Instrument() {
}


Instrument* Instrument::Create(Instrument_t eInputInstrument) {
    /* CREATE return the created instrument according to the input instrument
    code.*/
    if (eInputInstrument == INS_BELL) {
        std::cout << "BELL has been selected." << std::endl;
        return new Bell();
    }
    else if (eInputInstrument == INS_BELL8) {
        std::cout << "BELL8 has been selected." << std::endl;
        return new Bell8();
    }
    else if (eInputInstrument == INS_HARMONICA) {
        std::cout << "HARMONICA has been selected." << std::endl;
        return new Harmonica();
    }
    else if (eInputInstrument == INS_ORGAN) {
        std::cout << "ORGAN has been selected." << std::endl;
        return new Organ();
    }
    else if (eInputInstrument == INS_DEBUG) {
        std::cout << "DEBUG has been selected." << std::endl;
        return new Debug();
    }
    else if (eInputInstrument == INS_DRUM_KICK) {
        return new DrumKick();
    }
    else if (eInputInstrument == INS_DRUM_HIHAT) {
        return new DrumHiHat();
    }
    else if (eInputInstrument == INS_DRUM_SNARE) {
        return new DrumSnare();
    }
    else if (eInputInstrument == INS_NONE) {
        return NULL;
    }
    else {
        std::cout << "Not available instrument has been tried to be created." 
            << std::endl;
    }

    return NULL;
}


void Instrument::NoteOn(double dTime) {
    /*NOTEON is a wrapper with NoteOn method in envelopADSR. */
    this->obEnvelope.NoteOn(dTime);
}


void Instrument::NoteOff(double dTime) {
    /*NOTEOFF is a wrapper with NoteOff method in envelopADSR. */
    this->obEnvelope.NoteOff(dTime);
}


std::string Instrument::GetInstrumentLabel() {
    /*GETINSTRUMENTLABEL retuns the label which named the instrument.*/
    return this->sLabel;
}



ChooseInstrument::ChooseInstrument(Instrument_t eDefaultInstrument) {
    /* CHOOSINSTRUMENT constructor of the ChoosInstrument class, it is designed
    to create instrument objects. This way it is possible to use a print
    menu as interface.*/

    // Instrument selection
    int siUserInstrument = -1;
    bool bChooseAgain = true;
    Instrument_t eInstrument2Create = INS_NONE;

    while (bChooseAgain) {
        
        if (eDefaultInstrument == INS_NONE) {
            std::wcout << "\nSelect a instrument [" <<
                INS_BELL << "-BELL | " <<
                INS_BELL8 << "-BELL8 | " <<
                INS_HARMONICA << "-HARMONICA | " <<
                INS_ORGAN << "-ORGAN | " <<
                INS_DEBUG << "-DEBUG | " <<
                INS_NONE << "-EXIT]: ";

            std::cin >> siUserInstrument;
            eInstrument2Create = static_cast<Instrument_t>(siUserInstrument);
        }
        else {
            eInstrument2Create = eDefaultInstrument;
        }

        if ((eInstrument2Create != INS_BELL) &&
            (eInstrument2Create != INS_BELL8) &&
            (eInstrument2Create != INS_HARMONICA) &
            (eInstrument2Create != INS_ORGAN) &&
            (eInstrument2Create != INS_DRUM_KICK) &&
            (eInstrument2Create != INS_DRUM_HIHAT) &&
            (eInstrument2Create != INS_DRUM_SNARE) &&
            (eInstrument2Create != INS_DEBUG) &&
            (eInstrument2Create != INS_NONE)){
            std::cout << "Not available instrument." << std::endl;
            bChooseAgain = true;
        }
        else {
            bChooseAgain = false;
        }
    }

    // Create instrument
    this->eInstrumentId = eInstrument2Create;
    this->pobInstrument = Instrument::Create(eInstrument2Create);
}


ChooseInstrument::~ChooseInstrument() {
    if (this->pobInstrument) {
        delete[] this->pobInstrument;
        this->pobInstrument = NULL;
    }
}


Instrument_t ChooseInstrument::GetInstrumentId() {
    /*GETINSTRUMENTID retuns the id of the choosen instrument.*/
    return this->eInstrumentId;
}


Instrument *  ChooseInstrument::GetInstrument() {
    /*GETINSTRUMENT retuns the choosen instrument.*/
    return this->pobInstrument;
}

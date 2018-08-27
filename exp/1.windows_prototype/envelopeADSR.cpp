#include "envelopeADSR.h"
#include "constants.h"

EnvelopeADSR::EnvelopeADSR() {
    // Constructor, properties initialization
    this->dStartAmplitude = 0.0;
    this->dAttackTime = 0.0;
    this->dDecayTime = 0.0;
    this->dSustainLevel = 0.0;
    this->dReleaseTime = 0.0;
    this->dTriggerOffTime = 0.0;
    this->dTriggerOnTime = 0.0;
    this->bNoteOn = false;
    this->bIsCreated = false;
}


EnvelopeADSR::~EnvelopeADSR() {
    // Destructor
}


void EnvelopeADSR::Create(double dSA,
    double dAT,
    double dDT,
    double dSL,
    double dRT, 
    std::string sInstrument) {

    // ADSR model
    this->dStartAmplitude = dSA;
    this->dAttackTime = dAT;
    this->dDecayTime = dDT;
    this->dSustainLevel = dSL;
    this->dReleaseTime = dRT;

    // Notes information
    this->dTriggerOffTime = 0.0;
    this->dTriggerOnTime = 0.0;
    this->bNoteOn = false;
    this->bIsCreated = true;
    this->sInstrument = sInstrument;
}


int EnvelopeADSR::NoteOn(double dTimeOn) {
    /*NOTEOFF store the time in which a note is pressed.*/
    if (this->bIsCreated == false)
        return 1;

    this->dTriggerOnTime = dTimeOn;
    this->bNoteOn = true;
    return 0;
}


int EnvelopeADSR::NoteOff(double dTimeOff) {
    /*NOTEOFF store the time in which a note is released.*/
    if (this->bIsCreated == false)
        return 1;

    this->dTriggerOffTime = dTimeOff;
    this->bNoteOn = false;
    return 0;
}


double EnvelopeADSR::GetAmplitude(double dTime) {
    /* GETAMPLITUDE returns the amplitude of the wave in a certain time. It is
    obtained according to ADSR model. It is checked whether the note is pressed
    or released to proceed accordingly.*/

    if (this->bIsCreated == false)
        return 1.0;

    double dAmplitude = 0.0;
    double dLifeTime = dTime - this->dTriggerOnTime;

    if (this->bNoteOn) {

        if (dLifeTime <= this->dAttackTime) {
            // In attack Phase - approach max amplitude
            dAmplitude = (dLifeTime / this->dAttackTime) *
                this->dStartAmplitude;
        }

        if ((dLifeTime > this->dAttackTime) &&
            (dLifeTime <= (this->dAttackTime + this->dDecayTime))) {
            // In decay phase - reduce to sustained amplitude
            dAmplitude = ((dLifeTime - this->dAttackTime) / this->dDecayTime) *
                (this->dSustainLevel - this->dStartAmplitude) +
                this->dStartAmplitude;
        }

        if (dLifeTime > (this->dAttackTime + this->dDecayTime)) {
            // In sustain phase - dont change until note released
            dAmplitude = this->dSustainLevel;
        }
    }

    else {
        // Note has been released, so in release phase
        dAmplitude = ((dTime - this->dTriggerOffTime) / this->dReleaseTime) *
            (0.0 - this->dSustainLevel) +
            this->dSustainLevel;
    }

    // Amplitude should not be negative
    if (dAmplitude <= MINIMUM_AMPLITUDE)
        dAmplitude = 0.0;


    return dAmplitude;
}


bool EnvelopeADSR::IsCreated(void) {
    /* ISCREATED returns whether the enveloped has already been created.*/
    return this->bIsCreated;
}


int EnvelopeADSR::Print(void) {
    /* PRINT prints the envelope characteristics. */
    std::cout << 
        "\nENVELOPE:          " << this->sInstrument <<
        "\nStart amplitude:   " << this->dStartAmplitude <<
        "\nAttack time:       " << this->dAttackTime <<
        "\nDecay time:        " << this->dDecayTime <<
        "\nSustain level:     " << this->dSustainLevel <<
        "\nRelease time:      " << this->dReleaseTime <<
        std::endl;

    if (this->bIsCreated == false)
        return 1;
    else
        return 0;
}

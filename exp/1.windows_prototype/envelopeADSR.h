#include <string>
#include <iostream>

#ifndef _ENVELOPEADSR_h
#define _ENVELOPEADSR_h


class EnvelopeADSR {

private:
    // Properties
    double dAttackTime;
    double dDecayTime;
    double dSustainLevel;
    double dReleaseTime;
    double dStartAmplitude;
    double dTriggerOffTime;
    double dTriggerOnTime;
    bool   bNoteOn;
    bool   bIsCreated;
    std::string sInstrument;

public:
    // Constructor
    EnvelopeADSR();

    // Methods
    void Create(double, double, double, double, double, std::string);
    int NoteOn(double);
    int NoteOff(double);
    double GetAmplitude(double);
    bool IsCreated(void);
    int Print(void);

    // Destructor
    ~EnvelopeADSR();

};

#endif

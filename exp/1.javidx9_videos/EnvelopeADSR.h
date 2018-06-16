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
    bool   bNoteOff;

public:
    // Constructor
    EnvelopeADSR(double, double, double, double, double);

    // Methods
    void NoteOn(double);
    void NoteOff(double);
    double GetAmplitude(double);
    void Print(void);

    // Destructor
    ~EnvelopeADSR();

protected:

};

#endif
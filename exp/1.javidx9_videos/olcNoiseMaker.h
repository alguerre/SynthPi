/* 
	OneLoneCoder.com - Simple Audio Noisy Thing
	"Allows you to simply listen to that waveform!" - @Javidx9

	License
	~~~~~~~
	Copyright (C) 2018  Javidx9
	This program comes with ABSOLUTELY NO WARRANTY.
	This is free software, and you are welcome to redistribute it
	under certain conditions; See license for details. 
	Original works located at:
	https://www.github.com/onelonecoder
	https://www.onelonecoder.com
	https://www.youtube.com/javidx9

	GNU GPLv3
	https://github.com/OneLoneCoder/videos/blob/master/LICENSE

	From Javidx9 :)
	~~~~~~~~~~~~~~~
	Hello! Ultimately I don't care what you use this for. It's intended to be 
	educational, and perhaps to the oddly minded - a little bit of fun. 
	Please hack this, change it and use it in any way you see fit. You acknowledge 
	that I am not responsible for anything bad that happens as a result of 
	your actions. However this code is protected by GNU GPLv3, see the license in the
	github repo. This means you must attribute me if you use it. You can view this
	license here: https://github.com/OneLoneCoder/videos/blob/master/LICENSE
	Cheers!

	Author
	~~~~~~

	Twitter: @javidx9
	Blog: www.onelonecoder.com

	Versions
	~~~~~~~~

	1.0 - 14/01/17
	- Controls audio output hardware behind the scenes so you can just focus
	  on creating and listening to interesting waveforms.
	- Currently MS Windows only

	Documentation
	~~~~~~~~~~~~~

	See video: https://youtu.be/tgamhuQnOkM

	This will improve as it grows!

*/

#pragma once

#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <Windows.h>
#define MAX_SEM_COUNT 10

using namespace std;

const double PI = 2.0 * acos(0.0);

/*extern HANDLE ghSemaphoreSound = NULL;
extern HANDLE ghSemaphoreDriver = NULL;
extern bool bDriverExit = false;*/

template<class T>
class olcNoiseMaker {

public:
    olcNoiseMaker(wstring sOutputDevice,
        unsigned int nSampleRate = 44100,
        unsigned int nChannels = 1,
        unsigned int nBlocks = 8,
        unsigned int nBlockSamples = 512);

    ~olcNoiseMaker();

    bool Create(wstring sOutputDevice,
        unsigned int nSampleRate = 44100,
        unsigned int nChannels = 1,
        unsigned int nBlocks = 8,
        unsigned int nBlockSamples = 512);

    bool Destroy();

    void Stop();

	// Override to process current sample
    virtual double UserProcess(double dTime);

    double GetTime();
	
    static vector<wstring> Enumerate();

    void SetUserFunction(double(*func)(double));

    double clip(double dSample, double dMax);


private:
	double(*m_userFunction)(double);

	unsigned int m_nSampleRate;
	unsigned int m_nChannels;
	unsigned int m_nBlockCount;
	unsigned int m_nBlockSamples;
	unsigned int m_nBlockCurrent;

	T* m_pBlockMemory;
	WAVEHDR *m_pWaveHeaders;
	HWAVEOUT m_hwDevice;

	thread m_thread;
	atomic<bool> m_bReady;
	atomic<unsigned int> m_nBlockFree;
	condition_variable m_cvBlockNotZero;
	mutex m_muxBlockNotZero;

	atomic<double> m_dGlobalTime;

	// Handler for soundcard request for more data
    void waveOutProc(
        HWAVEOUT hWaveOut,
        UINT uMsg,
        DWORD dwParam1,
        DWORD dwParam2);

    // Static wrapper for sound card handler
    static void CALLBACK waveOutProcWrap(HWAVEOUT hWaveOut,
        UINT uMsg,
        DWORD dwInstance,
        DWORD dwParam1,
        DWORD dwParam2);


	// Main thread. This loop responds to requests from the soundcard to fill 'blocks'
	// with audio data. If no requests are available it goes dormant until the sound
	// card is ready for more data. The block is fille by the "user" in some manner
	// and then issued to the soundcard.
    void MainThread();

};

# Experimentation
This is the place for experimentation. This file describes the experimentation which is carried out in each of the directories, quoting the used resources.

### 1.javidx9_videos
  - (DONE) Sound Synthesizer #1 - Basic Noises: https://www.youtube.com/watch?v=tgamhuQnOkM
  - (DONE) Sound Synthesizer #2 - Oscillators & Envelopes: https://www.youtube.com/watch?v=OSCzKOqtgcA&t=946s
  - (Instruments->DONE, Polyphony->PENDING) Sound Synthesizer #3 - Instruments & Polyphony:  https://www.youtube.com/watch?v=kDuvruJTjOs
  - Sound Synthesizer #4 - Waveout API, Sequencing & Ducktales: https://www.youtube.com/watch?v=roRH3PdTajs
  - SPRs in current prototype:
  	- SPR-1: Instrument sounds are not like in the video #3.
		- SMR-1: char -> short
	- SPR-2: Volume change is not correctly implemented. Maybe a mutex is needed. Only two states, 0 or 1. 
		- SMR-2: applied as 10^dVolume.
  - Evolutions:
  	- Include polyphony.
	- Include drums. 

### 2.SDL_first_approach
  - First attempt to play a waveform using SDL library.
  

###  3.embedded_systems_project 
  - Project carried out during the embedded systems course in my master studies. 
  - It uses SDL_mixer to play some predefined sounds. It was created to be run on a Raspberry Pi where:
    - wiringPi library is used for threading, i2c, interruptions, ...
    - the note is selected according to the distance of an object to the sensor
    - drums are played with buttons
    - a LED panel shows a different combination according to the playing music.
	
### Interesting videos
   - CppCon 2015: Timur Doumler "C++ in the Audio Industry": https://www.youtube.com/watch?v=boPEO2auJj4&t=1911s
   - Lessons Learned from a Decade of Audio Programming: https://www.youtube.com/watch?v=Vjm--AqG04Y
   - The Golden Rules of Audio Programming, Pete Goodliffe: https://www.youtube.com/watch?v=SJXGSJ6Zoro
   - Audio Programming for Beginners Tutorial: https://www.youtube.com/watch?v=Ov3GXhorrJE&list=PLLgJJsrdwhPwLOC5aNH8hLTlQYOeESORS 

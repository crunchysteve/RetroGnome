# Retronome
An open source, Arduino metronome, not too dissimilar to the venerable Dr Rhythm. Please note, this project is a work in progress, it is offered publicly with no warranty, inferred or implied. See the licence for details.

For now, it goes, "Bleep, blip, blip, blip. Bleep, blip, blip, blip..." Here's the Wokwi simulation circuit so far...

<a href="https://wokwi.com/projects/387895335576882177" target="_blank"><img width="676" alt="Screenshot 2024-01-26 at 10 51 18 pm" src="https://github.com/crunchysteve/Retronome/assets/46626696/3d1bc020-caeb-465c-a704-16c57d75d0dc"></a>

## Project Roadmap
Mine is going to be a guitar "squash box" with potentiometer to set tempo (between 30 BPM and 285 BPM), probably another pot to set a few different time signatures, tap tempo ([using dxinteractive's library](https://github.com/dxinteractive/ArduinoTapTempo)), MIDI clock with start/stop, maybe 2/4, 3/4, 4/4, 5/4 & 7/8, perhaps a 3-way switch to set half time and double time (eg 4/2 and 4/8 at 4/4 in the middle position. I'm still winging this one. It arose out of a source of insomnia last night. (Invasion Day Eve in Australia) It's been an extremely "compliant" little beast to tease to this stage, so I am happy to keep working on it. Besides, I need a metronome for when it's too much work to power up the drum machine and that's really too much like cracking a peanut with a sledgehammer.

I could buy a metronome of exactly this type for AU$16 +post, but I have a workshop full of parts and it's shaping up as fun coding exercise. It works. Right as depicted here, now, but there are a few challenges to solve. For example, since adding the pot, the bleep and its blips have gone a bit squeeky. That may be just Wokwi.com's sim engine. I've yet to run this on hardware. You need 2 libraries to build this and upload it, my EdgieD state change detector for button sensing, and the 4x 7 seg display driver, TM1637TinyDisplay. I'm tossing up the idea of a Nokia 5110 display version, too. Are they still making that spare part? Seem to be a few about on eBay and Ali.

I want to add some sort of animation to the display or maybe a 2 colour LED on pins 12 and 13 to flash red, green, green, green, red, green, green, green when running, too. Should I add swing capability? Yes, it will be a guitar pedal form factor. No, it's not a guitar pedal, it's a foot operated metronome. I want it next to my effects. You should work with a metronome when workshopping effects switches during practice.

## Fritzing PCB File and Gerber Folder Added
![PCB Image](https://github.com/crunchysteve/Retronome/blob/main/RetroGnome_pcb.png)

At this stage, It hasn't been built, there may be errors. I've still to finalise code for features, such as time signature potentiometer. (The tempo pot has worked in simulation since first commit.) I promise, I'll get it to a basic release in the next few months. Clone the Gerber directory, zip it up and upload it PCBway or NextPCB, as is your preference. If you can't wait for the first release code, feel free to fork it and do it yourself. The only source restriction is on commercial use. This project is totally FOSS, see the licence for details.

## How It Works
When you power it up, the display cycles through, "Wlcm to Rtro nome," as 4 lines of 7-seg text. Once that's done, it sits and does nothing, tempo set to where the knob is, waiting for you to press the start/stop button. When you do finally press the button, it goes "Bleep, blip, blip, blip. Bleep, blip, blip, blip..." until you press the button again. It works like a computer mouse, action-on-release, because of the ```INPUT_PULLUP``` config on pin 2. You kind of want this with a foot pedal metronome, press the button, focus on the piece you want to play, lift your foot and play. As you approach the end of the piece, foot on the button, release as you play the last beat.

[You can try out the sim over here at wokwi](https://wokwi.com/projects/387895335576882177).

Feel free to use this in it's current form, in any way you see fit, but don't mass produce it off my code without asking, OK.

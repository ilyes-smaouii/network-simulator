# network-simulator
Multi-layer multi-purpose network simulating modules

## Intro/context
I just got the idea of trying to create a program that could help simulate networks on all levels
(physical, link, etc.), and created this repo in anticipation.\
If done right, I should be able to simulate for anything, and all protocols, with the
ability to controll all parameters.
It's mostly just an idea for now though, I don't know if I'll actually pursue it. If I do and the
standard protocols are too complex to implement - or if the specifications are not accessible
enough -, maybe I could try to create my own protocols.

## Purpose
Mostly for fun/curiosity/coding practice

## Personal notes
- Should be as modular as possible
  - If a layer N module can work without depending on lower layers, this allows 
me to, say, start working on UDP without having to work on Ethernet/MAC/other
first.
- Layers obviously make assumptions on lower/other layers. So can protocols !
- Allow for debugging/research/introspection functionality. e.g. allow for artificial latency

## Ideas/things to explore
- Impact of physical medium/other layers on applications
- Simple transmission, transmission w/ tracking of a few things
- ?

## Journal/Misc
### 2025/08/18
Created the repo
### 2025/10/04
Started to think a bit about some approaches I could take on here.
\
Update : found out some projects with a similar premise already exist. Doesn't change much though,
this was mostly meant as project for personal learning and exploration.

### 2026/04/20
Starting up again

### 2026/04/24
Some ideas for use cases :
- \[L1-L7\] device communicating with another \[L1-L7\] device, with several [L3] devices in-between. Simple HTTP exchange should be enough.
  - Allows to test for everything, and particulary L3
  - Config files for L3 network topology ?
- Same or similar, but with at least one \[L1-L3\] pair somewhere in the middle, to experiment with changing network conditions (intereferences, etc.)
- Same or similar, but with at least one \[L1-L3\] pair somewhere in the middle, to experiment with man-in-the-middle attacks ?
- ?

### 2026/04/28
Still in early drafting staged, but it's starting to have some structure.
Added generic layer entities, MAC and IP addresses - well at least basic functionalities -, and some other stuff I guess.
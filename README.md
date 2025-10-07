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
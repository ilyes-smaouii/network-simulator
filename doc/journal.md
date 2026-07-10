# 2025-08-18
Created the repo
# 2025-10-04
Started to think a bit about some approaches I could take on here.
\
Update : found out some projects with a similar premise already exist. Doesn't change much though,
this was mostly meant as project for personal learning and exploration.

# 2026-04-20
Starting up again

# 2026-04-24
Some ideas for use cases :
- \[L1-L7\] device communicating with another \[L1-L7\] device, with several [L3] devices in-between. Simple HTTP exchange should be enough.
  - Allows to test for everything, and particulary L3
  - Config files for L3 network topology ?
- Same or similar, but with at least one \[L1-L3\] pair somewhere in the middle, to experiment with changing network conditions (intereferences, etc.)
- Same or similar, but with at least one \[L1-L3\] pair somewhere in the middle, to experiment with man-in-the-middle attacks ?
- ?

# 2026-04-28
Still in early drafting staged, but it's starting to have some structure.
Added generic layer entities, MAC and IP addresses - well at least basic functionalities -, and some other stuff I guess.

# 2026-05-11
Haven't written here in a long time, but I've been writing some code, and mostly pondering about paradigm/architecture choices, and it's maybe not as straightforward as I initially expected. Mainly :
- Do the Entities I implement communicate directly with each other using designated functions, or do they pass messages via a Handler, which takes care of "connecting" the different Entities with each other, and dipatching messages properly ?
- Do I use the call chains/the call stack for propagating messages, or do I use some sort of event loop ?
- Do I make the program single threaded or multi-threaded ?
- What kind of Messages do different Entities use to transmit data ? Simple buffer whose data gets copied every time it's used ? Adaptable single buffer built with encapsulation in mind ? Some generic class which could add functionality above that of a simple memory buffer ?
- How much is determined at compile time vs. during runtime ?
- For genericity, do I rely more on `concept`s, or do I use base classes and inheritance ?
- How much genericity do I go for in the start before actually implementing my first use case ? (i.e. right balance between premature optimization and iterative approach)
- etc.
\
For example, the way things were going, `IPv4HandlerBase`'s `handleEncapuslatedMsg()`, which would be called from an `IPv4EntityBase`, would possibly process the messsage, and then go on and call another `IPv4EntityBase`'s `handleDecapsulatedMsg`, which would itself go back to calling the handler's `handleEncapuslatedMsg()` function, and so on and so forth. While relatively simple to implement, this would result in a growing call stack, which doesn't seem ideal. I'm thus now considering switching to some sort of event loop.
\
\
For now, this reasoning mostly happens in my mind, but it's starting to be a lot, and I should probably start to organize it written form, at least on paper or something.
\
Anyway, I started this project mostly with the intent of learning about different topics - software architecture, networking protocols, threading, etc. - , so as long as I learn something and make some progress, all these challenges are welcome.

# 2026-06-08
Another idea/thought I've had : should I keep the layers-oriented architecture, or switch to a more generic one ? \
Maybe make the `Handler` the entity that manages/checks interfaces rather than using concepts/other stuff in the rest of the code ?

# 2026-07-10
Currently reorganizing my files. \
Created a `doc/` folder to contain the journal, potentially a roadmap, some documentation and any such documents that are not actual code and can help approach the project. \
Created a distinct `journal.md` file for the journal and moved previous entries from `README.md` to that file. \

# Roadmap/things to work on
- Simulation engine
  - Scheduler ?
  - Event format and functionality to be specified
  - ?
- [TBC]

# Personal notes
- Should be as modular as possible
  - If a layer N module can work without depending on lower layers, this allows 
me to, say, start working on UDP without having to work on Ethernet/MAC/other
first.
- Layers obviously make assumptions on lower/other layers. So can protocols !
- Allow for debugging/research/introspection functionality. e.g. allow for artificial latency
- Roadmap, design choices, notes, big TO-DO's, etc. --> ?
- Use cases --> ?
- License ?
- entity_traits<> struct ?
- Dynamic traits ? (e.g. use an MTU that can change during runtime) --> for max code flexibility, need to use as many functions as possible (make it static/constexpr if needed)

# Ideas/things to explore
- Impact of physical medium/other layers on applications
- Simple transmission, transmission w/ tracking of a few things
- Capabilities framework (protocol wise) (e.g. whether or not an entity is thread safe, or more specifically which functions are thread-safe ?)
- Automated abstraction of entities/layers --> program runs detailed simulation first, makes some specific measurements, and uses those measurements to run a simulation with a higher layer of abstraction (e.g. rate of packet loss, or latency distribution)
- Create custom protocols
- Using static methods vs. objects (probably depends on data reuse, considering memory/data is main differentiating factor between the two)
- Figure out types of capabilities/specs : protocol specs (functional POV), class specs (e.g. thread safety), etc.
- ?
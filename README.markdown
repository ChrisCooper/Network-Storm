<h1>NetworkStorm</h1>
<p>NetworkStorm is an application which generates interesting audio from network traffic statistics on your computer.</p>
<p>This project is on <a href="https://www.pivotaltracker.com/projects/402735">
Pivotal Tracker: Network Storm.</a></p>
<h2> Dependencies </h2>
pcap

<h2>Todos</h2>
- Investigate audio libraries
    - OpenAL
        - Library specialized in 3D playback for games
        - High density of code jargon, most of which is easily hideable. 
          Otherwise, fairly understandable flow
        - No/hidden audio synthesis
    - irrKlang:
        - Library specialized 3D playback and basic effects. Optimized for games
        - Extremely simple usage
        - No low-level audio synthesis
    - STK
        - Low level audio processing
    - PortAudio
        - Low-level audio processing, can do I/O
        - Somewhat complicated, doesn't seem to handle real-time well
- Write some test apps for audio libraries
- Wrapper around pcap and audio libraries
- Determine desirable mapping of packets to sound to direct interface design

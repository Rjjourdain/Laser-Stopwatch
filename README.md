# Laser Stopwatch
Requires an Arduino, two photocells, sd card, sd shield, and two lasers. The lasers when pointed on a photocell cause the photocell to read a high value. When an object passes through the laser, thus blocking the light from hitting the photocell, the photocell will read a low value. This is used as the start/stop signal for the stopwatch. This code also records the elapsed time for an object to pass thru both lasers and writes it to an sd card.

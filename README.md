# ConPianist

**ConPianist** or **Connected Pianist** is an app to control Yamaha digital pianos of CSP (Clavinova Smart Piano) series. This is an alternative to Yamaha's own app "Smart Pianist". As opposite to Smart Pianist, which works on iOS and Android, Connected Pianist is designed for desktop systems - macOS, Windows and Linux.

## Features

At current stage it is a no replacement for official app. Nonetheless the program can:
- connect to piano via network (but can't connect via USB cable);
- upload midi-files to piano;
- playback control of uploaded midi-files (start, pause, position);
- stream lights control (on, off);
- guide mode control (on, off);
- select parts (backing, left hand, right hand);
- playback selected fragment;
- volume, tempo, transpose;
- select voices (all seven hundreds) for main, left and layer;
- show scores with correct playback position - scores must be loaded from a separate muscixml-file (can't show scores directly from midi-file).

## Screenshots

![Playback with scores](https://user-images.githubusercontent.com/3368402/64079783-1b11a480-ccec-11e9-9511-b94286b3855a.png)

![Voice selection](https://user-images.githubusercontent.com/3368402/64079788-206eef00-ccec-11e9-9fe7-bc7ece795525.png)

## Acknowledgements

The source code of ConPianist includes following libraries:
- [Lomse](https://github.com/lenmus/lomse) to display scores;
- [Arduino AppleMIDI Library](https://github.com/lathoub/Arduino-AppleMIDI-Library) to communicate with piano via network.

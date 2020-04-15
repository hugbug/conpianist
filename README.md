# ConPianist

**ConPianist** or **Connected Pianist** is an app to control Yamaha digital pianos of CSP (Clavinova Smart Piano) series. This is an alternative to Yamaha's own app "Smart Pianist". Unlike Smart Pianist, which works on iOS and Android, Connected Pianist is designed for desktop systems - macOS, Windows and Linux. It works on iPad too though.

## Features

The program is not an adequate replacement for the official app yet. Nonetheless the program already can:
- connect to piano via network or cable;
- connect/reconnect without losing piano state: the program reads whole piano state on start and indicates it in the UI;
- upload midi-files to piano via network (but can't upload via USB cable);
- playback control of uploaded midi-files: start, pause, position;
- stream lights control: on, off, slow, fast;
- guide mode control: on, off, guide mode;
- select parts: backing, right hand, left hand;
- playback selected fragment in a loop;
- volume, tempo, transpose;
- select voices (all seven hundreds) for main, left and layer;
- octave shift and split point (main/left) setting;
- mixer with all classic functions: midi-channels on/off, volume, pan, reverb, reverb effect;
- extra functions in mixer: part selection for midi-channels, voice selection directly from midi-channels;
- balance for main/left/layer/song/mic/auxin: volume, pan, reverb, reverb effect;
- show scores with correct playback position: scores must be provided in a separate muscixml-file (can't show scores directly from midi-file).

## Screenshots

![Playback with scores](https://user-images.githubusercontent.com/3368402/79354560-d8c86b00-7f3c-11ea-8710-9c948982de3a.png)

![Voice selection](https://user-images.githubusercontent.com/3368402/79360975-f699ce00-7f44-11ea-8aa1-803be03533d7.png)

![Mixer](https://user-images.githubusercontent.com/3368402/79354913-4ffdff00-7f3d-11ea-8bf9-0ecda2180204.png)

## Acknowledgements

The source code of ConPianist includes following libraries:
- [Lomse](https://github.com/lenmus/lomse) to display scores;
- [Arduino AppleMIDI Library](https://github.com/lathoub/Arduino-AppleMIDI-Library) to communicate with piano via network.

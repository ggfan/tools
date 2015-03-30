Google Nearby Connections C++ Samples
============================================================================
Copyright (C) 2015 Google Inc.

##Contents##

NearbyConnectionsNative: The sample demonstrates real time
multiplayer game on [C++ Nearby Connection interface SDK](https://developers.google.com/games/services/cpp/nearby).
*Create nearby_connection interface gpg::NearbyConnections::Builder
*Connect to other peers via StartAdvertising(), StartDiscovery()
*Send messages with SendReliableMessage() and SendUnreliableMessage()
*Clean up Google Nearby Connection with Stop()
*Other in-game communication like relaying connections/messages

##How to run a sample##

For generic play game related instruction, please follow steps described in [Getting Started for C++](https://developers.google.com/games/services/cpp/GettingStartedNativeClient)

For this specific demo,simple steps:
1. Build App
2. Install on phone
3. Set ONE and ONLY ONE phone/device to be advertising first
4. All other devices to be discovering after advertising is ready (indicator is "stop" button is enabled)
5. Monitor bottom of the UI for "Connected Clients"; once anyone connected, it should be bigger than 0, "Play Game" is enabled; From that, you could play it at any time
6. while playing, your own score and other player's score should be visible to you at the bottom of the screen
       note: play time is 30 second by default, set in GAME_DURATION in header file

##Support##

First of all, take a look at our [troubleshooting guide](https://developers.google.com/games/services/android/troubleshooting). Most setup issues can be solved by following this guide.

If your question is not answered by the troubleshooting guide, we encourage
you to post your question to [stackoverflow.com](stackoverflow.com). Our
team answers questions there reguarly.

//
// Created by nicolas on 8/30/24.
//

#include "../include/MainProtocol.h"

void MainProtocol::handleProtocol() {
    //TODO
    //1) Open Gossip Connection
    //2) First Gossip announce
    //3) send Gossip notify
    //4) Start Async loops
    //  -broadcastloop, notification loop
    //5) Create main event loop
    //6) bind and start APIServer (NSEServer)
    //7) run event loop forever
    //8) OnKey interrupt stop server
}

//Alternitive (indian guy)
// 1) gossip.define socket
// 2) Open connection to gossip
// 3) create (nse) - protocol handler
//      3.1) create Pow
//      3.2) calc time
//      3.3) form messages
// 4) Gossip notify
// 5) get msg and encrypt it
// 6) Gossip announce
// 7) ensure future -> Periodic Broadcast (every 50-60 secs)
// 8) wait for gossip notification
// 8) create event loop
// 9) start NSEServer
// 10) ensure future -> Gossip handler
// 11) run until key interrupt


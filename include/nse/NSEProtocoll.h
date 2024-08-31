//
// Created by nicolas on 8/30/24.
//

#ifndef NSEPROTOCOLL_H
#define NSEPROTOCOLL_H

class NSEProtocoll {

public:

    //Protocoll stuff
    bool forward(int delay);
    void broadcast();
    void handle_notifications();

    //NSE algorithm stuff
    bool update_msg();
    bool validate_msg();
};

#endif //NSEPROTOCOLL_H
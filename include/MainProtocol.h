//
// Created by nicolas on 8/30/24.
//

#ifndef MAINPROTOCOL_H
#define MAINPROTOCOL_H

class MainProtocol {

public:
    void forward(int delay);
    void broadcast();
    void handle_notifications();

    void handleProtocol();


private:
    int m_frequency = 3600;

    //TODO add NSEHandle

};

#endif //MAINPROTOCOL_H

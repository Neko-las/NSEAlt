//
// Created by nicolas on 8/25/24.
//

#ifndef GOSSIPCLIENT_H
#define GOSSIPCLIENT_H

#include <boost/asio.hpp>
#include <nse/NSEAlgorithm.h>

using boost::asio::ip::tcp;

class GossipClient {
public:
    GossipClient(const std::string& address, int port, NSEHandler& handler);

    void startBroadcastLoop();

    void startNotificationLoop();

    void waitForCompletion();

private:
    boost::asio::io_context m_io_context;
    tcp::socket m_socket;
    std::thread m_broadcast_thread;
    std::thread m_notification_thread;
    const std::string& m_address;
    int m_port;
    NSEHandler& m_handler;

    void connectToGossipModule(const std::string& address, int port);

    void broadcastLoop();
    void notificationLoop();

};

#endif //GOSSIPCLIENT_H

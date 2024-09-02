//
// Created by nicolas on 8/25/24.
//

#include "gossip/GossipClient.h"

#include <iostream>
#include <thread>

#include "security/CryptoUtils.h"
#include "util/utils.h"

GossipClient::GossipClient(const std::string &address, int port, NSEHandler& handler) : m_address(address), m_port(port), m_io_context(),m_socket(m_io_context), m_handler(handler){
    connectToGossipModule(address, port);
}

void GossipClient::broadcastLoop() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Broadcast loop running..." << std::endl;

        //Calulate time to next round and wait
        auto now = std::chrono::system_clock::now();
        auto next_hour = std::chrono::time_point_cast<std::chrono::hours>(now) + std::chrono::hours(1);
        auto duration_until_next_hour = std::chrono::duration_cast<std::chrono::seconds>(next_hour -now);
        auto deltaseconds = duration_until_next_hour.count();
        std::this_thread::sleep_for(std::chrono::seconds(deltaseconds));

        //New round -> so append old round message to history + create a new message
        m_handler.append_msg_to_history();
        m_handler.create_round_msg();

        //New round started, append old best round message to history and create new round message
        Message current_msg_hash = m_handler.getMsg();
        current_msg_hash = sha256(current_msg_hash);

        // Calculate flood delay and wait until reached
        int startingdelay = create_flood_delay();  // Replace with actual logic
        //std::this_thread::sleep_for(std::chrono::seconds(startingdelay));

    }
}

void waitUntilNextRound() {

}

void GossipClient::notificationLoop() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Notification loop running..." << std::endl;
    }
}

void GossipClient::startBroadcastLoop() {
    m_broadcast_thread = std::thread([this]() {
        GossipClient::broadcastLoop();
    });
}

void GossipClient::startNotificationLoop() {
    m_notification_thread = std::thread([this]() {
        GossipClient::notificationLoop();
    });
}

void GossipClient::waitForCompletion() {
    if(m_broadcast_thread.joinable()) {
        m_broadcast_thread.join();
    }

    if(m_notification_thread.joinable()) {
        m_notification_thread.join();
    }
}


void GossipClient::connectToGossipModule(const std::string& address, int port) {
    try {
        tcp::resolver resolver(m_io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(address,std::to_string(port));
        boost::asio::connect(m_socket,endpoints);
        std::cout << "Connected to Gossip Module at " << address << ":" << port << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
    }
}








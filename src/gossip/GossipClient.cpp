//
// Created by nicolas on 8/25/24.
//

#include "gossip/GossipClient.h"

#include <iostream>
#include <thread>

GossipClient::GossipClient(const std::string &address, int port) : m_address(address), m_port(port), m_io_context(),m_socket(m_io_context) {
    connectToGossipModule(address, port);
}

void GossipClient::broadcastLoop() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Broadcast loop running..." << std::endl;
    }
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








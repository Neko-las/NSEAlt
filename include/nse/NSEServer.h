//
// Created by nicolas on 8/25/24.
//

#ifndef NSESERVER_H
#define NSESERVER_H

#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <nse/NSEAlgorithm.h>

class NSEServer {
public:
    NSEServer(boost::asio::io_context& io_context, int port, NSEHandler& handler);
    void start();
    void stop();

private:
    void do_accept();
    void handle_request(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::io_context& m_io_context;
    std::optional<boost::asio::ip::tcp::socket> m_socket;
    NSEHandler& m_handler;
};

#endif //NSESERVER_H

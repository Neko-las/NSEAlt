//
// Created by nicolas on 8/25/24.
//

#include "nse/NSEServer.h"
#include "nse/NSEAlgorithm.h"

NSEServer::NSEServer(boost::asio::io_context &io_context, int port,NSEHandler& handler)
    :   m_io_context(io_context),
        m_acceptor(io_context,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port)),
        m_handler(handler){}

void NSEServer::start() {
    std::cout << "\nStartet NSE Server on Port " << m_acceptor.local_endpoint().port() << "!" << std::endl;
    do_accept();
}

void NSEServer::stop() {
    m_acceptor.close();
    std::cout << "NSE Server Stopped." << std::endl;
}

void NSEServer::do_accept() {
    //auto socket = std::make_shared<boost::asio::ip::tcp::socket>(m_acceptor.get_executor().context());
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(m_io_context);

    m_acceptor.async_accept(*socket,[this, socket](const boost::system::error_code& error){
        if (!error) {
            handle_request(socket);
        }else {
            std::cout << "Error connecting to NSE Server";
        }
        do_accept();
    });
}

void NSEServer::handle_request(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
    auto buffer = std::make_shared<std::vector<char>>(8);
    boost::asio::async_read(*socket,boost::asio::buffer(*buffer),[this, socket, buffer](const boost::system::error_code& error, std::size_t length){
        if(!error && length == 0) {
            std::string addr = socket->remote_endpoint().address().to_string();
            std::cout << "\n Recieved NSE query from" << addr << std::endl;


            if(m_handler.validate_query(*buffer)) {
                std::cout << "NSE query is valid, sending estimation!" << std::endl;
                std::string nse_estimate = m_handler.nse_estimate();

                boost::asio::async_write(*socket,boost::asio::buffer(nse_estimate),[socket](const boost::system::error_code& error, std::size_t length) {
                    socket->close();
                });
            }else {
                std::cout << "NSE Query not valid, closing the connection!" << std::endl;
                socket->close();
            }
        }else {
            socket->close();
        }
    });
}




#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include <MainProtocol.h>
#include <string>
#include "gossip/GossipClient.h"
#include "nse/NSEServer.h"
#include "util/ConfigParser.h"

void handleProtocoll() {
    //Message Types
    int gossip_notification = 502;
    int nse_query_dtype = 520;
    int nse_estimate_dtype = 521;
    int nse_msg_dtype = 530;

    int freq = 3600;
    const std::string& gossip_api_address = "127.0.0.1";
    int gossip_api_port = 6001;
    GossipClient gossip_client(gossip_api_address,gossip_api_port);

}

int main() {
    std::cout << "Hello, World!" << std::endl;

    ConfigParser parser;

    if(parser.parse("config.ini")) {
        std::cout << "Gossip cache_size: " << parser.getInt("gossip","cache_size") << std::endl;
    }

    try {
        boost::asio::io_context io_context;

        boost::asio::signal_set signals(io_context,SIGINT, SIGTERM);
        signals.async_wait([&io_context] (boost::system::error_code ec,int signo) {
            std::cout <<"\nServer stopping due to signal...\n";
            io_context.stop();
        });

        NSEHandler handler{};
        NSEServer server(io_context,7201,handler);
        server.start();

        std::thread io_thread([&io_context]() {
            io_context.run();
        });

        handleProtocoll();

        io_thread.join();

        return 0;
    }
    catch (std::exception& e) {
        std::cerr <<"Exception: " << e.what() << std::endl;
    }


    //boost::thread t(handleProtocoll);

    //t.join();
    return 0;
}

void forward(int delay,std::string currentRoundMessage) {

}



//
// Created by nicolas on 8/25/24.
//

#ifndef GOSSIPMESSAGETYPE_H
#define GOSSIPMESSAGETYPE_H

namespace gossip {

    std::string announce(int ttl, int data_type, const std::string& data) {
        std::ostringstream oss;
        oss << "GOSSIP ANNOUNCE\n";
        int announce = 500;
        int res = 0;
        int size = 8 + data.size();
        oss << std::setw(2) << std::setfill('0') << size;
        oss << std::setw(2) << std::setfill('0') << announce;
        oss << std::setw(2) << std::setfill('0') << ttl;
        oss << std::setw(2) << std::setfill('0') << res;
        oss << std::setw(2) << std::setfill('0') << data_type;
        oss << data;
        return oss.str();
    }

    std::string notify(int data_type) {
        std::ostringstream oss;
        oss << "GOSSIP NOTIFY\n";
        int notify = 501;
        int res = 0;
        int size = 8;
        oss << std::setw(2) << std::setfill('0') << size;
        oss << std::setw(2) << std::setfill('0') << notify;
        oss << std::setw(2) << std::setfill('0') << res;
        oss << std::setw(2) << std::setfill('0') << data_type;
        return oss.str();
    }

    std::string validation(int id, bool valid) {
        std::ostringstream oss;
        oss << "GOSSIP VALIDATION:\n";
        int validation = 503;
        int size = 8;
        int res = valid ? 1 : 0;
        oss << std::setw(2) << std::setfill('0') << size;
        oss << std::setw(2) << std::setfill('0') << validation;
        oss << std::setw(2) << std::setfill('0') << id;
        oss << std::setw(2) << std::setfill('0') << res;
        return oss.str();
    }

}

#endif //GOSSIPMESSAGETYPE_H

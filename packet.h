#ifndef PACKET_H
#define PACKET_H

#include "address.h"
#include <string>
#include <vector>

class Packet {
public:
  Packet(Address srcAddress, Address destAddress, short srcPort, short destPort,
         std::string data)
      : srcAddress_(srcAddress), destAddress_(destAddress), srcPort_(srcPort),
        destPort_(destPort) {
    for (size_t i = 0; i < data.size(); i++) {
      data_.push_back(data[i]);
    }
  }

  Packet(Address srcAddress, Address destAddress, short srcPort, short destPort,
         std::vector<char> data)
      : srcAddress_(srcAddress), destAddress_(destAddress), srcPort_(srcPort),
        destPort_(destPort), data_(data) {}

  // 전송자 주소
  Address srcAddress() { return srcAddress_; }

  // 수신자 주소
  Address destAddress() { return destAddress_; }

  // 전송자 포트
  short srcPort() { return srcPort_; }

  // 수신자 포트
  short destPort() { return destPort_; }

  // 패킷 데이터
  const std::vector<char> &data() { return data_; }

  // 패킷 데이터를 문자열로 변환한다
  std::string dataString() {
    std::string str;
    for (size_t i = 0; i < data_.size(); i++) {
      str += data_[i];
    }
    return str;
  }

private:
  Address srcAddress_;
  Address destAddress_;
  short srcPort_;
  short destPort_;
  std::vector<char> data_;
};

#endif
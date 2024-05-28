#ifndef IP_H
#define IP_H

#include <string>

// 주소를 나타내는 클래스
class Address {
private:
  std::string address_;

public:
  Address(const std::string &address) : address_(address) {}
  Address(int address) : address_(std::to_string(address)) {}
  std::string toString() const { return address_; }
  bool operator==(const Address &rhs) const { return address_ == rhs.address_; }
};

#endif
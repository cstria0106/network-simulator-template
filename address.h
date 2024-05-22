#ifndef IP_H
#define IP_H

#include <string>

// 주소를 나타내는 클래스
class Address {
private:
  int address_;

public:
  Address(int address) : address_(address) {}
  std::string toString() const { return std::to_string(address_); }
  bool operator==(const Address &rhs) const { return address_ == rhs.address_; }
};

#endif
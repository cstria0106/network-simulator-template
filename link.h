#ifndef LINK_H
#define LINK_H

#include "packet.h"
#include <cstdlib>

class Node;

class Link {
  friend class LinkInstaller;

private:
  Link(Node *nodeA, Node *nodeB) : nodeA_(nodeA), nodeB_(nodeB) {}

  Node *nodeA_;
  Node *nodeB_;

  Node *other(const Node *node) const {
    return node == nodeA_ ? nodeB_ : nodeA_;
  }
};

#endif
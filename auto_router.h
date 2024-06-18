#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>

class AutoRouter : public Router {
public:
  void calculate(const std::vector<Node *> &nodes,
                 const std::vector<Link *> &links) {
    // node a, node b, node c, node d
    // a <- link a (1.0) -> b
    // b <- link b (2.0) -> c

     // 어떤 노드에서, 다른 노드로 최소거리로 갈수있는, 다음 홉 

    double matrix[10000][10000];

    for(int i = 0; i < nodes.size(); i++) {
      for(int j = 0; j < nodes.size(); j++) {
        Node* a = nodes[i];
        Node* b = nodes[j];

        matrix[i][j] = 99999999;
        for(int k = 0; k < links.size(); k++) {
          Link* l = links[k];
          if(l->nodeA() == a && l->nodeB() == b) {
            matrix[i][j] = l->delay();
          }
        }
      }
    }
    
    // 다익스트라를 돌리면서 호스트에 대한 최소경로로 갈수잇는 다음 홉을 기록
    for(int i = 0; i < nodes.size(); i++) {
      Node* node = nodes[i];
      Host* host = dynamic_cast<Host*>(node);
      if(host == nullptr) {

      }
    }

  }
};

#endif
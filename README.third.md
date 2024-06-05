다음 링크를 통해 코드 변경점 확인하여 수정

https://github.com/cstria0106/network-simulator-template/compare/second...third

## 변경점

### 추가

- Firewall 구현
- NAT 구현

### 수정

- 모든 시나리오 코드 업데이트 (코드 복사하여 수정)
- Object 클래스 수정 (코드 복사하여 수정)

## 클래스

### Firewall

패킷을 규칙에 따라 통과시키거나 드롭하는 방화벽이다. Policy는 화이트리스트 형태로 구성된다. 즉 하나의 Policy만 만족시키더라도 통과할 수 있다. setReceiveLink로 설정된 링크에서 패킷이 오면 등록된 Policy를 검사하여 패킷을 반대편 링크로 보낼지 드롭할지 결정한다.

Firewall에 연결되는 링크는 receiveLink와 반대편 링크 두 개라고 가정한다. initialize 함수로 이를 검사하는 코드를 넣을수도 있다 (필수는 아님)

### Nat

LAN과 WAN 사이에서 사설 주소와 공인 주소 간의 적절한 변환을 도와주는 NAT 노드이다. WAN 링크 하나와 LAN 링크 여러 개를 가지며, setWanLink 함수로 WAN 링크를 설정할 수 있으며 나머지 링크는 LAN 링크로 취급된다.

LAN 링크에서 패킷이 도달하는 경우 패킷의 출발지 주소와 출발지 포트를 적절히 변환한 패킷을 WAN 링크로 내보낸다.

WAN 링크에 패킷이 도달하는 경우 패킷의 도착지 주소와 도착지 포트를 적절히 변환한 패킷을 모든 LAN 링크로 내보낸다 (Broadcast).

## 출력 예시

bin 폴더에 있는 바이너리를 실행해 확인할 것

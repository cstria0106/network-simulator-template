# 네트워크 시뮬레이터

네트워크 시뮬레이터를 구현하고자 한다.


## 클래스

### Node
링크로 연결할 수 있는 장치를 나타낸 클래스다. id를 가지며 Node를 생성할 때마다 1씩 증가한다. (id는 이미 구현돼있다.)

### Host
우리가 일반적으로 사용하는 컴퓨터와 같이 네트워킹이 가능한 기기를 나타낸 클래스다. 하나의 주소를 가지며 여러 링크를 가지지만, 패킷 전송 시 하나의 링크를 랜덤으로 골라 전송한다.

### Service
Host에 설치된 프로그램을 나타낸 클래스다. 하나의 포트를 사용하며, 패킷을 생성하여 전송하거나 자신에게 온 패킷을 처리한다.

### Router
라우터를 나타낸 클래스다. 패킷을 받으면 라우팅 테이블에 따라 패킷을 다음 링크로 전송한다. 패킷을 포워딩할 때 다음과 같이 출력한다.

```
Router #2: forwarding packet (from: 1, to: 0, 13 bytes)
```

### ManualRouter
라우팅 테이블을 직접 설정할 수 있는 클래스다.

### Address
Host의 주소를 저장하는 클래스다.

### Link
Node를 잇는 경로다. 한 Node에서 패킷을 받아 다른 Node로 전달한다. 패킷을 전달할 때 보낸 쪽의 노드와 받는 쪽의 노드 id와 함께 다음과 같이 메시지를 출력한다.
```
Link: forwarding packet from node #1, to node #5
```

### ...Installer
Link와 각 Service를 설치하는 것에 도움을 주는 Helper 클래스다.

### EchoService
받은 패킷을 전송자에게 그대로 다시 전달하는 Service를 나타내는 클래스다. 받은 패킷을 다음과 같이 출력한다.
```
EchoService: received "Hello, world!"
```

### MessageService
send 함수를 호출하여 문자열 데이터를 네트워크로 전송할 수 있는 Service를 나타낸 클래스다. 받은 패킷을 다음과 같이 출력한다.
```
MessageService: received "Hello, world!"
```

## first 시나리오 출력 예시
```
Link: forwarding packet from node #1, to node #5
Router #5: forwarding packet (from: 0, to: 1, 13 bytes)
Link: forwarding packet from node #5, to node #3
Router #3: forwarding packet (from: 0, to: 1, 13 bytes)
Link: forwarding packet from node #3, to node #2
Router #2: forwarding packet (from: 0, to: 1, 13 bytes)
Link: forwarding packet from node #2, to node #0
EchoService: received "Hello, world!"
Link: forwarding packet from node #0, to node #2
Router #2: forwarding packet (from: 1, to: 0, 13 bytes)
Link: forwarding packet from node #2, to node #3
Router #3: forwarding packet (from: 1, to: 0, 13 bytes)
Link: forwarding packet from node #3, to node #5
Router #5: forwarding packet (from: 1, to: 0, 13 bytes)
Link: forwarding packet from node #5, to node #1
MessageService: received "Hello, world!"
Link: forwarding packet from node #1, to node #5
Router #5: forwarding packet (from: 0, to: 1, 11 bytes)
Link: forwarding packet from node #5, to node #3
Router #3: forwarding packet (from: 0, to: 1, 11 bytes)
Link: forwarding packet from node #3, to node #2
Router #2: forwarding packet (from: 0, to: 1, 11 bytes)
Link: forwarding packet from node #2, to node #0
EchoService: received "Bye, world!"
Link: forwarding packet from node #0, to node #2
Router #2: forwarding packet (from: 1, to: 0, 11 bytes)
Link: forwarding packet from node #2, to node #3
Router #3: forwarding packet (from: 1, to: 0, 11 bytes)
Link: forwarding packet from node #3, to node #5
Router #5: forwarding packet (from: 1, to: 0, 11 bytes)
Link: forwarding packet from node #5, to node #1
MessageService: received "Bye, world!"
```

## 과제 조건
- 시나리오 코드를 수정하면 안된다.
- 클래스의 상속 관계를 수정하거나 이미 선언된 함수, 변수의 역할을 변경하거나 삭제해서는 안된다.
- 클래스에 요구사항에 맞는 적절한 코드를 작성해야 한다. (README에서 설명하는 클래스의 설명과 함수에 달린 주석에 맞게 작성)
- 동적 할당으로 사용한 메모리를 적절히 해제해야 한다.
- Makefile에 선언된 CC와 FLAGS를 그대로 사용해야 한다.
- MinGW가 설치된 Windows 환경에서 컴파일, 실행이 가능해야 한다.
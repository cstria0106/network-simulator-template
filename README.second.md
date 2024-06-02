다음 링크를 통해 코드 변경점 확인하여 수정

https://github.com/cstria0106/network-simulator-template/compare/main...second

## 변경점

### 추가

- Object 클래스 추가 (코드 제공)
- AutoRouter 및 라우팅 알고리즘 구현
- Simulator 구현
- BulkSend, PacketSink 구현

### 수정

- Link에 delay 추가
- Node, Link, Packet, Service가 Object를 상속하도록 변경
- 각 클래스에 Object::name 함수를 override하여 작성하고, 기존 cout으로 된 로그를 Object::log 함수로 대체
- Address의 값을 string으로 수정

## 클래스

### Object

네트워크 상에 존재하는 객체를 나타내는 오브젝트. 고유한 id를 가지며 이는 랜덤 4자리 수로 결정된다. log 함수를 제공한다. 또한 CHECK_MEMORY_LEAK 매크로가 정의된 경우 Object::checkMemoryLeak 함수를 호출하여 Object를 상속하는 클래스에 대한 메모리 누수를 검사할 수 있다.

### AutoRouter

다익스트라 알고리즘을 통한 라우팅 알고리즘을 구현하는 라우터이다. calculate 함수를 호출하면 네트워크에 존재하는 모든 호스트로 통하는 최소 경로를 계산하여 라우팅 테이블에 지정한다.

### BulkSendService

정해진 시간동안, 정해진 딜레이마다 512 바이트의 패킷을 전송하는 서비스.

### PacketSinkService

패킷을 받아 누적시켜 총 바이트 수를 출력하는 서비스.

### Simulator

시뮬레이션의 스케줄링을 담당하는 클래스. 코드 전체에서 Simulator::schedule 함수를 통해 함수 실행을 예약할 수 있고, Simulator::time을 통해 시뮬레이터 상의 현재 시간을 알아낼 수 있다.

## 출력 예시

bin 폴더에 있는 바이너리를 실행해 확인할 것

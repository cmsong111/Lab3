# 실습 3. 파일 처리, 프로세스 및 프로세스간 통신

## 1. 실습의 목표

본 실습에서는 리눅스에서 파일 처리, 프로세스 및 프로세스간 통신 기법에 대한 기본 개념
을 확립하고 프로그래밍 및 설계 능력을 갖추는 것이 주요 목표이다.

## 2. 실습에 필요한 기초 지식

본 실습에서는 파일 및 디렉토리 관련 함수들, 리눅스 프로세스와 프로세스간 통신 관련 함
수들에 대한 이해와 지식을 필요로 한다.

## 3. 실습에 필요한 장비

### 하드웨어

1. PC Host Computer

### 소프트웨어

1. 리눅스 사용 환경
2. gcc GNU 컴파일러 패키지
3. make 프로그래밍 도구
4. git 버전 관리 시스템
5. gdb GNU 디버거

## 4. 실습에 필요한 준비 사항

### 1. 파일 처리 함수에 대하여 조사하고 이해한다.

파일 처리 함수는 프로그램에서 파일을 열고 읽거나 쓰는 등의 작업을 수행하는 데 사용됩니다.
파일 처리 함수는 stdio.h 헤더 파일에 선언되어 있습니다.

1. fopen() 함수

   파일을 열기 위해 사용됩니다.
   파일을 열 때는 해당 파일의 경로와 열기 모드를 지정해야 합니다. 열기 모드에는 읽기, 쓰기, 추가하기 등이 있습니다.

   ```c
   FILE *fopen(const char *path, const char \*mode);
   ```

2. fclose() 함수

   파일을 닫습니다. 파일을 열었으면 작업이 끝난 후에 반드시 파일을 닫아야 합니다.

   ```c
   int fclose(FILE \*stream);
   ```

3. fread() 함수

   파일로부터 데이터를 읽습니다.

   ```c
   size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
   ```

4. fwrite() 함수

   데이터를 파일에 씁니다.

   ```c
   size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
   ```

5. fseek() 함수

   파일 내의 위치를 이동시킵니다.

   ```c
   int fseek(FILE \*stream, long offset, int whence);
   ```

6. ftell() 함수

   현재 파일 위치 지정자의 오프셋을 반환합니다.

   ```c
   long ftell(FILE \*stream);
   ```

7. rewind() 함수

   파일 내의 위치를 파일의 처음으로 되돌립니다.

   ```c
   void rewind(FILE \*stream);
   ```

8. feof() 함수

   파일의 끝에 도달했는지 확인합니다.

   ```c
   int feof(FILE \*stream);
   ```

9. remove() 함수

   파일을 삭제합니다.

   ```c
   int remove(const char \*filename);
   ```

### 2. 입출력 장치 파일에 대하여 조사하고 요약하여 보고서에 정리하여 본다.

입출력 장치 파일은 리눅스 시스템에서 하드웨어 장치와 상호 작용하기 위해 사용되는 파일입니다. 이러한 파일들은 /dev 디렉토리에 위치하며, 다양한 장치에 대한 파일이 제공됩니다. 주로 입출력 장치 파일은 문자 장치 파일과 블록 장치 파일로 나뉩니다.

1. 문자 장치 파일(Character Device Files):

   - 문자 장치 파일은 한 번에 하나의 문자(또는 바이트)를 - 처리합니다.
   - 주로 입출력이 시리얼하게 일어나는 장치에 사용됩니다.
   - 예시: 터미널 (/dev/tty), 마우스 (/dev/mouse)

2. 블록 장치 파일(Block Device Files):

   - 블록 장치 파일은 블록 단위로 데이터를 처리합니다. 블록은 여러 바이트의 데이터를 포함하는 고정 크기의 덩어리입니다.
   - 주로 파일 시스템이나 디스크와 같은 장치에 사용됩니다.
   - 예시: 하드 디스크 (/dev/sda), CD-ROM 드라이브 (/dev/cdrom)

3. 일반적인 입출력 장치 파일 및 예시:

   - /dev/null: 모든 데이터를 무시하고 폐기하는 특수한 파일. 출력을 버릴 때 사용됩니다.
   - /dev/zero: 모든 읽기 작업에 0으로 채워진 데이터를 생성하는 파일.
   - /dev/random 및 /dev/urandom: 무작위 데이터를 생성하는 파일. 주로 암호화에 사용됩니다.
   - /dev/tty: 현재 프로세스와 관련된 터미널 파일.
   - /dev/sda1, /dev/sdb2, 등: 디스크 파티션에 대한 블록 장치 파일.

4. 장치 파일 접근 권한 및 소유권:

   - 입출력 장치 파일도 일반 파일처럼 파일 시스템에서 관리되며, 접근 권한과 소유권이 설정됩니다. ls -l 명령어를 사용하여 확인할 수 있습니다.

   ```bash
   $ ls -l /dev/tty
   crw-rw-rw- 1 root tty 5, 0 Nov 16 10:00 /dev/tty
   ```

   여기서 "c"는 문자 장치를 나타내고, "b"는 블록 장치를 나타냅니다. rw-rw-rw-는 읽기와 쓰기 권한이 모든 사용자에게 부여되어 있음을 나타냅니다.

### 3. 교재에서 프로세스 및 시그널에 대한 내용을 읽고 이해한다.

**프로세스(Process)**

프로세스는 실행 중인 프로그램을 나타냅니다. 각 프로세스는 독립적인 메모리 공간과 실행 상태를 가지며, 운영 체제에서 관리됩니다. 프로세스 간 통신을 통해 정보를 교환할 수 있고, 각 프로세스는 고유한 프로세스 ID (PID)를 가지고 있습니다.

프로세스의 주요 특성 및 관련 함수:

- PID (프로세스 ID): 각 프로세스는 고유한 식별자인 PID를 가지고 있습니다.
- 프로세스 생성: fork() 함수를 사용하여 새로운 프로세스를 생성할 수 있습니다.
- 프로세스 종료: exit() 함수를 사용하여 현재 프로세스를 종료할 수 있습니다.
- 프로세스 대기: wait() 함수를 사용하여 자식 프로세스의 종료를 기다릴 수 있습니다.

**시그널(Signal)**

시그널은 프로세스 간에 발생하는 이벤트를 나타냅니다. 예를 들어, 프로세스가 잘못된 명령을 수행하거나 특정 조건이 충족될 때 시그널이 발생할 수 있습니다. 시그널은 이러한 이벤트에 대한 감지 및 처리를 제공합니다.

시그널과 관련된 주요 개념 및 관련 함수:

- 시그널 종류: 예시로는 SIGTERM (프로세스 종료 요청), SIGKILL (프로세스 강제 종료), SIGINT (인터럽트 시그널) 등이 있습니다.
- 시그널 핸들러: 특정 시그널이 발생할 때 실행되는 함수로, 프로세스가 시그널에 대한 반응을 정의할 수 있습니다.
- signal() 함수: 특정 시그널에 대한 핸들러를 등록하는 함수입니다.
- kill() 함수: 특정 프로세스에게 시그널을 보내는 함수입니다.

프로세스와 시그널은 운영 체제에서의 중요한 개념이며, 프로세스 간 통신 및 상태 관리에 큰 역할을 합니다.

### 4. 리눅스의 프로세스 모델과 시그널/쓰레드와의 관계에 대하여 조사하고 요약하여 보고서에 정리하여 본다.

**리눅스의 프로세스 모델**

리눅스에서 프로세스는 실행 중인 프로그램을 나타냅니다. 각 프로세스는 고유한 프로세스 ID(PID)를 가지며, 독립적인 메모리 공간을 갖고 있습니다. 리눅스는 다양한 프로세스 간 통신 기법을 제공하여 프로세스들이 정보를 교환할 수 있도록 합니다.

주요 특징

- 각 프로세스는 자체적인 메모리 공간, 파일 디스크립터, 환경 변수 등을 가짐
- 프로세스 간 통신(IPC)을 위해 파이프, 소켓, 메시지 큐, 공유 메모리 등의 기법을 사용.

**시그널과 프로세스의 관계**

시그널은 리눅스에서 프로세스 간 통신 및 상태 관리에 사용되는 중요한 메커니즘입니다. 시그널은 특정 이벤트가 발생했음을 알리기 위해 사용되며, 예를 들어 프로세스 종료, 사용자 입력 (Ctrl+C), 혹은 다른 프로세스로부터의 메시지 등이 해당됩니다.

주요 특징

- kill 명령어나 프로그램에서 kill() 함수를 사용하여 특정 프로세스에 시그널을 보낼 수 있음.
- 프로세스는 시그널에 대한 행동을 정의하기 위해 시그널 핸들러를 등록할 수 있음.
- 일부 일반적인 시그널은 SIGTERM (프로세스 종료 요청), SIGKILL (프로세스 강제 종료), SIGINT (인터럽트 시그널) 등이 있음.

**쓰레드와의 관계**

리눅스에서 쓰레드는 경량 프로세스로 간주됩니다. 쓰레드는 동일한 프로세스 내에서 공유 메모리 공간을 가지며, 각 쓰레드는 고유한 스택을 가지고 있습니다. 쓰레드 간 통신은 주로 공유 메모리를 통해 이루어집니다.

주요 특징

- 쓰레드는 프로세스 내의 여러 실행 흐름을 나타냄.
- 쓰레드 간 통신은 공유 메모리를 통해 이루어지며, 동기화가 필요한 경우에는 세마포어, 뮤텍스 등을 사용할 수 있음.
- 시그널은 프로세스나 쓰레드 간의 통신에서 이벤트를 전달하는데 사용될 수 있음.

리눅스에서는 프로세스와 쓰레드 간의 관계를 통해 다양한 병렬 프로그래밍 및 통신 기법을 지원하고 있습니다. 이러한 메커니즘들은 프로그래머가 효율적으로 자원을 활용하고 다양한 작업을 동시에 수행할 수 있도록 돕습니다.

### 5. 교재에서 프로세스 간 통신에 대한 내용을 읽고 이해한다.

**파이프 (Pipe)**

- 설명

  단방향 통신을 지원하는 가장 간단한 IPC 메커니즘 중 하나입니다. 부모 프로세스와 자식 프로세스 간에 통신에 사용됩니다.

- 특징

  파이프는 파일 디스크립터로 표현되며, 부모와 자식 사이에 생성됩니다.
  pipe() 시스템 호출을 사용하여 생성하며, read()와 write() 함수를 통해 데이터를 읽고 쓸 수 있습니다.

**메시지 큐 (Message Queue)**

- 설명

메시지 큐는 여러 프로세스 간에 메시지를 교환하는 데 사용됩니다. 메시지 큐는 큐 형태의 버퍼를 가지고 있어 여러 유형의 데이터를 전송할 수 있습니다.

- 특징

msgget(), msgsnd(), msgrcv()와 같은 시스템 호출을 사용하여 생성 및 조작됩니다.
각 메시지는 메시지 유형, 데이터, 우선 순위 등의 정보를 포함합니다

**세마포어 (Semaphore)**

- 설명

프로세스 간의 동기화를 제어하기 위한 카운터입니다. 주로 공유 자원의 접근을 제한하거나 특정 이벤트를 동기화하는 데 사용됩니다.

- 특징

semget(), semop(), semctl()과 같은 시스템 호출을 사용하여 생성 및 조작됩니다.
상호 배제 및 동기화에 사용되며, 공유 메모리와 함께 사용되기도 합니다.

### 6. 리눅스에서 비동기 통신 기법에 대하여 조사하고 요약하여 보고서에 정리하여본다.

리눅스에서 비동기 통신은 여러 프로세스 또는 스레드가 동시에 실행되는 환경에서 데이터를 교환하고 통신하는 기법을 의미합니다. 비동기 통신은 블로킹과 논블로킹 방식으로 나뉘며, 다양한 기법들이 사용됩니다.

**파일 입출력의 비동기 통신**

- 블로킹 파일 입출력

open(), read(), write() 등의 시스템 호출을 사용하여 파일을 열고 읽고 쓰는 것은 블로킹 방식입니다.
프로세스는 파일 입출력 작업이 완료될 때까지 대기합니다.

- 논블로킹 파일 입출력

O_NONBLOCK 플래그를 사용하여 파일을 논블로킹 모드로 열면, 입출력 작업이 끝나지 않아도 프로세스는 블로킹되지 않고 다른 작업을 수행할 수 있습니다.
open() 시에 O_NONBLOCK 플래그를 사용하거나 fcntl() 함수를 통해 런타임에 설정할 수 있습니다.

**비동기 신호 (Asynchronous Signals)**

리눅스에서 프로세스는 다른 프로세스나 커널에 의해 비동기적으로 신호를 받을 수 있습니다.
signal() 함수를 사용하여 특정 시그널에 대한 핸들러를 등록하고, 프로세스는 해당 신호를 받으면 등록된 핸들러가 실행됩니다.
대표적인 예시는 SIGIO 신호로, 파일 디스크립터에 대한 비동기 I/O 이벤트를 처리할 수 있습니다.

**비동기 입출력 (Asynchronous I/O, AIO)**

aio_read(), aio_write() 함수 등을 사용하여 비동기적으로 파일을 읽고 쓸 수 있습니다.
프로세스는 I/O 작업이 완료될 때까지 블로킹되지 않고 다른 작업을 수행할 수 있습니다.
주로 디스크 I/O나 네트워크 I/O에서 사용되며, aio_suspend() 함수를 통해 작업 완료를 기다릴 수 있습니다.

**epoll**

epoll은 리눅스에서 사용되는 I/O 이벤트 통지 메커니즘 중 하나입니다.
다수의 파일 디스크립터에 대해 이벤트를 모니터링하고 발생한 이벤트에 대해 비동기적으로 대응할 수 있습니다.
epoll_ctl(), epoll_wait() 함수 등을 사용하여 구현됩니다.

**비동기 소켓 (Asynchronous Sockets)**

- 소켓 통신에서도 비동기 방식을 지원합니다.
- fcntl() 함수나 select(), poll(), epoll 등을 사용하여 비동기적으로 소켓 이벤트를 처리할 수 있습니다.

리눅스에서 비동기 통신은 여러 기법을 통합적으로 사용하여 구현됩니다. 파일 입출력, 신호, AIO, epoll 등을 조합하여 특정 상황에 적합한 비동기 통신 방식을 선택할 수 있습니다.

## 5. 실습 순서

1. 자신의 github 저장소에 lab3 프로젝트를 생성하고 아래의 모든 과제 프로그램
   을 업로드한다.
2. 파일 및 디렉토리와 관련된 함수들을 사용하여 프로그램을 작성하고 실행하여
   보고, 익숙해지도록 사용해 본다.
3. 주어진 디렉토리 내에 존재하는 파일과 디렉토리를 나열하고, 디렉토리의 경우
   재귀적으로 방문해서 그 디렉토리 내에 존재하는 파일과 디렉토리를 나열하는
   프로그램을 작성하시오. 즉, “ls –R” 명령과 동일한 결과를 보이도록 하시오.
4. 몇 개의 문장을 타자하도록 하여 잘못 타이핑한 횟수와 평균 분당 타자수를 측
   정하는 타자 연습 프로그램을 구현하여 보시오.
5. 프로세스와 관련된 함수들을 사용하여 프로그램을 작성하고 실행하여 보고, 익
   숙해지도록 사용해 본다.
6. system 함수는 쉘 명령이 실행되도록 하는데, 예를 들면, system("ls -la") 을
   호출하면, 현재 디렉토리의 파일들을 나열해 준다. 이와 같은 기능을 수행하는
   함수를 직접 구현하여 보자. 또, 이 함수를 이용하는 예제 프로그램을 통해서
   “a.out ls -la" 와 같이 명령이 잘 동작하도록 해 보자.
7. 시그널과 관련된 함수들을 사용하여 프로그램을 작성하고 실행하여 보고, 익숙
   해지도록 사용해 본다.
8. 프로세스 간 통신 함수들을 사용하여 프로그램을 작성하고 실행하여 보고, 익
   숙해지도록 사용해 본다.
9. 메시지 큐를 사용하여 텍스트 기반의 간단한 채팅 프로그램을 구현하시오.
10. 공유 메모리를 사용하여 한 파일을 다른 파일로 복사하는 프로그램을 작성하시
    오. 단, 부모(읽는 프로세스)와 자식(쓰는 프로세스)프로세스가 공유 메모리 영
    역을 동시에 접근하는 일이 없도록 세마포어 같은 동기화 기법을 활용하시오.
11. (팀과제) 간단한 쉘 프로그램을 만들고 다음과 같이 동작하도록 수정하시오.
    1. "exit"를 치면 프로그램을 끝내도록 프로그램을 수정하시오.
    2. csh, bash 등에서처럼 쉘 명령의 마지막에 ‘&’을 입력하면 백그라운드
       로 실행되도록 프로그램을 수정하시오.
    3. csh, bash 등에서처럼 인터럽트키 (SIGINT: Ctrl-C, SIGQUIT: Ctrl-Z)
       가 동작하도록 프로그램을 수정하시오.
    4. 파일 재지향 (>, <) 및 파이프(|) 기능이 가능하도록 프로그램을 수정
       하시오.
    5. ls, pwd, cd, mkdir, rmdir, ln, cp, rm, mv, cat 명령을 팀원이 공평하게
       나누어 구현하시오.

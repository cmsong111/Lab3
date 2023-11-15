#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Ctrl+C를 누르면 호출되는 핸들러 함수
void sigintHandler(int signo) {
    printf("\nCtrl+C가 눌렸습니다. 프로그램을 종료합니다.\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // SIGINT 시그널에 대한 핸들러 등록
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        fprintf(stderr, "시그널 핸들러 등록 실패\n");
        return EXIT_FAILURE;
    }

    printf("Ctrl+C를 눌러보세요. (프로그램은 종료되지 않습니다.)\n");

    // 무한 루프
    while (1) {
        // 작업을 계속 진행하거나 대기
    }

    return 0;
}
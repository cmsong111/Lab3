#include <stdio.h>
#include <unistd.h>

int main() {
    // 부모 프로세스 ID 저장
    pid_t parentPID = getpid();

    // 새로운 프로세스 생성
    pid_t childPID = fork();

    if (childPID < 0) {
        // fork 실패
        fprintf(stderr, "프로세스 생성 실패\n");
        return 1;
    } else if (childPID == 0) {
        // 자식 프로세스
        printf("자식 프로세스 - ID: %d, 부모 프로세스 ID: %d\n", getpid(), parentPID);
        printf("자식 프로세스: 안녕하세요! (PID: %d)\n", getpid());
    } else {
        // 부모 프로세스
        printf("부모 프로세스 - ID: %d\n", getpid());
        printf("부모 프로세스: 안녕하세요! (PID: %d)\n", getpid());
    }

    return 0;
}

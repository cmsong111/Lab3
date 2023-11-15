#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int executeCommand(int argc, char *argv[]) {
    pid_t childPID = fork();

    if (childPID < 0) {
        // fork 실패
        fprintf(stderr, "프로세스 생성 실패\n");
        return -1;
    } else if (childPID == 0) {
        // 자식 프로세스
        execvp(argv[0], argv);
        // execvp 실패 시 아래 코드가 실행됨
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스
        int status;
        waitpid(childPID, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            fprintf(stderr, "자식 프로세스 비정상 종료\n");
            return -1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s <command> [arg1] [arg2] [...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 명령을 실행하는 함수 호출
    int result = executeCommand(argc - 1, &argv[1]);

    if (result == 0) {
        printf("명령이 성공적으로 실행되었습니다.\n");
    } else {
        fprintf(stderr, "명령 실행 중 오류가 발생했습니다.\n");
    }

    return result;
}

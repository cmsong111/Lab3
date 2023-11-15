#include <stdio.h>

int main() {
    // 파일 경로 설정
    const char *filename = "example.txt";

    // 파일 열기
    FILE *file = fopen(filename, "r");

    // 파일 열기에 실패한 경우
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 파일에서 데이터 읽기
    char buffer[100];  // 읽은 데이터를 저장할 버퍼
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // 파일 내용 콘솔에 출력
        printf("%s\n", buffer);
    }

    // 파일 닫기
    fclose(file);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TEXT_LENGTH 500

// 함수 선언
void typingPractice(char *text);
double calculateTypingSpeed(clock_t startTime, clock_t endTime, int typedCharacters);

int main() {
    char practiceText[MAX_TEXT_LENGTH];

    // 타자 연습 텍스트 설정
    strcpy(practiceText, "동해 물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세 무궁화 삼천리 화려강산 대한 사람 대한으로 길이 보전하세");

    // 타자 연습 함수 호출
    typingPractice(practiceText);

    return 0;
}

void typingPractice(char *text) {
    printf("타자 연습을 시작합니다. 아래의 텍스트를 입력하세요.\n\n%s\n", text);

    // 현재 시간 저장
    clock_t startTime = clock();

    char userInput[MAX_TEXT_LENGTH];
    fgets(userInput, MAX_TEXT_LENGTH, stdin);

    // 현재 시간 저장
    clock_t endTime = clock();

    // 오타 수 계산
    int errors = 0;
    for (int i = 0; i < strlen(text) && i < strlen(userInput); i++) {
        if (text[i] != userInput[i]) {
            errors++;
        }
    }

    // 평균 분당 타자수 계산
    int typedCharacters = strlen(text);  // 정확한 길이로 수정
    double typingSpeed = calculateTypingSpeed(startTime, endTime, typedCharacters);

    // 결과 출력
    printf("\n오타 수: %d\n", errors);
    printf("평균 분당 타자수: %.2f\n", typingSpeed);
}

double calculateTypingSpeed(clock_t startTime, clock_t endTime, int typedCharacters) {
    double totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC; // 초 단위로 변환
    double typingSpeed = (typedCharacters / 5.0) / (totalTime / 60.0);  // 분당 타자수 계산

    return typingSpeed;
}

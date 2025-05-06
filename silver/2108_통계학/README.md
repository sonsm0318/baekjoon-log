# ❀ 백준 2108번 통계학 문제 정리

## ✅ 문제 요구
- N개의 정수가 주어지면 다음 4가지를 구해야 한다:
  1. ㅎ 삼술평균 (Arithmetic Mean): 소수점 첫째자리로 반올림
  2. ㅎ 중앙값 (Median): 정렬 후 중간에 위치한 값
  3. ㅎ 최비값 (Mode): 남들 보다 더 많이 나온 값 (2개 이상이면 두 번째)
  4. ㅎ 범위 (Range): 최대값 - 최소값

## ⚡ 가존 조건
- N 수: 1 가지 한 것이 보상 (N과 같은 값이 주어지는 것은 거의 바로 부팅과 같은 단계)
- 입력 값 범위: -4000 ~ 4000
- 타입은 정수만 이용 (double 맞지 않음)

## ⚖️ 패턴
- 입력값을 정수 범위를 이용해 `arr[8001]`에 번좌화해 건드
- 정렬한 값은 `sortedArr[]`에  \uaccumulation
- 최비값은 `maxFreq`를 찾은 후, 같은 횟수를 가지는 값 두 개 중 두 번째를 찾음
- 삼술평균은 `round()` 함수로 정수 반올림

## 하지만 최비값 찾기 때 발생하는 오류 분석
- `arr[i]--` 후에 `arr[]`의 횟수가 0이 되면 그 후에 최비값을 찾는 방법이 만점
- 설정한 두 번째 값을 찾지 못하고 것이 참이 성공하지 못하는 원인

## 프로그램 가능 정보
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int arr[8001];             // -4000 ~ 4000 범위
int sortedArr[500000];     // 정렬 위해 입력  \uaccum

int main(void) {
    int N;
    cin >> N;

    int sum = 0;
    int max = -4000;
    int min = 4000;

    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        arr[tmp + 4000]++;
        sum += tmp;
        if (tmp > max) max = tmp;
        if (tmp < min) min = tmp;
    }

    // 최비값 보걸림을 위해 먼저 곃산
    int maxFreq = 0;
    for (int i = 0; i <= 8000; i++) {
        if (arr[i] > maxFreq)
            maxFreq = arr[i];
    }

    // 최비값 두 개 중 두 번째 값 검색
    int mode = 0;
    bool first = true;
    for (int i = 0; i <= 8000; i++) {
        if (arr[i] == maxFreq) {
            if (first) {
                mode = i;
                first = false;
            }
            else {
                mode = i;
                break;
            }
        }
    }

    // 정렬 방식  \uaccum
    int idx = 0;
    for (int i = 0; i <= 8000; i++) {
        for (int j = 0; j < arr[i]; j++)
            sortedArr[idx++] = i - 4000;
    }

    // 중앙값
    int center = sortedArr[(N - 1) / 2];

    // 출력
    cout << (int)round((double)sum / N) << endl;
    cout << center << endl;
    cout << mode - 4000 << endl;
    cout << max - min << endl;

    return 0;
}
```

## ✅ 모든 요구 마치 완료!
- [x] 삼술평균: round 적용 OK
- [x] 중앙값: sortedArr[(N-1)/2] OK
- [x] 최비값: 두 번째 값 검색 OK
- [x] 범위: max - min OK

---

프로파일에 계산 기능이 서식적으로 가득해있고, 양적인 사고 통계 문제의 해결 가능성을 다 가지고 있는 전파격 프로그램이다. 다음 문제로 넘어가기 전에 기본 통계 구조를 풀어내는 하나의 가장 진단한 방법을 탐산했다고 보줄 수 있어!

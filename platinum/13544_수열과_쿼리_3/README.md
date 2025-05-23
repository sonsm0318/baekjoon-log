# [백준 13544] 수열과 쿼리 3 — 사고 흐름 정리

## ✅ 문제 접근 방식

- 정렬된 배열에서 특정 값보다 큰 수의 개수를 빠르게 구해야 한다.
- 이분 탐색을 효율적으로 쓰기 위해 **Merge Sort Tree**를 사용하기로 결정.
- 각 세그먼트 노드에는 해당 구간의 정렬된 벡터를 저장한다.

## ✅ 자료구조 선택 이유

- **세그먼트 트리 + 정렬된 벡터** 조합은
  - 구간 쿼리(log n)
  - 정렬 상태 유지(log n)
  - 이분 탐색(log n)
- → O(log² n)에 k보다 큰 수의 개수를 빠르게 계산 가능.

## ✅ 구현 시 고려한 핵심 조건

1. **쿼리 XOR 처리**:
   - 쿼리 입력값 (a, b, c)은 이전 쿼리의 결과값(`answer`)과 XOR해야 한다.
   - `i = a ^ answer`, `j = b ^ answer`, `k = c ^ answer`

2. **i와 j의 정렬 순서 보장**:
   - 세그먼트 트리는 [start, end] 범위를 기준으로 동작하므로
   - 항상 `i <= j`가 되도록 `if (i > j) swap(i, j)` 처리 필요.

3. **answer 초기화 위치**:
   - 쿼리마다 `answer`는 누적되어야 하므로 루프 밖에서 초기화해야 함.
   - 루프 안에서 0으로 초기화하면 XOR가 무의미해지고, 잘못된 결과 발생.

## ✅ 주요 실수 및 수정

- ❌ 잘못된 `swap` 방향 → 항상 i > j가 되어 쿼리가 무효
  - ✔️ 수정: `if (i > j) swap(i, j)`

- ❌ answer를 for 루프 안에서 매번 0으로 초기화함
  - ✔️ 수정: `int answer = 0;` 선언을 for 루프 바깥으로 이동

## ✅ 결론

- 단순한 오타나 방향성 실수만으로 0만 출력되는 상황이 발생할 수 있음.
- 문제 조건을 **한 번 더 텍스트로 정제해보는 습관**이 중요.
- 코드보다 **사고 구조의 흐름이 맞는지**를 먼저 점검하는 게 핵심이다.

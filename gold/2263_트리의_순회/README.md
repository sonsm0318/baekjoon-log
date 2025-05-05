# 🌲 포스트오더 + 인오더 → 프리오더 복원 문제 풀이 및 사고 과정 정리

## 🧩 문제 개요

- 주어지는 두 트리 순회 결과:  
  - `inorder` (중위순회): 왼 → 루트 → 오  
  - `postorder` (후위순회): 왼 → 오 → 루트  
- 위 두 정보를 바탕으로 **전위순회 (루트 → 왼 → 오)** 결과를 구하는 문제

---

## 🧠 핵심 아이디어

1. **postorder의 마지막 값은 항상 루트 노드**이다.
2. **inorder에서 루트의 인덱스를 기준으로**  
   왼쪽과 오른쪽 서브트리를 나눌 수 있다.
3. 이 구조를 재귀적으로 반복하며 전위순회를 구성하면 된다.

---

## 💻 구현 코드

```cpp
int inOrderArray[100000];
int hashInOrderArray[100000];  // 값 → 인오더 인덱스 매핑
int postOrderArray[100000];

void solve(int iStart, int iEnd, int pStart, int pEnd)
{
	if (iStart > iEnd || pStart > pEnd) return;

	int root = postOrderArray[pEnd];
	cout << root << " ";

	int idx = hashInOrderArray[root];       // O(1) 인덱스 찾기
	int leftSize = idx - iStart;

	solve(iStart, idx - 1, pStart, pStart + leftSize - 1);  // 왼쪽 서브트리
	solve(idx + 1, iEnd, pStart + leftSize, pEnd - 1);      // 오른쪽 서브트리
}
```

⚙️ 자료구조 설계 판단

    hashInOrderArray[]: 값을 인덱스로 바로 접근하기 위해 사용

    처음에는 while로 탐색하려 했지만, 시간복잡도 O(N)이 되어 비효율적

    배열 기반 해시를 통해 O(1) 조회 최적화를 적용함

🤯 착각 & 개념 구분
착각	교정
계수 정렬이 LaTeX 정렬?	❌ → Counting Sort는 정렬 알고리즘, LaTeX은 수식 조판 시스템
내가 만든 인덱스 테이블은 캐시인가?	❌ → 진짜 캐시는 CPU의 메모리 계층에 위치함.
해시와 캐시 구분이 모호함	✅ → 해시는 위치 계산용, 캐시는 값 재사용용
내가 만든 배열은?	✅ lookup table, 혹은 memoization array로 부르는 것이 정확
🧠 정리된 개념
개념	요약
해시	키 → 해시 함수 → 정수 인덱스
캐시	최근 사용된 값을 빠르게 재사용하는 임시 저장소 (자동 관리됨)
lookup table	어떤 계산 결과를 미리 저장해두는 정적 배열 (캐시처럼 동작할 수 있음)
✅ 얻은 교훈

    개념을 “감으로” 접근하되, 정확한 정의로 검증하는 훈련이 중요하다

    자료구조 선택은 데이터 범위 + 목적 + 성능을 고려해 결정해야 한다

    캐시, 해시, 메모이제이션은 비슷하지만 역할과 구현이 다르다

✍️ 앞으로 할 일

    이 문제를 기반으로 트리 구조 복원, DP + 트리, 세그먼트 트리까지 확장할 예정

    해시/캐시 개념을 OS 공부와 병행하여 더 정교하게 다듬어 나갈 계획

    나만의 사고 흐름을 계속 기록하며 “문제 푼 코드”가 아니라 “생각을 정리한 코드”를 쌓아갈 것


---

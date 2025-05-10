# 🧠 Segment Tree Beats 사고방식 정리

## ✅ 문제 유형

주어진 수열에서 다음 3가지 쿼리를 반복적으로 처리해야 한다:

1. `range-chmin`: 주어진 구간에서 원소들을 특정 값 `X` 이하로 줄이기  
2. `range-max`: 구간의 최댓값 구하기  
3. `range-sum`: 구간의 총합 구하기  

> 단순한 lazy propagation만으로는 `range-chmin` 최적화가 어려워 `Segment Tree Beats` 기법이 필요하다.

---

## 🧠 사고방식 요약

### 1. struct Node 설계

```cpp
struct Node {
    int max;        // 최댓값
    int maxCount;   // max가 등장하는 횟수
    int secondMax;  // 두 번째로 큰 값 (≠ max)
    long long sum;  // 구간 합
    int lazy;       // lazy chmin 값 (-1이면 없음)
};
```
2. 불변식 (Invariant)

    항상 max > secondMax

    sum은 정확히 구간의 합

    merge(Node a, Node b) 는 이 조건을 유지하도록 구현되어야 함

3. 쿼리 처리 전략

firstQuery (range-chmin):

if (minNum >= max)             -> 아무 작업 안 함
else if (minNum > secondMax)   -> 이 노드에서 바로 자름 (apply_chmin)
else                            -> 자식 노드로 내려가야 함 (pushDown)

secondQuery (range-max):
→ lazy pushDown 후 자식 둘 max 중 더 큰 값

thirdQuery (range-sum):
→ lazy pushDown 후 자식 둘 sum 합산
4. lazy 전파 구조

void apply_chmin(Node& n, int x) {
    if (x >= n.max) return;
    n.sum -= 1LL * (n.max - x) * n.maxCount;
    n.max = x;
    if (n.lazy == -1 || x < n.lazy) n.lazy = x;
}

void pushDown(int idx) {
    if (tree[idx].lazy == -1) return;
    apply_chmin(tree[idx<<1], tree[idx].lazy);
    apply_chmin(tree[idx<<1|1], tree[idx].lazy);
    tree[idx].lazy = -1;
}

🪛 디버깅 기준

    max == secondMax 상태는 segment tree beats 조건 위반

    자식 노드를 직접 수정하지 말고 항상 merge()로 부모 갱신

    build()에서 secondMax = INT_MIN 으로 설정해야 잘림 조건이 정상 작동

✅ 성장 포인트

    updateTree → merge 함수로 교체하면서 코드 중복 감소

    lazy propagation의 정확한 전파 타이밍 감을 익힘

    Segment Tree Beats 핵심 분기 케이스를 코드로 구현해봄

🔚 현재 상태 요약

    ✅ 세그트리 비트 구현 성공

    ✅ 실전 문제도 AC

    ❗ GPT 없이 구현하려 했으면 분기 조건(especially secondMax, lazy)에서 막혔을 것

    📌 다음 단계는 이 패턴을 직접 암기 없이 구성하는 연습!


---

# 트리 개수 판별 (사이클이 없는 연결 컴포넌트 세기)

## 🧠 문제 해결 흐름

### 1. 문제 이해
- 무방향 그래프가 주어졌을 때, 사이클이 없는 연결 컴포넌트(트리)의 개수를 세는 문제.
- 간선 수가 많아도 사이클만 없으면 트리이고, 정점 하나만 있어도 트리다.
- 여러 테스트 케이스가 주어지고, 입력 종료는 `0 0`.

---

### 2. 알고리즘 선택
- DFS를 통해 컴포넌트를 순회하며 사이클이 있는지 체크.
- 사이클이 없는 컴포넌트만 `treeNum++`.
- 방문 배열 `visited[]`를 통해 정점 방문 여부를 확인.
- 사이클 여부는 `loopCheck` 플래그로 관리.

---

### 3. 구현 아이디어
- DFS 중 `현재 노드`의 이웃이 `방문된 상태인데, 부모가 아니라면` → 사이클 존재.
- 사이클이 없는 경우에만 트리 개수 증가.
- 연결 리스트 구조 (`vector<vector<int>>`)로 그래프 구성.
- `treeNum++`는 DFS 함수 내부가 아니라, **DFS 호출 후 사이클이 없을 때만 증가**.

---

### 4. 실수 & 디버깅 경험

#### ❌ 실수:
```cpp
if (visited[neighbor] && neighbor != parent)
    loopCheck = true;
treeNum++;  // (잘못된 위치)
    
    DFS 중에 바로 트리 개수를 증가시켜서 사이클이 있어도 증가됨

    if로 분기해서 모든 인접 노드를 사이클로 오인할 수도 있음

✅ 수정:

else if (neighbor != parent)
    loopCheck = true;

    else if로 해야만 이전 DFS에서 넘어온 부모 노드를 제외하고만 사이클 탐지

5. 정답 코드 핵심 부분
```cpp
void DFS(int curr, int parent)
{
    visited[curr] = true;
    for (int neighbor : nodeArray[curr])
    {
        if (!visited[neighbor])
        {
            DFS(neighbor, curr);
        }
        else if (neighbor != parent)
        {
            loopCheck = true;
        }
    }
}
    
for (int i = 0; i < N; i++)
{
    if (!visited[i])
    {
        loopCheck = false;
        DFS(i, -1);
        if (!loopCheck)
            treeNum++;
    }
}
      
💡 교훈

    DFS에서 사이클 판정할 때 else if 구조를 꼭 신경 쓰자.

    컴포넌트별 로직은 반드시 DFS 호출 후 판단해야 한다.

    정점 하나짜리도 트리라는 점을 놓치지 말자.

    문제에서 ‘트리 판별’은 결국 사이클 유무 판별이라는 걸 명확히 이해했다.


---

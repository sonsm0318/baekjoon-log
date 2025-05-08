# 📘 DFS 기본 문제 풀이 정리 (백준 24479 등)

## ✅ 배운 점 요약

| 내용 | 정리 |
|------|------|
| `vector`는 `sort()` 멤버 함수가 없다 | 정렬은 `std::sort(v.begin(), v.end())` 형태로 사용해야 함 |
| DFS 구현 | 재귀함수를 이용해 방문 체크 + 탐색 진행 |
| 방문 순서 지정 필요 시 | adjacency list 내부를 정렬해 탐색 순서를 제어 |
| 시간 최적화 | `ios::sync_with_stdio(false); cin.tie(NULL);` 사용 |
| 전역 변수 활용 | 방문 순서 `sequence`를 전역으로 유지하면 간단하게 처리 가능 |

---

## 🧠 문제 접근 사고 과정

1. **그래프 형태 파악**  
   정점이 N개, 간선 M개 → 인접 리스트 (`vector<vector<int>>`) 사용  
   무방향 그래프 → `arr[a].push_back(b)` 와 `arr[b].push_back(a)` 모두 추가

2. **정점 순서 조건 확인**  
   DFS 방문 순서를 오름차순/내림차순으로 요구하는 경우 → `sort()` 필요

3. **방문 순서 저장 방식**  
   `visited[node] = 순서값` 형태로 방문 시 기록  
   방문 순서는 `sequence` 변수를 증가시키며 관리

4. **입력 최적화**  
   N이 최대 100,000이므로 `ios::sync_with_stdio(false);`와 `cin.tie(NULL);`로 속도 향상

---

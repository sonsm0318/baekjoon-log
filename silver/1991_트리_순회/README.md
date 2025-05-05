# 📘 이진 트리 순회 문제 - 사고 과정 정리

## 🧠 문제 인식
- 입력은 노드 + 왼쪽 자식 + 오른쪽 자식으로 구성됨
- `A B C` → A의 왼쪽 자식은 B, 오른쪽 자식은 C
- 자식이 없을 경우 `.` 으로 입력됨

## 🧩 구조 설계
- **노드는 항상 A~Z 범위 안**이므로 고정 크기 배열 사용
  ```cpp
  struct Node {
      char left;
      char right;
  };
  Node tree[26];  // 'A'부터 'Z'까지 26개 노드

    문자 인덱싱: 'A' - 'A' = 0, 'B' - 'A' = 1 식으로 변환

🔁 순회 로직

    전위 순회 (Preorder): 현재 → 왼쪽 → 오른쪽

    중위 순회 (Inorder): 왼쪽 → 현재 → 오른쪽

    후위 순회 (Postorder): 왼쪽 → 오른쪽 → 현재

void preorder(char node) { ... }  
void inorder(char node) { ... }  
void postorder(char node) { ... }  

💡 변수/함수 네이밍 고민

    전위/중위/후위 → preorder, inorder, postorder

    구조체 → Node, TreeNode (필요 시 명확하게 역할 표현)

    입력 간단하지만 순회는 DFS 그대로 → 트리지만 본질은 DFS

🤔 반성 및 개선 포인트

    처음엔 vector<vector<Node>>로 구성했지만 불필요하게 중첩됨

    각 노드는 자식 정보 하나만 가지므로 단일 Node 배열로 충분함
    → 단순한 구조가 오히려 가독성과 효율 모두 좋음

✅ 결론

    트리는 결국 그래프다 → 구조는 DFS 기반으로 접근 가능

    하지만 입력이 트리 구조로 주어진 경우엔 구조만 잘 잡으면 간단

    알고리즘 구현보다 자료구조 모델링과 네이밍이 핵심


---

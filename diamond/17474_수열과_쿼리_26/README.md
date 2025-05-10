세그트리 최적화 문제 풀이 사고방식 정리

✅ 문제 유형

주어진 수열에서 다음 3가지 쿼리를 반복적으로 처리해야 한다:

range-chmin: 주어진 구간에서 원소들을 특정 값 X 이하로 줄이기

range-max: 구간의 최댓값 구하기

range-sum: 구간의 총합 구하기

단순한 lazy propagation만으로는 range-chmin 최적화가 어려워 Segment Tree Beats 기법 필요

🧠 사고방식 요약

1. 정보 설계 (struct Node)

각 노드에는 다음 값들을 저장해야 한다:

max: 구간의 최댓값 (최댓값 자체)

maxCount: max가 등장하는 개수

secondMax: 두 번째로 큰 값 (최댓값 제외한 최댓값)

sum: 구간 합

lazy: chmin 연산을 지연시킬 값 (없으면 -1)

2. 불변식 유지

항상 다음 조건이 유지되어야 함:

max > secondMax

sum 은 정확한 합계

merge(a, b) 함수는 항상 위 조건을 만족하도록 구현

3. 쿼리 처리 전략

firstQuery (range-chmin):

세 가지 분기로 나뉜다:

minNum >= max: 아무 일도 하지 않음

minNum > secondMax: 이 노드에서 한 번에 잘라버릴 수 있음 → apply_chmin

minNum <= secondMax: 자식 노드로 내려가야 함 → pushDown, 재귀 호출

secondQuery (range-max):

lazy 전파 후 자식 둘에서 max 받아서 비교

thirdQuery (range-sum):

lazy 전파 후 자식 둘의 sum 합

4. lazy 전파 구조

apply_chmin(Node& n, int x)

x < n.max일 때만 적용

sum 보정, max 변경, lazy 저장

pushDown(idx)

lazy 값을 자식 노드에 흘려보내고 현재 노드의 lazy를 제거

5. 디버깅 기준

max == secondMax 상태가 되면 세그트리 비트의 전제 조건이 깨지므로 반드시 방지해야 함

자식 노드를 직접 수정하지 않고, 항상 merge()로 부모 노드 값을 갱신해야 함

✅ 성장 포인트

원래는 updateTree를 반복해서 쓰면서 부모값을 갱신했지만, 이 방식은 오류가 생기기 쉬움

merge 함수 도입 후부터는 코드도 짧아지고 오류도 줄었음

pushDown을 통해 lazy 값이 제대로 전파되어야 전체 쿼리 정확도가 유지됨

🔚 현재 상태 요약

세그트리 비트 구현 성공 ✅

실전 문제도 AC ✅

하지만 이 방식은 내가 완전히 혼자 생각해낸 건 아님 😓

GPT의 도움 없이 풀었으면 아마 secondMax나 lazy 분기에서 틀렸을 확률이 높았음

📌 따라서 지금은 구현 패턴을 복습하고, 다음번엔 내가 직접 조건 분기를 구성하는 훈련이 필요함.


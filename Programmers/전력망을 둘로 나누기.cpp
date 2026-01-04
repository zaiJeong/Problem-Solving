#include <string>
#include <vector>
#include <queue>

using namespace std;

int dfs(int cur, int parent, vector<vector<int>>& graph, int cutA, int cutB) {
    int cnt = 1;
    for (int nxt : graph[cur]) {
        if (nxt == parent) continue;
        
        // 끊는 간선이면 패스
        if ((cur == cutA && nxt == cutB) || (cur == cutB && nxt == cutA)) continue;
        
        cnt += dfs(nxt, cur, graph, cutA, cutB);
    }
    return cnt;
}

int solution(int n, vector<vector<int>> wires) {
    int answer = 1000000;
    
    vector<vector<int>> graph(101);
    
    // graph 생성
    for (vector<int> wire : wires) {
        graph[wire[0]].push_back(wire[1]);
        graph[wire[1]].push_back(wire[0]);
    }
    
    // 전선 하나씩 끊고 count
    for (auto wire : wires) {
        int a = wire[0], b = wire[1];
        
        int cnt = dfs(1, 0, graph, a, b);
        int other = n - cnt;
        
        answer = min(answer, abs(cnt - other));
    }
    
    return answer;
}

// 완전 탐색으로 하나씩 끊어보기 
// 그리고 각각 BFS/DFS 돌려서 개수 카운팅 
// 최소값 초기화

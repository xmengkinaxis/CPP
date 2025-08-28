#include <vector>
#include <unordered_set>

using namespace std; 

void setMatrixZeros(vector<vector<int>> matrix) {
    const int M = matrix.size(), N = matrix[0].size(); 
    
    unordered_set<int> rows, cols; 
    for (int r = 0; r < M; ++r)
        for (int c = 0; c < N; ++c) {
            if (0 == matrix[r][c]) {
                rows.insert(r); 
                cols.insert(c);
            }
        }
    
    for (auto r : rows) {
        for (int c = 0; c < N; ++c) {
            matrix[r][c] = 0; 
        }
    }
    
    for (auto c : cols) {
        for (int r = 0; r < M; ++r) {
            matrix[r][c] = 0; 
        }
    }
}
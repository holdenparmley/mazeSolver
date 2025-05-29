#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

std::vector<int> BFS(std::vector<int> maze, int S, int n) {
  int neighbors[] = {1, n, -1, -n};
  std::queue<int> Q;
  int size = n * n;  // It is useful to save this as a variable                                                                                                                       
  std::vector<std::string> color(size, "white");
  std::vector<int> p(size, -1);  // -1 represents no parent                                                                                                                           
  // I chose to define "infinite" distance as a number just greater than the                                                                                                          
  // total number of squares                                                                                                                                                          
  // This program does not actually need distances, but I still included it in                                                                                                        
  // my implementation                                                                                                                                                                
  std::vector<int> d(size, size + 1);
  color[S] = "gray";
  d[S] = 0;
  Q.push(S);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    std::vector<int> adj;
    for (int i = 0; i < 4; i++) {
      if (!(maze[u] & (1 << i))) {
        int neighbor = u + neighbors[i];  // Index of the neighbor                                                                                                                    
        // Bounds check, because the entrance square will be open on the left                                                                                                         
        // and the exit square will be open on the right, but following these                                                                                                         
        // will lead to invalid indices                                                                                                                                               
        if (neighbor >= 0 && neighbor < size) adj.push_back(neighbor);
      }
    }
    for (int v : adj) {
      if (color[v] == "white") {
        color[v] = "gray";
        p[v] = u;
        d[v] = d[u] + 1;
        Q.push(v);
      }
    }
    color[u] = "black";
  }
  return p;  // All we need to find a path back is the vector of parents                                                                                                              
}

std::vector<int> coordinateMaker(std::vector<int> p, int n) {
  std::vector<int> traversal;
  int current = n * n - 1;  // Move "backwards", starting at the end                                                                                                                  
  while (current != -1) {  // Will terminate after we get to the starting square                                                                                                      
    traversal.push_back(current);
    int parent = p[current];  // Find the parent                                                                                                                                      
    current = parent;  // Inspect the parent                                                                                                                                          
  }
  return traversal;
}

int main() {
  std::unordered_map<char, int> lookup = { {'0', 0}, {'1', 1}, {'2', 2},
       {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
       {'a', 10}, {'A', 10}, {'b', 11}, {'B', 11}, {'c', 12}, {'C', 12},
       {'d', 13}, {'D', 13}, {'e', 14}, {'E', 14}, {'f', 15}, {'F', 15} };
  std::vector<int> maze;
  std::string line;
  int n = 0;
  while (std::getline(std::cin, line)) {
    n++;  // The number of lines is the same as the number of rows and columns                                                                                                        
    for (char c : line) maze.push_back(lookup[c]);
  }
  std::vector<int> p = BFS(maze, 0, n);  // BFS starting at the top left                                                                                                              
  std::vector<int> traversal = coordinateMaker(p, n);
  while (!traversal.empty()) {
    // Use a stack to print in backwards order from insertion                                                                                                                         
    int pos = traversal.back();
    traversal.pop_back();
    int col = pos % n;
    int row = pos / n;
    std::cout << '(' << col << ", " << row << ')' << std::endl;
  }
}

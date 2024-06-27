# Trenuri

 - Complexity:
   - Time: O(n + m)
      - Explanation: Topsort has a complexity of O(n + m). While calculation the max number of cities we iterate through the cities (O(n)) and the through the edges (O(m)). O(n + m + n + m) = O(n + m).
   - Space: O(n + m)
      - Explanation: The graph is represented by an adjacency list => O(n + m). Visited, topsort and dp have O(n). O(n + m + n + n + n) = O(n + m).
 - We read the graph.
 - We topsort it to ensure that each city if processed only after all the cities before it have been processed.
 - We use dynamic programming to calculate the max distance (count the max number of cities) from start to destination.

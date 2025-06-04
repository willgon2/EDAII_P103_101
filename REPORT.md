# Report: Building a search engine like Google

> [!NOTE]  
> Complete the report in this file before delivering the project.
> The lab guide has a list of the questions you must answer.


Project Report: Search Engine Implementation and Analysis
With the following diagram we can understand the underlying structure of our project.

![Document Flowchart](diagram.png)


When it comes to memory management, all components in the diagram, except for the dataset files, were generated via heap allocation and freed at the end of the execution.
Runtime Complexity Analysis
Parsing a Document into the Struct
Parsing each document involves reading all characters and identifying tokens (words and links). The complexity is O(n), where n is the number of characters in a document, as each character is processed exactly once. Adding links to a linked list incurs an O(1) cost per link, resulting in a total complexity of O(n + m), where m is the number of links.
Parsing a Query into the Struct
Parsing a query is done similarly to documents but typically shorter. The complexity remains linear with respect to the number of characters, O(q), where q is the query length.
Counting Neighbours in the Graph		
Counting neighbours for all documents involves iterating over all nodes and their adjacency lists. If d is the number of documents and a is the average adjacency list size, complexity is O(d × a).
Counting Neighbours of a Document
Counting neighbours for a single document directly involves accessing its adjacency list, with a complexity of O(a), where a is the adjacency list length for that specific document.
Finding Documents Containing a Keyword in the Reverse Index
This operation uses hashing and linear probing. Hashing complexity is O(1) on average, but with collisions, linear probing can degrade to O(n). However, with proper resizing and load balancing, the complexity remains practically O(1).
Finding Documents Matching All Query Keywords
For multiple keywords, complexity involves intersecting multiple posting lists. Intersection has complexity O(p), where p is the length of the smallest posting list. Overall complexity is O(k × p), where k is the number of keywords.
Sorting Documents According to Relevance Score
Sorting relevance scores uses bubble sort, with complexity O(d²) where d is the number of documents retrieved. However, the implementation can be optimized to O(d log d) using a more efficient sorting algorithm such as quicksort.
Search and Initialization Time Analysis
Search Time by Dataset Size (with/without Reverse Index)
(Placeholder for the dataset size vs. search time plots) TBD
Discussion
Utilizing a reverse index significantly improves search performance. Without it, each query requires scanning all documents (O(d)). With a reverse index, search time remains constant or near-constant O(1), clearly outperforming the non-indexed method, especially as dataset size grows.
Initialization Time by Hashmap Slot Count
(Placeholder for the slot count vs. initialization time plot) TBD
Discussion
Initialization times initially decrease rapidly as the hashmap slot count increases, stabilizing after a certain threshold. This happens due to fewer collisions and rehashes required when adequate capacity is allocated at initialization.
Search Time by Slot Count
(Placeholder for the slot count vs. search time plot) TBD
Discussion
Search performance improves significantly with increased hashmap slot counts due to fewer collisions and faster hash lookups. However, returns diminish beyond a certain capacity, highlighting the importance of choosing an optimal slot count balancing memory use and speed.
Reverse Index Improvement Proposal
Proposed Improvement
A notable enhancement involves using sorted arrays or binary search trees (BSTs) instead of linked lists for storing document IDs. This enables binary search for checking existence, dramatically reducing search time complexity.
Memory Implications
A BST or sorted array typically uses the same or slightly more memory compared to linked lists, as additional pointers or sorting overhead is introduced. However, the increased memory use is modest.
Runtime Complexity (Big-O)
Implementing BSTs or sorted arrays improves complexity from linear search O(n) to logarithmic search O(log n). Although initialization may require slightly more time due to sorting overhead (O(n log n)), the significant improvement in query times, especially at large scales, justifies this trade-off.


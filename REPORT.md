# Report: Building a search engine like Google

![Document Flowchart](diagram.png)

# Memory Management

When it comes to memory management, all components in the diagram—except for the dataset files—were generated via heap allocation and freed at the end of the execution.

---

# Runtime Complexity Analysis

## Parsing a Document into the Struct

Parsing each document involves reading all characters and identifying tokens (words and links). The complexity is:

- **O(n)**, where `n` is the number of characters in a document, as each character is processed exactly once.
- Adding links to a linked list incurs an **O(1)** cost per link.
- Total complexity: **O(n + m)**, where `m` is the number of links.

## Parsing a Query into the Struct

Similar to document parsing but typically shorter. The complexity is:

- **O(q)**, where `q` is the query length.

## Counting Neighbours in the Graph

Counting neighbours for all documents involves iterating over all nodes and their adjacency lists:

- Let `d` be the number of documents and `a` the average adjacency list size.
- Complexity: **O(d × a)**

## Counting Neighbours of a Document

Counting neighbours for a single document:

- Complexity: **O(a)**, where `a` is the adjacency list length for that document.

## Finding Documents Containing a Keyword in the Reverse Index

- Uses hashing and linear probing.
- Average case complexity: **O(1)**
- Worst case (collisions): **O(n)**
- With proper resizing/load balancing: practically **O(1)**

## Finding Documents Matching All Query Keywords

- Involves intersecting multiple posting lists.
- Let `k` be the number of keywords, and `p` the length of the smallest posting list.
- Complexity: **O(k × p)**

## Sorting Documents According to Relevance Score

- Uses bubble sort: **O(d²)**, where `d` is the number of retrieved documents.
- Can be optimized to **O(d log d)** using quicksort or other efficient algorithms.

---

# Search and Initialization Time Analysis

## Search Time by Dataset Size (with/without Reverse Index)

**(Placeholder for the dataset size vs. search time plots)**  
**TBD**

### Discussion

- A reverse index significantly improves search performance.
- Without a reverse index: **O(d)** (scanning all documents).
- With a reverse index: practically **O(1)**.
- Reverse indexing scales better as dataset size increases.

## Initialization Time by Hashmap Slot Count

**(Placeholder for the slot count vs. initialization time plot)**  
**TBD**

### Discussion

- Initialization time decreases with increased slot count.
- Fewer collisions and rehashes improve performance.
- Eventually stabilizes once capacity becomes sufficient.

## Search Time by Slot Count

**(Placeholder for the slot count vs. search time plot)**  
**TBD**

### Discussion

- Performance improves with higher slot counts due to fewer collisions.
- Diminishing returns beyond a certain capacity.
- Importance of balancing memory use vs. performance.

---

# Reverse Index Improvement Proposal

## Proposed Improvement

- Use **sorted arrays** or **binary search trees (BSTs)** instead of linked lists for storing document IDs.
- Enables **binary search** for existence checks.

## Memory Implications

- BSTs or sorted arrays may use slightly more memory than linked lists.
- Overhead comes from pointers or sorting.
- Overall memory impact is modest.

## Runtime Complexity (Big-O)

- Searching improves from **O(n)** (linear search) to **O(log n)** (binary search).
- Initialization may take **O(n log n)** due to sorting.
- Query performance greatly improves at scale, making the trade-off worthwhile.


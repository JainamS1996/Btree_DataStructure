
 
 # DataStructure_BplusTrees
This project is dedicated to develop and to test a class B+Tree to store pairs of the form (key, value). For this project I've implemented a memory resident B+tree (i.e., the entire tree resides in main memory).It stores multiple pairs that have the same key (i.e., duplicates). The leaves are linked into a doubly linked list to support efficient range retrieval. The supported operations are: 
 
1. Initialize(m): create a new order m B+Tree 2. Insert (key, value)  3. Search (key) : returns all values associated with the key 4. Search (key1,key2): returns (all key value pairs) such that key1 <= key <= key2. 

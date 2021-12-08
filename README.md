# CSCI_Project

1. Does one hashing collision resolution work better than the other? Consider the
datasets we used and a much larger dataset with 1 million records. Explain your
answer.
In my opinion, hash map chaining works better for implementing and inserting and searching. All we need to know is the bucket and go from there to insert or find any element we want. For hash open addressing, if we have a lot of records, then the collision will happen a lot more.

2- We used the same BST for both hashing mechanisms. What alternative data
structure would you advise? Why?
Since we want to store the Professor in a orted list and have quick access to the information with 0(log n). Another data structure that ciould be used is sorted array. Its not as goood as BST since it will take more time. 

3- Explain a few ways you could improve the application
If the initial hash table was a default size and we could resize during the program's excecution. 

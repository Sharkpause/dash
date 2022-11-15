all: 
	gcc LinkedList/linkedlist.c -o LinkedList/linkedlist
	gcc BST/bst.c -o BST/bst
	gcc Stack/stack.c -o Stack/stack
	gcc Heap/heap.c -o Heap/heap
	gcc Queue/queue.c -o Queue/queue
	gcc dscli.c -o dscli
clean:
	rm BST/bst
	rm LinkedList/linkedlist
	rm Stack/stack
	rm Heap/heap
	rm Queue/queue
	rm dscli

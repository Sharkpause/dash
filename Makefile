all: 
	gcc LinkedList/linkedlist.c -o LinkedList/linkedlist
	gcc BST/bst.c -o BST/bst
	gcc Stack/stack.c -o Stack/stack
	gcc dscli.c -o dscli
clean:
	rm BST/bst
	rm LinkedList/linkedlist
	rm Stack/stack
	rm dscli

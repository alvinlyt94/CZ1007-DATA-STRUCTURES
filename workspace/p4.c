//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
2016/17 S1
Author and Lab Group: ALVIN LEE YONG TECK / FSP7
Program name: FSP7_ALVIN_LEE_YONG_TECK
Date: 03 November 2016
Purpose: Implementing the required functions for Assignment 1 (Question 4)*/

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode {
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode {
	BSTNode *item;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

		///////////////////////// function prototypes ////////////////////////////////////

		// This is for question 4. You should not change the prototypes of these functions
void insertBSTNode(BSTNode **node, int value);
void printPostOrderIterative(BSTNode *root);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode * pop(Stack *s);
BSTNode * peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	c = 1;
	root = NULL;

	printf("1:Insert an integer into the binary search tree;\n");
	printf("2:Print the post-order traversal of the binary search tree;\n");
	printf("0:Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			printPostOrderIterative(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value) {
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void printPostOrderIterative(BSTNode *root)
{
	Stack *s1, *s2;				// Declare 2 Stacks (s1 & s2)
	BSTNode *cur;				// Declare BSTNode cur (a.k.a current) to 
	s1 = malloc(sizeof(s1));	// Dynamically allocate memory for Stack s1
	s2 = malloc(sizeof(s2));	// Dynamically allocate memory for Stack s2
	s1->top = NULL;				// Point the top of Stack s1 to NULL
	s2->top = NULL;				// Point the top of Stack s2 to NULL

	// If Stack s1 is not empty, point the top of stack to NULL
	if (!isEmpty(s1)) {
		s1->top = NULL;
	}

	// If Stack s2 is not empty, point the top of stack to NULL
	if (!isEmpty(s2)) {
		s2->top = NULL;
	}

	// If BSTNode root is NULL, return back to main function
	if (root == NULL) {
		return;
	}
	push(s1, root); // Push the root node to the first stack

	// Repeat until the Stack s1 is empty
	while (!isEmpty(s1)) {
		// Pop a node out from Stack s1 and push it into Stack s2
		push(s2, pop(s1));

		// Set the node that recently being pushed into Stack s2 to BSTNode cur
		cur = s2->top->item;

		// Push the node's left child to Stack s1
		if (cur->left != NULL) {
			push(s1, cur->left);
		}

		// Push the node's right child to Stack s1
		if (cur->right != NULL) {
			push(s1, cur->right);
		}
	}

	// Repeat until Stack s2 is empty
	while (!isEmpty(s2)) {
		printf("%d ", pop(s2)->item); // Print the output that being popped out from Stack s2
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode *node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->item = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode* pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->item;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode* peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->item;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
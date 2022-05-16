/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {       //��� ����ü ����
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20      //���� ũ�� 20
Node* stack[MAX_STACK_SIZE];        //���� ����
int top = -1;

Node* pop();                
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20      //ť ũ��
Node* queue[MAX_QUEUE_SIZE];        //ť ����
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);        //Ʈ�� ����

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	Node* head = NULL;
    printf("[----- [����ȭ] [2019038062] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");       //�޴� ���
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);   //Ʈ�� ����
			break;
		case 'q': case 'Q':
			freeBST(head);          //�Ҵ�� �޸� ����,���α׷� ����
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);      //Ű���� �Է¹ް�
			insert(head, key);      //��� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);      //Ű���� �Է¹ް�
			deleteNode(head, key);  //��� ����
			break;

		case 'r': case 'R':
			recursiveInorder(head->left); //��ȯ�� ������ȸ
			break;
		case 't': case 'T':
			iterativeInorder(head->left); //�ݺ��� ������ȸ
			break;

		case 'l': case 'L':
			levelOrder(head->left);       //�������� ��ȸ
			break;

		default:                //�޴� �̿��� �ٸ� �� �Է� �� �������� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');		//q�� Q�� �Է¹����� �ݺ��� ����

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)      //tree�� �����Ǿ� �ִٸ�
		freeBST(*h);    //�Ҵ�� �޸� ����

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));   //Ʈ���� head �����޸� �Ҵ�
	(*h)->left = NULL;	/* root */      //Ʈ���� head�� left�� root
	(*h)->right = *h;                   //Ʈ���� head�� right�� �ڱ� �ڽ��� ����Ŵ
	(*h)->key = -9999;

	top = -1;       //������ top�� -1�� �ʱ�ȭ

	front = rear = -1;      //ť�� front�� rear�� -1�� �ʱ�ȭ

	return 1;
}


void recursiveInorder(Node* ptr)        //��ȯ�� ������ȸ
{
	if(ptr) {       //ptr�� NULL�� �ƴ϶�� �ݺ� 
		recursiveInorder(ptr->left);        //ptr�� ���� �ڽĳ�� ���� ��ȸ
		printf(" [%d] ", ptr->key);         //ptr�� Ű�� ���
		recursiveInorder(ptr->right);       //ptr�� ������ �ڽĳ�� ���� ��ȸ
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)       //�ݺ��� ������ȸ
{
	for(;;)
	{
		for(; node; node = node->left)  //��尡 NULL�� �ƴϸ� �ݺ�,�ݺ��� ���� ���� �ڽĳ��� �̵�
			push(node);         //���ÿ� node�� push
		node = pop();           //������ ������ ��带 pop�Ͽ� node�� ����

		if(!node) break;        //��尡 NULL�̸� �ݺ��� ����
		printf(" [%d] ", node->key);    //����� Ű�� ���

		node = node->right;     //���� ������ �ڽĳ��� �̵�
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)      //�������� ��ȸ
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr);       //ť�� root��� ����

	for(;;)
	{
		ptr = deQueue();    //front�� �ִ� ��带 ptr�� ����
		if(ptr) {
			printf(" [%d] ", ptr->key); //ptr�� Ű�� ���

			if(ptr->left)       //ptr�� ���� �ڽĳ�尡 �ִٸ�
				enQueue(ptr->left);     //���� �ڽĳ�带 ť�� ����
			if(ptr->right)      //ptr�� ������ �ڽĳ�尡 �ִٸ�
				enQueue(ptr->right);    //������ �ڽĳ�带 ť�� ����
		}
		else
			break;          //ptr�� NULL�̶�� �ݺ��� ����

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));        //������ ��� ���� �޸��Ҵ�
	newNode->key = key;         //�Է¹��� Ű�� ����
	newNode->left = NULL;       
	newNode->right = NULL;

	if (head->left == NULL) {   //root�� NULL�̸�
		head->left = newNode;   //root�� ���ο� ���
		return 1;   //�Լ� ����
	}

	/* head->left is the root */
	Node* ptr = head->left;     //ptr�� root

	Node* parentNode = NULL;    //�θ��带 ������ ���
	while(ptr != NULL) {        //ptr�� NULL�� �ƴϸ� �ݺ�

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;   //������ ����� Ű���� ���� ��尡 �̹� �����Ѵٸ� �Լ� ����

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;   //�θ��忡 ptr����

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)          //ptr�� Ű���� ������ ����� Ű������ �۴ٸ�
			ptr = ptr->right;       //ptr�� ������ �ڽ� ��尡 ��
		else                        //ptr�� Ű���� ������ ����� Ű������ ũ�ٸ�
			ptr = ptr->left;        //ptr�� ���� �ڽ� ��尡 ��
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)           //�θ����� Ű���� ������ ����� Ű������ ũ�ٸ�
		parentNode->left = newNode;     //�θ����� ���� �ڽĳ�忡 ���ο� ��� ����
	else                                //�θ����� Ű���� ������ ����� Ű������ �۴ٸ�
		parentNode->right = newNode;    //�θ����� ������ �ڽĳ�忡 ���ο� ��� ����
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {     //head�� NULL�̶�� 
		printf("\n Nothing to delete!!\n");     //�������� ���
		return -1;  //�Լ� ����
	}

	if (head->left == NULL) {   //root�� NULL�̶��
		printf("\n Nothing to delete!!\n");     //�������� ���
		return -1;  //�Լ� ����
	}

	/* head->left is the root */
	Node* root = head->left;    // ������ head->left�� ������ root��� ����

	Node* parent = NULL;        //�θ��带 ������ parent��� ����
	Node* ptr = root;           //ptr�� root��带 ����

	while((ptr != NULL)&&(ptr->key != key)) {   //ptr�� NULL�� �ƴϰ� ptr�� Ű���� �Է¹��� Ű���� ���� ������ �ݺ�
		if(ptr->key != key) {       //ptr�� Ű���� �Է¹��� Ű���� ���� ������
			parent = ptr;	/* save the parent */   //�θ��忡 ptr ����

			if(ptr->key > key)      //ptr�� Ű���� �Է¹��� Ű������ ũ�ٸ�
				ptr = ptr->left;    //ptr�� ���� �ڽĳ�尡 ��
			else                    //ptr�� Ű���� �Է¹��� Ű������ �۴ٸ�
				ptr = ptr->right;   //ptr�� ������ �ڽĳ�尡 ��
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) //ptr�� NULL�̸�
	{
		printf("No node for key [%d]\n ", key);     //�������� ���
		return -1;  //�Լ� ����
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)     //ptr�� �ڽĳ�尡 ���ٸ�
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)     //�ڽ� ��尡 ptr�̸� NULL�� �ٲ�
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {    //�θ��尡 ���ٸ�
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;  //root�� NULL

		}

		free(ptr);  //ptr�� �Ҵ�� �޸� ����
		return 1;   //�Լ� ����
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))  //ptr�� �ڽĳ���� �ϳ��� NULL�̶��
	{
		Node* child;        //�ڽ� ��带 ������ ��� ����
		if (ptr->left != NULL)  //ptr�� ���� �ڽĳ�尡 �ִٸ�
			child = ptr->left;  //child��忡 ptr�� ���� �ڽĳ�带 ����
		else                    //ptr�� ���� �ڽĳ�尡 ���ٸ�
			child = ptr->right; //child��忡 ptr�� ������ �ڽĳ�带 ����

		if(parent != NULL)      //�θ��尡 �ְ�
		{
			if(parent->left == ptr)     //�θ����� ���� �ڽĳ�尡 ptr�̶��
				parent->left = child;   //�θ����� ���� �ڽĳ�忡 child��� ����
			else                        //�θ����� ���� �ڽĳ�尡 ptr�� �ƴ϶��
				parent->right = child;  //�θ����� ������ �ڽĳ�忡 child��� ����
		} else {    //�θ��尡 NULL�̶��
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;   //root�� child��� ����
		}

		free(ptr);  //ptr�� �Ҵ�� �޸� ����
		return 1;   //�Լ� ����
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)  //candidate���� ������ ���� ��������尡��
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)     //�θ����� ������ �ڽĳ�尡 candidate��� �̸�
		parent->right = candidate->right;   //�θ����� ������ �ڽĳ�忡 candidate�� ������ �ڽĳ�带 ����
	else                                //�θ����� ������ �ڽĳ�尡 candidate��尡 �ƴϸ�
		parent->left = candidate->right;    //�θ����� ���ʳ�忡 candidate�� ������ �ڽĳ�带 ����

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;  //ptr�� Ű���� candidate�� Ű���� ����

	free(candidate);    //candidate�� �Ҵ�� �޸� ����
	return 1;
}


void freeNode(Node* ptr)    //ptr�� �� �Ʒ� �ڽ� ���鿡 �Ҵ�� �޸� ���� 
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)     //Ʈ���� �Ҵ�� �޸� ����
{

	if(head->left == NULL)  //root�� NULL�̸�
	{
		free(head);     //head��忡 �Ҵ�� �޸� ����
		return 1;
	}

	Node* p = head->left;   //p�� root���

	freeNode(p);    //Ʈ���� �Ҵ�� �޸� ����

	free(head);     //head��忡 �Ҵ�� �޸� ����
	return 1;
}

Node* pop()
{
	if (top < 0) return NULL;   //top�� 0���� �۴ٸ� NULL����
	return stack[top--];    //������ top�� ��ġ�� ��� ���� �� top�� �� -1
}

void push(Node* aNode)
{
	stack[++top] = aNode;       //top�� ���� +1, ������ top�� ��ġ�� ��� �߰�
}

Node* deQueue()
{
	if (front == rear) {    //front�� rear�� ���ٸ�
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;    //NULL����
	}

	front = (front + 1) % MAX_QUEUE_SIZE;   //front�� +1 �� ���� ť�� ũ�⸦ ���� ��
	return queue[front];    //ť�� front�� ��ġ�� ��� ����

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;     //rear�� +1 �� ���� ť�� ũ�⸦ ���� ��
	if (front == rear) {        //front�� rear�� ���ٸ�
		// printf("\n....Now Queue is full!!\n");
		return;     //�Լ� ����
	}

	queue[rear] = aNode;    //ť�� rear�� ��ġ�� ��� ����
}
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



typedef struct node {       //노드 구조체 선언
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20      //스택 크기 20
Node* stack[MAX_STACK_SIZE];        //스택 생성
int top = -1;

Node* pop();                
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20      //큐 크기
Node* queue[MAX_QUEUE_SIZE];        //큐 생성
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);        //트리 생성

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
    printf("[----- [염중화] [2019038062] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");       //메뉴 출력
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
			initializeBST(&head);   //트리 생성
			break;
		case 'q': case 'Q':
			freeBST(head);          //할당된 메모리 해제,프로그램 종료
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);      //키값을 입력받고
			insert(head, key);      //노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);      //키값을 입력받고
			deleteNode(head, key);  //노드 삭제
			break;

		case 'r': case 'R':
			recursiveInorder(head->left); //순환적 중위순회
			break;
		case 't': case 'T':
			iterativeInorder(head->left); //반복적 중위순회
			break;

		case 'l': case 'L':
			levelOrder(head->left);       //레벨순서 순회
			break;

		default:                //메뉴 이외의 다른 값 입력 시 에러문구 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');		//q나 Q를 입력받으면 반복문 종료

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)      //tree가 생성되어 있다면
		freeBST(*h);    //할당된 메모리 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));   //트리의 head 동적메모리 할당
	(*h)->left = NULL;	/* root */      //트리의 head의 left는 root
	(*h)->right = *h;                   //트리의 head의 right는 자기 자신을 가리킴
	(*h)->key = -9999;

	top = -1;       //스택의 top을 -1로 초기화

	front = rear = -1;      //큐의 front와 rear를 -1로 초기화

	return 1;
}


void recursiveInorder(Node* ptr)        //순환적 중위순회
{
	if(ptr) {       //ptr이 NULL이 아니라면 반복 
		recursiveInorder(ptr->left);        //ptr의 왼쪽 자식노드 중위 순회
		printf(" [%d] ", ptr->key);         //ptr의 키값 출력
		recursiveInorder(ptr->right);       //ptr의 오른쪽 자식노드 중위 순회
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)       //반복적 중위순회
{
	for(;;)
	{
		for(; node; node = node->left)  //노드가 NULL이 아니면 반복,반복후 노드는 왼쪽 자식노드로 이동
			push(node);         //스택에 node를 push
		node = pop();           //스택의 마지막 노드를 pop하여 node에 저장

		if(!node) break;        //노드가 NULL이면 반복문 종료
		printf(" [%d] ", node->key);    //노드의 키값 출력

		node = node->right;     //노드는 오른쪽 자식노드로 이동
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)      //레벨순서 순회
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr);       //큐에 root노드 삽입

	for(;;)
	{
		ptr = deQueue();    //front에 있는 노드를 ptr에 저장
		if(ptr) {
			printf(" [%d] ", ptr->key); //ptr의 키값 출력

			if(ptr->left)       //ptr의 왼쪽 자식노드가 있다면
				enQueue(ptr->left);     //왼쪽 자식노드를 큐에 삽입
			if(ptr->right)      //ptr의 오른쪽 자식노드가 있다면
				enQueue(ptr->right);    //오른쪽 자식노드를 큐에 삽입
		}
		else
			break;          //ptr이 NULL이라면 반복문 종료

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));        //삽입할 노드 동적 메모리할당
	newNode->key = key;         //입력받은 키값 저장
	newNode->left = NULL;       
	newNode->right = NULL;

	if (head->left == NULL) {   //root가 NULL이면
		head->left = newNode;   //root는 새로운 노드
		return 1;   //함수 종료
	}

	/* head->left is the root */
	Node* ptr = head->left;     //ptr은 root

	Node* parentNode = NULL;    //부모노드를 저장할 노드
	while(ptr != NULL) {        //ptr이 NULL이 아니면 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;   //삽입할 노드의 키값과 같은 노드가 이미 존재한다면 함수 종료

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;   //부모노드에 ptr저장

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)          //ptr의 키값이 삽입할 노드의 키값보다 작다면
			ptr = ptr->right;       //ptr은 오른쪽 자식 노드가 됨
		else                        //ptr의 키값이 삽입할 노드의 키값보다 크다면
			ptr = ptr->left;        //ptr은 왼쪽 자식 노드가 됨
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)           //부모노드의 키값이 삽입할 노드의 키값보다 크다면
		parentNode->left = newNode;     //부모노드의 왼쪽 자식노드에 새로운 노드 삽입
	else                                //부모노드의 키값이 삽입할 노드의 키값보다 작다면
		parentNode->right = newNode;    //부모노드의 오른쪽 자식노드에 새로운 노드 삽입
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {     //head가 NULL이라면 
		printf("\n Nothing to delete!!\n");     //에러문구 출력
		return -1;  //함수 종료
	}

	if (head->left == NULL) {   //root가 NULL이라면
		printf("\n Nothing to delete!!\n");     //에러문구 출력
		return -1;  //함수 종료
	}

	/* head->left is the root */
	Node* root = head->left;    // 저장할 head->left를 저장할 root노드 생성

	Node* parent = NULL;        //부모노드를 저장할 parent노드 생성
	Node* ptr = root;           //ptr에 root노드를 저장

	while((ptr != NULL)&&(ptr->key != key)) {   //ptr이 NULL이 아니고 ptr의 키값이 입력받은 키값과 같지 않으면 반복
		if(ptr->key != key) {       //ptr의 키값과 입력받은 키값이 같지 않으면
			parent = ptr;	/* save the parent */   //부모노드에 ptr 저장

			if(ptr->key > key)      //ptr의 키값이 입력받은 키값보다 크다면
				ptr = ptr->left;    //ptr은 왼쪽 자식노드가 됨
			else                    //ptr의 키값이 입력받은 키값보다 작다면
				ptr = ptr->right;   //ptr은 오른쪽 자식노드가 됨
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) //ptr이 NULL이면
	{
		printf("No node for key [%d]\n ", key);     //에러문구 출력
		return -1;  //함수 종료
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)     //ptr의 자식노드가 없다면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)     //자식 노드가 ptr이면 NULL로 바꿈
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {    //부모노드가 없다면
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;  //root는 NULL

		}

		free(ptr);  //ptr에 할당된 메모리 해제
		return 1;   //함수 종료
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))  //ptr의 자식노드중 하나가 NULL이라면
	{
		Node* child;        //자식 노드를 저장할 노드 생성
		if (ptr->left != NULL)  //ptr의 왼쪽 자식노드가 있다면
			child = ptr->left;  //child노드에 ptr의 왼쪽 자식노드를 저장
		else                    //ptr의 왼쪽 자식노드가 없다면
			child = ptr->right; //child노드에 ptr의 오른쪽 자식노드를 저장

		if(parent != NULL)      //부모노드가 있고
		{
			if(parent->left == ptr)     //부모노드의 왼쪽 자식노드가 ptr이라면
				parent->left = child;   //부모노드의 왼쪽 자식노드에 child노드 저장
			else                        //부모노드의 왼쪽 자식노드가 ptr이 아니라면
				parent->right = child;  //부모노드의 오른쪽 자식노드에 child노드 저장
		} else {    //부모노드가 NULL이라면
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;   //root에 child노드 저장
		}

		free(ptr);  //ptr에 할당된 메모리 해제
		return 1;   //함수 종료
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
	while(candidate->left != NULL)  //candidate노드는 왼쪽의 가장 마지막노드가됨
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)     //부모노드의 오른쪽 자식노드가 candidate노드 이면
		parent->right = candidate->right;   //부모노드의 오른쪽 자식노드에 candidate의 오른쪽 자식노드를 저장
	else                                //부모노드의 오른쪽 자식노드가 candidate노드가 아니면
		parent->left = candidate->right;    //부모노드의 왼쪽노드에 candidate의 오른쪽 자식노드를 저장

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;  //ptr의 키값에 candidate의 키값을 저장

	free(candidate);    //candidate에 할당된 메모리 해제
	return 1;
}


void freeNode(Node* ptr)    //ptr과 그 아래 자식 노드들에 할당된 메모리 해제 
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)     //트리에 할당된 메모리 해제
{

	if(head->left == NULL)  //root가 NULL이면
	{
		free(head);     //head노드에 할당된 메모리 해제
		return 1;
	}

	Node* p = head->left;   //p는 root노드

	freeNode(p);    //트리에 할당된 메모리 해제

	free(head);     //head노드에 할당된 메모리 해제
	return 1;
}

Node* pop()
{
	if (top < 0) return NULL;   //top이 0보다 작다면 NULL리턴
	return stack[top--];    //스택의 top에 위치한 노드 리턴 후 top의 값 -1
}

void push(Node* aNode)
{
	stack[++top] = aNode;       //top의 값에 +1, 스택의 top에 위치에 노드 추가
}

Node* deQueue()
{
	if (front == rear) {    //front와 rear가 같다면
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;    //NULL리턴
	}

	front = (front + 1) % MAX_QUEUE_SIZE;   //front는 +1 한 값에 큐의 크기를 나눈 값
	return queue[front];    //큐의 front에 위치한 노드 리턴

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;     //rear는 +1 한 값에 큐의 크기를 나눈 값
	if (front == rear) {        //front와 rear가 같다면
		// printf("\n....Now Queue is full!!\n");
		return;     //함수 종료
	}

	queue[rear] = aNode;    //큐의 rear의 위치에 노드 삽입
}
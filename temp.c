#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int color;
    int key;
    struct Node *left, *right, *parent;
} Node;

Node EList = {0, 0, NULL, NULL, NULL};

int getInt (int *);
Node *find(Node *, int);
Node *RB_Search(Node *);
Node *insert(Node *, int);
void Left_Rotate (Node *, Node *);
void Right_Rotate (Node *, Node *);
void RB_Insert_FixUp(Node *, Node *);
Node *RB_Insert(Node *);
Node *RB_Delete(Node *);
void ShowTree(Node *, int);
Node *RB_ShowTree(Node *);
Node *maxNode(Node *);
Node *RB_MaxNode (Node *);
void deltree(Node *);
int dialog (const char **, int);



int main()
{
	Node *root = &EList;
	int rc, N = 6;
	const char *msgs[] = {"0. Quit","1. Add","2. Find","3. Find max","4. Delete","5. Show Tree"};
	Node *(*fptr[])(Node*) = {NULL, RB_Insert, RB_Search, RB_MaxNode, RB_Delete, RB_ShowTree};
	while(rc = dialog(msgs, N))
	    root = fptr[rc](root);
	printf("Good Bye!\n");
	deltree(root);
	return 0;
}

int getInt (int *a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n < 0)
            return 0;
        else if (n == 0) {
            printf("Wrong input! Please, repeat!\n");
            scanf("%*c");
        }
    } while(n == 0);
    return 1;
}

Node *find(Node *root, int key){
    Node *ptr = root;
    while(ptr != &EList){
        if(key == ptr->key)
            return ptr;
        else if(key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    return 0;
}

Node *RB_Search(Node *root){
    Node *x = &EList;
    int k, n = 1;
    printf("Enter key: ");
    n = getInt(&k);
    x = find(root, k);
    if (x != 0) {
		puts("FIND");
		printf("%d \n", x->key);
	}
	else  puts("KEY NOT FOUND");
	return root;
}

Node *insert(Node *root, int key){
    Node *x, *par, *ptr;
    par = &EList;
    ptr = root;
    x = (Node *) calloc (1, sizeof(Node));
    if (ptr == &EList){
        x->color = 0;
        x->key = key;
        x->left = &EList;
        x->right = &EList;
        x->parent = &EList;
        ptr = x;
        return ptr;
    }
    while(ptr != &EList){
        par = ptr;
        if(key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    x->parent = par;
    if(key < par->key)
        par->left = x;
    else
        par->right = x;
    x->color = 1;
    x->right = &EList;
    x->left = &EList;
    x->key = key;
    RB_Insert_FixUp(x, root); 
    return root;
}
    
    

void Left_Rotate (Node *x, Node *root){
    Node *y = x->right;
    Node *p = x->parent;
    Node *ptr = root;
    x->right = y->left;
    if (y->left != &EList)
        y->left->parent = x;
    y->parent = p;
    if (p == &EList)
        ptr = y;
    else{
        if(p->left == x)
            p->left = y;
        else
            p->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Right_Rotate (Node *x, Node *root){
    Node *y = x->parent;
    Node *p = y->parent;
    Node *ptr = root;
    y->left = x->right;
    if (x->right != &EList)
        x->right->parent = y;
    x->parent = p;
    if (p == &EList)
        ptr = x;
    else{
        if(p->left == y)
            p->left = x;
        else
            p->right = x;       
    }
    x->right = y;
    y->parent = x;
}

void RB_Insert_FixUp(Node *x, Node *root){
    Node *p1, *p2, *pp;
    while(x->parent->color == 1){
        p1 = x->parent;
        pp = p1->parent;
        if(p1 = pp->left){
            p2 = pp->right;
            if(p2->color == 1){
                p1->color = 0;
                p2->color = 0;
                pp->color = 1;
                x = pp;
            }
            else if (x = p1->right){
                x = p1;
                Left_Rotate(x, root);
                p1 = x->parent;
                p1->color = 0;
                pp->color = 1;
                Right_Rotate(pp, root);
            }
        }
        else if(p1 = pp->right){
            p2 = pp->left;
            if(p2->color == 1){
                p1->color = 0;
                p2->color = 0;
                pp->color = 1;
                x = pp;
            }
            else if (x = p1->left){
                x = p1;
                Right_Rotate(x, root);
                p1 = x->parent;
                p1->color = 0;
                pp->color = 1;
                Left_Rotate(pp, root);
            }
        }
    }
    root->color = 0;
}

Node *RB_Insert(Node *root){
    int k, n = 1;
    printf("Enter key: ");
    n = getInt(&k);
    root = insert(root, k);
	puts("ADD");
    return root;
}

Node *RB_Delete(Node *root){
    printf("Deleted\n");
    return root;
}

void ShowTree(Node *root, int flag){
    flag += 5;
    if(root == &EList)
        return;
    ShowTree(root->right, flag);
    printf("\n");
    for(int i = 0; i < flag; ++i)
        printf(" ");
    printf("%d . %d\n", root->key, root->color);
    ShowTree(root->left, flag);
}

Node *RB_ShowTree(Node *root){
    ShowTree(root, 0);
    return root;
}

Node *maxNode(Node *root){
    Node *ptr = root;
    Node *par;
    if (ptr == &EList)
        return 0;
    while(ptr != &EList){
        par = ptr;
        ptr = ptr->right;
    }
    return par;
}

Node *RB_MaxNode (Node *root){
	Node *x;
    if (root == NULL)
        return 0;
	x = maxNode(root);
	puts("FIND MAX");
	printf("%d \n", x->key);
	return root;
}

void deltree(Node *p)
{
	if (p != &EList) {
		deltree(p->left);
		deltree(p->right);
		free(p);
	}
}

int dialog (const char *msgs[], int N){
    const char *errmsg = "";
	int rc,i,n;
	do{
		puts(errmsg);
		errmsg = "Wrong input! Please, repeat!";
		for (i = 0; i < N; ++i)
            puts(msgs[i]);
		puts("Make your choice:-->");
		n = getInt(&rc);
		if(n==0)
            rc = 0;
	} while (rc < 0 || rc >= N);
	return rc;
}

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int el;
    struct node * left;
    struct node * right;
};

typedef struct node Node;
typedef Node * Tree;

Tree R_insert(Tree root, int x)
{
    if(!root)
    {
        Tree p = (Tree)malloc(sizeof(Node));
        p -> el = x;
        p -> left = p -> right = NULL;
        return p;
    }
    if(x > root -> el) {
        root -> right = R_insert(root -> right, x);
    } else {
        root -> left = R_insert(root -> left, x);
    }
    return root;
}

void print(Tree root, int lvl) {
    if(root) {
        for (int i = lvl; i; i--) {
            putchar('.');
        }
        printf("%d\n", root -> el);
        print(root -> left, lvl + 1);
        print(root -> right, lvl + 1);
    }
}

void deleteTree(Tree * root) {
    if (*root) {
        deleteTree(&((*root) -> left));
        deleteTree(&((*root) -> right));
        free(*root);
    }
}

void rm_leaves(Tree * root) {
    if ((*root) == NULL) {
        return;
    }
    if ((*root) -> left != NULL && ((*root) -> left) -> left == NULL && ((*root) -> left) -> right == NULL) {
        Tree rt = (*root) -> left;
        (*root) -> left = NULL;
        free(rt);
    }
    if ((*root) -> right != NULL && ((*root) -> right) -> left == NULL && ((*root) -> right) -> right == NULL) {
        Tree rt = (*root) -> right;
        (*root) -> right = NULL;
        free(rt);
    }
    rm_leaves(&((*root) -> left));
    rm_leaves(&((*root) -> right));
}

int main() {
    Tree root = NULL;
    int in;
    scanf("%d", &in);
    while(in) {
        root = R_insert(root, in);
        scanf("%d", &in);
    }
    rm_leaves(&root);
    print(root, 0);
    deleteTree(&root);
    return 0;
}

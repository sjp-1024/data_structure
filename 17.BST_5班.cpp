/***********************************************************
*       &Author: Shi Jinpeng     
*       &E-mail: shi_jinpeng@foxmail.com
*       &Motto: Believe in yourself.
*       &File Name: 17.BST.cpp
*       &Created Time: 19Century 2019年09月12日 星期四 10时09分43秒 
*                          CST  Day/255 and Week/36 of this year
*       &Description:
*
*
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = val;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (root->key == val) return root;
    if (root->key < val) {
        root->rchild = insert(root->rchild, val);
    } else {
        root->lchild = insert(root->lchild, val);
    }
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int val) {
    if (root == NULL) return NULL;
    if (root->key > val) {
        root->lchild = erase(root->lchild, val);
    } else if (root->key < val) {
        root->rchild = erase(root->rchild, val);
    } else {
        if (root->lchild == NULL && root->rchild == NULL) {
            free(root);
            return NULL;
        }
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        }
        Node *temp = predecessor(root);
        root->key = temp->key;
        root->lchild = erase(root->lchild, temp->key);
    }
    return root;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output(Node *root) {
    if (root == NULL) return ;
    int lval = root->lchild ? root->lchild->key : 0;
    int rval = root->rchild ? root->rchild->key : 0;
    printf("(%d, lval = %d,  rval = %d)\n", root->key, lval, rval);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int op, val;
    Node *root = NULL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 1: {
                root = insert(root, val);
            } break;
            case 2: {
                root = erase(root, val);
            } break;
        }
        output(root);
    }
    return 0;
}

/***********************************************************
*       &Author: Shi Jinpeng     
*       &E-mail: shi_jinpeng@foxmail.com
*       &Motto: Believe in yourself.
*       &File Name: 15.DA_Trie.cpp
*       &Created Time: 19Century 2019年08月19日 星期一 21时38分49秒 
*                          CST  Day/231 and Week/33 of this year
*       &Description:
*
*
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 26
#define BASE_LETTER 'a'

typedef struct Node {
    int flag;
    struct Node *next[BASE];
} Node;

typedef struct DANode {
    int base, check;
} DANode;

int cnt = 0;
int letter_cnt = 0;

Node *getNewNode() {
    cnt += 1;
    Node *p = (Node *)calloc(1, sizeof(Node));
    return p;
}

DANode *getDANode(int cnt) {
    DANode *arr = (DANode *)calloc(cnt, sizeof(DANode));
    return arr;
}

void insert(Node *node, const char *s) {
    Node *p = node;
    for (int i = 0; s[i]; i++) {
        if (p->next[s[i] - BASE_LETTER] == NULL) {
            p->next[s[i] - BASE_LETTER] = getNewNode();
        }
        p = p->next[s[i] - BASE_LETTER];
    }
    p->flag = 1;
    return ;
}

int query(Node *node, const char *s) {
    Node *p = node;
    for (int i = 0; s[i]; i++) {
        p = p->next[s[i] - BASE_LETTER];
        if (p == NULL) return 0;
    }
    return p->flag;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

int getBaseValue(Node *root, DANode *darr) {
    int base = 2;
    while (1) {
        int flag = 1;
        for (int i = 0; i < BASE; i++) {
            if (root->next[i] == NULL) continue;
            if (darr[base + i].check == 0) continue;
            flag = 0;
            break;
        }
        if (flag) return base;
        base += 1;
    }
    return base;
}


int trans_trie_to_double_array(Node *root, int ind, DANode *darr) {
    int ans = ind;
    darr[ind].base = getBaseValue(root, darr);
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        darr[darr[ind].base + i].check = ind * (root->next[i]->flag ? -1 : 1);
    }
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        int ret = trans_trie_to_double_array(root->next[i], darr[ind].base + i, darr);
        if (ret > ans) ans = ret;
    }
    return ans;
}

void output_double_array(int ind, int k, DANode *darr, char *buff) {
    if (darr[ind].check < 0) {
        printf("%s\n", buff);
    }
    for (int i = 0; i < BASE; i++) {
        if (abs(darr[darr[ind].base + i].check) - ind) continue;
        buff[k] = BASE_LETTER + i;
        buff[k + 1] = 0;
        output_double_array(darr[ind].base + i, k + 1, darr, buff);
    }
    return ;
}

int main() {
    char str[100];
    int n, m;
    scanf("%d%d", &n, &m);
    Node *root = getNewNode();
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        letter_cnt += strlen(str);
        insert(root, str);
    }
    DANode *darr = getDANode(cnt * 26 + 100);
    int total = trans_trie_to_double_array(root, 1, darr);
    //output_double_array(1, 0, darr, str);
    for (int i = 1; i <= total; i++) {
        printf("(%3d | %3d %3d) ", i, darr[i].base, darr[i].check);
        if (i % 5 == 0) printf("\n");
    }
    printf("\n");
    printf("rate : %lf\n", 1.0 * letter_cnt / (cnt * sizeof(Node)));
    for (int i = 0; i < m; i++) {
        scanf("%s", str);
        printf("query(%s) = %d\n", str, query(root, str));
    }
    return 0;
}

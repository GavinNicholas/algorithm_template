#pragma GCC optimize("O3,no-stack-protector")

#include <bits/stdc++.h>

using namespace std;

#define debug
#define file_io

const size_t data[] = {1, 5, 2, 3, 6, 0, 7, 4, 8};

class Node {
public:
    size_t data;
    Node *next;

    Node() : data(-1), next(nullptr) {}

    Node(int data) : data(data), next(nullptr) {}

    Node(int data, Node *next) : data(data), next(next) {}

    void output() {
        Node *p = this;
        while (p) {
            printf("%zd%s", p->data, p->next != nullptr ? " " : "\n");
            p = p->next;
        }
    }

    void push_back(int val) {
        Node *p = this;
        while (p->next) {
            p = p->next;
        }
        p->next = new Node(val);
    }

    void push_back(Node *t) {
        Node *p = this;
        while (p->next) {
            p = p->next;
        }
        p->next = t;
    }
};

Node *init() {
    Node *L = new Node(data[0]);
    Node *p = L;
    for (size_t i = 1; i < sizeof(data) / sizeof(data[0]); i++) {
        p->next = new Node(data[i]);
        p = p->next;
    }
    return L;
}

vector<Node *> GetIndex(Node *L) {
    vector<Node *> ret;
    ret.push_back(L);
    while (L->next) {
        if (L->next->data < L->data) {
            ret.push_back(L->next);
            Node *p = L;
            L = L->next;
            p->next = nullptr;
        } else {
            L = L->next;
        }
    }
    return ret;
}

void Merge(Node *A, Node *B) {
    Node *L = new Node(-1);
    while (A && B) {
        Node *buff;
        if (A->data < B->data) {
            buff = A;
            A = A->next;
        } else {
            buff = B;
            B = B->next;
        }
        buff->next = nullptr;
        L->push_back(buff);
#ifdef debug
        printf("push_back data %zd, now list is ", buff->data);
        L->output();
#endif
    }
    if (A) {
        L->push_back(A);
#ifdef debug
        printf("push_back left list in A : ");
        A->output();
#endif
    } else {
        L->push_back(B);
#ifdef debug
        printf("push_back left list in B : ");
        B->output();
#endif
    }
    A = L->next;
}

Node *MergeSort(vector<Node *> ve) {
    size_t roundNum = 1;
    while (roundNum < ve.size()) {
        for (size_t i = 0; i + roundNum < ve.size(); i += 2 * roundNum) {
#ifdef debug
            printf("Merge:\n");
            printf("  ");
            ve[i]->output();
            printf("  ");
            ve[i+roundNum]->output();
#endif
            Merge(ve[i], ve[i + roundNum]);
        }
        roundNum <<= 1;
    }
    return ve[0];

}

int main() {
#ifdef file_io
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

#ifdef debug
    puts("this is a list of 'init()'");
    init()->output();
    puts("");
#endif
    vector<Node *> Index = GetIndex(init());
#ifdef debug
    puts("this is lists in vector 'Index'");
    for (auto list : Index) {
        list->output();
    }
    puts("");
#endif
    Node *ans = MergeSort(Index);
    ans->output();

    return 0;
}
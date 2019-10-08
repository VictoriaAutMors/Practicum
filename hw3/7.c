#include <stdio.h>
#include <stdlib.h>

typedef struct node * Link;

struct node {
    int elem;
    Link next;
};

Link push_front(Link list, int elem) {
    Link ptr = (Link)malloc(sizeof(struct node));
    ptr -> elem = elem;
    ptr -> next = list;
    return ptr;
}

Link push_back(Link list, int elem) {
    if (list == NULL || list -> elem > elem) {
        return push_front(list, elem);
    }
    Link ptr = list;
    while (ptr -> next != NULL) {
        if ((ptr -> next) -> elem > elem) {
            Link var = push_front(ptr -> next, elem);
            ptr -> next = var;
            return list;
        }
        ptr = ptr -> next;
    }
    ptr -> next = push_front(NULL, elem);
    return list;
}

void destruct (Link head) {
    Link q;
    while (head != NULL) {
        q = head;
        head = head -> next;
        free (q);
    }
}

void print(Link head) {
    putchar('[');
    for (Link t = head; t != NULL; t = t -> next) {
        printf("%d ", t -> elem);
    }
    putchar(']');
    putchar('\n');
}

int main(void) {
    int input;
    Link list = NULL;
    scanf("%d", &input);
    while(input) {
        list = push_back(list, input);
        print(list);
        scanf("%d", &input);
    }
    destruct(list);
    return 0;
}

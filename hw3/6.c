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

Link push_num(Link list, int elem) {
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

Link create(Link list) {
    int input;
    scanf("%d", &input);
    while(input) {
        list = push_num(list, input);
        scanf("%d", &input);
    }
    return list;
}

Link merge(Link list1, Link list2) {
    Link temp, ptr;
    if (list1 -> elem >= list2 -> elem) {
        temp = list2 -> next;
        list2 -> next = list1;
        list1 = list2;
        list2 = temp;
    }
    ptr = list1;
    while (ptr -> next != NULL && list2 != NULL) {
        if ((ptr -> next) -> elem >= list2 -> elem) {
            temp = list2 -> next;
            list2 -> next = ptr -> next;
            ptr -> next = list2;
            list2 = temp;
        }
        ptr = ptr -> next;
    }
    if (list2 != NULL) {
        ptr -> next = list2;
    }
    return list1;
}

int main(void) {
    Link list_1 = NULL;
    Link list_2 = NULL;
    list_1 = create(list_1);
    list_2 = create(list_2);
    list_1 = merge(list_1, list_2);
    print(list_1);
    destruct(list_1);
    return 0;
}

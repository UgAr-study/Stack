#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int number;
    int* arr;
};

void S_push (struct Stack* MyStack, int elem);
void S_pop (struct Stack* MyStack);
void S_fill (struct Stack* MyStack);
int Num_Check (struct Stack MyStack);
void S_print (struct Stack* MyStack);

int main()
{
    struct Stack MyStack;
    MyStack.number = 0;
    MyStack.arr = (int*) calloc (10, sizeof(int));

    S_fill(&MyStack);
    S_print(&MyStack);

    return 0;
}

void S_push (struct Stack* MyStack, int elem){
    MyStack->arr[MyStack->number] = elem;
    MyStack->number++;
}

void S_pop (struct Stack* MyStack){
    int prin = MyStack->arr[--MyStack->number];
    printf("%d\n", prin);
}

void S_fill (struct Stack* MyStack){

    for (int i = 0; i < 10; i++){
        printf("\nInput the element you want to push: ");
        int elem = 0;
        scanf("%d", &elem);
        S_push(MyStack, elem);
    }

}

int Num_Check (struct Stack MyStack){

    if(MyStack.number == 0) return 0;
    else return 1;
}

void S_print (struct Stack* MyStack){

    for(; ; ) {
        printf("Do you want to know the last element? (Y/N): ");
        getchar();

        if (getchar() == 'Y') {
            if(Num_Check(*MyStack))
                S_pop(MyStack);
            else {
                printf ("Stack is empty\n");
                return;
            }
        }
        else return;
    }
}

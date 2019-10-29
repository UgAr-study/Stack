#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int S_size;
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
    MyStack.S_size = 20;
    MyStack.number = 0;
    MyStack.arr = (int*) calloc (MyStack.S_size, sizeof(int));

    S_fill(&MyStack);
    //S_print(&MyStack);

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

    printf("Do you want to begin your work with Stack?(Y/N): ");
    if (getchar() == 'Y'){
        for (int i = 0; ; i++){

            printf("Do you want to push the element (Y/N) or finish your work(F)? ");
            getchar();
            char c = getchar();

            if (c == 'Y'){

                if (MyStack->number == MyStack->S_size)
                    MyStack->arr = (int*) realloc (MyStack->arr, (MyStack->S_size += 10) * sizeof(int));

                printf("\nInput the element you want to push: ");
                int elem = 0;
                scanf("%d", &elem);
                S_push(MyStack, elem);
            }

            if (c == 'N')
                S_print(MyStack);

            if (c == 'F')
                return;
            else continue;
        }
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
        char c = getchar();

        if (c == 'Y') {
            if(Num_Check(*MyStack))
                S_pop(MyStack);
            else {
                printf ("Stack is empty\n");
                return;
            }
        }
        if (c == 'N') return;
    }
}

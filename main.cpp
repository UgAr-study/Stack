#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>


void Print (int i) {printf ("%d ", i);}
void Print (double d) {printf ("%lg ", d);}
void Print (char c) {printf ("%c ", c);}

void Scan (int* i) {scanf ("%d", i);}
void Scan (double* d) {scanf ("%lg", d);}
void Scan (char* c) {scanf ("%c", c);}

template <typename T>

class Stack {
public:
    int d_size_;
    int number;
    T* data_;
public:
    Stack(int a);
    Stack(const Stack& object);
    ~Stack();
    void Push(T val);
    void Pop();
};

template <typename T>
void ReFill (Stack <T> obj);

template <typename T>
void S_print (Stack <T> obj);

int main() {    //!!!!!!!!!!!!!!!!!!

    Stack <int> obj1 (10);
    ReFill(obj1);
    S_print(obj1);

    return 0;
}               //!!!!!!!!!!!!!!!!!!

template <typename T>
Stack <T>::Stack(int a){

    d_size_ = a;
    printf("construct\n");
    data_ = (T*) calloc (d_size_, sizeof(T));
    assert(data_ != NULL);

    for (int i = 0; i < d_size_; i++) {
        data_[i] = 1;
    }

    for(int i = 0; i < d_size_; i++)
        Print(data_[i]);
    printf("\n");
}

template <typename T>
Stack <T>::Stack(const Stack& object){

    printf ("Copy\n d_size = ");
    Print(object.d_size_);
    printf("\n");

    d_size_ = object.d_size_;
    number = object.number;

    data_ = (T*)calloc(d_size_, sizeof(T));
    assert(data_ != NULL);

    //memcpy (data_, object.data_, d_size_);

    for(int i = 0; i < d_size_; i++)
        data_[i] = object.data_[i];
}


template <typename T>
Stack <T>::~Stack(){
    printf("distruct\n");
    free(data_);
}

template <typename T>
void Stack <T>::Push(T val){
    this->data_[this->number++] = val;
}

template <typename T>
void Stack <T>::Pop(){
    Print(this->data_[--this->number]);
}

template <typename T>
void S_print(Stack <T> obj){

    for (int i = 0; i < obj.d_size_; i++){
        Print(obj.data_[i]);
    }

    printf("\n");
}

template <typename T>
void ReFill(Stack <T> obj){

    for(int i = 0; i < obj.d_size_; i++){
        obj.data_[i] = 2;
    }

    printf("after refilling:\n");
    S_print(obj);
}

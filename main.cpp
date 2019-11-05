#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>

#define D_SIZE 20

class Stack {
private:
    int canary1;
    int d_size_;
    int number;
    int* data_;
    int hash1, hash2;
    int canary2;
    friend bool Check_Hash(const Stack*);
    friend void S_print(Stack&);
public:
    Stack();
    Stack(const Stack& object);
    ~Stack();
    bool Push(int val);
    bool Pop();

};


int main() {    //!!!!!!!!!!!!!!!!!!

    Stack obj1;
    obj1.Pop();
    obj1.Pop();
    obj1.Push(1);
    obj1.Pop();
    //obj1.Push(13);
    S_print(obj1);

    return 0;
}               //!!!!!!!!!!!!!!!!!!

bool Check_Hash(const Stack* object){   //true = everything is OK; else false

    int check1 = 0, check2 = 1;

    for (int i = 0; i <= object->number; i++){
        check1 = (check1 + ((i + 1) % 131) * ((object->data_[i]) % 131)) % 131;
        check2 = (check2 * ((i + object->data_[i]) % 131)) % 131;
    }

    //printf("Checking: check1 = %d\tcheck2 = %d\n", check1, check2);

    if(check1 == object->hash1 && check2 == object->hash2)
        return true;

    else {
        printf("----ERROR----hash is not true\n");
        return false;
    }
}

Stack::Stack(){

    d_size_ = D_SIZE;
    hash1 = 0;
    hash2 = 0;
    number = -1;
    printf("construct\n");
    data_ = (int*) calloc (d_size_, sizeof(int));
    assert(data_ != NULL);

    int i = 0;
    while(Push(i + 1))
        i++;

    for(int i = 0; i < d_size_; i++)
        printf("%d ", data_[i]);
    printf("\n");
}

Stack::Stack(const Stack& object){

    if (!Check_Hash(&object))
        return;

    printf ("Copy\n d_size = ");
    printf("%d", object.d_size_);
    printf("\n");

    d_size_ = object.d_size_;
    number = object.number;
    hash1 = object.hash1;
    hash2 = object.hash2;

    data_ = (int*)calloc(d_size_, sizeof(int));
    assert(data_ != NULL);

    for(int i = 0; i < d_size_; i++)
        data_[i] = object.data_[i];

}


Stack::~Stack(){

    if (!Check_Hash(this))
        return;

    printf("distruct\n");
    free(data_);
}

bool Stack::Push(int val){

    if (this->number != -1){
        if(!Check_Hash(this))
            return false;
    }

    if (this->number == this->d_size_ - 1){
        printf("stack is over\n");
        return false;
    }

    this->data_[++this->number] = val;

    hash1 = 0;
    hash2 = 1;

    for(int i = 0; i <= this->number; i++){
        this->hash1 = (this->hash1 + ((i + 1) % 131) * ((this->data_[i]) % 131)) % 131;
        this->hash2 = (this->hash2 * ((i + this->data_[i]) % 131)) % 131;
        //printf("in for.Push: hash1 = %d\thash2 = %d\n", hash1, hash2);
    }

    return true;
}

bool Stack::Pop(){

    if(!Check_Hash(this))
        return false;

    printf("data[%d] = %d\n", number + 1, this->data_[this->number]);
    number--;

    this->hash1 = 0;
    this->hash2 = 1;
    for(int i = 0; i <= this->number; i++){
        this->hash1 = (this->hash1 + ((i + 1) % 131) * ((this->data_[i]) % 131)) % 131;
        this->hash2 = (this->hash2 * ((i + this->data_[i]) % 131)) % 131;
        //printf("in for.Pop: hash1 = %d\thash2 = %d\n", hash1, hash2);
    }
    return true;
}

void S_print(Stack& obj){

    for (int i = 0; i <= obj.number; i++){
        printf("%d ", obj.data_[i]);
    }

    printf("\n");
}
//
//void ReFill(Stack obj){
//
//    for(int i = 0; i < obj.d_size_; i++){
//        obj.data_[i] = 2;
//    }
//
//    printf("after refilling:\n");
//    S_print(obj);
//}

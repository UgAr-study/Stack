#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include <time.h>

//в дуструкторе удалять вообще все, но сначала испортить все данные, потом у переменных брать адрес и free

typedef unsigned long long ull;

class Stack {
private:
    ull canary1;

    int d_size_;
    int number;
    char* data_;
    int shaf1, shaf2;
    int flag;

    int Hash1();
    int Hash2();
    int Hash3();
    int Hash4();
    int Hash5();
    int Hash6();
    int (Stack::*foo[6]) () = {&Stack::Hash1, &Stack::Hash2, &Stack::Hash3, &Stack::Hash4, &Stack::Hash5, &Stack::Hash6};

    int hash1, hash2;

    int Ok();
    void Shafle();

    ull canary2;

    friend bool Check_Hash(Stack*);
    friend void S_print(Stack&);

public:
    Stack();
    void IncData();
    Stack(const Stack& object);
    ~Stack();
    bool Push(int val);
    bool Pop();
    //bool Check_Canary();
};

typedef int (Stack::*pf)();

class random_int{
private:
    int ran;
//    friend bool Stack::Check_Canary();
public:
    random_int(){
        srand(time(NULL));
        ran = rand() % 10000;
    }
};

//const static random_int canary1;
//const static random_int canary2;


int main() {    //!!!!!!!!!!!!!!!!!!

    Stack obj1;
    obj1.Pop();
    obj1.Pop();
    obj1.Push(1);
    obj1.Pop();
    //obj1.Push(13);
    //S_print(obj1);

    return 0;
}               //!!!!!!!!!!!!!!!!!!



//bool Stack::Check_Canary(){
//
//    if(canary1.ran != canary1 || canary2.ran != canary2)
//        return false;
//
//    return true;
//}

int Stack::Hash1(){
    int hash_ = 0;
    for(int i = 0; i <= this->number; i++){
        hash_ = 111;
//        hash_ = (hash_ + ((i + 1) % 131) * ((this->data_[i]) % 131)) % 131;
    }
    return hash_;
}

int Stack::Hash2() {
    int hash_ = 0;
    for (int i = 0; i <= number; i++){
         hash_ = 222;
//        hash_ = (hash_ + data_[i] % 131);
    }
    return hash_;
}

int Stack::Hash3() {
    int hash_ = 2;
    for (int i = 0; i <= number; i++){
        hash_ = 333;
//        hash_ = (hash_ * (data_[i] % 131)) % 131;
    }
    return hash_;
}

int Stack::Hash4() {
    int hash_ = 1;
    for (int i = 0; i < number; i++)
        hash_ = 444;
//        hash_ = (hash_ * ((i + this->data_[i]) % 131)) % 131;
    return hash_;
}

int Stack::Hash5() {
    int hash_ = 1;
    for (int i = 0; i < number; i++)
        hash_ = 555;
//        hash_ = (hash_ * (data_[i] % 131)) % 131;
    return hash_;
}

int Stack::Hash6() {
    int hash_ = 1;
    for (int i = 0; i < number; i++)
        hash_ = 666;
//        hash_ = (hash_ + data_[i] % 131);
    return hash_;
}

bool Check_Hash(Stack* object){   //true = everything is OK; else false

    pf hash1 = object->foo[object->shaf1];
    pf hash2 = object->foo[object->shaf2];

    int check1 = (object->*hash1)();
    int check2 = (object->*hash2)();

    printf("Checking: check1 = %d\tcheck2 = %d\n", check1, check2);

    if (check1 == object->hash1 && check2 == object->hash2){
        return true;
    } else {
        //printf("----ERROR----hash is not true\n");
        return false;
    }

}

int Stack::Ok(){    //0 если взломали данные стека, -1 если взломали массив, 1 если все ок

    if (canary1 != 88005553535 || canary2 != 53535550088)
        return 0;

    if ((ull)*data_ != canary1 || (ull)*(data_ + 2 + d_size_) != canary2)
        return -1;

    return 1;
}

//int (Stack::*Stack::Shafle())(int* shaf) {
void Stack::Shafle (){

    int ran1 = rand() % 6;
    shaf1 = ran1;

    int ran2 = rand() % 6;
    shaf2 = ran2;
}

Stack::Stack(){

    flag = 0;
    canary1 = 88005553535;
    canary2 = 53535550088;

    d_size_ = 20;
    number = sizeof(ull);

    printf("construct\n");

    data_ = (char*) calloc (d_size_ * sizeof(int) + 2 * sizeof (ull), sizeof(char));
    assert(data_ != NULL);

    *data_ = canary1;
    *(data_ + sizeof(ull) + d_size_ * sizeof (int)) = canary2;

    srand(time(NULL));
    shaf1 = 0;
    shaf2 = 1;

    pf p1 = foo[shaf1];
    pf p2 = foo[shaf2];

    hash1 = (this->*p1)();
    hash2 = (this->*p2)();

    for (int i = 0; i < 20; i++)
        Push(i + 1);

    //for(int i = 0; i < d_size_; i++)
    //    printf("%d ", data_[i]);

    printf("\n");
}

Stack::Stack(const Stack& object){

    if (flag == 1)
        return;

    flag++;
    Stack fake_obj = object;
    flag = 0;

    if (!Check_Hash(&fake_obj))
        return;

    printf ("Copy\n d_size = ");
    printf("%d", object.d_size_);
    printf("\n");

    canary1 = object.canary1;
    d_size_ = object.d_size_;
    number = object.number;
    hash1 = object.hash1;
    hash2 = object.hash2;
    shaf1 = object.shaf1;
    shaf2 = object.shaf2;
    flag = object.flag;
    canary2 = object.canary2;

    data_ = (char*) calloc (d_size_ * sizeof(int) + 2 * sizeof (ull), sizeof(char));
    assert(data_ != NULL);

    *data_ = canary1;
    for(unsigned i = sizeof(ull); i < sizeof (ull) + d_size_ * sizeof (int); i += sizeof (int))
        data_[i] = object.data_[i];

    *(data_ + sizeof (ull) + d_size_ * sizeof (int)) = canary2;
}

void Stack::IncData(){

    data_ = (char*) realloc (data_, (d_size_ + sizeof (ull) / sizeof (int)) * sizeof (int));
    d_size_ += 10;

    data_ = (char*) realloc (data_, (d_size_ + 2 * sizeof (ull) / sizeof (int)) * sizeof (int));
    *(data_ + 2 + d_size_) = canary2;
}

Stack::~Stack(){

    if (!Check_Hash(this))
        return;

    printf("distruct\n");
    free(data_);
}

bool Stack::Push(int val){

    if (this->number > (int)sizeof(ull)){
        if(!Check_Hash(this))
            return false;
    }

    if (number == (int) (sizeof(ull) + d_size_ * sizeof (int)))
        this->IncData();

    this->data_[this->number] = val;
    number += sizeof (int);

    Shafle();

    pf p1 = foo[shaf1];
    pf p2 = foo[shaf2];

    hash1 = (this->*p1)();
    hash2 = (this->*p2)();

    return true;
}

bool Stack::Pop(){

    if(!Check_Hash(this))
        return false;

    int num = (number - sizeof (ull)) / sizeof (int);
    printf("data[%d] = %d\n", num, this->data_[this->number - sizeof(int)]);
    number -= sizeof (int);

    Shafle();

    pf p1 = foo[shaf1];
    pf p2 = foo[shaf2];

    hash1 = (this->*p1)();
    hash2 = (this->*p2)();

    return true;
}

void S_print(Stack& obj){

    for (int i = 0; i <= obj.number; i++){
        printf("%d ", obj.data_[i]);
    }

    printf("\n");
}

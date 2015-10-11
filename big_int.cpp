#include "big_int.h"

bigInt::bigInt(){
    this->num.push_back(0);
}

void bigInt::bigIntInit(){
    for (int i = 0; i < this->size; i++){  // initializing all elements to zero.
        this->num[i] = 0;
    }
}

void bigInt::bigIntSet(std::string s){
    int lim = s.length() - 1;
    char test[] = "-";
    if (s[0] == test[0]){
        this->isNegative = 1;
        for (int i = 1; i <= lim; i++){
            this->num[lim - i] = s[i] - '0';
        }
        this->num.pop_back();
        this->size -= 1;
    }
    else{
        this->isNegative = 0;
        for (int i = 0; i <= lim; i++){
            this->num[lim - i] = s[i] - '0';
        }
    }
}

bigInt::bigInt(std::string _s){
    this->size = _s.length();
    this->limit = size - 1;
    this->num.resize(size);
    this->bigIntInit();
    this->bigIntSet(_s);
}


void bigInt::incr(){
    this->num[0]++;
    for (int i = 0; i <= limit -1 ; i++){
        this->num[i + 1] += this->num[i] / 10;
        this->num[i] = this->num[i] % 10;
    }

}

void bigInt::decr(){
    int subtractor = 1;
    if (this->num[0] > 0){
        this->num[0]--;
    }
    else
    {

        for (int i = 0; i <= this->limit; i++){
            if (this->num[i] - subtractor < 0){
                this->num[i] = (10 + ~this->num[i]) % 10;
                //this->num[i + 1] -= subtractor;
            }
        }
        this->num.pop_back();
        this->limit -= 1;
    }

}




void bigInt::print(){
    this->pretty();
    this->limit = this->num.size() - 1;
    if (this->isNegative){
        std::cout << "-";
    }
    for (int i = limit; i >= 0; i--){
        std::cout << num[i];
    }
    std::cout << "\n";
}

void bigInt::pretty(){
    int end = this->num.size()-1;
    for (int i = end; i >= 0; i--){
        if ((this->num[i] == 0) && (this->num.size() != 1)){
            this->num.pop_back();
        }
        else
        {
            break;
        }
    }
}

void bigInt::comp(){
    this->limit = this->num.size() - 1;
    for (int i = 0; i <= this->limit; i++){
        this->num[i] = 10 + ~this->num[i];
    }
}

void bigInt::parseString(std::string str){
    this->num.resize(str.length());
    this->limit = this->num.size() - 1;
    bigIntInit();
    bigIntSet(str);
}

bigInt addBigInt(bigInt a, bigInt b){
    while (b.num.size() < a.num.size()){
        b.num.push_back(0);
    }
    while (b.num.size() > a.num.size()){
        a.num.push_back(0);
    }
    a.limit = b.num.size() - 1;
    b.limit = b.num.size() - 1;


    if(!a.isNegative && b.isNegative){
        b.comp();
        b.incr();

        for (int i = 0; i <= a.limit; i++){
            a.num[i] += b.num[i];
        }

        for (int i = 0; i <= a.limit - 1; i++){
            a.num[i + 1] += a.num[i] / 10;
            a.num[i] = a.num[i] % 10;
        }

// If "a" does not have carry and the sign of "a" and "b" are different
// then use complement to find the correct solution.

        if (a.num[a.limit] <= 9){
            a.comp();
            a.incr();
            a.isNegative = 1;
        }
        a.num[a.limit] = a.num[a.limit] % 10;

        return a;

    }
    else if (a.isNegative && !b.isNegative){
        a.comp();
        a.incr();
        for (int i = 0; i <= b.limit; i++){
            b.num[i] += a.num[i];
        }
        for (int i = 0; i <= a.limit - 1; i++){
            b.num[i + 1] += b.num[i] / 10;
            b.num[i] = b.num[i] % 10;
        }

        if (b.num[b.limit] <= 9){
            b.comp();
            b.incr();
            b.isNegative = 1;
        }
        b.num[b.limit] = b.num[b.limit] % 10;


        return b;
    }
    else if (a.isNegative && b.isNegative){
        for (int i = 0; i <= a.limit; i++){
            a.num[i] += b.num[i];
        }
        for (int i = 0; i <= a.limit - 1; i++){
            a.num[i + 1] += a.num[i] / 10;
            a.num[i] = a.num[i] % 10;
        }
        a.isNegative = 1;
        return a;
    }
    else{
        for (int i = 0; i <= a.limit; i++){
            a.num[i] += b.num[i];
        }
        for (int i = 0; i <= a.limit - 1; i++){
            a.num[i + 1] += a.num[i] / 10;
            a.num[i] = a.num[i] % 10;
        }
        return a;
    }




}

bigInt subtractBigInt(bigInt a, bigInt b){
    while (b.num.size() < a.num.size()){
            b.num.push_back(0);
    }
    while (b.num.size() > a.num.size()){
        a.num.push_back(0);
    }
    a.limit = b.num.size() - 1;
    b.limit = b.num.size() - 1;

    b.isNegative = !b.isNegative;

    a = addBigInt(a, b);
    return a;

}

bigInt multiplyBigInt(bigInt a, bigInt b){
    bigInt product("0");
    bigInt greater("0");
    bigInt lesser("0");

    if (b.num.size() > a.num.size()){
        greater = b;
        lesser = a;
    }
    else{
        greater = a;
        lesser = b;
    }
    product.num.resize(a.num.size() + b.num.size());
    product.size = product.num.size();
    product.bigIntInit();
    int k = 0;
    for (int i = 0; i < lesser.size; i++){
        for (int j = 0; j < greater.size; j++){
            product.num[j+k] += greater.num[j] * lesser.num[i];
        }
        k++;
    }
    for (int i = 0; i < product.size - 1; i++){
        product.num[i + 1] += product.num[i] / 10;
        product.num[i] = product.num[i] % 10;
    }
    if (a.isNegative != b.isNegative){
        product.isNegative = 1;
    }
    return product;

}

bigInt R;								// Global value for remainder calculation

bigInt divideBigInt(bigInt a, bigInt b){
    bigInt quotient;
    bigInt greater;
    bigInt lesser;
    bigInt zero;

    if (b.num.size() > a.num.size()){
        return zero;
    }
    else{
        greater = a;
        lesser = b;
    }
    quotient.num.resize(greater.num.size());
    while (greater.num.size() >= lesser.num.size()){
        greater.pretty();
        if (((greater.num.size() == lesser.num.size()) && (greater.num[greater.num.size() - 1] < lesser.num[lesser.num.size() - 1])) || (greater.num.size() < lesser.num.size())){
            R = greater;
            break;
        }
        else{
            quotient.incr();
            greater = subtractBigInt(greater, lesser);

        }
    }
    if (a.isNegative != b.isNegative){
        quotient.isNegative = 1;
    }
    return quotient;
}

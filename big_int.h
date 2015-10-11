#ifndef bigint_h
#define bigint_h

#include <iostream>
#include <string>
#include <vector>

class bigInt{
public:
    bigInt();
    bigInt(std::string _s);

    
    std::vector <int> num = {0};

    bool isNegative;
    void bigIntInit();
    void incr();
    void decr();
    void print();
    void pretty();
    void comp();
    void parseString(std::string str);

private:
    void bigIntSet(std::string s);
};

bigInt addBigInt(bigInt, bigInt);
bigInt subtractBigInt(bigInt, bigInt);
bigInt multiplyBigInt(bigInt, bigInt);
bigInt divideBigInt(bigInt, bigInt, bigInt&);

#endif

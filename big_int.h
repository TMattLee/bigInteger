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
	void cleanCarries();
    void increment();
	void print();
    void removeLeadZeroes();
    void complement();
    void parseString(std::string str);

	bigInt operator+(const bigInt& b);
	bigInt operator-(const bigInt& b);
	bigInt operator*(const bigInt& b);
	bigInt operator/(const bigInt& b);
	bigInt operator=(const long long& b);
	bigInt operator=(const std::string & b);
	bigInt operator=(const char * b);



private:
    void bigIntSet(std::string s);
};


bigInt addBigInt(bigInt, bigInt);
bigInt subtractBigInt(bigInt, bigInt);
bigInt multiplyBigInt(bigInt, bigInt);

bool operator==(bigInt a, bigInt b);
bool isEqual(bigInt a, bigInt b);

bool isNotEqual(bigInt a, bigInt b);
bool operator!=(bigInt a, bigInt b);

//bool isLessThan(bigInt a, bigInt b);
bool operator<(bigInt a, bigInt b);
bool operator>(bigInt a, bigInt b);
bool operator>=(bigInt a, bigInt b);
bool operator<=(bigInt a, bigInt b);


bigInt divideBigInt(bigInt, bigInt, bigInt&);


#endif
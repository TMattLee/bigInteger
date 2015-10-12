#include "big_int.h"

bigInt::bigInt(){
	this->num.push_back(0);
}

bigInt::bigInt(std::string _s){
	this->num.resize(_s.length());
	bigIntInit();
	bigIntSet(_s);
}

void bigInt::bigIntInit(){
	for (int i = 0; i < this->num.size(); i++){  // initializing all elements to zero.
		this->num[i] = 0;
	}
}

void bigInt::bigIntSet(std::string s){
	int lim = s.length() - 1;
	char test[] = "-";
	if (s[0] == test[0]){
		this->isNegative = 1;
		for (int i = 1; i <= lim; i++){
			this->num[lim - i] = s[i] - 48;
		}
		this->num.pop_back();
	}
	else{
		this->isNegative = 0;
		for (int i = 0; i <= lim; i++){
			this->num[lim - i] = s[i] - '0';
		}
	}
}

void bigInt::incr(){
	this->num[0]++;
	if (this->num.size() == 1){									// Necessary to keep within vector bounds
		this->num.push_back(0);
	}
	for (int i = 0; i <= this->num.size() - 2; i++){
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
		for (int i = 0; i <= this->num.size()-1; i++){
			if (this->num[i] - subtractor < 0){
				this->num[i] = (10 + ~this->num[i]) % 10;
			}
		}
		this->num.pop_back();
	}
}

bigInt addBigInt(bigInt a, bigInt b){
	if (a.num.size() == 1){									// Necessary to keep within vector bounds
		a.num.push_back(0);
	}
	while (b.num.size() < a.num.size()){					// Make vectors the same size.
		b.num.push_back(0);
	}
	while (b.num.size() > a.num.size()){
		a.num.push_back(0);
	}
	
	
	
	if (!a.isNegative && b.isNegative){						// Perform subtraction is b is negative
		b.comp();
		b.incr();

		for (int i = 0; i <= a.num.size() - 1; i++){					// Add vector elements
			a.num[i] += b.num[i];
		}

		for (int i = 0; i <= a.num.size() - 1 - 1; i++){				// Perform carries
			a.num[i + 1] += a.num[i] / 10;
			a.num[i] = a.num[i] % 10;
		}

		/* If "a" does not have carry and the sign of "a" and "b" are different
		then use complement to find the correct solution.*/

		if (a.num[a.num.size() - 1] <= 9){
			a.comp();
			a.incr();
			a.isNegative = 1;
		}
		a.num[a.num.size() - 1] = a.num[a.num.size() - 1] % 10;
		return a;
	}
	else if (a.isNegative && !b.isNegative){
		a.comp();
		a.incr();
		for (int i = 0; i <= b.num.size() - 1; i++){
			b.num[i] += a.num[i];
		}
		for (int i = 0; i <= a.num.size() - 1 - 1; i++){
			b.num[i + 1] += b.num[i] / 10;
			b.num[i] = b.num[i] % 10;
		}
		if (b.num[b.num.size() - 1] <= 9){
			b.comp();
			b.incr();
			b.isNegative = 1;
		}
		b.num[b.num.size() - 1] = b.num[b.num.size() - 1] % 10;
		return b;
	}
	else if (a.isNegative && b.isNegative){
		for (int i = 0; i <= a.num.size() - 1; i++){
			a.num[i] += b.num[i];
		}
		for (int i = 0; i <= a.num.size() - 1 - 1; i++){
			a.num[i + 1] += a.num[i] / 10;
			a.num[i] = a.num[i] % 10;
		}
		a.isNegative = 1;
		return a;
	}
	else{
		for (int i = 0; i <= a.num.size() - 1; i++){
			a.num[i] += b.num[i];
		}
		for (int i = 0; i <= a.num.size() - 1 - 1; i++){
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
	b.isNegative = !b.isNegative;							// Subtraction is adding the negative of b
	a = addBigInt(a, b);
	return a;
}

bigInt multiplyBigInt(bigInt a, bigInt b){
	bigInt product("0");
	bigInt greater("0");
	bigInt lesser("0");

	if (b.num.size() > a.num.size()){						// Find vector with most elements
		greater = b;
		lesser = a;
	}
	else{
		greater = a;
		lesser = b;
	}
	product.num.resize(a.num.size() + b.num.size());		// Getting magnitude of product 
	product.bigIntInit();
	int k = 0;
	for (int i = 0; i < lesser.num.size(); i++){					// By hand style multiplacation
		for (int j = 0; j < greater.num.size(); j++){
			product.num[j + k] += greater.num[j] * lesser.num[i];
		}
		k++;
	}
	for (int i = 0; i < product.num.size() - 1; i++){
		product.num[i + 1] += product.num[i] / 10;
		product.num[i] = product.num[i] % 10;
	}
	if (a.isNegative != b.isNegative){
		product.isNegative = 1;
	}
	return product;
}

bigInt divideBigInt(bigInt a, bigInt b,bigInt  &r){
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
			r = greater;
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

void bigInt::print(){
	this->pretty();
	if (this->isNegative){
		std::cout << "-";
	}
	for (int i = num.size() - 1; i >= 0; i--){
		std::cout << num[i];
	}
	std::cout << "\n";
}

void bigInt::pretty(){
	int end = this->num.size() - 1;
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
	for (int i = 0; i <= this->num.size() - 1; i++){
		this->num[i] = 10 + ~this->num[i];
	}
}
void bigInt::parseString(std::string str){
    this->bigIntSet(str);
}

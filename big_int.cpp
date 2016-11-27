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
	for (unsigned long i = 0; i < this->num.size(); i++){  // initializing all elements to zero.
		this->num[i] = 0;
	}
}

void bigInt::bigIntSet(std::string s){
	unsigned long lim = s.length() - 1;
	char test[] = "-";
	if (s[0] == test[0]){
		this->isNegative = 1;
		for (unsigned long i = 1; i <= lim; i++){
			this->num[lim - i] = s[i] - 48;
		}
		this->num.pop_back();
	}
	else{
		this->isNegative = 0;
		for (unsigned long i = 0; i <= lim; i++){
			this->num[lim - i] = s[i] - '0';
		}
	}
}


void::bigInt::cleanCarries() {
	//--------------------------------------------------------------------
	// This method processes numeric carries on elements greater than 9 
	//--------------------------------------------------------------------

	if (this->num.size() < 2) {
		if (this->num[this->num.size() - 1] > 9) {
			this->num.push_back(this->num[this->num.size() - 1] / 10);
			this->num[this->num.size() - 2] = this->num[this->num.size() - 2] % 10;
		}
	}
	else {
		for (unsigned long i = 0; i <= this->num.size() - 2; i++) {
			this->num[i + 1] += this->num[i] / 10;
			this->num[i] = this->num[i] % 10;
		}
		
	}
	if (this->num[this->num.size() - 1] > 9) {
		this->num.push_back(this->num[this->num.size() - 1] / 10);
		this->num[this->num.size() - 2] = this->num[this->num.size() - 2] % 10;
	}
}

void bigInt::increment(){
	this->num[0]++;
	this->cleanCarries();
	
}





//-------------------------- Arithmetic operations and assignments -------------------------------

bigInt bigInt::operator=(const long long& b) {
	std::string intString = std::to_string(b);
	bigInt R(intString);
	*this = R;
	return *this;
}

bigInt bigInt::operator=(const char * b) {
	bigInt R(b);
	*this = R;
	return *this;
}

bigInt bigInt::operator=(const std::string& b) {
	bigInt R(b);
	*this = R;
	return *this;
}



// Peform addition or subtraction using 10's complement

bigInt addBigInt(bigInt a, bigInt b){
	//------------------------------------------------
	// First Make the vectors the same size in order
	// to perform operations on each element.
	//------------------------------------------------
	while (b.num.size() < a.num.size()){					
		b.num.push_back(0);
	}
	while (b.num.size() > a.num.size()){
		a.num.push_back(0);
	}
	
	
	if (!a.isNegative && b.isNegative){						
		
		// Perform subtraction if b is negative
		b.complement();
		b.increment();

		for (unsigned long i = 0; i <= a.num.size() - 1; i++){					
			// Add vector elements 
			a.num[i] += b.num[i];
		}

		a.cleanCarries();
		
		//---------------------------------------------------------------
		// If "a" does not have carry and the signs of "a" and "b"
		// are different then use its complement to find the correct solution.
		// If they are of equal size then there is no final carry.
		//---------------------------------------------------------------

		if (a.num.size() == b.num.size()){

			a.complement();
			a.increment();
			a.isNegative = 1;
		}
		else {
			a.num[a.num.size() - 1] = a.num[a.num.size() - 1] % 10;
			a.num.pop_back(); // removes leading 1
		}
		return a;
	}
	else if (a.isNegative && !b.isNegative){
		a.complement();
		a.increment();

		for (unsigned long i = 0; i <= b.num.size() - 1; i++){
			b.num[i] += a.num[i];
		}

		b.cleanCarries();

		//---------------------------------------------------------------
		// If "b" does not have carry and the signs of "a" and "b"
		// are different then use its complement to find the correct solution.
		// If they are of equal size then there is no final carry.
		//---------------------------------------------------------------

		if (a.num.size() == b.num.size()){   
			b.complement();
			b.increment();
			b.isNegative = 1;
		}
		else {
			b.num[b.num.size() - 1] = b.num[b.num.size() - 1] % 10;
			b.num.pop_back(); // removes leading 1
		}
		return b;
	}
	else if (a.isNegative && b.isNegative){
		for (unsigned long i = 0; i <= a.num.size() - 1; i++){
			a.num[i] += b.num[i];
		}
		a.cleanCarries();
		a.isNegative = 1;
		return a;
	}
	else{
		for (unsigned long i = 0; i <= a.num.size() - 1; i++){
			a.num[i] += b.num[i];
		}
		a.cleanCarries();
		return a;
	}
}

bigInt bigInt::operator+(const bigInt &b) {
	return(addBigInt(*this, b));
}


bigInt subtractBigInt(bigInt a, bigInt b){
	
	b.isNegative = !b.isNegative;							// Subtraction is adding the negative of b
	bigInt c = addBigInt(a, b);
	return c;
}

bigInt bigInt::operator-(const bigInt &b) {
	return(subtractBigInt(*this, b));
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
	product.num.resize(a.num.size() + b.num.size());		// Get the magnitude of the product 
	product.bigIntInit();
	int k = 0;
	for (unsigned long i = 0; i < lesser.num.size(); i++){					// By hand style multiplacation
		for (unsigned long j = 0; j < greater.num.size(); j++){
			product.num[j + k] += greater.num[j] * lesser.num[i];
		}
		k++;
	}
	product.cleanCarries();
	if (a.isNegative != b.isNegative){
		product.isNegative = 1;
	}
	return product;
}

bigInt bigInt::operator*(const bigInt &b) {
	return(multiplyBigInt(*this, b));
}


//-------------------------- Comparisons and operator assignments --------------------------------

bool isEqual(bigInt a, bigInt b) {
	if (a.num.size() == b.num.size()) {
		for (unsigned long a_i = 0; a_i < a.num.size(); a_i++) {
			if (a.num[a_i] != b.num[a_i]) {
				return 0;
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}

bool operator==(bigInt a, bigInt b) {
	return isEqual(a, b);
}

bool isNotEqual(bigInt a, bigInt b) {
	if (a==b){
		return 0;
	}
	else {
		return 1;
	}
}

bool operator!=(bigInt a, bigInt b) {
	return isNotEqual(a, b);
}


bool operator<(bigInt a, bigInt b) {
	bigInt c = a-b;
	if (c.isNegative) {
		return 1;
	}
	else {
		return 0;
	}
	return 0;
}

bool operator>(bigInt a, bigInt b) {
	return b < a;
}

bool operator<=(bigInt a, bigInt b) {
	return !(a > b);
}

bool operator>=(bigInt a, bigInt b) {
	return !(a < b);
}


//-------------------------- Division Algorithm and operator assignment --------------------------------


bigInt divideBigInt(bigInt a, bigInt b) {
	bigInt greater;
	bigInt lesser;
	bigInt r;
	const bigInt zero("0");
	const bigInt ten("10");
	const bigInt one("1");
	bigInt divisor = b;
	bigInt dividend = a;
	

	//- Both values are made positive to simply calculations
	divisor.isNegative = false;
	dividend.isNegative = false;

	if (dividend < divisor) {		
		return zero;
	}
	else if (dividend == divisor) {
		
		return one;
	}
	else {
		bigInt quotient = zero;
		if (a.num.size() == b.num.size()) {
			
			while ((a -b) > zero) {
				quotient.increment();
				a = a - b;				
			}
			return quotient;
		}
		else { 
			//-------------------------------------------------------
			// use long division here to reduce calculation time when a >> b
			//
			
			bigInt loopCounter = zero;
			std::string loopBuf = std::to_string(dividend.num.size() * 5);
			bigInt loopLimit(loopBuf);
			while (dividend > divisor) {
				bigInt buf = divisor;
				bigInt tensPlace = one;
				while (buf*ten < dividend) {
					buf = buf*ten;			
					tensPlace = tensPlace * ten;
				}
				while (dividend - buf >= zero) {
					quotient = quotient + tensPlace;
					dividend = dividend - buf;
				}
				loopCounter.increment();
				if (loopCounter > loopLimit) {
					std::cout << "Error: Calculation entered infinite loop.\n" << "Quotient is currently: ";
					quotient.print();
					std::cout << "Calculation cyles: ";
					loopCounter.print();
					std::cout << "Consider revising algorithm.\n";
					break;
				}
			}
			if ((!a.isNegative == b.isNegative)) {
				quotient.isNegative = true;
			}
			return quotient;

		}
	}



	/*if (b.num.size() > a.num.size()) {
		return zero;
	}
	else {
		greater = a;
		lesser = b;
	}
	quotient.num.resize(greater.num.size());
	while (greater.num.size() >= lesser.num.size()) {
		greater.removeLeadZeroes();
		if (((greater.num.size() == lesser.num.size()) && (greater.num[greater.num.size() - 1] < lesser.num[lesser.num.size() - 1])) || (greater.num.size() < lesser.num.size())) {
			r = greater;
			break;
		}
		else {
			quotient.increment();
			greater = subtractBigInt(greater, lesser);

		}
	}
	if (a.isNegative != b.isNegative) {
		quotient.isNegative = 1;
	}
	return quotient;*/
}

bigInt bigInt::operator/(const bigInt &b) {
	return(divideBigInt(*this, b));
}



void bigInt::print(){
	this->removeLeadZeroes();
	if (this->isNegative){
		std::cout << "-";
	}
	for (unsigned long i = num.size() - 1; i > 0; i--){
		std::cout << num[i];
	}
	std::cout << num[0];
	std::cout << "\n";
}

void bigInt::removeLeadZeroes(){
	unsigned long end = this->num.size() - 1;
	for (unsigned long i = end; i >= 0; i--){
		if ((this->num[i] == 0) && (this->num.size() != 1)){
			this->num.pop_back();
		}
		else
		{
			break;
		}
	}
}

void bigInt::complement(){
	for (unsigned long i = 0; i <= this->num.size() - 1; i++){
		this->num[i] = 10 + ~this->num[i];
	}
}
void bigInt::parseString(std::string str){
    this->bigIntSet(str);
}

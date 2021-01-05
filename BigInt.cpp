//
//  main.cpp
//  Project4_YinYu_Lo
//
//  Created by yin yu lo on 11/17/20.
//  Copyright © 2020 yin yu lo. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
using namespace std;

class Block;

class BigInt{
private:
    Block* rep;
    char* bigInt;
    int size;
public:
    //default constructor
    BigInt(){
        bigInt = nullptr;
        size = 1;
        bigInt = new char[size + 1];
        bigInt[0] = '0';
        bigInt[size] = '\0';
    }
    
    //conversion constructor
    BigInt(const char* s){
        size = (unsigned)strlen(s);
        bigInt = new char[size + 1];
        for(int i = 0; i < size; i++){
            bigInt[i] = s[i];
        }
        bigInt[size] = '\0';
    }
    
    //conversion constructor
    BigInt(int s){
        size = 1;
        int n = s;
        while(n/=10){
            size++;
        }
        bigInt = new char[size + 1];
        int temp = 0;
        for(int i = size - 1; i >= 0; i--){
            temp = s % 10;
            bigInt[i] = temp + '0';
            s = s / 10;
        }
        bigInt[size] = '\0';
    }
    
    //copy constructor
    BigInt(const BigInt &s){
        size = s.size;
        bigInt = new char[size];
        for(int i = 0; i < size; i++){
            bigInt[i] = s.bigInt[i];
        }
    }
    
    //destructor
    ~BigInt(){
        delete [] bigInt;
    }
    
    //overloaded assignment operator
    //assign one BigInt to another
    BigInt& operator=(const BigInt &s){
        if(this == &s)
            return *this;
        delete [] bigInt;
        size = s.size;
        bigInt = new char[size];
        for(int i = 0; i < size; i++){
            bigInt[i] = s.bigInt[i];
        }
        return *this;
    }
    
    //overloaded arithmetic operator (+)
    BigInt& operator+(const BigInt &s){
        char* result;
        int val1, val2, sum;
        int carry = 0;
        if(s.size > this->size){
            int diff = s.size - this->size;
            result = new char[s.size + 1];
            for(int i = size - 1; i >= 0; i--){
                val1 = bigInt[i] - '0';
                val2 = s.bigInt[i+diff] - '0';
                if((val1 + val2 + carry) >= 10){
                    sum = (val1 + val2 + carry) % 10;
                    carry = (val1 + val2 + carry) / 10;
                }
                else{
                    sum = val1 + val2 + carry;
                    carry = 0;
                }
                result[i+diff] = sum + '0';
            }
            for(int i = s.size - size - 1; i >= 0; i--){
                //cout << carry << endl;
                if(carry >= 1){
                    result[i] = (((s.bigInt[i] - '0') + carry) % 10) + '0';
                    carry = (((s.bigInt[i] - '0') + carry) / 10);
                }
                else{
                    result[i] = (((s.bigInt[i] - '0') + carry) % 10) + '0';
                    carry = 0;
                }
                if(i <= 0 && carry >= 1){
                    char* temp = new char[s.size+1];
                    for(int j = 0; j < s.size; j++){
                        temp[j] = result[j];
                    }
                    temp[s.size] = '\0';
                    delete [] result;
                    result = new char[s.size + 2];
                    result[0] = carry + '0';
                    for(int j = 1; j <= s.size; j++){
                        result[j] = temp[j-1];
                    }
                    result[s.size+1] = '\0';
                }
            }
            if(carry <= 0){
                result[s.size] = '\0';
            }
        }
        else if(this->size > s.size){
            int diff = this->size - s.size;
            result = new char[size + 1];
            for(int i = s.size - 1; i >= 0; i--){
                val1 = bigInt[i+diff] - '0';
                val2 = s.bigInt[i] - '0';
                if((val1 + val2 + carry) >= 10){
                    sum = (val1 + val2 + carry) % 10;
                    carry = (val1 + val2 + carry) / 10;
                }
                else{
                    sum = val1 + val2 + carry;
                    carry = 0;
                }
                result[i+diff] = sum + '0';
            }
            for(int i = size - s.size - 1; i >= 0; i--){
                if(carry >= 1){
                    result[i] = (((bigInt[i] - '0') + carry) % 10) + '0';
                    carry = (((bigInt[i] - '0') + carry) / 10);
                }
                else{
                    result[i] = (((bigInt[i] - '0') + carry) % 10) + '0';
                    carry = 0;
                }
                if(i <= 0 && carry >= 1){
                    char* temp = new char[size+1];
                    for(int j = 0; j < size; j++){
                        temp[j] = result[j];
                    }
                    temp[size] = '\0';
                    delete [] result;
                    result = new char[size + 2];
                    result[0] = carry + '0';
                    for(int j = 1; j <= size; j++){
                        result[j] = temp[j-1];
                    }
                    result[size+1] = '\0';
                }
            }
            if(carry <= 0){
                result[size] = '\0';
            }
        }
        else{
            result = new char[size+1];
            for(int i = size - 1; i >= 0; i--){
                val1 = bigInt[i] - '0';
                val2 = s.bigInt[i] - '0';
                if((val1 + val2 + carry) >= 10){
                    sum = (val1 + val2 + carry) % 10;
                    carry = (val1 + val2 + carry) / 10;
                }
                else{
                    sum = val1 + val2 + carry;
                    carry = 0;
                }
                result[i] = sum + '0';
                if(i <= 0 && carry >= 1){
                    char* temp = new char[size+1];
                    for(int j = 0; j < size; j++){
                        temp[j] = result[j];
                    }
                    temp[size] = '\0';
                    delete [] result;
                    result = new char[size + 2];
                    result[0] = carry + '0';
                    for(int j = 1; j <= size; j++){
                        result[j] = temp[j-1];
                    }
                    result[size+1] = '\0';
                }
            }
        }
        BigInt *r = new BigInt(result);
        return *r;
    }
    
    //overloaded arithmetic operator (-)
    BigInt& operator-(const BigInt &s){
        char* result;
        int val1, val2, sub;
        int carry = 0;
        bool secBigger = false;
        if(bigInt[0] == '0' && s.bigInt[0] == '0'){
            result = new char[2];
            result[0] = '0';
            result[1] = '\0';
            BigInt *r = new BigInt(result);
            return *r;
            
        }
        if(this->size == s.size){
            for(int i = 0; i < size; i++){
                if(this->bigInt[i] > s.bigInt[i]){
                    secBigger = false;
                    break;
                }
                else if(s.bigInt[i] > this->bigInt[i]){
                    secBigger = true;
                    break;
                }
                else{
                    secBigger = false;
                }
            }
        }
        if(this->size > s.size || ((this->size == s.size) && !secBigger)){
            int diff = this->size - s.size;
            result = new char[size + 1];
            for(int i = s.size - 1; i >= 0; i--){
                val1 = bigInt[i+diff] - '0';
                val2 = s.bigInt[i] - '0';
                sub = val1 - val2 - carry;
                if(sub < 0){
                    sub = sub + 10;
                    carry = 1;
                }
                else{
                    carry = 0;
                }
                result[i+diff] = sub + '0';
            }
            for(int i = size - s.size - 1; i >= 0; i--){
                if(bigInt[i] =='0' && carry == 1){
                    result[i] = '9';
                }
                else{
                    sub = (bigInt[i] - '0') - carry;
                    if( i >= 0 || sub > 0){
                        result[i] = sub +'0';
                    }
                    carry = 0;
                }
            }
            result[size] = '\0';
            int count = 0;
            if(result[0] == '0'){
                int index = 0;
                for(int i = 0; i < size; i++){
                    if(result[i] != '0'){
                        index = i;
                        break;
                    }
                    count++;
                }
                if(count == size){
                    index = size - 1;
                }
                int len = size - index;
                char* temp = new char[len+1];
                for(int j = 0; j < len; j++){
                    temp[j] = result[j+index];
                }
                temp[len] = '\0';
                delete [] result;
                result = new char[len+1];
                for(int j = 0; j < len; j++){
                    result[j] = temp[j];
                }
                result[len] = '\0';
            }
        }
        else if(s.size > this->size || ((this->size == s.size) && secBigger)){
            int diff = s.size - this->size;
            result = new char[s.size+1];
            for(int i = size - 1; i >= 0; i--){
                val1 = s.bigInt[i+diff] - '0';
                val2 = bigInt[i] - '0';
                sub = val1 - val2 - carry;
                if(sub < 0){
                    sub = sub + 10;
                    carry = 1;
                }
                else{
                    carry = 0;
                }
                result[i+diff] = sub + '0';
            }
            for(int i = s.size - size - 1; i >= 0; i--){
                if(s.bigInt[i] =='0' && carry == 1){
                    result[i] = '9';
                }
                else{
                    sub = (s.bigInt[i] - '0') - carry;
                    if( i >= 0 || sub > 0){
                        result[i] = sub +'0';
                    }
                    carry = 0;
                }
            }
            result[s.size] = '\0';
            int index = 0;
            for(int i = 0; i < s.size; i++){
                if(result[i] != '0'){
                    index = i;
                    break;
                }
            }
            int len = s.size - index;
            char* temp = new char[len+1];
            for(int j = 0; j < len; j++){
                temp[j] = result[j+index];
            }
            temp[len] = '\0';
            delete [] result;
            result = new char[len+2];
            for(int j = 1; j < len+1; j++){
                result[j] = temp[j-1];
            }
            result[0] = '-';
            result[len+1] = '\0';
        }
        else{
            result = new char[1];
            result[0] = '\0';
        }
        BigInt *r = new BigInt(result);
        return *r;
    }
    
    //overloaded arithmetic operator (*)
    BigInt& operator*(const BigInt &s){
        int len = size + s.size;
        char* result = new char[len + 1];
        int* arr = new int[len];
        for(int i = 0; i < len; i++){
            arr[i] = 0;
        }
        if(bigInt[0] == '0' || s.bigInt[0] == '0'){
            result[0] = '0';
            result[1] = '\0';
            BigInt *r = new BigInt(result);
            return *r;
        }
        int val1, val2, sum;
        int k = 1;
        for(int i = size - 1; i >= 0; i--){
            val1 = bigInt[i] -'0';
            int carry = 0;
            int index = len - k;
            for(int j = s.size - 1; j >= 0; j--){
                val2 = s.bigInt[j] - '0';
                sum = val1 * val2 + arr[index] + carry;
                carry = sum / 10;
                arr[index] = sum % 10;
                index--;
            }
            if(carry > 0){
                arr[index] = arr[index] + carry;
            }
            k++;
            
        }
        if(arr[0] != 0){
            for(int i = 0; i < len; i++){
                result[i] = arr[i] + '0';
            }
            result[len] = '\0';
        }
        else{
            for(int i = 1; i < len; i++){
                result[i-1] = arr[i] + '0';
            }
            result[len-1] = '\0';
        }
        BigInt *r = new BigInt(result);
        return *r;
    }
    
    //overloaded arithmetic operator (/)
    BigInt& operator/(const BigInt &s){
        char* result = new char[size + 1];
        if(s.bigInt[0] == '0'){
            strncpy(result, "Math error", 10);
            BigInt *r = new BigInt(result);
            return *r;
        }
        else if(bigInt[0] == '0' || s.size > size){
            result[0] = '0';
            result[1] = '\0';
            BigInt *r = new BigInt(result);
            return *r;
        }
        else if(size == 1 && s.size == 1){
            result[0] = ((bigInt[0] - '0') / (s.bigInt[0] - '0')) + '0';
            result[1] = '\0';
            BigInt *r = new BigInt(result);
            return *r;
        }
        int i;
        int length,len1,len2,len,index;
        bool flag;
        string str1 = bigInt;
        string str2 = s.bigInt;
        
        len1 = (unsigned)str1.length();
        len2 = (unsigned)str2.length();
        length = len1 - len2;
        if(length < 0){
            result[0] = '0';
            result[1] = '\0';
            BigInt *r = new BigInt(result);
            return *r;
        }
        int *num1 = new int[len1+1];
        int *num2 = new int[len2+1];
        int *quotient = new int[length+2];
        
        memset(num1,0,sizeof(int)*(len1+1));
        memset(num2,0,sizeof(int)*(len2+1));
        memset(quotient,0,sizeof(int)*(length+2));
        
        for(i = len1-1,index = 0; i >= 0; i--){
            num1[index++]=str1[i]-'0';
        }
        for(i = len2-1,index = 0; i >= 0; i--){
            num2[index++]=str2[i]-'0';
        }
        
        while(true){
            for(i = len1-1; i >= 0; i--){
                if(num1[i]){
                    len1 = i+1;
                    break;
                }
                if(i==0) len1=0;
            }
            
            len=len1-len2;
            if(len<0) break;
            
            flag=false;
            index=0;
            
            for(i = len1-1; i >= len; i--){
                if(num1[i] == num2[i-len]) continue;
                else if(num1[i] < num2[i-len]){
                    flag = true;
                    break;
                }
                else{
                    break;
                }
            }
            
            if(flag) --len;
            if(len<0) break;
            
            while(++index){
                flag = false;
                for(i = len1-1; i >= len; i--){
                    if(num1[i] == num2[i-len]) continue;
                    else if(num1[i] < num2[i-len]){
                        flag = true;
                        break;
                    }
                    else{
                        break;
                    }
                }
                if(flag){
                    --index;
                    break;
                }
                
                for(i = len; i < len1; i++){
                    num1[i] -= num2[i-len];
                    if(num1[i] < 0){
                        num1[i] += 10;
                        --num1[i+1];
                    }
                }
            }
            if(index==0)
                break;
            else
                quotient[len] = index;
        }
        
        string ans;
        flag = false;
        for(i = length; i >= 0; i--){
            if(flag || quotient[i])
            {
                flag = true;
                ans+='0'+quotient[i];
            }
        }
        if(!flag) ans="0";
        
        delete [] num1;
        delete [] num2;
        delete [] quotient;
        
        char* arr;
        arr = &ans[0];
        BigInt *r = new BigInt(arr);
        return *r;
        
    }
    
    friend ostream& operator<<(ostream& os, BigInt& s);
};

ostream& operator<<(ostream& os, BigInt& s){
    int size = s.size;
    for(int i = 0; i < size; i++){
        os << s.bigInt[i];
    }
        //os << endl;
    return os;
}

int main(){

/*
 Test 1
 constructing and outputting with default constructor
 */
cout<<endl<<"-----TEST 1 : default constructor output -----" <<endl;

cout<<"Default constructed bigint a is:" <<endl;
BigInt a;
cout<<a<<endl;

/*
 Test 2
 constructing and outputting with char input constructor
 */
cout<<endl<<"-----TEST 2 :  c_string input constructor output -----" <<endl;

char* charb = new char[10];
charb[0] = '1'; charb[1] = '2'; charb[2] = '3'; charb[3] = '4'; charb[4] = '5';
charb[5] = '6'; charb[6] = '7'; charb[7] = '8'; charb[8] = '9'; charb[9] = '\0';

cout<<"The char array charb being input into the constructor is "<<endl<<charb <<endl;
cout<<"Now constructing and outputting the BigInt b with charb as input"<<endl;
BigInt b(charb);
cout<<b<<endl<<endl;

delete[] charb;


/*
 Test 3
 constructing and outputting with integer input constructor
 */
cout<<endl<<"-----TEST 3 :  int input constructor output -----" <<endl;

int intc = 1234;
cout<<"The int intc being input into the constructor is "<<endl<<intc <<endl;
cout<<"Now constructing and outputting the BigInt c with intc as input:"<<endl;
BigInt c(intc);
cout << c << endl<<endl;




/*
 Test 4
 constructing and outputting with copy constructor
 */
cout<<endl<<"-----TEST 4 :  copy constructor output -----" <<endl;

int intd = 1234;
BigInt d(intd);
cout<<"The BigInt d being input into the constructor is "<<endl<< d <<endl;
cout<<"Now constructing and outputting the BigInt e with BigInt d as input:"<<endl;
BigInt e(d);
cout << e << endl<<endl;



/*
 Test 5
 Testing char* and int constructor with 0 input
 */
cout<<endl<<"-----TEST 5 :  constructing 0 -----" <<endl;

cout<<"Outputting result of constructing bigint with 0 int and 0 c_string input(should be 0 twice):"<<endl;
int intf = 0;
char* charg = new char[2];
charg[0] = '0'; charg[1] = '\0';
BigInt f(intf);
BigInt g(charg);
cout<<f<<endl<<g<<endl<<endl;

delete[] charg;


/*
 Test 6
 Testing the assignment operator
 */
cout<<endl<<"-----TEST 6 :  assignment operator -----" <<endl;

BigInt h(4321);
BigInt k(1234);
BigInt l(5678);
cout<< "h is: "<<h<<endl<<"k is: "<<k<<endl<<"l is: "<<l<<endl;
cout<<"after doing h = k; k = l; and the values of h, k and l are:"<<endl;
h = k; k = l;
cout<< "h is: "<<h<<endl<<"k is: "<<k<<endl<<"l is: "<<l<<endl;


/*
 Test 7
 Testing addition
 */
cout<<endl<<"-----TEST 7 :  + operator -----" <<endl;

cout<<"Same order with overflow:"<<endl;
int intm =87654;
char* charn = new char[6];
charn[0] = '5'; charn[1] = '4'; charn[2] = '3'; charn[3] = '2';
charn[4] = '1'; charn[5] = '\0';
BigInt m(intm);
BigInt n(charn);
cout << m << " + " << n << " = " << m+n <<endl<<endl;

cout<< "Large numbers"<<endl;
char* charp = new char[13];
charp[0] = '1'; charp[1] = '2'; charp[2] = '3'; charp[3] = '4'; charp[4] = '5';
charp[5] = '6'; charp[6] = '7'; charp[7] = '8'; charp[8] = '9'; charp[9] = '0';
charp[10] = '1'; charp[11] = '2'; charp[12] = '\0';
char* charq = new char[14];
charq[0] = '1'; charq[1] = '2'; charq[2] = '3'; charq[3] = '4'; charq[4] = '5';
charq[5] = '6'; charq[6] = '7'; charq[7] = '8'; charq[8] = '9'; charq[9] = '0';
charq[10] = '1'; charq[11] = '2'; charq[12] = '3'; charq[13] = '\0';
BigInt p(charp);
BigInt q(charq);
cout<< p << " + " << q << " = " << p + q <<endl<<endl;

delete[] charn;
delete[] charp;
delete[] charq;


/*
 Test 8
 Testing subtraction
 */
cout<<endl<<"-----TEST 8 :  - operator -----" <<endl;

cout<<"No change in order of magnitude:"<<endl;
int intr =876543;
char* chars = new char[6];
chars[0] = '5'; chars[1] = '4'; chars[2] = '3'; chars[3] = '2';
chars[4] = '1'; chars[5] = '\0';
BigInt r(intr);
BigInt s(chars);
cout << r << " - " << s << " = " << r - s <<endl<<endl;

cout<< "Large numbers:"<<endl;
char* chart = new char[15];
chart[0] = '1'; chart[1] = '2'; chart[2] = '3'; chart[3] = '4'; chart[4] = '5';
chart[5] = '6'; chart[6] = '7'; chart[7] = '8'; chart[8] = '9'; chart[9] = '0';
chart[10] = '1'; chart[11] = '2'; chart[12] = '3'; chart[13] = '4'; chart[14] = '\0';
char* charu = new char[14];
charu[0] = '1'; charu[1] = '2'; charu[2] = '3'; charu[3] = '4'; charu[4] = '5';
charu[5] = '6'; charu[6] = '7'; charu[7] = '8'; charu[8] = '9'; charu[9] = '0';
charu[10] = '1'; charu[11] = '2'; charu[12] = '3'; charu[13] = '\0';
BigInt t(chart);
BigInt u(charu);
cout<< t << " - " << q << " = " << t - q << endl << endl;

cout<< "Cancellation of Order:"<<endl;
int intv = 1000010;
int intw = 1000000;
BigInt v(intv);
BigInt w(intw);
cout<< v << " - " << w << " = " << v - w << endl << endl;

cout<<"Different order operands cancellation of Order"<<endl;
int intx = 100000;
int inty = 99;
BigInt x(intx);
BigInt y(inty);
cout<< x << " - " << y << " = " << x - y << endl << endl;

delete[] chars;
delete[] chart;
delete[] charu;




/*
 Test 9
 Testing multiplication
 */
cout<<endl<<"-----TEST 9 :  * operator -----" <<endl;

cout<<"Normal ints:"<<endl;
int intaa = 87654;
char* charz = new char[6];
charz[0] = '5'; charz[1] = '4'; charz[2] = '3'; charz[3] = '2';
charz[4] = '1'; charz[5] = '\0';
BigInt aa(intaa);
BigInt z(charz);
cout << aa << " * " << z << " = " << aa * z <<endl<<endl;

cout<< "Large numbers"<<endl;
char* charbb = new char[13];
charbb[0] = '1'; charbb[1] = '2'; charbb[2] = '3'; charbb[3] = '4';
charbb[4] = '5'; charbb[5] = '6'; charbb[6] = '7'; charbb[7] = '8';
charbb[8] = '9'; charbb[9] = '0'; charbb[10] = '1'; charbb[11] = '2';
charbb[12] = '\0';
char* charcc = new char[14];
charcc[0] = '1'; charcc[1] = '2'; charcc[2] = '3'; charcc[3] = '4';
charcc[4] = '5'; charcc[5] = '6'; charcc[6] = '7'; charcc[7] = '8';
charcc[8] = '9'; charcc[9] = '0'; charcc[10] = '1'; charcc[11] = '2';
charcc[12] = '3'; charcc[13] = '\0';
BigInt bb(charbb);
BigInt cc(charcc);
cout<< bb << " * " << cc << " = " << bb * cc <<endl<<endl;

delete[] charz;
delete[] charbb;
delete[] charcc;



/*
 Test 10
 Testing Zero Cases
 */
cout<<endl<<"-----TEST 10 : 0 cases -----" <<endl;

BigInt dd(0);
BigInt ee(12345);
cout<< ee << " + " << dd << " = " << ee + dd <<endl<<endl;
cout<< ee << " - " << dd << " = " << ee - dd <<endl<<endl;
cout<< ee << " * " << dd << " = " << ee * dd <<endl<<endl;
cout<< dd << " + " << dd << " = " << dd + dd <<endl<<endl;
cout<< ee << " - " << ee << " = " << ee - ee <<endl<<endl;
cout<< dd << " * " << dd << " = " << dd * dd <<endl<<endl;


/*
 Test 11
 HUGE NUMBERS
 */
cout<<endl<<"-----TEST 11 : HUGE NUMBERS -----" <<endl;

cout<< "HUGE numbers"<<endl;
char* charff = new char[24];
charff[0] = '1'; charff[1] = '2'; charff[2] = '3'; charff[3] = '4';
charff[4] = '5'; charff[5] = '6'; charff[6] = '7'; charff[7] = '8';
charff[8] = '9'; charff[9] = '0'; charff[10] = '1'; charff[11] = '2';
charff[12] = '3';  charff[13] = '4'; charff[14] = '5'; charff[15] = '6';
charff[16] = '7'; charff[17] = '8'; charff[18] = '9'; charff[19] = '0';
charff[20] = '1'; charff[21] = '2'; charff[22] = '3'; charff[23] = '\0';
char* chargg = new char[23];
chargg[0] = '1'; chargg[1] = '2'; chargg[2] = '3'; chargg[3] = '4';
chargg[4] = '5'; chargg[5] = '6'; chargg[6] = '7'; chargg[7] = '8';
chargg[8] = '9'; chargg[9] = '0'; chargg[10] = '1'; chargg[11] = '2';
chargg[12] = '3'; chargg[13] = '4'; chargg[14] = '5'; chargg[15] = '6';
chargg[16] = '7'; chargg[17] = '8'; chargg[18] = '9'; chargg[19] = '0';
chargg[20] = '1'; chargg[21] = '2'; chargg[22] = '\0';

BigInt ff(charff);
BigInt gg(chargg);
cout<< ff << " + " << gg << " = " << ff + gg <<endl<<endl;
cout<< ff << " - " << gg << " = " << ff - gg <<endl<<endl;
cout<< ff << " * " << gg << " = " << ff * gg <<endl<<endl;


delete[] charff;
delete[] chargg;


/*
 Test 12
 I also consider when smaller number minus larger number.
 Then it will have NEGATIVE NUMBERS as result
 */
cout<<endl<<"-----EXTRA TEST : smaller number minus larger number and NEGATIVE NUMBERS as result -----" <<endl;
char* char_arr;
string s1("11566");
char_arr = &s1[0];
BigInt str1(char_arr);
string s2("234685");
char_arr = &s2[0];
BigInt str2(char_arr);
cout<< str1 << " - " << str2 << " = " << str1 - str2 <<endl<<endl;

string s3("3345");
char_arr = &s3[0];
BigInt str3(char_arr);
string s4("9959931234586356968");
char_arr = &s4[0];
BigInt str4(char_arr);
cout<< str3 << " - " << str4 << " = " << str3 - str4 <<endl<<endl;


/*
 Test 13
 Division
 */

cout<<endl<<"-----TEST 12 :  / operator -----" <<endl;

cout<<"Normal ints:"<<endl;
int inthh = 8765432;
char* charkk = new char[6];
charkk[0] = '5'; charkk[1] = '4'; charkk[2] = '3'; charkk[3] = '2';
charkk[4] = '1'; charkk[5] = '\0';
BigInt hh(inthh);
BigInt kk(charkk);
cout << hh << " / " << kk << " = " << hh / kk <<endl<<endl;

cout<< "Large ints"<<endl;
char* charll = new char[12];
charll[0] = '1'; charll[1] = '2'; charll[2] = '3'; charll[3] = '4';
charll[4] = '5'; charll[5] = '6'; charll[6] = '7'; charll[7] = '8';
charll[8] = '9'; charll[9] = '0'; charll[10] = '1'; charll[11] = '\0';
char* charmm = new char[14];
charmm[0] = '1'; charmm[1] = '2'; charmm[2] = '3'; charmm[3] = '4';
charmm[4] = '5'; charmm[5] = '6'; charmm[6] = '7'; charmm[7] = '8';
charmm[8] = '9'; charmm[9] = '0'; charmm[10] = '1'; charmm[11] = '2';
charmm[12] = '3'; charmm[13] = '\0';
BigInt ll(charll);
BigInt mm(charmm);
cout<< mm << " / " << ll << " = " << mm / ll <<endl<<endl;
cout<< "Smaller numerator than Denominator(should be zero)" <<endl;
cout<< ll << " / " << mm << " = " << ll / mm <<endl<<endl;

cout<< "Small ints"<<endl;
BigInt nn(9);
BigInt oo(3);
BigInt qq(1);
cout<< nn << " / " << oo << " = " << nn / oo <<endl<<endl;
cout<< nn << " / " << qq << " = " << nn / qq <<endl<<endl;

delete[] charkk;
delete[] charll;
delete[] charmm;

        
/*
 Test 14
 Division by Zero
 This shouldn't work,
 it should print an error message
 */

cout<<endl<<"----TEST 14 : Dividing by zero ----"<<endl;

BigInt rr(99);
BigInt tt(0);
cout<<"The next statement may not print because it's division by zero:"<<endl;
cout<< rr << " / " << tt << " = " << rr / tt <<endl<<endl;

return 0;
}

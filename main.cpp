
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 1;
    n1 = 1;
    d1 = 2;

    c2 = 2;
    n2 = 2;
    d2 = 3; 

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 123;
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 456;
    denominator = 1000;
    return true;
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //get the numerators of both numbers
    int numeratorFirstNum = c1 * d1 + n1;
    int numeratorSecondNum = c2 * d2 + n2;
    //get the total numerator
    int totalNumerator = numeratorFirstNum + numeratorSecondNum;

    int lcm = d1;
    //if the denominators are not equal
    if (d1 != d2) {
        //get least common denominator
        lcm = d1 * d2;
        //get the total numerator with the lcm
        totalNumerator = (numeratorFirstNum * d2) + (numeratorSecondNum * d1);
    }
    //get number before decimal
    int total = totalNumerator / lcm;
    //get remainder
    int remainder = totalNumerator % lcm;
    //add whole number before decimal to result
    int resultLength = 0;
    while (total != 0) {
        result[resultLength] = '0' + total;
        total = total / 10;
        resultLength++;
    }
    //add remainder after the decimal place
    if (remainder != 0) {
        //add decimal place
        result[resultLength] = '.';
        resultLength++;
        int currentLength = resultLength;
        //loop until length is reached or remainder is 0
        for (int j = 0; j < len - currentLength - 1 && remainder != 0; j++) {
            //get the next digit
            remainder *= 10;
            int nextDigit = remainder / lcm;
            //add to result
            result[resultLength] = '0' + nextDigit;
            resultLength++;
            //get next remainder
            remainder = remainder % lcm;
        }
    }
    //add newline character to end of result
    result[resultLength] = '\0';
    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //1.5-2.66_



    
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers
    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';
    
    return true;
}

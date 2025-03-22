
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

    if(subtract(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on subtract"<<endl;
    }

    if(multiply(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on multiply"<<endl;
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
    //error handling improper fractions and 0 length
    if (d1 == 0 || d2 == 0 || len == 0) {
        return false;
    }

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
    int wholeNumber = totalNumerator / lcm;
    //get remainder
    int remainder = totalNumerator % lcm;
    //add whole number before decimal to result
    int resultLength = 0;
    while (wholeNumber != 0) {
        result[resultLength] = '0' + wholeNumber;
        wholeNumber = wholeNumber / 10;
        resultLength++;
    }
    //if the whole number is greater than the length given
    if (resultLength > len-1) {
        return false;
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
    //error handling improper fractions and 0 length
    if (d1 == 0 || d2 == 0 || len == 0) {
        return false;
    }

    //get the numerators of both numbers
    int numeratorFirstNum = c1 * d1 + n1;
    int numeratorSecondNum = c2 * d2 + n2;
    //get the total numerator
    int subtractedNumerator = numeratorFirstNum - numeratorSecondNum;

    int lcm = d1;
    //if the denominators are not equal
    if (d1 != d2) {
        //get least common denominator
        lcm = d1 * d2;
        //get the total numerator with the lcm
        subtractedNumerator = (numeratorFirstNum * d2) - (numeratorSecondNum * d1);
    }

    int resultLength = 0;
    //if negative add the sign
    if (subtractedNumerator < 0) {
        subtractedNumerator = subtractedNumerator * -1;
        result[resultLength] = '-';
        resultLength++;
    }

    //get number before decimal
    int wholeNumber = subtractedNumerator / lcm;
    //get remainder
    int remainder = subtractedNumerator % lcm;
    //add whole number before decimal to result
    while (wholeNumber != 0) {
        result[resultLength] = '0' + wholeNumber;
        wholeNumber = wholeNumber / 10;
        resultLength++;
    }
    //if the whole number is greater than the length given
    if (resultLength > len-1) {
        return false;
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
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //error handling improper fractions and 0 length
    if (d1 == 0 || d2 == 0 || len == 0) {
        return false;
    }

    //get the numerators of both numbers
    int numeratorFirstNum = c1 * d1 + n1;
    int numeratorSecondNum = c2 * d2 + n2;
    //get the totals
    int totalNumerator = numeratorFirstNum * numeratorSecondNum;
    int totalDenominator = d1 * d2;

    //get number before decimal
    int wholeNumber = totalNumerator / totalDenominator;
    //get remainder
    int remainder = totalNumerator % totalDenominator;
    //add whole number before decimal to result
    int resultLength = 0;
    while (wholeNumber != 0) {
        result[resultLength] = '0' + wholeNumber;
        wholeNumber = wholeNumber / 10;
        resultLength++;
    }
    //if the whole number is greater than the length given
    if (resultLength > len-1) {
        return false;
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
            int nextDigit = remainder / totalDenominator;
            //add to result
            result[resultLength] = '0' + nextDigit;
            resultLength++;
            //get next remainder
            remainder = remainder % totalDenominator;
        }
    }
    //add newline character to end of result
    result[resultLength] = '\0';
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //error handling improper fractions and 0 length
    if (d1 == 0 || d2 == 0 || len == 0) {
        return false;
    }

    //get the numerator and reciprocal of both numbers
    int numeratorFirstNum = c1 * d1 + n1;
    int denominatorSecondNum = c2 * d2 + n2;
    //get the totals, use reciprocal
    int totalNumerator = numeratorFirstNum * d2;
    int totalDenominator = d1 * denominatorSecondNum;

    //get number before decimal
    int wholeNumber = totalNumerator / totalDenominator;
    //get remainder
    int remainder = totalNumerator % totalDenominator;
    //add whole number before decimal to result
    int resultLength = 0;
    if (wholeNumber == 0) {
        result[resultLength] = '0';
        resultLength++;
    }
    else {
        while (wholeNumber != 0) {
            result[resultLength] = '0' + wholeNumber;
            wholeNumber = wholeNumber / 10;
            resultLength++;
        }
    }
    //if the whole number is greater than the length given
    if (resultLength > len-1) {
        return false;
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
            int nextDigit = remainder / totalDenominator;
            //add to result
            result[resultLength] = '0' + nextDigit;
            resultLength++;
            //get next remainder
            remainder = remainder % totalDenominator;
        }
    }
    //add newline character to end of result
    result[resultLength] = '\0';
    return true;
}

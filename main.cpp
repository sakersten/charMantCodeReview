
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

//helper Math functions
bool checkLength(int currentLength, int maxLength);
void handleRemainder(int remainder, int lcd, char result[], int len, int &resultLength);
void handleWholeNumber (int wholeNumber, char result[], int &resultLength);
void calculateNumerators (int c1, int n1, int d1, int c2, int n2, int d2, int &numeratorFirstNum, int &numeratorSecondNum);
void AddNegativeSign (int &totalNumerator, char result[], int &resultLength);
// characteristic and mantissa helper functions
int skipLeadingSpaces(const char numString[]); 
int skipTrailingSpaces(const char numString[]); 
bool validString(const char numString[]); 
void extractCharacteristic(const char numString[], int& c); 
void extractMantissa(const char numString[], int& numerator, int& denominator); 

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    
    const char number[] = "123."; //"123.456"; 
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

    for (int i = -2; i < 1; i++) {
        //initialize the values
        c1 = i;
        n1 = 1;
        d1 = 2;

        c2 = i;
        n2 = 2;
        d2 = 3;

        //if the c-string can hold at least the characteristic
        if(add(c1, n1, d1, c2, n2, d2, answer, 10))
        {
            //display string with answer
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
    }
        
    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    // return false if the input is NOT valid
    if (!validString(numString))
    {
        return false; 
    }
    // otherwise, run the function and return true
    else 
    {
        extractCharacteristic(numString, c); 
        return true;
    }
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    // return false if the input is NOT valid
    if (!validString(numString))
    {
        return false; 
    }
    // otherwise, run the function and return true
    else 
    {
        extractMantissa(numString, numerator, denominator); 
        return true;
    }
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //error handling improper fractions and 0 length
    if (d1 == 0 || d2 == 0 || len == 0 || n1 < 0 || d1 < 0 || n2 < 0 || d2 < 0) {
        return false;
    }

    //get the numerators of both numbers
    int numeratorFirstNum, numeratorSecondNum;
    calculateNumerators (c1, n1, d1, c2, n2, d2, numeratorFirstNum, numeratorSecondNum);
    //get the total numerator
    int totalNumerator = numeratorFirstNum + numeratorSecondNum;
    int lcd = d1;
    //if the denominators are not equal
    if (d1 != d2) {
        //get least common denominator
        lcd = d1 * d2;
        //get the total numerator with the lcd
        totalNumerator = (numeratorFirstNum * d2) + (numeratorSecondNum * d1);
    }

    int resultLength = 0;
    //if negative add the sign
    AddNegativeSign (totalNumerator, result, resultLength);

    //get number before decimal
    int wholeNumber = totalNumerator / lcd;
    //get remainder
    int remainder = totalNumerator % lcd;

    //add whole number before decimal to result
    handleWholeNumber(wholeNumber, result, resultLength);
    //if the whole number is greater than the length given
    if (!checkLength(resultLength, len)) {
        return false;
    }

    //add remainder after the decimal place
    if (remainder != 0) {
        handleRemainder(remainder, lcd, result, len, resultLength);
    }
    //add null terminator to end of result
    result[resultLength] = '\0';
    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //error handling improper fractions and 0 length
    if (d1 == 0 || d2 == 0 || len == 0 || n1 < 0 || d1 < 0 || n2 < 0 || d2 < 0) {
        return false;
    }

    //get the numerators of both numbers
    int numeratorFirstNum, numeratorSecondNum;
    calculateNumerators (c1, n1, d1, c2, n2, d2, numeratorFirstNum, numeratorSecondNum);
    //get the total numerator
    int subtractedNumerator = numeratorFirstNum - numeratorSecondNum;

    int lcd = d1;
    //if the denominators are not equal
    if (d1 != d2) {
        //get least common denominator
        lcd = d1 * d2;
        //get the total numerator with the lcd
        subtractedNumerator = (numeratorFirstNum * d2) - (numeratorSecondNum * d1);
    }

    int resultLength = 0;
    //if negative add the sign
    AddNegativeSign (subtractedNumerator, result, resultLength);

    //get number before decimal
    int wholeNumber = subtractedNumerator / lcd;
    //get remainder
    int remainder = subtractedNumerator % lcd;

    //add whole number before decimal to result
    handleWholeNumber(wholeNumber, result, resultLength);
    //if the whole number is greater than the length given
    if (!checkLength(resultLength, len)) {
        return false;
    }

    //add remainder after the decimal place
    if (remainder != 0) {
        handleRemainder(remainder, lcd, result, len, resultLength);
    }
    //add null terminator to end of result
    result[resultLength] = '\0';
    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //error handling improper fractions and 0 length
    if (d1 == 0 || d2 == 0 || len == 0 || n1 < 0 || d1 < 0 || n2 < 0 || d2 < 0) {
        return false;
    }

    //get the numerators of both numbers
    int numeratorFirstNum, numeratorSecondNum;
    calculateNumerators (c1, n1, d1, c2, n2, d2, numeratorFirstNum, numeratorSecondNum);
    //get the totals
    int totalNumerator = numeratorFirstNum * numeratorSecondNum;
    int totalDenominator = d1 * d2;

    int resultLength = 0;
    //if negative add the sign
    AddNegativeSign (totalNumerator, result, resultLength);

    //get number before decimal
    int wholeNumber = totalNumerator / totalDenominator;
    //get remainder
    int remainder = totalNumerator % totalDenominator;

    //add whole number before decimal to result
    handleWholeNumber(wholeNumber, result, resultLength);
    //if the whole number is greater than the length given
    if (!checkLength(resultLength, len)) {
        return false;
    }

    //add remainder after the decimal place
    if (remainder != 0) {
        handleRemainder(remainder, totalDenominator, result, len, resultLength);
    }
    //add null terminator to end of result
    result[resultLength] = '\0';
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //error handling improper fractions and 0 length
    if (d1 == 0 || d2 == 0 || len == 0 || n1 < 0 || d1 < 0 || n2 < 0 || d2 < 0) {
        return false;
    }

    //get the numerator and reciprocal of both numbers
    int numeratorFirstNum, denominatorSecondNum;
    calculateNumerators (c1, n1, d1, c2, n2, d2, numeratorFirstNum, denominatorSecondNum);
    //get the totals, use reciprocal
    int totalNumerator = numeratorFirstNum * d2;
    int totalDenominator = d1 * denominatorSecondNum;

    int resultLength = 0;
    //if either the numerator or denominator is negative add the sign
    //if numerator is negative
    if (totalNumerator < 0 && totalDenominator >= 0) {
        totalNumerator = totalNumerator * -1;
        result[resultLength] = '-';
        resultLength++;
    }
    //if denominator is negative
    else if (totalNumerator >= 0 && totalDenominator < 0) {
        totalDenominator = totalDenominator * -1;
        result[resultLength] = '-';
        resultLength++;
    }

    //get number before decimal
    int wholeNumber = totalNumerator / totalDenominator;
    //get remainder
    int remainder = totalNumerator % totalDenominator;

    //add whole number before decimal to result
    handleWholeNumber(wholeNumber, result, resultLength);
    //if the whole number is greater than the length given
    if (!checkLength(resultLength, len)) {
        return false;
    }

    //add remainder after the decimal place
    if (remainder != 0) {
        handleRemainder(remainder, totalDenominator, result, len, resultLength);
    }
    //add null terminator to end of result
    result[resultLength] = '\0';
    return true;
}

bool checkLength (int currentLength, int maxLength) {
    if (currentLength > maxLength-1) {
        return false;
    }
    return true;
}

void handleRemainder(int remainder, int lcd, char result[], int len, int &resultLength)
{
    //add decimal place
    result[resultLength] = '.';
    resultLength++;
    // Loop until length is reached or remainder is 0
    int currentLength = resultLength;
    for (int j = 0; j < len - currentLength - 1 && remainder != 0; j++) {
        // Get the next digit
        remainder *= 10;
        int nextDigit = remainder / lcd;
        // Add to result
        result[resultLength] = '0' + nextDigit;
        resultLength++;
        // Get next remainder
        remainder = remainder % lcd;
    }
}

void handleWholeNumber (int wholeNumber, char result[], int &resultLength) {
    //if 0 just display 0
    if (wholeNumber == 0) {
        result[resultLength] = '0';
        resultLength++;
    }
    //if not 0 add all whole numbers
    else {
        while (wholeNumber != 0) {
            //Get the last digit
            result[resultLength] = '0' + wholeNumber % 10;
            //Remove the last digit
            wholeNumber = wholeNumber / 10;  
            resultLength++;
        }
        
        //Reverse the result to display the digits correctly
        //if the value is negative, start at 1
        if ( result[0] == '-') {
            for (int beginningChar = 1, endChar = resultLength - 1; beginningChar < endChar; beginningChar++, endChar--) {
                //Reverse
                char temporaryChar = result[beginningChar];
                result[beginningChar] = result[endChar];
                result[endChar] = temporaryChar;
            }
        }
        //if the value is positive, start at 0
        else {
            for (int beginningChar = 0, endChar = resultLength - 1; beginningChar < endChar; beginningChar++, endChar--) {
                //Reverse
                char temporaryChar = result[beginningChar];
                result[beginningChar] = result[endChar];
                result[endChar] = temporaryChar;
            }
        }
    }
}

void calculateNumerators (int c1, int n1, int d1, int c2, int n2, int d2, int &numeratorFirstNum, int &numeratorSecondNum) {
    if (c1 < 0) {
        numeratorFirstNum = c1 * d1 - n1;
    }
    else {
        numeratorFirstNum = c1 * d1 + n1;
    }
    if (c2 < 0) {
        numeratorSecondNum = c2 * d2 - n2;
    }
    else {
        numeratorSecondNum = c2 * d2 + n2;
    }
}

void AddNegativeSign (int &totalNumerator, char result[], int &resultLength) {
    //if numerator is negative add the sign
    if (totalNumerator < 0) {
        totalNumerator = totalNumerator * -1;
        result[resultLength] = '-';
        resultLength++;
    }
}

// CHARACTERISTIC AND MANTISSA HELPER FUNCTIONS

// helper function to skip over leading (start) spaces
int skipLeadingSpaces(const char numString[])
{
    int i = 0; 

    // while loop will run if there are spaces in the beginning
    while (numString[i] == ' ')
    {
        i++; 
    }
    return i; // return the index of the first non-space character 
}

// helper function to check if we have any trailing (end) spaces 
int skipTrailingSpaces(const char numString[])
{
    int i = 0; 

    // find the last non-null character
    while (numString[i] != '\0')
    {
        i++; 
    }
    i--; // step back to the last valid character

    // skip the trailing spaces
    while (i >= 0 && numString[i] == ' ')
    {
        i--; 
    }

    return i; // return the index of the last non-space character
}

// helper function to check if we have a valid c-string
bool validString(const char numString[]) 
{
    int i = skipLeadingSpaces(numString); // skip over the leading spaces, if there are any 
    int lastValidIndex = skipTrailingSpaces(numString); // get the last meaningful character

    // i cannot be larger than lastValidIndex
    if (i > lastValidIndex)
    {
        return false; 
    }

    // check if the first character is valid (digit, +, or -)
    if (numString[i] == '+' || numString[i] == '-')
    {
        i++; // increment
    }

    bool hasDecimal = false; // keep track of if there is one singular decimal point within the c-string
    bool foundDigit = false; // to ensure that at least one digit is found

    // check for an empty string 
    if (numString[i] == '\0')
    {
        return false; 
    }

    // loop through each character in the c-string
    while (i <= lastValidIndex)
    {
        // check to ensure that the characters are digits, otherwise return false
        if (numString[i] >='0' && numString[i] <= '9')
        {
            foundDigit = true; 
        }

        else if (numString[i] == '.')
        {
            // we cannot have more than one decimal
            if (hasDecimal)
            {
                return false; 
            }

            // ensure the decimal is not at the beginning or end, otherwise return false
            if (i == 0 || numString[i + 1] == '\0')
            {
                return false; 
            }
        }

        // check for + or - in the middle of the function
        else if (numString[i] == '+' || numString[i] == '-')
        {
            return false; 
        }

        else 
        {
            return false; 
        }
        i++; // move to the next character 
    }

    return foundDigit; // will return true if we have found a singular digit (that was not set to false by any of our conditions above)
}

// CHARACTERISTIC helper function to extract the integer part of the number (before decimal point)
void extractCharacteristic(const char numString[], int& c)
{
    int i = skipLeadingSpaces(numString); // set our index to wherever the first actual value is
    bool isNegative = false; // check for negative numbers

    // check if the string is valid 
    if (!validString(numString))
    {
        return; // do nothing if the string is invalid
    }

    // check for the sign (if there is one)
    if (numString[i] == '+' || numString[i] == '-')
    {
        isNegative = (numString[i] == '-'); // update negative if needed
        i++; // move to the next character
    }

    c = 0; // initialize characteristic

    // parse the integer part before the decimal
    while (numString[i] >= '0' && numString[i] <= '9')
    {
        // multiply c by 10 to shift left (increase place value) before adding new digit
        c = c * 10 + (numString[i] - '0'); 
        i++; 
    }

    // apply the negative sign if needed
    if (isNegative)
    {
        c = -c; 
    }
}

// MANTISSA helper function to extract the fractional part of the number (after the decimal point)
void extractMantissa(const char numString[], int& numerator, int& denominator)
{  
    // check if the string is valid 
    if (!validString(numString))
    {
        return; // do nothing if the string is invalid
    }

    int i = skipLeadingSpaces(numString); // set our index to wherever the first actual value is

    // default values
    numerator = 0; 
    denominator = 1; 

    // check for the sign (if there is one) and skip over it
    if (numString[i] == '+' || numString[i] == '-')
    {
        i++; 
    }

    // skip through the characteristic part
    while (numString[i] >= '0' && numString[i] <= '9')
    {
        i++; 
    }

    // if there is no decimal point, the mantissa is 0/1
    if (numString[i] != '.')
    {
        return; // nothing changes
    }

    i++; // move over the decimal point

    // parse the mantissa (after the decimal point)
    while (numString[i] >= '0' && numString[i] <= '9')
    {
        // builds the numerator by multiplying by 10 and adding the current digit
        numerator = numerator * 10 + (numString[i] - '0'); 

        // increase the denominator by a factor of 10 for each digit
        denominator = denominator * 10; 

        i++; // move to the next digit
    }
}

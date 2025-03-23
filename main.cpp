
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

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
    //you will have to come up with an algorithm to add the two numbers
    //hard coded return value to make the main() work
    result[0] = '4';
    result[1] = '.';
    result[2] = '1';
    result[3] = '6';
    result[4] = '6';
    result[5] = '6';
    result[6] = '6';
    result[7] = '6';
    result[8] = '6';
    result[9] = '\0';

    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
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

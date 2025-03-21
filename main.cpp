
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
bool validString(const char numString[]); 

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    
    // testing
    cout << "0: " << validString("0") << endl; 
    cout << "2342342: " << validString("2342342") << endl; 
    cout << "234.234: " << validString("234.234") << endl; 
    cout << ".234 :" << validString(".234") << endl;
    cout << "23.: " << validString("23.") << endl; 
    cout << "+234 :" << validString("+234") << endl;
    cout << "-234.2: " << validString("-234.2") << endl; 
    cout << "-234:" << validString("-234") << endl;
    cout << "2+3: " << validString("2+3") << endl; 
    cout << "23-: " << validString("23-") << endl; 

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
    //c = 123;
    //return true;
    
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    // hard coded return value to make the main() work

    // parse string without strings
    // spaces on either end -> skip over
    // spaces in the middle between digits -> problem
    // string could have decimal OR not
    // uniary + or - start -> only FIRST character can be that 
    // check for valid string first, if all rules are met, then actually execute the two functions
    // successive powers of 10
    // yes or no valid string helper
    // start and end positions of characteristic, another for mantissa
    // helper function for math (multiply by 10)

    numerator = 456;
    denominator = 1000;
    return true;
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
//

// CHARACTERISTIC AND MANTISSA HELPER FUNCTIONS

// helper function to skip over leading spaces
int skipLeadingSpaces(const char numString[])
{
    int i = 0; 
    while (numString[i] == ' ')
    {
        i++; 
    }
    return i; // returns the index of the first non-space character 
}

// helper function to skip over middle space -> returns false if no middle spaces are found
bool hasMiddleSpaces(const char numString[])
{
    // bool that is set to true when we come across a digit
    bool foundDigit = false; 

    for (int i = 0; numString[i] != '\0'; i++)
    {
        if (numString[i] >= '0' && numString[i] <= '9')
        {
            foundDigit = true; // found a digit
        }
        else if (numString[i] == ' ' && foundDigit)
        {
            return true; // a space has been found AFTER a digit
        }
    }
    return false; // no middle spaces were found
}

// helper function to check if we have a valid c-string
bool validString(const char numString[]) 
{
    int i = 0; 

    // check if the first character is valid (digit, +, or -)
    if (numString[i] == '+' || numString[i] == '-')
    {
        i++; // increment
    }

    bool hasDecimal = false; // keep track of if there is one singular decimal point within the c-string

    // check for an empty string 
    if (numString[i] == '\0')
    {
        return false; 
    }

    // loop through each character in the c-string
    while (numString[i] != '\0')
    {
        // check to ensure that the characters are digits, otherwise return false
        if (numString[i] >='0' && numString[i] <= '9')
        {
            // continue
        }

        else if (numString[i] == '.')
        {
            // we cannot have return decimal occur twice
            if (hasDecimal)
            {
                return false; 
            }

            // ensure the decimal is not at the beginning or end, otherwise return false
            if (i == 0 || numString[i+1] == '\0')
            {
                return false; 
            }
        }

        else if (numString[i] == '+' || numString[i] == '-')
        {
            return false; 
        }

        else 
        {
            return false; 
        }
        i++;
    }
    return true; 
}


// helper function to check for leading spaces
//void skipLeadingSpaces

// helper function to check 
//void skipEndSpace

// helper function to 
//void skipMiddleSpace
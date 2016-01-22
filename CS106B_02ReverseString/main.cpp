/* 
 * File:   main.cpp
 * Author: xmeng
 *
 * Created on February 26, 2015, 2:02 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

string reverse(string inputStr)
{
    if (inputStr.length() <=1)
        return inputStr;
    else 
        return reverse(inputStr.substr(1, inputStr.length() -1 )) + inputStr[0];
}

/*
 * 
 */
int main(int argc, char** argv) {

    string inputStr = string("Nubian Ibex"); 
    // cin >> inputStr;
    
    cout << reverse(inputStr) << endl;
    return 0;
}


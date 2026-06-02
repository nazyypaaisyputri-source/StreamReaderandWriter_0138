#include <iostream>
#include <exception>
#include <array>
using namespace std;


int main()
{
    cout << "Awal Program" << endl;
    try
    {
        array <int, 3> data = { 1, 2, 3 };
        cout <<data.at(5) << endl;
    }
    catch (exception& e)
#include <iostream>
#include <string>

using namespace std;
string str;

int main()
{
   while (cin >> str) {
       int n = str.length();
       int i = 0;
       int flag = 0;

       while (i < n) {
           if (str[i] == '"' && flag == 0) {
               str[i] = '``';
               flag = 1;
               cout << str[i];
               i++;
           }
           if (str[i] == '"' && flag == 1) {
               str[i] = '\'\'';
               flag = 0;
               cout << str[i];
               i++;
           }
           cout << str[i];
           i++;
       }
       cout << " ";
   }
}
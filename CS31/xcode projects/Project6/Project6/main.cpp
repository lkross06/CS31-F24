#include <iostream>
using namespace std;

void removeS(char* c){
    char* temp;
    while (*c != 0){
        temp = c;
    if (*c == 'S' || *c == 's'){
        while(*temp != 0){
            *temp = *(temp + 1);
        temp++;
        }
        *temp = 0;
    } else c++;
    }
}

int main(){
    char msg[50] = "She'll blossom like a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll bloom like a male prince.
}

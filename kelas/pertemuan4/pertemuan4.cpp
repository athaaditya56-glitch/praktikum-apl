#include <iostream>
using namespace std;

int main() {
    int var = 10;
    int *varPtr = &var;

    cout << "Hasil dari varPtr: " << varPtr << endl;
    cout << "Hasil dari *varPtr: " << *varPtr << endl;

    return 0;
}
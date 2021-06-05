
#include <iostream>
using namespace std;

#include <iomanip>
using std::setw;    // set width or something? 
// setw(k) seems to insert k spaces
//cout << "Element" << setw(13) << "Value" << endl;

int main () {
 
    int n[ 10 ]; 
    
    for (int i=0; i<10; i++) {
        n[i] = i + 100;
    }

    cout << "Element" << setw(13) << "Value" << endl;
    cout << "Element" << "-------------" << "Value" << endl;
    //for (int i=0; i<N; i++) {

    //}
    
    return 0;
}

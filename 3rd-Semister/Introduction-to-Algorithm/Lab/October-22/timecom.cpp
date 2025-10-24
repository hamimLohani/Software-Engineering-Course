
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {

    double n = 1000;

    auto start = high_resolution_clock::now();
    for(int i = 0; i < n; i++) {
        // for (int j = 0; j < 1; j++) {
        //     int x = i * j;
        // }
        double y = i * i;
    }


    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
    
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    
    return 0;
}
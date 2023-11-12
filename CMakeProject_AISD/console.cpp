#include "CMakeProject_AISD.cpp"

using namespace std;
using namespace space_class;

void run() {
    cout << "Enter your details here" << endl;
    int choice;
    cin >> choice;

}

int main() {
    while (true) {
        cout << "Press '1' to run the function again or '0' to exit." << endl;
        int choice;
        cin  >> choice;
        if (choice) {
            run();
        }
        else {
            break;
        }
    }
    return 0;
}
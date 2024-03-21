#include <iostream>
#include <string>
#include "../../utils/func.h"


using std::cout;
using std::endl;
using std::string;
using std::rand;


int exception() {
    {
        try {
            long dice = get_random_number() % 100;
            cout << "dice: " << dice <<  endl;

            if (dice > 50) {
                throw 1;
            }
            else {
                throw (string) "asdasdasd";
            }
        }
        catch (int e) {
            cout << "thrown int exception: " << e << endl;
        }
        catch (string& e) {
            cout << "thrown string exception: " << e << endl;
        }
    }
}


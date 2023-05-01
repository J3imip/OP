#include <iostream>

using namespace std;

enum Month {
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

Month operator++(Month &m) {
    m = (m == Month::December) ? Month::January : (Month)((int)(m) + 1);
    return m;
}

Month operator--(Month &m) {
    m = (m == Month::January) ? Month::December : (Month)((int)(m) - 1);
    return m;
}

int main() {
    Month m = Month::December;

    cout << "Current month:\t" << m+1 << endl;
    ++m;
    cout << "Next month:\t" << m+1 << endl;
    --m;
    cout << "Previous month:\t" << m+1 << endl;
}

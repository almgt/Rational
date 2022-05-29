#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <exception>
#include <numeric>


using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;// Реализуйте конструктор по умолчанию
    }

    Rational(int numerator, int denominator) {
        if (denominator == 0) throw invalid_argument("invalid_argument");
        if (numerator == 0) denominator = 1;
        else if ((denominator < 0) || (denominator < 0 && numerator < 0)) { 
            denominator*= (-1); numerator*= (-1); 
        } 
        p = numerator / (std::gcd(numerator, denominator));
        q = denominator / (std::gcd(numerator, denominator));
        // Реализуйте конструктор
    }

    int Numerator() const {
        return p;// Реализуйте этот метод
    }

    int Denominator() const {
        return q;// Реализуйте этот метод
    }

private:
    int p;
    int q;
    // Добавьте поля
};

Rational operator + ( const Rational& one, const Rational& two) {
    if (one.Denominator() != two.Denominator()) {
        return Rational(one.Numerator() * two.Denominator() + two.Numerator() * one.Denominator(),
            one.Denominator() * two.Denominator());
    }
    else if ((one.Numerator() + two.Numerator()) % (one.Denominator()) == 0) {
        return Rational((one.Numerator() + two.Numerator()) / one.Denominator(), 1);
    }
    else return Rational(one.Numerator() + two.Numerator(),
        one.Denominator());
}

Rational operator - (const Rational& one, const Rational& two) {
    if (one.Denominator() != two.Denominator()) {
        return Rational(one.Numerator() * two.Denominator() - two.Numerator() * one.Denominator(),
            one.Denominator() * two.Denominator());
    }
    else if ((one.Numerator() - two.Numerator()) % (one.Denominator()) == 0) {
        return Rational((one.Numerator() - two.Numerator()) / one.Denominator(), 1);
    }
    else return Rational(one.Numerator() - two.Numerator(),
        one.Denominator());
}
bool operator == (const Rational& one, const Rational& two) {
    if (one.Numerator() == two.Numerator()&& one.Denominator() == two.Denominator()) {
        return true;
    }
    return false;
}

Rational operator * (const Rational& one, const Rational& two) {
    return Rational(one.Numerator() * two.Numerator(), one.Denominator() * two.Denominator());
}
 
Rational operator / (const Rational& one, const Rational& two) {
    if (two.Numerator() == 0) throw domain_error("domain_error");
    return Rational(one.Numerator() * two.Denominator(), one.Denominator() * two.Numerator());
}

istream& operator >>(istream& stream, Rational& r) {
    int n1 = 0, d1 = 0;  
    stream >> n1;
    if(stream.peek() == '/') stream.ignore();
    stream >> d1;
    if (!stream >> n1 || !stream >> d1) { return stream; }
    r = { n1, d1 };
    return stream;
}

ostream& operator <<(ostream& stream, const Rational& r) {
    stream  << r.Numerator() << "/" << r.Denominator();
    return stream;
}

bool operator <(const Rational& l, const Rational& r) {
    if (l.Denominator() == r.Denominator()) {
        return l.Numerator() < r.Numerator();
    } return l.Numerator() * r.Denominator() < r.Numerator() * l.Denominator();
}

int main() { 

    /*try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    }
    catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    }
    catch (domain_error&) {
    }

    cout << "OK" << endl;*/

    /* {
    const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
    if (rs.size() != 3) {
        cout << "Wrong amount of items in the set" << endl;
        return 1;
    }

    vector<Rational> v;
    for (auto x : rs) {
        v.push_back(x);
    }
    if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
        cout << "Rationals comparison works incorrectly" << endl;
        return 2;
    }
}

{
    map<Rational, int> count;
    ++count[{1, 2}];
    ++count[{1, 2}];

    ++count[{2, 3}];

    if (count.size() != 2) {
        cout << "Wrong amount of items in the map" << endl;
        return 3;
    }
}

cout << "OK" << endl;*/

    /* {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    {
        istringstream input("2/4/6/8");
        Rational r1;
        input >> r1;
        bool correct = r1 == Rational(1, 2);
        if (!correct) {
            cout << "Multiple-slashed number sequence value read incorrectly: " << r1 << endl;
            return 7;
        }
    }

    cout << "OK" << endl;*/

    /* {
        Rational r1(4, 6);
        Rational r2(2, 3);
        //r1 = r2;
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        //a + b;
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        //a - b;
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }*/
    /* {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }*/

    return 0;
}


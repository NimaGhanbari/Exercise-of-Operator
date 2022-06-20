#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
 
using namespace std;

////////////////////////////////////////
// class error

class error
{
private:
    string errormessage;

public:
    error(string);
    void print();
};

error::error(string mes)
{
    errormessage = mes;
}

void error::print()
{
    cout << "ERROR: " << errormessage << '\n';
}

////////////////////////////////////////
// class term

class term
{
private:
    float coefficient;
    int power;

public:
    term(string obj);
    term();
    static pair<float, int> Separation(string object);
    float get_f();
    int get_i();
    term operator+(term);
    term operator+(float);
    term operator-(term);
    term operator-(float);
    term operator*(term);
    term operator*(float);
    term operator/(term);
    term operator/(float);
    term operator+=(term);
    term operator-=(term);
    term operator*=(term);
    term operator/=(term);
    term operator=(term);
    int operator>(term);
    int operator>(float);
    int operator<(term);
    int operator<(float);
    int operator>=(term);
    int operator>=(float);
    int operator<=(term);
    int operator<=(float);
    int operator==(term);
    int operator==(float);
    int operator!=(term);
    int operator!=(float);
    term operator~();
    term operator++();
    term operator--();
    float operator()(float);
    friend ostream &operator<<(ostream &out, term &obj);
    friend istream &operator>>(istream &in, term &obj);
    friend class polynomial;
};

float term::get_f()
{
    return coefficient;
}

int term::get_i()
{
    return power;
}

term::term(string obj)
{
    coefficient = Separation(obj).first;
    power = Separation(obj).second;
}

term::term()
{
}

pair<float, int> term::Separation(string object)
{
    string temp1 = "";
    string temp2 = "";
    bool flag = true;
    int i = 0;
    for (; i < object.size() && flag == true; i++)
    {
        if (object[i] >= '0' && object[i] <= '9' || object[i] == '.')
        {
            temp1 += object[i];
        }

        else
        {
            flag = false;
            --i;
        }
    }
    float num1 = stof(temp1);
    int num2 = 0;
    ++i;
    ++i;
    if (i < object.size())
    {
        for (; i < object.size(); i++)
        {
            temp2 += object[i];
        }
    }
    else
    {
        temp2 = "0";
    }
    num2 = stoi(temp2);
    return {num1, num2};
}

term term::operator+(term obj)
{
    try
    {
        if (power != obj.power)
        {
            throw error("These sentences can not be combined due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return term("0x^0");
    }
    // if (power != obj.power)
    // {
    //     cout << "These two sentences do not come together. " << '\n';
    //     return term("0x^0");
    // }
    term temp;
    temp.coefficient = coefficient + obj.coefficient;
    temp.power = obj.power;
    return temp;
}

term term::operator+(float number)
{
    try
    {
        if (power != 0)
        {
            throw error("These sentences can not be combined due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return term("0x^0");
    }
    // if (power != 0)
    // {
    //     cout << "These two sentences do not come together. " << '\n';
    //     return term("0x^0");
    // }
    term temp = *this;
    temp.coefficient = coefficient + number;
    temp.power = 0;
    return temp;
}

term term::operator-(term obj)
{
    try
    {
        if (power != obj.power)
        {
            throw error("These two sentences can not be reduced due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return term("0x^0");
    }
    // if (power != obj.power)
    // {
    //     cout << "These two sentences do not come together. " << '\n';
    //     return term("0x^0");
    // }

    term temp = obj;
    temp.coefficient = coefficient - obj.coefficient;
    temp.power = obj.power;
    return temp;
}

term term::operator-(float number)
{
    try
    {
        if (power != 0)
        {
            throw error("These two sentences can not be reduced due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return term("0x^0");
    }
    // if (power != 0)
    // {
    //     cout << "These two sentences do not come together. " << '\n';
    //     return term("0x^0");
    // }
    term temp = *this;
    temp.coefficient = coefficient - number;
    temp.power = 0;
    return temp;
}

term term::operator*(term obj)
{
    term temp = obj;
    temp.coefficient = coefficient * obj.coefficient;
    temp.power = power + obj.power;
    return temp;
}

term term::operator*(float number)
{
    term temp = *this;
    temp.coefficient = coefficient * number;
    temp.power = power;
    return temp;
}

term term::operator/(term obj)
{
    term temp = obj;
    temp.coefficient = coefficient / obj.coefficient;
    temp.power = power - obj.power;
    return temp;
}

term term::operator/(float number)
{
    try
    {
        if (number == 0)
        {
            throw error("division sentence on the input number is not possible because the input number is zero.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return term("0x^0");
    }
    term temp = *this;
    temp.coefficient = coefficient / number;
    temp.power = power;
    return temp;
}

term term::operator+=(term obj)
{
    try
    {
        if (power != obj.power)
        {
            throw error("These sentences can not be combined due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return term("0x^0");
    }
    coefficient = coefficient + obj.coefficient;
    return *this;
}

term term::operator-=(term obj)
{
    try
    {
        if (power != obj.power)
        {
            throw error("These two sentences can not be reduced due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return term("0x^0");
    }
    // if (power != obj.power)
    // {
    //     cout << "These two sentences do not come together. " << '\n';
    //     return term("0x^0");
    // }

    coefficient = coefficient - obj.coefficient;
    return *this;
}

term term::operator*=(term obj)
{
    coefficient = coefficient * obj.coefficient;
    power = power + obj.power;
    return *this;
}

term term::operator/=(term obj)
{
    coefficient = coefficient / obj.coefficient;
    power = power - obj.power;
    return *this;
}

term term::operator=(term obj)
{
    coefficient = obj.coefficient;
    power = obj.power;
    return *this;
}

int term::operator>(term obj)
{
    if (power > obj.power)
    {
        return 1;
    }
    if (power == obj.power)
    {
        if (coefficient > obj.coefficient)
        {
            return 1;
        }
    }
    return 0;
}

int term::operator>(float number)
{
    if (power > 0)
    {
        return 1;
    }
    if (power < 0)
    {
        return 0;
    }

    if (power == 0)
    {
        if (coefficient > number)
        {
            return 1;
        }
    }

    return 0;
}

int term::operator<(float number)
{
    if (power > 0)
    {
        return 0;
    }
    if (power < 0)
    {
        return 1;
    }

    if (power == 0)
    {
        if (coefficient < number)
        {
            return 1;
        }
    }

    return 0;
}

int term::operator>=(term obj)
{
    if (power > obj.power)
    {
        return 1;
    }
    if (power == obj.power)
    {
        if (coefficient >= obj.coefficient)
        {
            return 1;
        }
    }
    return 0;
}

int term::operator>=(float number)
{
    if (power > 0)
    {
        return 1;
    }
    if (power < 0)
    {
        return 0;
    }

    if (power == 0)
    {
        if (coefficient >= number)
        {
            return 1;
        }
    }

    return 0;
}

int term::operator<=(term obj)
{
    if (power < obj.power)
    {
        return 1;
    }
    if (power == obj.power)
    {
        if (coefficient <= obj.coefficient)
        {
            return 1;
        }
    }
    return 0;
}

int term::operator<=(float number)
{
    if (power > 0)
    {
        return 0;
    }
    if (power < 0)
    {
        return 1;
    }

    if (power == 0)
    {
        if (coefficient <= number)
        {
            return 1;
        }
    }

    return 0;
}

int term::operator<(term obj)
{
    if (power < obj.power)
    {
        return 1;
    }
    if (power == obj.power)
    {
        if (coefficient < obj.coefficient)
        {
            return 1;
        }
    }
    return 0;
}

int term::operator==(float number)
{

    if (power != 0)
    {
        return 0;
    }
    if (coefficient == number)
    {
        return 1;
    }
    return 0;
}

int term::operator!=(term obj)
{
    if (coefficient != obj.coefficient || power != obj.power)
    {
        return 1;
    }
    return 0;
}

int term::operator!=(float number)
{
    if (power != 0)
    {
        return 1;
    }
    if (coefficient != number)
    {
        return 1;
    }
    return 0;
}

term term::operator~()
{
    term temp = *this;
    temp.coefficient = temp.coefficient * temp.power;
    if (temp.power != 0)
    {
        --temp.power;
    }

    return temp;
}

ostream &operator<<(ostream &out, term &obj)
{
    out << "\"" << obj.coefficient << "x^" << obj.power << "\"" << '\n';
    return out;
}

term term::operator++()
{
    try
    {
        if (power != 0)
        {
            throw error("These sentences can not be combined due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return *this;
    }
    // if (power != 0)
    // {
    //     cout << "This sentence cannot be increased by one unit. " << '\n';
    //     return *this;
    // }
    ++coefficient;
    return *this;
}

term term::operator--()
{
    try
    {
        if (power != 0)
        {
            throw error("These two sentences can not be reduced due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return *this;
    }
    // if (power != 0)
    // {
    //     cout << "This sentence cannot be increased by one unit. " << '\n';
    //     return *this;
    // }
    --coefficient;
    return *this;
}

float term::operator()(float number)
{
    float sum = 1;
    for (int i = 0; i < power; i++)
    {
        sum = sum * number;
    }
    sum = sum * coefficient;
    return sum;
}

istream &operator>>(istream &in, term &obj)
{
    string object;
    in >> object;
    string temp1 = "";
    string temp2 = "";
    bool flag = true;
    int i = 0;
    for (; i < object.size() && flag == true; i++)
    {
        if (object[i] >= '0' && object[i] <= '9' || object[i] == '.')
        {
            temp1 += object[i];
        }

        else
        {
            flag = false;
            --i;
        }
    }
    obj.coefficient = stof(temp1);
    int num2 = 0;
    ++i;
    ++i;
    if (i < object.size())
    {
        for (; i < object.size(); i++)
        {
            temp2 += object[i];
        }
    }
    else
    {
        temp2 = "0";
    }
    obj.power = stoi(temp2);

    return in;
}

//////////////////////////////////////
// class polynomial

class polynomial
{
private:
    vector<term> current;

public:
    polynomial(vector<term>);
    polynomial();
    void sort(vector<term> &);
    polynomial operator+=(polynomial);
    polynomial operator-=(polynomial);
    polynomial operator*(polynomial);
    polynomial operator*=(polynomial);
    polynomial operator~();
    bool operator>(polynomial);
    bool operator>=(polynomial);
    bool operator<(polynomial);
    bool operator<=(polynomial);
    bool operator==(polynomial);
    bool operator!=(polynomial);
    polynomial operator+(polynomial);
    polynomial operator-(polynomial);
    float operator()(float);
    void operator=(polynomial obj1);
    term operator[](int);
    term operator[](int) const;
    int find_number(polynomial);
    void fun_equel(polynomial &);
    void operator++();
    void operator--();
    static void read_of_file_txt(polynomial &);
    static void read_of_file_bin(polynomial &);
    static void check_power(polynomial &);
    static polynomial processing(string);
    friend ostream &operator<<(ostream &out, polynomial &obj);
    friend istream &operator>>(istream &in, polynomial &obj);
    friend void write_in_file_txt(polynomial);
    friend void write_in_file_bin(polynomial);
    friend void print_polynomial(polynomial);
    friend void fun_add(polynomial &);
    friend void fun_subtract(polynomial &);
    friend void fun_multiply(polynomial &);
    friend void fun_derivative(polynomial);
    friend void fun__find_degree(polynomial);
    friend void fun_Find_Value_for_specific_x(polynomial);
    friend void comparee(polynomial);
    friend int find_number(polynomial);
};

void write_in_file_txt(polynomial obj)
{
    string name_file;
    cout << "file name:";
    cin >> name_file;
    ofstream mystream(name_file);
    try
    {
        if (!mystream)
        {
            throw "The file will not open.";
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return;
    }
    for (int i = 0; i < obj.current.size(); i++)
    {
        mystream << obj.current[i].get_f() << ' ' << obj.current[i].get_i() << '\n';
    }
    mystream.close();
}

void write_in_file_bin(polynomial obj)
{
    string name_file;
    cout << "file name:";
    cin >> name_file;
    term temp;
    ofstream mystream(name_file, ios::binary);
    try
    {
        if (!mystream)
        {
            throw "The file will not open.";
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return;
    }
    // int size_term = sizeof(temp);
    int size_polynomial = obj.current.size();
    mystream.write((char *)&size_polynomial, sizeof(int));
    // for (int i = 0; i < obj.current.size(); i++)
    // {
    //     mystream.write((char *)&obj, sizeof(obj));
    // }
    for (term i : obj.current)
    {
        mystream.write((char *)&i, sizeof(int));
    }

    mystream.close();
}

void polynomial::read_of_file_txt(polynomial &obj)
{
    string name;
    cout << "file name: ";
    cin >> name;
    ifstream mystream(name);
    try
    {
        if (!mystream)
        {
            throw "The file will not open.";
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return;
    }
    vector<term> vec;
    term temp;
    while (mystream >> temp.coefficient >> temp.power)
    {
        vec.push_back(temp);
    }
    for (int i = 0; i < vec.size(); i++)
    {
        obj.current.push_back(vec[i]);
    }
    mystream.close();
}

void polynomial::read_of_file_bin(polynomial &obj)
{
    string name;
    cout << "file name: ";
    cin >> name;
    ifstream mystream(name, ios::binary);
    try
    {
        if (!mystream)
        {
            throw "The file will not open.";
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return;
    }
    cout << "aaw\n";
    getch();
    int size;
    mystream.read((char *)&size, sizeof(int));
    cout << size;
    getch();
    vector<term> vec(size);
    for (term &i : vec)
    {
        mystream.read((char *)&i, sizeof(int));
    }
    mystream.close();
    for (int i = 0; i < vec.size(); i++)
    {
        obj.current.push_back(vec[i]);
    }
}

polynomial::polynomial()
{
}

polynomial::polynomial(vector<term> current1)
{
    sort(current1);

    for (int i = 0; i < current1.size(); i++)
    {
        current.push_back(current1[i]);
    }
}

void polynomial::sort(vector<term> &current)
{
    int i, j;
    for (i = 0; i < current.size() - 1; i++)
    {
        for (j = 0; j < current.size() - 1 - i; j++)
        {
            if (current[j].power > current[j + 1].power)
            {
                term temp = current[j];
                current[j] = current[j + 1];
                current[j + 1] = temp;
            }
        }
    }
}

polynomial polynomial::operator+=(polynomial obj1)
{

    for (int i = 0; i < obj1.current.size(); i++)
    {
        bool hp = false;
        int j = 0;
        for (; j < current.size(); j++)
        {
            if (obj1.current[i].get_i() == current[j].get_i())
            {
                current[j].coefficient += obj1.current[i].coefficient;
                hp = true;
                break;
            }
        }
        int rec = current.size();
        if (hp == false)
        {
            current.push_back(obj1.current[i]);
        }
    }
    sort(current);
    return *this;
}

polynomial polynomial::operator-=(polynomial obj1)
{
    for (int k = 0; k < obj1.current.size(); k++)
    {
        obj1.current[k].coefficient *= -1;
    }

    for (int i = 0; i < obj1.current.size(); i++)
    {
        bool hp = false;
        int j = 0;
        for (; j < current.size(); j++)
        {
            if (obj1.current[i].get_i() == current[j].get_i())
            {
                current[j].coefficient += obj1.current[i].coefficient;
                hp = true;
                break;
            }
        }
        int rec = current.size();
        if (hp == false)
        {
            current.push_back(obj1.current[i]);
        }
    }
    sort(current);
    return *this;
}

polynomial polynomial::operator*(polynomial obj1)
{
    term temp;
    // vector<term> vec;
    // vec.push_back(temp);
    // polynomial temp1(current);
    polynomial temp1;
    int temp3 = 0;
    for (int i = 0; i < current.size(); i++)
    {
        for (int j = 0; j < obj1.current.size(); j++)
        {
            temp.coefficient = 0;
            temp.power = 0;
            temp.coefficient = current[i].coefficient * obj1.current[j].coefficient;
            temp.power = current[i].power + obj1.current[j].power;
            cout << temp.coefficient << '\n';
            cout << temp.power << '\n';
            temp1.current.push_back(temp);
            ++temp3;
        }
    }
    // cout << "11";
    // getch();
    print_polynomial(temp1);
    getch();
    // sort(temp1.current);
    return temp1;
}

polynomial polynomial::operator~()
{
    polynomial object(current);
    for (int i = 0; i < current.size(); i++)
    {
        object.current[i] = ~object.current[i];
    }
    return object;
}

bool polynomial::operator>(polynomial obj1)
{
    int size = current.size();
    int size1 = obj1.current.size();
    int result;
    bool checking = true;
    for (;;)
    {
        if (current[size - 1] > obj1.current[size1 - 1])
        {
            result = 1;
            return result;
        }
        if (current[size - 1].power == obj1.current[size1 - 1].power)
        {
            if (current[size - 1].coefficient > obj1.current[size1 - 1].coefficient)
            {
                result = 1;
                return result;
            }
            if (current[size - 1].coefficient < obj1.current[size1 - 1].coefficient)
            {
                result = 0;
                return result;
            }
        }
        if (current[size - 1] < obj1.current[size1 - 1])
        {
            result = 0;
            return result;
        }
        --size;
        --size1;
        if (size == 0 && size1 == 0)
        {
            return 0;
        }

        if (size == 0)
        {
            return 0;
        }
        if (size1 == 0)
        {
            return 1;
        }
    }
    return result;
}

polynomial polynomial::operator*=(polynomial obj1)
{
    term temp;
    polynomial temp1;
    int temp3 = 0;
    for (int i = 0; i < current.size(); i++)
    {
        for (int j = 0; j < obj1.current.size(); j++)
        {
            temp.coefficient = 0;
            temp.power = 0;
            temp.coefficient = current[i].coefficient * obj1.current[j].coefficient;
            temp.power = current[i].power + obj1.current[j].power;
            cout << temp.coefficient << '\n';
            cout << temp.power << '\n';
            temp1.current.push_back(temp);
            ++temp3;
        }
    }
    print_polynomial(temp1);
    getch();
    *this = temp1;
    return *this;
}

bool polynomial::operator>=(polynomial obj1)
{
    int size = current.size();
    int size1 = obj1.current.size();
    int result;
    bool checking = true;
    for (;;)
    {
        if (current[size - 1] > obj1.current[size1 - 1])
        {
            result = 1;
            return result;
        }
        if (current[size - 1].power == obj1.current[size1 - 1].power)
        {
            if (current[size - 1].coefficient > obj1.current[size1 - 1].coefficient)
            {
                result = 1;
                return result;
            }
            if (current[size - 1].coefficient < obj1.current[size1 - 1].coefficient)
            {
                result = 0;
                return result;
            }
        }
        if (current[size - 1] < obj1.current[size1 - 1])
        {
            result = 0;
            return result;
        }
        --size;
        --size1;
        if (size == 0 && size1 == 0)
        {
            return 1;
        }

        if (size == 0)
        {
            return 0;
        }
        if (size1 == 0)
        {
            return 1;
        }
    }
    return result;
}

bool polynomial::operator<(polynomial obj1)
{
    int size = current.size();
    int size1 = obj1.current.size();
    int result;
    bool checking = true;
    for (;;)
    {
        if (current[size - 1] > obj1.current[size1 - 1])
        {
            result = 0;
            return result;
        }
        if (current[size - 1].power == obj1.current[size1 - 1].power)
        {
            if (current[size - 1].coefficient > obj1.current[size1 - 1].coefficient)
            {
                result = 0;
                return result;
            }
            if (current[size - 1].coefficient < obj1.current[size1 - 1].coefficient)
            {
                result = 1;
                return result;
            }
        }
        if (current[size - 1] < obj1.current[size1 - 1])
        {
            result = 1;
            return result;
        }
        --size;
        --size1;
        if (size == 0 && size1 == 0)
        {
            return 0;
        }

        if (size == 0)
        {
            return 1;
        }
        if (size1 == 0)
        {
            return 0;
        }
    }
    return result;
}

bool polynomial::operator<=(polynomial obj1)
{
    int size = current.size();
    int size1 = obj1.current.size();
    int result;
    bool checking = true;
    for (;;)
    {
        if (current[size - 1] > obj1.current[size1 - 1])
        {
            result = 0;
            return result;
        }
        if (current[size - 1].power == obj1.current[size1 - 1].power)
        {
            if (current[size - 1].coefficient > obj1.current[size1 - 1].coefficient)
            {
                result = 0;
                return result;
            }
            if (current[size - 1].coefficient < obj1.current[size1 - 1].coefficient)
            {
                result = 1;
                return result;
            }
        }
        if (current[size - 1] < obj1.current[size1 - 1])
        {
            result = 1;
            return result;
        }
        --size;
        --size1;
        if (size == 0 && size1 == 0)
        {
            return 1;
        }
        if (size == 0)
        {
            return 1;
        }
        if (size1 == 0)
        {
            return 0;
        }
    }
    return result;
}

bool polynomial::operator==(polynomial obj1)
{
    int size = current.size();
    int size1 = obj1.current.size();
    for (;;)
    {
        if (current[size - 1] != obj1.current[size1 - 1])
        {
            return 0;
        }
        if (size != size1)
        {
            return 0;
        }
        --size;
        --size1;
        if (size == 0 && size1 == 0)
        {
            break;
        }
    }
    return 1;
}

bool polynomial::operator!=(polynomial obj1)
{
    int size = current.size();
    int size1 = obj1.current.size();
    for (;;)
    {
        if (current[size - 1] != obj1.current[size1 - 1])
        {
            return 1;
        }
        if (size != size1)
        {
            return 1;
        }
        --size;
        --size1;
        if (size == 0 && size1 == 0)
        {
            break;
        }
    }
    return 0;
}

polynomial polynomial::operator+(polynomial obj1)
{
    polynomial temp2;
    term temp1;
    int i = 0;
    for (; i < current.size(); i++)
    {
        temp1.coefficient = 0;
        temp1.power = 0;
        temp1.coefficient = current[i].coefficient;
        temp1.power = current[i].power;
        temp2.current.push_back(temp1);
    }

    for (int j = 0; j < obj1.current.size(); j++)
    {
        temp1.coefficient = 0;
        temp1.power = 0;
        temp1.coefficient = obj1.current[j].coefficient;
        temp1.power = obj1.current[j].power;
        temp2.current.push_back(temp1);
    }

    polynomial::check_power(temp2);
    return temp2;
}

polynomial polynomial::operator-(polynomial obj1)
{
    polynomial temp2;
    term temp1;
    int i = 0;
    for (; i < current.size(); i++)
    {
        temp1.coefficient = 0;
        temp1.power = 0;
        temp1.coefficient = current[i].coefficient;
        temp1.power = current[i].power;
        temp2.current.push_back(temp1);
    }

    for (int j = 0; j < obj1.current.size(); j++)
    {
        temp1.coefficient = 0;
        temp1.power = 0;
        temp1.coefficient = obj1.current[j].coefficient * -1;
        temp1.power = obj1.current[j].power;
        temp2.current.push_back(temp1);
    }
    polynomial::check_power(temp2);
    return temp2;
}

void polynomial::operator--()
{
    try
    {
        if (current.size() != 1 && current[0].power != 0)
        {
            throw error("These sentences can not be combined due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return;
    }
    --current[0].coefficient;
}

void polynomial::operator++()
{
    try
    {
        if (current.size() != 1 && current[0].power != 0)
        {
            throw error("These sentences can not be combined due to unequal powers.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return;
    }
    ++current[0].coefficient;
}

void polynomial::operator=(polynomial obj1)
{
    for (int i = current.size() - 1; i >= 0; --i)
    {
        current.erase(current.end());
    }
    for (int i = 0; i < obj1.current.size(); i++)
    {
        current.push_back(obj1.current[i]);
    }
}

void polynomial::fun_equel(polynomial &obj1)
{
    string temp;
    cout << "Enter the desired polynomial. " << '\n';
    cout << "polynomial: ";
    cin >> temp;
    polynomial obj2(polynomial::processing(temp).current);
    obj1 = obj2;
}

void polynomial::check_power(polynomial &obj)
{
    for (int i = 0; i < obj.current.size(); i++)
    {
        for (int y = i + 1; y < obj.current.size(); y++)
        {
            if (obj.current[i].get_i() == obj.current[y].get_i())
            {
                obj.current[i].coefficient += obj.current[y].coefficient;
                obj.current.erase(obj.current.begin() + (y));
                --y;
            }
        }
    }
    for (int i = 0; i < obj.current.size(); i++)
    {
        if (obj.current[i].get_f() == 0)
        {
            obj.current.erase(obj.current.begin() + (i));
        }
    }
}

int polynomial::find_number(polynomial obj)
{
    return obj.current.size();
}

term polynomial::operator[](int number)
{
    return current[number - 1];
}

term polynomial::operator[](int number) const
{
    return current[number - 1];
}

polynomial polynomial::processing(string Entrance)
{
    int i = 0;
    vector<term> vec;
    string temp4 = "";
    for (; i < Entrance.size();)
    {
        string temp = "";
        term temp1("0x^0");
        do
        {
            temp = temp + Entrance[i];
            ++i;
        } while (Entrance[i] != '+' && Entrance[i] != '-' && i < Entrance.size());

        if (temp[0] == '-')
        {
            for (int i = 0; i < temp.size() - 1; i++)
            {
                temp4 += temp[i + 1];
            }
            temp1.coefficient = term::Separation(temp4).first * -1;
            temp1.power = term::Separation(temp4).second;
            vec.push_back(temp1);
        }
        else
        {
            if (temp[0] == '+')
            {
                for (int i = 0; i < temp.size() - 1; i++)
                {
                    temp4 += temp[i + 1];
                }
                temp1.coefficient = term::Separation(temp4).first;
                temp1.power = term::Separation(temp4).second;
                vec.push_back(temp1);
            }
            else
            {
                temp1.coefficient = term::Separation(temp).first;
                temp1.power = term::Separation(temp).second;
                vec.push_back(temp1);
            }
        }
        temp4 = "";
    }
    return vec;
}

float polynomial::operator()(float value)
{
    float temp = 0;
    float num[current.size()];
    for (int i = 0; i < current.size(); i++)
    {
        num[i] = current[i](value);
    }
    for (int k = 0; k < current.size(); k++)
    {
        temp += num[k];
    }
    return temp;
}

ostream &operator<<(ostream &out, polynomial &obj)
{
    if (obj.current.size() == 0)
    {
        cout << "0";
        return out;
    }

    for (int i = 0; i < obj.current.size(); i++)
    {
        if (obj.current[i].get_f() == 0)
        {
            int ss = 0;
            out << ss << " ";
            continue;
        }

        cout.setf(ios::showpos);
        if (obj.current[i].get_i() == 0)
        {
            out << obj.current[i].get_f() << " ";
            continue;
        }
        out << obj.current[i].get_f() << "x^" << obj.current[i].get_i() << " ";
    }
    cout.unsetf(ios::showpos);
    return out;
}

void princple();
void princple_2();
void princple_3();
void menu_princple();
void Select(int);
void menu_poly();
void Select_poly(int, polynomial &);
void print_polynomial(polynomial);

enum menu
{
    New_Polynomial = 1,
    Load_From_Text_File,
    Load_From_Binary_File,
    Quit
};

enum menu_poly
{
    add = 1,
    subtract,
    multiply,
    derivative,
    find_degree,
    find_value,
    compare,
    save_text,
    save_bin,
    back,
    equaly
};

int main()
{

    int choice;
    do
    {
        menu_princple();
        cin >> choice;
        system("cls");
        Select(choice);
    } while (choice != Quit);

    return 0;
}

void menu_princple()
{
    system("cls");
    cout << '\t' << '\t' << "IN THE NAME OF ALLAH" << '\n'
         << '\n';
    cout << "Main Menu" << '\n'
         << '\n';
    cout << "  1- New Polynomial" << '\n';
    cout << "  2- Load From Text File" << '\n';
    cout << "  3- Load From Binary File" << '\n';
    cout << "  4- Quit" << '\n'
         << '\n';
    cout << "Your Choose: ";
}

void Select(int choose)
{
    switch (choose)
    {
    case New_Polynomial:
        princple();
        break;

    case Load_From_Text_File:
        princple_2();
        break;

    case Load_From_Binary_File:
        princple_3();
        break;

    case Quit:
        break;
    default:
        int a = 0;
        try
        {
            if (a == 0)
            {
                throw error("Input number is invalid. try again");
            }
        }
        catch (error e)
        {
            e.print();
            getch();
            return;
        }
    }
    return;
}

void Select_poly(int choose, polynomial &object)
{
    switch (choose)
    {
    case add:
        fun_add(object);
        break;

    case subtract:
        fun_subtract(object);
        break;

    case multiply:
        fun_multiply(object);
        break;

    case derivative:
        fun_derivative(object);
        break;

    case find_degree:
        fun__find_degree(object);
        break;

    case find_value:
        fun_Find_Value_for_specific_x(object);
        break;

    case compare:
        comparee(object);
        break;

    case save_text:
        write_in_file_txt(object);
        break;

    case save_bin:
        write_in_file_bin(object);
        break;

    case back:

        break;
    case equaly:
        object.fun_equel(object);
        break;
    default:
        break;
    }
    try
    {
        if (choose <= 0 || choose > 11)
        {
            throw error("Input number is invalid.\nPlease select again.");
        }
    }
    catch (error e)
    {
        e.print();
        getch();
        return;
    }
    return;
}

void princple()
{
    polynomial object1;
    int choice;
    do
    {
        system("cls");
        cout << "   Polynomial Menu" << '\n'
             << '\n';
        cout << "Current Polynomial = ";
        if (object1.find_number(object1) != 1)
        {
            polynomial::check_power(object1);
        }
        print_polynomial(object1);
        cout << '\n'
             << '\n';
        menu_poly();
        cin >> choice;
        Select_poly(choice, object1);
    } while (choice != back);
}

void menu_poly()
{
    cout << "1- Add" << '\n';
    cout << "2- Subtract" << '\n';
    cout << "3- Multiply" << '\n';
    cout << "4- Derivative" << '\n';
    cout << "5- Find Degree" << '\n';
    cout << "6- Find Value for specific x" << '\n';
    cout << "7- Compare" << '\n';
    cout << "8- Save to a text file" << '\n';
    cout << "9- Save to a binary file" << '\n';
    cout << "10- Back to Main Menu" << '\n';
    cout << "11- Equal " << '\n';
    cout << '\n'
         << '\n'
         << "Your Choose: ";
}

void print_polynomial(polynomial obj)
{
    cout << obj;
}

void fun_add(polynomial &obj1)
{
    string temp;
    cout << "Enter the desired polynomial. " << '\n';
    cout << "polynomial: ";
    cin >> temp;
    polynomial obj2(polynomial::processing(temp).current);
    // obj1 += obj2;
    obj1 = obj1 + obj2;
}

void fun_subtract(polynomial &obj1)
{
    string temp;
    cout << "Enter the desired polynomial. " << '\n';
    cout << "polynomial: ";
    cin >> temp;
    polynomial obj2(polynomial::processing(temp).current);
    // obj1 -= obj2;
    obj1 = obj1 - obj2;
}

void fun_multiply(polynomial &obj1)
{
    string temp;
    cout << "Enter the desired polynomial. " << '\n';
    cout << "polynomial: ";
    cin >> temp;
    polynomial obj2(polynomial::processing(temp).current);
    // obj1 = obj1 * obj2;
    obj1 *= obj2;
}

void fun_derivative(polynomial obj1)
{
    obj1 = ~obj1;
    cout << "result: " << obj1 << '\n';
    getch();
}

void fun__find_degree(polynomial obj1)
{
    int size = obj1.current.size();
    cout << "Polynomial degree: " << obj1.current[size - 1].get_i() << '\n';
    getch();
}

void fun_Find_Value_for_specific_x(polynomial obj1)
{
    float value;
    float temp;
    cout << "Enter a value for x: ";
    cin >> value;
    temp = obj1(value);
    cout << "The desired result: " << temp << '\n';
    getch();
}

void comparee(polynomial obj1)
{
    bool temp1 = false;
    bool temp2 = false;
    bool temp3 = false;
    bool temp4 = false;
    bool temp5 = false;
    bool temp6 = false;
    string temp;
    cout << "Enter the desired polynomial. " << '\n';
    cout << "other polynomial: ";
    cin >> temp;
    polynomial obj2(polynomial::processing(temp).current);
    cout << "Current polynomial: ";
    print_polynomial(obj1);
    cout << '\n';
    cout << "Other Polynomial: ";
    print_polynomial(obj2);
    cout << '\n'
         << '\n';
    cout << "Comparing Current Polynomial with Other Polynomial. " << '\n'
         << '\n';
    cout.setf(ios::boolalpha);
    cout << "Current Polynomial > Other Polynomial:";
    temp1 = obj1 > obj2;
    cout << temp1 << '\n';
    cout << "Current Polynomial >= Other Polynomial:";
    temp2 = obj1 >= obj2;
    cout << temp2 << '\n';
    cout << "Current Polynomial < Other Polynomial:";
    temp3 = obj1 < obj2;
    cout << temp3 << '\n';
    cout << "Current Polynomial <= Other Polynomial:";
    temp4 = obj1 <= obj2;
    cout << temp4 << '\n';
    cout << "Current Polynomial == Other Polynomial:";
    temp5 = obj1 == obj2;
    cout << temp5 << '\n';
    cout << "Current Polynomial != Other Polynomial:";
    temp6 = obj1 != obj2;
    cout << temp6 << '\n';
    getch();
    cout.unsetf(ios::boolalpha);
}

void princple_2()
{
    polynomial obj;
    int choice;
    polynomial::read_of_file_txt(obj);
    do
    {
        system("cls");
        cout << "   Polynomial Menu" << '\n'
             << '\n';
        cout << "Current Polynomial = ";
        if (obj.find_number(obj) != 1)
        {
            polynomial::check_power(obj);
        }
        print_polynomial(obj);
        cout << '\n'
             << '\n';
        menu_poly();
        cout << '\n';
        cout << "size: " << obj.find_number(obj) << '\n';
        cin >> choice;
        Select_poly(choice, obj);
    } while (choice != back);
}

void princple_3()
{
    polynomial obj;
    int choice;
    polynomial::read_of_file_bin(obj);
    do
    {
        system("cls");
        cout << "   Polynomial Menu" << '\n'
             << '\n';
        cout << "Current Polynomial = ";
        if (obj.find_number(obj) != 1)
        {
            polynomial::check_power(obj);
        }
        print_polynomial(obj);
        cout << '\n'
             << '\n';
        menu_poly();
        cout << '\n';
        cout << "size: " << obj.find_number(obj) << '\n';
        cin >> choice;
        Select_poly(choice, obj);
    } while (choice != back);
}
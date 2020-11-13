#include <iostream>
#include<vector>
#include<math.h>
using namespace std;

// Коэффициенты в системе
const double a1 = -500.005;
const double a2 = 499.995;

//Первая компанента функции f
double f1(vector<double> u)
{
    return a1 * u[0] + a2 * u[1];
}

//Вторая компанента функции f
double f2(vector<double> u)
{
    return a2 * u[0] + a1 * u[1];
}

//  Two - stage implicit method 
vector<double> TSI_RK_3(vector<double> _current, double h)
{
    //  0 - x , 1 - u1, 2 - u2
    vector<double> next(3);
   
    // Вычислим Xn+1
    next[0] = _current[0] + h;

    //  Вычислим необходимые коэффициенты
    vector<double> koef1(2);
    //  Для красоты введем коэффициент
    double c1 = (3 + sqrt(3)) / 6;
    koef1[0] = (a1 * (_current[0] + c1 * h) + a2 * _current[1]) / (1 - a2 * c1 * h);
    koef1[1] = (a2 * (_current[0] + c1 * h) + a1 * _current[2]) / (1 - a1 * c1 * h);

    vector<double> koef2(2);
    //  Для красоты введем коэффициент
    double c2 = (3 - sqrt(3)) / 6;
    double c3 = (-sqrt(3)) / 3;
    koef2[0] = (a1 * (_current[0] + c2 * h) + a2 * (_current[1] + h * c3 * koef1[0])) / (1 - a2 * h * c1);
    koef2[0] = (a2 * (_current[0] + c2 * h) + a1 * (_current[2] + h * c3 * koef1[1])) / (1 - a1 * h * c1);

    // Вычислим Un+1
    next[1] = _current[1] + (h/2) * (koef1[0] + koef2[0]);
    next[2] = _current[2] + (h/2) * (koef1[1] + koef2[1]);
    return next;

}


int main()
{
    //  ну
    //  X0=0, U01=7, U02=13
    //  initialization
    vector<double> current = { 0, 7, 13 };
    
    double h;
    cout << "h" << endl;
    cin >> h;

    double n;
    cout << "n" << endl;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << i << "  x =  " << current[0] << "  u1 =  " << current[1] << "  u2 =  " << current[2] << endl;
        current = TSI_RK_3(current, h);
    }

    return 0;
}



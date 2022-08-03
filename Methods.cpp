#include <iostream>
#include <cmath>
int counter=0;
int counter_f = 0;
int counter_f_1 = 0;
int counter_gld=0;
int counter_pok = 0;
using namespace std;

double F(double x) 
{
    counter_f++;
    return pow((4-x),3)/(9*(2-x));
}
double F(double x1, double x2) {
    return (2 * pow(x1, 2) + 4 * x1 * x2 + 8 * pow(x2, 2) + 100);
}
void perebor(double a, double b, double e)
{
    cout << "1:" << endl;
    double x = a;
    int n = int(abs(a - b) / e); 
    double h = abs(b - a) / n;
    double min = a;
    for (int i = 1; i <= n; i++)
    {
        x +=h;
        if (F(min) > F(x)) 
            min = x;
        counter++;
  
    }
    cout <<"Min value = "<< min<< "; \t Function value = " << F(min) << endl;
    cout << "counter = " << counter<<"\t counter_f="<< counter_f << endl<<endl;
}

void porasryadn(double a, double b, double e)
{
    counter = 0;
    counter_f = 0;
    cout << "2:" << endl;
    double h = abs(b - a) / 4;
    int count = 3;
    double x = a;
    double y_old, y_new;
    y_old = F(a);
    y_new = F(a + h);
    int i = 0;
    while (abs(h) > e)
    {
        i = 0;
        while ((i < count) and (y_old > y_new))
        {
            x += h;
            y_old = y_new;
            y_new = F(x + h);
            i++;
        }
            if ((abs(h) > e) and (i != 0))
                x += h;

            if (i != 0)
            {
                y_old = y_new;
                h *= -1;
            }
            count *= 4;
            h /= 4;
            y_new = F(x + h);
            counter++;
    }
    cout << "min x=" << x << "\t" << "F(min x) = " << F(x) << endl;
    cout << "counter = " << counter << "\t counter_f=" << counter_f << endl<<endl;
}

void dihotomi(double a, double b, double e) {
    double del = 0.01;
    counter = 0;
    counter_f = 0;
    double x1, x2, e_current=1;
    cout << "3:" << endl;
    while (e_current > e)
    {
        
        x1 = (a + b - del) / 2;
        x2 = (a + b + del) / 2;
        if (F(x1) <= F(x2))
            b = x2;
        else
            a = x1;
        e_current = abs(b-a)/2;
       
        counter++;
 
    }
    cout << "Итог:  x = "<<(b+a)/2<<"\t F(x) = " <<F((b+a)/2)<<endl ;
    cout << "counter = " << counter << "\t counter_f=" << counter_f << endl<<endl;
}

void Golden(double a, double b, double e) {
    counter = 0;
    counter_f = 0;
    cout << "4:" << endl;
    double t = (sqrt(5) - 1) / 2;
    double x_left = a + (1 - t) * (b - a), x_right = a + t * (b - a);
    double e_current = abs(b - a) / 2;
    double y_left = F(x_left), y_right = F(x_right);
    while (e_current > e) {
        if (y_left<=y_right)
        {
            b = x_right;
            x_right = x_left;
            y_right = y_left;
            x_left = b - t * (b - a);
            y_left = F(x_left);
        }
        else
        {
            a = x_left;
            x_left = x_right;
            y_left = y_right;
            x_right = a + t * (b - a);
            y_right = F(x_right);
        }
        e_current *= t;
        counter++;
    }
}


double F_1_por(double x) {
    counter_f_1++;
    return (pow((4 - x), 3)-3*(2-x)*pow((4-x),2)) / (9 * pow((2 - x),2));
}
double F_2_por(double x) {
    return (2 * pow(x, 3) - 12*pow(x,2)+24*x-32) / (9*pow(x,3)-54*pow(x,2)+108*x-72);
}

void MidPoint(double a, double b, double e) {
    double x;
    int counter = 0;
    int i=0;
    do {
        x = (a + b) / 2;
        i++;
        cout << "i = " << i << "\t a=" << a << " b=" << b << " x=" << x << "\t F1 =" << F_1_por(x) << endl;
        if (abs(F_1_por(x)) < e) {
            break;
        }
        if (F_1_por(x) < 0) {
            a = x;
        }
        else {
            b = x;
        }
    }while(true);
    cout << "x = " << x << "\t Fx =" << F(x) << endl;;
    cout << "f(x) = " << counter_f << "\t counter_f_1 = " << counter_f_1 << endl;
}
void Hord(double a, double b, double e) {
    double x=1, Fx = 1;
    int i = 0;
    int counter = 0;
    double F_a= F_1_por(a), F_b= F_1_por(b);
    do {
        x = a - (F_a / (F_a - F_b)) * (a - b);
        i++;
        cout << "i = " << i << "\t a=" << a << " b=" << b << " x=" << x << "\t F1 =" << F_1_por(x) << endl;
        if (abs(F_1_por(x)) <= e) {
            break;
        }
        if (F_1_por(x) < 0) {
            a = x;
            F_a = F_1_por(x);
        }
        else {
            b = x;
            F_b = F_1_por(x);
        }
    } while (true);
    cout << "x = " << x << "\t Fx =" << F(x) << endl;
    cout << "f(x) = " << counter_f << "\t counter_f_1 = " << counter_f_1 << endl;
}
void Nyton(double a, double b, double e) {
    double x = (a + b) / 2;
    int counter = 0;
    int i = 0;
    do {
        i++;
        if ((abs(F_1_por(x)) > e) and F_2_por(x)>0) {
            cout <<"x = "<< x << "\t F(x) = " << F(x) << "\t F_1_por(x) = " << F_1_por(x) << "\t F_2_por(x) = "<<F_2_por(x)<< endl;
            x =x - (F_1_por(x) / F_2_por(x));
        }
        else {
            break;
        }
    } while (abs(F_1_por(x)) >= e);
    cout <<"Resault: x = "<< x << "\t F(x) = " << F(x) << endl;
    cout << "f(x) = " << counter_f << "\t counter_f_1 = " << counter_f_1 << endl;
}

double Step(double x1, double x2, double h, int check) {
    switch (check)
    {
    case 1:
        return (2 * pow(x1 + h, 2) + 4 * (x1 + h) * x2 + 8 * pow(x2, 2) + 100);
        break;
    case 2:
        return (2 * pow(x1, 2) + 4 * x1 * (x2 + h) + 8 * pow(x2 + h, 2) + 100);
        break;
    default:
        cout << "ERROR" << endl;
        break;
    }
}
double Golden_5(double a, double b, double x, double y, double e, int check) {
    double t = (sqrt(5) - 1) / 2;
    double x_left = a + (1 - t) * (b - a), x_right = a + t * (b - a);
    double e_current = abs(b - a) / 2;
    double y_left = Step(x, y, x_left, check), y_right = Step(x, y, x_right, check);
    while (e_current > e) {
        if (y_left <= y_right)
        {
            b = x_right;
            x_right = x_left;
            y_right = y_left;
            x_left = b - t * (b - a);
            y_left = Step(x, y, x_left, check);
        }
        else
        {
            a = x_left;
            x_left = x_right;
            y_left = y_right;
            x_right = a + t * (b - a);
            y_right = Step(x, y, x_right, check);
        }
        e_current *= t;
        counter_gld++;
    }
        return (a + b) / 2;
}
void Pokoord(double x, double y, double e) {
    double f = 0;
    double h = 0;
    do {
        f = F(x, y);
        h = Golden_5(-2, 3, x, y, e, 1);
        cout << "h for x = " << h << endl;
        x += h;
        h = Golden_5(-2, 3, x, y, e, 2);
        cout << "h for y = " << h << endl;
        y += h;
        cout << x << "\t" << y << endl;
        counter_pok++;
    } while (abs(f - F(x, y)) > e);
    cout << x << "\t" << y <<"\t F(x,y) ="<< F(x, y) << endl;
    cout << "counter_gld = " << counter_gld << "\t counter_pok = " << counter_pok << endl;
}

double Grad_1(double x1, double x2) {
    return 4 * (x1 + x2);
}

double Grad_2(double x1, double x2) {
    return 4 * (x1 + 4 * x2);
}

double Step_dop( double x1, double x2, double h, double grad_x1, double grad_x2) {
    return (2 * pow((x1-h*grad_x1), 2) + 4 * (x1-h*grad_x1) * (x2-h*grad_x2) + 8 * pow(x2-h*grad_x2, 2) + 100);
}
double Golden_6(double a, double b, double x, double y,double grad_x1,double grad_x2, double e) {
    double t = (sqrt(5) - 1) / 2;
    double x_left = a + (1 - t) * (b - a), x_right = a + t * (b - a);
    double e_current = abs(b - a) / 2;
    double y_left = Step_dop(x, y, x_left, grad_x1, grad_x2);
    double y_right = Step_dop(x, y, x_right,grad_x1,grad_x2);
    while (e_current > e) {
        if (y_left <= y_right)
        {
            b = x_right;
            x_right = x_left;
            y_right = y_left;
            x_left = b - t * (b - a);
            y_left = Step_dop(x, y, x_left, grad_x1, grad_x2);
        }
        else
        {
            a = x_left;
            x_left = x_right;
            y_left = y_right;
            x_right = a + t * (b - a);
            y_right = Step_dop(x, y, x_right, grad_x1, grad_x2);
        }
        e_current *= t;
        counter_gld++;
    }
    return (a + b) / 2;
}

void Quick(double x1, double x2, double e) {
    double grad_x1=0, grad_x2=0;
    double y1 = 0, y2 = 0;
    double h;
    do {
        grad_x1 = Grad_1(x1, x2);
        grad_x2 = Grad_2(x1,x2);
        y1 = F(x1, x2);
        h = Golden_6(-3, 1, x1, x2, grad_x1, grad_x2,e);
        x1 -= grad_x1 * h;
        x2 -= grad_x2 * h;
        
        y2 = F(x1, x2);
        cout << "grad_x1 = " << x1 << " ; \t grad_x1= " << x2 << endl;
        counter_pok++;
    } while (abs(y2-y1)>e);
    cout << "F = "<< F(x1, x2)<<"\t x1=" <<x1 <<" x2=" <<x2<< endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double a = 2;
    double b =-1;
    double e = 0.01;
    Quick(a,b,e);
}


double Fstep(double h, double x, double y, bool stepForX)
{
    if (stepForX)
    {
        double result = (2 * pow(x + h, 2) + 4 * (x + h) * y + 8 * pow(y, 2) + 100);
        return result;
    }
    else
    {
        double result = (2 * pow(x, 2) + 4 * x * (y + h) + 8 * pow(y + h, 2) + 100);
        return result;
    }
}
double GldRatioMethod(double a, double b, double x, double y, bool stepForX, double e = 0.001)
{
    int counter_gld = 0;
    double t = (sqrt(5) - 1) / 2;
    double E = e, x1 = a + (1 - t) * (b - a), x2 = a + t * (b - a), En = abs(b - a) / 2;
    double y1 = Fstep(x1, x, y, stepForX), y2 = Fstep(x2, x, y, stepForX);
    while (En > E)
    {
        if (y1 <= y2)
        {
            b = x2; 
            x2 = x1; 
            y2 = y1; 
            x1 = b - t * (b - a); 
            y1 = Fstep(x1, x, y, stepForX);
        }
        else
        {
            a = x1; x1 = x2; y1 = y2; x2 = a + t * (b - a); y2 = Fstep(x2, x, y, stepForX);
        }
        En *= t;
        counter_gld++;
    }
    cout << " counter_gld = " << counter_gld << "\t";
    double step = (a + b) / 2;
    cout << " step = " << step << endl;
    return step;
}
 void Coordinate_Descent_Method(double x1_Init, double x2_Init, double e = 0.001)
{
    double f0, f1 = F(x1_Init, x2_Init);
    double x = x1_Init, y = x2_Init;
    double h;
    int it_count = 0;
    do
    {
        f0 = f1;
        h = GldRatioMethod(-1, 1.5, x, y, true, 0.0001);
 
        x = x + h;
        h = GldRatioMethod(-1, 1.5, x - h, y, false, 0.0001);

        y = y + h;
        f1 = F(x, y);
        it_count++;
        cout << " \t\t x = " << x << "\t y = " << y << endl;
    } while (abs(f0 - f1) > e);
    cout << x << " " << y <<"\t f(x,y) = "<< F(x,y) << endl;
}


#include <iostream>
#include <cmath>
#include <iomanip>  // Для форматированного вывода
#include <limits> // Для numeric_limits
#include <locale> // Для setlocale

using namespace std;

// Пример вычисления суммы
double sum_numbers_bad(double arr[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

double sum_numbers_good(double arr[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}


// Пример вычисления производной (с ошибкой усечения)
double derivative_bad(double f(double), double x, double h) {
    return (f(x + h) - f(x)) / h;
}

// Улучшенный метод центральной разности
double derivative_good(double f(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}


// Пример решения квадратного уравнения (с избеганием вычитания близких чисел)
pair<double, double> solve_quadratic(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return make_pair(numeric_limits<double>::quiet_NaN(), numeric_limits<double>::quiet_NaN()); // нет корней
    }
    double sqrt_discriminant = sqrt(discriminant);

    double root1 = (-b - sqrt_discriminant) / (2 * a);
    double root2 = (-b + sqrt_discriminant) / (2 * a);

    // Если b > 0, меняем вычисление root1, чтобы избежать вычитания близких чисел
    if (b > 0)
    {
        root1 = (-2 * c) / (b + sqrt_discriminant);
    }
    else {
        root2 = (-2 * c) / (b - sqrt_discriminant);
    }
    return make_pair(root1, root2);
}



double example_func(double x) {
    return x * x;
}



int main() {
    setlocale(LC_ALL, "Ru");

    // Пример ошибки округления
    double small_numbers[] = { 1e-10, 1e-9, 1e-8, 1e-7, 1e-6, 1e-5 };

    double result1 = sum_numbers_bad(small_numbers, 6);
    double result2 = sum_numbers_good(small_numbers, 6);
    double actual_sum = 1e-10 + 1e-9 + 1e-8 + 1e-7 + 1e-6 + 1e-5;
    cout << fixed << setprecision(15);

    cout << "Сумма с ошибками: " << result1 << " Истинная сумма: " << actual_sum << endl;
    cout << "Сумма без ошибок: " << result2 << " Истинная сумма: " << actual_sum << endl;



    // Пример ошибки усечения (производная)
    double x_deriv = 2.0;
    double h_deriv_bad = 0.1;
    double h_deriv_good = 0.01;

    double deriv_bad_result = derivative_bad(example_func, x_deriv, h_deriv_bad);
    double deriv_good_result = derivative_good(example_func, x_deriv, h_deriv_good);
    double actual_deriv = 2 * x_deriv;

    cout << "Производная с ошибкой усечения: " << deriv_bad_result << "  Истинная производная: " << actual_deriv << endl;
    cout << "Производная с улучшенным методом: " << deriv_good_result << "  Истинная производная: " << actual_deriv << endl;

    // Пример решения квадратного уравнения
    double a = 1.0;
    double b = -10000000.0;
    double c = 1.0;

    pair<double, double> roots = solve_quadratic(a, b, c);

    cout << "Квадратное уравнение: " << a << "*x^2 + " << b << "*x + " << c << " = 0" << endl;
    cout << "Корень 1: " << roots.first << endl;
    cout << "Корень 2: " << roots.second << endl;

    return 0;
}
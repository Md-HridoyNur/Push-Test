#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

double f(const vector<double>& coeffs, double x) {
    int n = coeffs.size() - 1;
    double result = 0.0;
    for (int i = 0; i <= n; i++) {
        result += coeffs[i] * pow(x, n - i);
    }
    return result;
}

double df(const vector<double>& coeffs, double x) {
    int n = coeffs.size() - 1;
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += (n - i) * coeffs[i] * pow(x, n - i - 1);
    }
    return result;
}

void newtonRaphson(const vector<double>& coeffs, double x0, double tolerance, int maxIterations) {
    double x1, fx, dfx, relativeError;
    int iteration = 0;
    bool converged = false;

    cout << "\nIteration Table:\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    cout << "Iter |       x0       |       f(x0)     |      f'(x0)     |       x1       | Relative Error\n";
    cout << "-----------------------------------------------------------------------------------------\n";

    do {
        fx = f(coeffs, x0);
        dfx = df(coeffs, x0);

        if (fabs(dfx) < 1e-12) {
            cout << "Error: Derivative became zero. Method cannot continue.\n";
            return;
        }

        x1 = x0 - fx / dfx;

        if (iteration == 0) {
            relativeError = 100.0;
        } else {
            relativeError = fabs((x1 - x0) / x1) * 100;
        }

        cout << setw(4) << right << iteration + 1 << " | "
             << setw(13) << fixed << setprecision(6) << x0 << " | "
             << setw(14) << fx << " | "
             << setw(14) << dfx << " | "
             << setw(13) << x1 << " | "
             << setw(13) << relativeError << " %"
             << endl;

        if (fabs(fx) < tolerance || relativeError < tolerance) {
            converged = true;
            break;
        }

        x0 = x1;
        iteration++;
    } while (iteration < maxIterations);

    cout << "-----------------------------------------------------------------------------------------\n";

    if (converged)
        cout << "Root found: " << fixed << setprecision(6) << x1 << " after " << iteration + 1 << " iterations.\n";
    else
        cout << "Method did not converge within max iterations.\n";
}

int main() {
    int degree;
    cout << "=== NEWTON RAPHSON METHOD (General Polynomial) ===\n\n";

    cout << "Enter degree of polynomial: ";
    cin >> degree;

    vector<double> coeffs(degree + 1);
    cout << "Enter coefficients one by one (highest degree first):\n";
    for (int i = degree; i >= 0; i--) {
        cout << "a" << i << " = ";
        cin >> coeffs[degree - i];
    }

    double x0, tolerance;
    int maxIterations;

    cout << "\nEnter initial guess (x0): ";
    cin >> x0;
    cout << "Enter tolerance (e.g., 0.0001): ";
    cin >> tolerance;
    cout << "Enter maximum number of iterations: ";
    cin >> maxIterations;

    newtonRaphson(coeffs, x0, tolerance, maxIterations);

    return 0;
}


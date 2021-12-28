#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>




using namespace std;

double Distance(double x, double y, double X, double Y) {
    double d = fabs((y * Y - x * X) / sqrt(x * x + y * y));


    return d;

}

void ReadAll(const string& path) {
    double XR_MAX = 0, XL_MAX = 0, YR_MAX = 0, YL_MAX = 0;
    double DISTL = 0, DISTR = 0;
    double d = 0;
    double x = 0, y = 0, xV, yV;
    ifstream file(path);
    if (file.is_open()) {
        string str;
        int n = 0;
        while (!file.eof()) {

            //read vector
            if (n == 0) {
                file >> str;
                xV = stoi(str);
                file >> str;
                yV = stoi(str);
                n++;
            }
            str = "";
            file >> str;
            if (str == "") break;
            //read x or y
            x = stoi(str);
            file >> str;
            y = stoi(str);

            if (xV > 0) {

                if ((yV * x - xV * y < 0)) {
                    d = fabs((yV * x - xV * y) / sqrt(xV * xV + yV * yV));
                    if (d >= DISTL)
                    {
                        DISTL = d;
                        XL_MAX = x;
                        YL_MAX = y;
                    }
                }
                else {
                    d = fabs((yV * x - xV * y) / sqrt(xV * xV + yV * yV));
                    if (d >= DISTR)
                    {
                        DISTR = d;
                        XR_MAX = x;
                        YR_MAX = y;
                    }

                }


            }
            else {
                if (yV * x - xV * y < 0) {
                    d = fabs((yV * x - xV * y) / sqrt(xV * xV + yV * yV));
                    if (d >= DISTL)
                    {
                        DISTL = d;
                        XL_MAX = x;
                        YL_MAX = y;
                    }
                }
                else {
                    d = fabs((yV * x - xV * y) / sqrt(xV * xV + yV * yV));
                    if (d >= DISTR)
                    {
                        DISTR = d;
                        XR_MAX = x;
                        YR_MAX = y;
                    }
                }
            }
        }
    }
    file.close();

    cout << "Leftmost:" << ' ' << XL_MAX << ' ' << YL_MAX << endl;
    cout << "Rightmost:" << ' ' << XR_MAX << ' ' << YR_MAX << endl;
}


int main() {
    const string path = "in.txt";

    ReadAll("in.txt");
    return 0;
}
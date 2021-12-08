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
    float DISTL = NAN+1, DISTR = NAN+1;
    float d=0;
    double x=0,y=0,xV,yV,xr0=0, xl0=0, yr0=0, yl0=0;
    bool ch = false;
    ifstream file(path);
    if (file.is_open()) {
        string str;
        int n = 0;
        while (!file.eof()) {

            //read vector
            if (n ==0) {
                file >> str;
                xV = stoi(str);
                file >> str;
                yV = stoi(str);
            }

            file >> str;



            //read x or y
            x = stoi(str);
            file >> str;
            y = stoi(str);


            //pair exist



            double k = yV / xV;

            double check = y - k * x;
            double check2 = k * x - y;


            d = Distance(xV, yV, x, y);
            double a = yV * yV / (xV * xV) + 1;
            double b = fabs(yV / xV * x - y);
            if (xV > 0) {
                if ((check2 > 0) || (check2 == 0)) {
                    xl0 = x;
                    yl0 = y;
                    if (d == max(d, DISTR))
                    {
                        DISTR = d;
                        XL_MAX = x;
                        YL_MAX = y;
                    }
                }
                else {
                    xr0 = x;
                    yr0 = y;
                    if (d == max(d, DISTL))
                    {
                        DISTL = d;
                        XR_MAX = x;
                        YR_MAX = y;
                    }


                }

            }
            else {
                if ((check > 0)) {
                    xl0 = x;
                    yl0 = y;
                    if (d == max(d, DISTR))
                    {
                        DISTR = d;
                        XL_MAX = xl0;
                        YL_MAX = yl0;
                    }
                }
                else {
                    xr0 = x;
                    yr0 = y;
                    if (d == max( d, DISTL))
                    {
                        DISTL = d;
                        XR_MAX = x;
                        YR_MAX = y;
                    }

                }
            }




            //Dist:






            n++;
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
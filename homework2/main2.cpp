#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

const double G = 9.81;

vector<double> point_X;
vector<double> point_Y;
double height;
double speed_x, speed_y;
int check1 = 1, check2 = 0;

void ReadFile(char* path)
{
    double x=0, y;
    std::ifstream in(path);
    if (in.is_open())
    {
        in >> height >> speed_x >> speed_y;
        point_X.push_back(0);
        point_Y.push_back(height);
        while (!in.eof() && check1 <= speed_x * (speed_y + sqrt(speed_y * speed_y + 2 * G * height)) / G)
        {


            in >> x >> y;
            if (x == atoi("") || y == atoi("")) return;

            point_X.push_back(x);
            point_Y.push_back(y);
        }
    }
}

void FlyPoint(char ch) {
    if (ch == 'R')
        height = -G * (point_X[check2 + 1] - point_X[check1 - 1]) * (point_X[check2 + 1] - point_X[check1 - 1]) / 2 / speed_x / speed_x + (speed_y - G * point_X[check1 - 1] / speed_x) * (point_X[check2 + 1] - point_X[check1 - 1]) / speed_x + height;
    else
        height = -G * (point_X[check1] - point_X[check2 + 1]) * (point_X[check1] - point_X[check2 + 1]) / 2 / speed_x / speed_x - (speed_y - G * point_X[check2 + 1] / speed_x) * (point_X[check1] - point_X[check2 + 1]) / speed_x + height;

}





void Check(char ch) {
    if (ch == 'R') {
        for (int i = check1; i <= point_X.size()-1; ++i) {
            double length = -G * (point_X[i] - point_X[check1 - 1]) * (point_X[i] - point_X[check1 - 1]) / 2 / speed_x / speed_x + (speed_y - G * point_X[check1 - 1] / speed_x) * (point_X[i] - point_X[check1 - 1]) / speed_x + height;
            if (length < point_Y[i]) {
                check2 = i - 1;
                return;
            }
            check2 = i;
        }
    }
    else
    {
        for (int i = 0; i <= check2; ++i) {
            double length = -G * (point_X[check2 - i] - point_X[check2 + 1]) * (point_X[check2 - i] - point_X[check2 + 1]) / 2 / speed_x / speed_x - (speed_y - G * point_X[check2 + 1] / speed_x) * (point_X[check2 - i] - point_X[check2 + 1]) / speed_x + height;

            if (length < point_Y[check2 - i]) {
                check1 = check2 - i;
                return;
            }
            else if (check2 - i == 0) {
                check1 = check2 - i;
                return;
            }
            check1 = check2 - i;
        }
    }
}

void Start() {
    while (height >= 0) {
        if (check1 == check2) {
            cout << check2 << endl;
            return;
        }

        Check('R');
        if (check2 == point_X.size()-1) {
            cout << check2 << endl;
            return;
        }

        FlyPoint('R');
        if (height < 0) {
            cout << int(check2) << endl;
            return;
        }

        Check('L');
        if (check1 == 0) {
            cout << check1 << endl;
            return;
        }

        FlyPoint('L');
        if (height < 0) {
            cout << check1 << endl;
            return;
        }


    }
}



int main(int argc, char** argv)
{
    if (argc == 2) {

        ReadFile(argv[1]);

        if (speed_x == 0 || point_X.size() == 0) {
            cout << 0;
            return 0;
        }
        Start();
        return 0;
    }
    else return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;


vector <string> ReadAll(const string& path) {
    vector<string> points;
    ifstream file(path);
    if (file.is_open()) {
        string str;
        while (!file.eof()) {
            file >> str;
            points.push_back(str);
        }
        points.push_back(str);   //...
        points.pop_back();
    }
    file.close();
    return points;
}


void PrintVector(const vector<double>& v) {
    for (auto i : v) {
        cout << i << ' ';
    }
    cout << endl;
}

void PrintVecStr(const vector<string>& v) {
    for (auto i : v) {
        cout << i << ' ';
    }
}

vector<double> ChangeToDoubleX(vector<string>& vec) {
    vector<double> X;

    int n = vec.size();
    for (int i = 0; i < n; i++) {
        if ((i % 2) == 0) {
            X.push_back(stoi(vec[i]));
        }


    }
    return X;
}
vector<double> ChangeToDoubleY(vector<string>& vec) {
    vector<double> Y;

    int n = vec.size();
    for (int i = 0; i < n + 1; i++) {
        if ((i % 2) != 0) {
            Y.push_back(stoi(vec[i]));
        }


    }
    return Y;
}
vector<double> CheckSide(vector<double>& x, vector<double>& y, string coordType, string side) {
    vector<double> Xr;
    vector<double> Yr;
    vector<double> Xl;
    vector<double> Yl;
    double k = y[0] / x[0];
    for (int i = 1; i < x.size(); i++) {
        double check = y[i] - k * x[i];
        if ((check == 0) | (check > 0)) {
            Xl.push_back(x[i]);
            Yl.push_back(y[i]);
        }
        else {
            Xr.push_back(x[i]);
            Yr.push_back(y[i]);
        }

    }
    if (coordType == "X") {
        if (side == "Right") {
            return Xr;
        }
        else if (side == "Left") {
            return Xl;
        }
    }
    else {
        if (side == "Right") {
            return Yr;
        }
        else if (side == "Left") {
            return Yl;
        }
    }
}

vector<double> Distance(double x, double y, vector<double>& X, vector<double>& Y, string type) {
    vector<double>  xn;
    vector<double> yn;
    vector<double> distance;
    double ynew;
    double xnew;
    for (int i = 0; i < X.size(); i++) {
        if (type == "R") {
            xnew = X[i] - x;
            ynew = Y[i] - y;
        }
        else {
            xnew = X[i] + x;
            ynew = Y[i] + y;
        }
        xn.push_back(xnew);
        yn.push_back(ynew);
    }
    for (int i = 0; i < X.size(); i++) {
        double d = sqrt(xn[i] * xn[i] + yn[i] * yn[i]);
        distance.push_back(d);
    }
    return distance;

}
void CoordOfMaxDist(double& m, vector<double>& dist, vector<double>& X, vector<double>& Y, string type) {
    int a = 0;
    for (int i = 0; i < dist.size(); i++) {
        if (dist[i] == m) {
            a = i;
        }

    }
    if (type == "L") {
        cout << "Leftmost:" << ' ' << X[a] << ' ' << Y[a] << endl;
    }
    else {
        cout << "Rightmost:" << ' ' << X[a] << ' ' << Y[a] << endl;
    }




}




int main() {
    const string path = "in.txt";


    vector<string> points = ReadAll("in.txt");

    vector<double> Xm = ChangeToDoubleX(points);
    vector<double> Ym = ChangeToDoubleY(points);
    double x0 = Xm[0];
    double y0 = Ym[0];


    vector<double> Xr = CheckSide(Xm, Ym, "X", "Right");
    vector<double> Yr = CheckSide(Xm, Ym, "Y", "Right");
    vector<double> Xl = CheckSide(Xm, Ym, "X", "Left");
    vector<double> Yl = CheckSide(Xm, Ym, "Y", "Left");
    vector<double> Rdistances = Distance(x0, y0, Xr, Yr, "R");
    vector<double> Ldistances = Distance(x0, y0, Xl, Yl, "L");
    double maxR = *max_element(Rdistances.begin(), Rdistances.end());
    double maxL = *max_element(Ldistances.begin(), Ldistances.end());

    CoordOfMaxDist(maxL, Ldistances, Xl, Yl, "L");
    CoordOfMaxDist(maxR, Rdistances, Xr, Yr, "R");





}
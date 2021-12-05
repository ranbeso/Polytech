#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
using namespace std;

double ar[2];

struct Point {
    int x;
    int y;
};

struct Answer
{
    Point left;
    Point right;
};

struct Wall
{
    double x;
    double h;
};

struct System
{
    double startHeight;
    Wall* walls;
    double vx;
    double vy;
};

System readFile2(char*, int&);
double flyPath(double x, double x0, double h, double vx, double vy);
double* roots(double a, double b, double c, double move);

double flyPath(double x, double x0, double h, double vx, double vy)
{
    const double g = 9.81;
    double v02 = vx * vx + vy * vy;
    double tan = vy / vx;
    return h + (x - x0) * tan - (g * (x - x0) * (x - x0)) / (2 * v02) * (tan * tan + 1);
}

double* roots(double a, double b, double c, double move)
{

    double dis = sqrt(b * b - 4 * a * c);
    double x1 = (-b - dis) / (2 * a);
    double x2 = (-b + dis) / (2 * a);

    ar[0] = x1 + move;
    ar[1]= x2 + move;
    return ar;
}

System readFile2(char* path, int& n)
{
    System system;
    const int MAX = 10;
    char buffer[MAX];
    std::ifstream in(path);
    if (in.is_open())
    {
        while (!in.eof())
        {
            in.getline(buffer, MAX);
            n++;
        }
        in.seekg(0);
        in >> system.startHeight;
        in >> system.vx >> system.vy;

        system.walls = new Wall[n - 1];
        system.walls[0] = Wall{ 0, system.startHeight };
        n = 1;
        while (!in.eof())
        {
            Wall inWall;
            in >> inWall.x >> inWall.h;
            system.walls[n] = inWall;
            n++;
        }
        return system;
    }
    else {
        throw std::runtime_error("No file!");
    }
}





int main(int argc, char** argv)
{
    if (argc == 2) {
        int n = 0;
        System system = readFile2(argv[1], n);
        Wall* walls = system.walls;
        double vx, vy, h;
        vx = system.vx;
        vy = system.vy;
        h = system.startHeight;
        const double g = 9.81;
        double pointOfLand;

        bool flyRight = true;
        bool isLanded = false;
        bool collided = false;
        int wallHit = 0;
        while (!isLanded)
        {
            if (flyRight)
            {
                for (int i = wallHit + 1; i < n; i++)
                {
                    double temp = flyPath(walls[i].x, walls[wallHit].x, h, vx, vy);
                    if (temp < walls[i].h && temp > 0)
                    {
                        collided = true;
                        flyRight = !flyRight;
                        wallHit = i;
                        h = temp;
                        vy = vy - g * walls[i].x / vx;
                        vx = -vx;
                        break;
                    }
                }
                if (!collided)
                {
                    isLanded = true;
                    double v0 = vx * vx + vy * vy;
                    double tan = vy / vx;
                    pointOfLand = roots(-g / (2 * v0) * (tan * tan + 1), tan, h, walls[wallHit].x)[0];
                }
            }
            else {
                collided = false;
                for (int i = wallHit - 1; i >= 1; i--)
                {
                    double temp = flyPath(walls[i].x, walls[wallHit].x, h, vx, vy);
                    if (temp < walls[i].h && temp > 0)
                    {
                        collided = true;
                        flyRight = !flyRight;
                        wallHit = i;
                        h = temp;
                        vy = vy - g * walls[i].x / vx;
                        vx = -vx;
                        break;
                    }
                }
                if (!collided)
                {
                    isLanded = true;
                    double v0 = vx * vx + vy * vy;
                    double tan = vy / vx;
                    pointOfLand = roots(-g / (2 * v0) * (tan * tan + 1), tan, h, walls[wallHit].x)[1];
                }
            }
        }

        delete system.walls;

        for (int i = 0; i < n - 1; i++)
            if (pointOfLand > walls[i].x && pointOfLand < walls[i + 1].x)
            {
                cout << "Area of landing: " << i << endl;
                return 0;
            }
        cout << "Area of landing: " << n << endl;
        return 0;
    }
    else
    {
        cerr << "NOT ENOUGH ARGUMENTS" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n'); //////////////
        cin.get();
        return -1;
    }
}
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

struct Point {
  int x;
  int y;
};

void readFile(string& filePath, int& n, vector<Point>& points) {
    ifstream fin(filePath);

    fin >> n;
    points.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> points[i].x >> points[i].y;
    }
    
    fin.close();
}

double computeAngle(Point from, Point to) {
    double angle = atan2(to.y - from.y, to.x - from.x);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

pair<Point, double> findNextExtremePoint(const std::vector<Point>& S, const Point& cur, double curAngle) {
    double minAngle = 2 * M_PI;
    Point next;
    
    for (const auto& p : S) {
        if (p.x == cur.x && p.y == cur.y)
            continue;
        
        double angle = computeAngle(cur, p);
        if (angle < minAngle && angle >= curAngle) {
            next = p;
            minAngle = angle;
        }
    }
    
    return {next, minAngle};
}

vector<Point> computeConvexHull(std::vector<Point>& S) {
    vector<Point> convexHull;
    Point first = S[0]; 
    convexHull.push_back(first);
    double curAngle = 0;
    Point cur = first;
    
    while (true) {
        auto [next, minAngle] = findNextExtremePoint(S, cur, curAngle);
        if (first.x == next.x && first.y == next.y)
            break;
        
        convexHull.push_back(next);
        cur = next;
        curAngle = minAngle;
    }
    
    return convexHull;
}

int main() {
    string filePath = "3.txt";
    int n;
    vector<Point> points;
    readFile(filePath, n, points);

    vector<Point> convexHull = computeConvexHull(points);
    for (auto& p : convexHull) {
        cout << p.x << " " << p.y << endl;
    }
    return 0;
}
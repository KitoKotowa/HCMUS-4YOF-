#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Point{
    int x;
    int y;
};

struct PointDist {
    Point p1;
    Point p2;
    float dist;
};

void readFile(string& filePath, int& n, vector<Point>& P) {
    ifstream fin(filePath);
    fin >> n;
    P.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> P[i].x >> P[i].y;
    }
    
    fin.close();
}

PointDist minDist(PointDist p1, PointDist p2) {
    return p1.dist < p2.dist ? p1 : p2;
}

PointDist distance(Point& a, Point& b) {
    PointDist p;
    p.p1 = a;
    p.p2 = b;
    p.dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return p;
}

PointDist bruteForce(vector<Point>& p) {
    PointDist minDistimum;
    bool hasminDist = false;
    int n = p.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            PointDist dist = distance(p[i], p[j]);
            if (!hasminDist) {
                minDistimum = dist;
                hasminDist = true;
            }
            else minDistimum = minDist(minDistimum, dist);
        }
    }
    return minDistimum;
}

PointDist ClosestDistanceSorted(vector<Point> &P, vector<Point> &Q) {
	if (P.size() <= 3) {
        return bruteForce(P);
    }
    int n = P.size();
    int mid = n / 2;
    Point midPoint = P[mid];
	float l = midPoint.x;

    vector<Point> pLeft(P.begin(), P.begin() + mid);
    vector<Point> pRight(P.begin() + mid, P.end());
    vector<Point> qLeft(Q.begin(), Q.begin() + mid);
    vector<Point> qRight(Q.begin() + mid, Q.end());

    PointDist dLeft = ClosestDistanceSorted(pLeft, qLeft);
    PointDist dRight = ClosestDistanceSorted(pRight, qRight);

	PointDist d = minDist(dLeft, dRight);
	PointDist dminDist = d;

	vector<Point> S;
	for (Point &p : Q) {
		if (abs(p.x - l) < d.dist) S.push_back(p);
	}

	int k = S.size();

    for (int i = 0; i < k - 1; ++i) {
        int j = i + 1;
        while (j < k && abs(S[i].y - S[j].y) < dminDist.dist) {
            dminDist = minDist(dminDist, distance(S[i], S[j]));
            ++j;
        }
    }

	return dminDist;
}

bool xLower (Point &p1, Point &p2) {
	return p1.x <= p2.x;
}

bool yLower (Point &p1, Point &p2) {
	return p1.y <= p2.y;
}

PointDist ClosestDistance(vector<Point> &points) {
	vector<Point> P = points, Q = points;

	sort(P.begin(), P.end(), xLower);
	sort(Q.begin(), Q.end(), yLower);
	return ClosestDistanceSorted(P, Q);
}

void printPair(Point& p) {
    cout << p.x << " " <<  p.y << endl;
}


int main() {
    string filePath = "5.txt";
    // vector<Point> P = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    vector<Point> P;
    int n;
    readFile(filePath, n, P);
    PointDist closest = ClosestDistance(P);

    printPair(closest.p1);
    printPair(closest.p2);
    cout << closest.dist << endl;
}
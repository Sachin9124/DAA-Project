#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y));
}

double bruteForce(vector<Point>& P, int n) {
    double minDist = DBL_MAX;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            minDist = min(minDist, dist(P[i], P[j]));
    return minDist;
}

double closestPairRec(vector<Point>& Px, vector<Point>& Py) {
    int n = Px.size();
    if (n <= 3) return bruteForce(Px, n);

    int mid = n / 2;
    Point midPoint = Px[mid];

    vector<Point> Pyl, Pyr;
    for (auto p : Py) {
        if (p.x <= midPoint.x) Pyl.push_back(p);
        else Pyr.push_back(p);
    }

    vector<Point> Pxl(Px.begin(), Px.begin() + mid);
    vector<Point> Pxr(Px.begin() + mid, Px.end());

    double dl = closestPairRec(Pxl, Pyl);
    double dr = closestPairRec(Pxr, Pyr);

    double d = min(dl, dr);
    vector<Point> strip;
    for (auto p : Py)
        if (fabs(p.x - midPoint.x) < d)
            strip.push_back(p);

    double minStrip = d;
    for (int i = 0; i < strip.size(); i++)
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++)
            minStrip = min(minStrip, dist(strip[i], strip[j]));

    return min(d, minStrip);
}

void runClosestPairDemo() {
    int n;
    cout << "\nEnter number of points: ";
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter x and y for point " << i + 1 << ": ";
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> Px = points, Py = points;
    sort(Px.begin(), Px.end(), [](Point a, Point b){ return a.x < b.x; });
    sort(Py.begin(), Py.end(), [](Point a, Point b){ return a.y < b.y; });

    double minDistance = closestPairRec(Px, Py);
    cout << "\nMinimum Distance (Divide & Conquer): " << minDistance << "\n";
}

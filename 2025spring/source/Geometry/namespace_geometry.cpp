template <typename T> 
class Point {
public:
    T x, y;
    Point() : x(0), y(0) {};
    Point(T _x, T _y) : x(_x), y(_y) {};

    Point operator+(Point p2){
        return Point(x + p2.x, y + p2.y);
    }
    Point operator-(Point p2){
        return Point(x - p2.x, y - p2.y);
    }
    T operator*(Point p2){
        return x * p2.x + y * p2.y;
    }
    T operator/(Point p2) {
        return x * p2.y - p2.x * y;
    }
    T operator==(Point p2) {
        return (x == p2.x) && (y == p2.y);
    }
    T sqdist() {
        return x*x + y*y;
    }
    bool operator<(Point p2) {
        if(y == p2.y)
            return x < p2.x;
        return y < p2.y;
    }

};  

namespace geometry {
    template <typename T> 
    ll ccw(Point<T> center, Point<T> p2, Point<T> p3) {
        ll res = (p2 - center) / (p3 - center);
        return (res > 0) - (res < 0);
    }

    template <typename T> 
    double theta(Point<T> center, Point<T> p2, Point<T> p3) {
        return acos(p2 * p3 / sqrt(p2.sqdist() * p3.sqdist()));
    }

    template <typename T> 
    function<bool(Point<T> &, Point<T> &, Point<T>)> cmp_point = [](Point<T> &l, Point<T> &r, Point<T> O = {(T)0, (T)0}) -> bool {
        return (l < O) != (r < O) ? l < r : l/r > 0;
    };

    template <typename T> 
    T sq_dist(Point<T> &p1, Point<T> &p2) {
        return (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y);
    }

    template <typename T>
    double dist(Point<T> &p1, Point<T> &p2) {
        return sqrt((double)sq_dist(p1, p2));
    }

    template <typename T>
    double line_point_dist(pair<Point<T>, Point<T>> &l, Point<T> p)
    {
        Point<T> p1 = p - l.first, p2 = l.second - l.first;
        return abs(p1 / p2)/(dist(l.first, l.second));
    }

    template <typename T>
    double line_min_dist(pair<Point<T>, Point<T>> &l1, pair<Point<T>, Point<T>> &l2) {
        double ans = INFINITY;
        ans = min({ans, dist(l1.first, l2.first), dist(l1.first, l2.second), dist(l1.second, l2.first), dist(l1.second, l2.second)});

        if((l1.second - l1.first)*(l2.first - l1.first) > 0 && (l1.first - l1.second)*(l2.first - l1.second) > 0)
            ans = min({ans, line_point_dist<double>(l1, l2.first)});
        if((l1.second - l1.first)*(l2.second - l1.first) > 0 && (l1.first - l1.second)*(l2.second - l1.second) > 0)
            ans = min({ans, line_point_dist<double>(l1, l2.second)});
        swap(l1, l2);
        if((l1.second - l1.first)*(l2.first - l1.first) > 0 && (l1.first - l1.second)*(l2.first - l1.second) > 0)
            ans = min({ans, line_point_dist<double>(l1, l2.first)});
        if((l1.second - l1.first)*(l2.second - l1.first) > 0 && (l1.first - l1.second)*(l2.second - l1.second) > 0)
            ans = min({ans, line_point_dist<double>(l1, l2.second)});
        swap(l1, l2);
        return ans;
    }

    template <typename T> 
    vector<T> convex_hull(vector<Point<T>> &pts) {
        assert(pts.size() >= 2);
        vector<Point<T>> res;

        swap(pts[0], *min_element(pts.begin(), pts.end()));
        sort(pts.begin()+1, pts.end(), [&pts](Point<T> &a, Point<T> &b){
            ll cw = ccw(pts[0], a, b);
            if(cw) return cw > 0;
            return sq_dist(pts[0], a) < sq_dist(pts[0], b);
        });
        auto itr = pts.begin();
        res.push_back(*(itr++)); res.push_back(*(itr++));

        while(itr != pts.end())
        {
            while(res.size() >= 2 && ccw(res[res.size()-2], res[res.size()-1], *itr) <= 0)
                res.pop_back();
            res.push_back(*(itr++));
        }
        return res;
    }
}
using namespace geometry;

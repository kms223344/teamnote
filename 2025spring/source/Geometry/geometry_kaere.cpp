typedef pair<ll, ll> pll;
#define _x first
#define _y second

pll operator-(const pll &a, const pll &b){
    return {a._x - b._x, a._y - b._y};
}

ll cross(const pll &a, const pll &b){
    return a._x * b._y - b._x * a._y;
}

ll dot(const pll &a, const pll &b){
    return a._x * b._x + a._y * b._y;
}

int ccw(const pll &p1, const pll &p2, const pll &p3){
    ll res = cross(p2 - p1, p3 - p1);
    return (res != 0) * (res < 0 ? -1 : 1);
}

// dist of point - point
double dist(const pll &p1, const pll &p2){
    return sqrt((p1._x - p2._x) * (p1._x - p2._x) + (p1._y - p2._y) * (p1._y - p2._y));
}

// dist of line - point
double dist(const pll &l1, const pll &l2, const pll &p){
    ll area = abs(cross(l2 - l1, p - l1));
    return area / dist(l1, l2);
}

// dist of seg - point
double segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

P perp() const { return P(-y, x); } // rotates +90 degrees
int sgn(T x) { return (x > 0) - (x < 0); } // sign of x

// Returns where p is as seen from s towards e. 1/0/-1 <-> left/on line/right.
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

// Returns a vector of either 0, 1, or 2 intersection points.
template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

// Computes the pair of points at which two circles intersect.
typedef Point<double> P;
bool circleInter(P a,P b,double r1,double r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

// Returns true iff p lies on the line segment from s to e.
template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

// Circumcircle
typedef Point<double> P;
double ccRadius(const P& A, const P& B, const P& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
			abs((B-A).cross(C-A))/2;
}
P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

// Minimum enclosing circle
pair<P, double> mec(vector<P> ps) {
	shuffle(all(ps), mt19937(time(0)));
	P o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
	rep(i,0,sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
		o = ps[i], r = 0;
		rep(j,0,i) if ((o - ps[j]).dist() > r * EPS) {
			o = (ps[i] + ps[j]) / 2;
			r = (o - ps[i]).dist();
			rep(k,0,j) if ((o - ps[k]).dist() > r * EPS) {
				o = ccCenter(ps[i], ps[j], ps[k]);
				r = (o - ps[i]).dist();
			}
		}
	}
	return {o, r};
}

// point inside convex hull in logN
bool inHull(const vector<P>& l, P p, bool strict = true) {
	int a = 1, b = sz(l) - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}

// convex hull
vector<pll> convex_hull(vector<pii> &arr){
    vector<pll> up, down;
    for(auto p : arr){
        while(up.size() >= 2 && ccw(up[up.size() - 2], up[up.size() - 1], p) >= 0) up.pop_back();
        while(down.size() >= 2 && ccw(down[down.size() - 2], down[down.size() - 1], p) <= 0) down.pop_back();
        up.push_back(p);
        down.push_back(p);
    }
    up.insert(up.end(), down.rbegin() + 1, down.rend());
    return up;
}

// rotating callipers
typedef Point<ll> P;
array<P, 2> hullDiameter(vector<P> S) {
	int n = sz(S), j = n < 2 ? 0 : 1;
	pair<ll, array<P, 2>> res({0, {S[0], S[0]}});
	rep(i,0,j)
		for (;; j = (j + 1) % n) {
			res = max(res, {(S[i] - S[j]).dist2(), {S[i], S[j]}});
			if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
				break;
		}
	return res.second;
}

// Closest pair
typedef Point<ll> P;
pair<P, P> closest(vector<P> v) {
	assert(sz(v) > 1);
	set<P> S;
	sort(all(v), [](P a, P b) { return a.y < b.y; });
	pair<ll, pair<P, P>> ret{LLONG_MAX, {P(), P()}};
	int j = 0;
	for (P p : v) {
		P d{1 + (ll)sqrt(ret.first), 0};
		while (v[j].y <= p.y - d.x) S.erase(v[j++]);
		auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
		for (; lo != hi; ++lo)
			ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
		S.insert(p);
	}
	return ret.second;
}
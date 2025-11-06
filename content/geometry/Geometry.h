/**
* Author: KickingKun
* Description: Geometric Template
* Time: O(1)
* Status: Seems OK
*/

struct Point {
	double x, y;
	Point() {}
	Point (double _x, double _y) {
		this->x = _x; this->y = _y;
	}
	
	double len() {
		return x * x + y * y;
	}
	
	Point operator - (Point other) {
		return {x - other.x, y - other.y};
	}
	
	Point operator - () {
		return Point(-x, -y);
	}
	
	bool operator == (Point other) {
		return x == other.x && y == other.y;
	}
	
	bool operator != (Point other) {
		return x != other.x || y != other.y;
	}
	
	void show() {
		cout << x << ' ' << y << '\n';
	}
};
 
struct Line {
	double a, b, c;
	Line() {}
	Line (double _a, double _b, double _c) {
		this->a = _a; this->b = _b; this->c = _c;
	}
	
	void simplify() { // if double = ll
		double d = __gcd(__gcd((ll)a, (ll)b), (ll)c);
		a /= d, b /= d, c /= d;
		// else do nothing
	}
	void show() {
		cout << a << ' ' << b << ' ' << c << '\n';
	}
};
 
double dot(Point A, Point B) { // dot product
	return A.x * B.x + A.y * B.y;
}
 
double cross(Point A, Point B) { // cross product
	return A.x * B.y - A.y * B.x;
}

int sign(double x) {
	if (x < 0) return -1;
	if (x == 0) return 0;
	return 1;
}
 
double dis(Point A, Point B) {
	return sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
}
 
double dis(Point m, Line d) { // d(M, delta)
	return abs(d.a * m.x + d.b * m.y + d.c) / sqrt(d.a * d.a + d.b * d.b);
}
 
double polygon_area(vector <Point> p) {
	double res = 0;
	for (int i = 1; i < p.size() - 1; i++)
		res += cross(p[i] - p[0], p[i + 1] - p[0]);
	return abs(res) / 2.0;
} // tested
 
bool same_side(Point A, Point B, Line d) { // out of line
	double y1 = d.a * A.x + d.b * A.y + d.c;
	double y2 = d.a * B.x + d.b * B.y + d.c;
	return (y1 > 0 && y2 > 0) || (y1 < 0 && y2 < 0);
} // tested by eyes
 
Line lineVector(Point A, Point n) { // Point + vector n
	return Line(n.x, n.y, -n.x * A.x - n.y * A.y);
}
 
Line line(Point A, Point B) { // Point A, B
	Point n(A.y - B.y, B.x - A.x);
	return Line(n.x, n.y, -n.x * A.x - n.y * A.y);
}
 
bool inside_line(Point A, Line d) { // inside of line
	return d.a * A.x + d.b * A.y + d.c == 0;
}
 
bool inside_segment(Point M, Point A, Point B) { // inside of segment AB
	if (M.x > max(A.x, B.x) || M.x < min(A.x, B.x)) return false;
	if (M.y > max(A.y, B.y) || M.y < min(A.y, B.y)) return false;
	return inside_line(M, line(A, B));
} // tested CSES / VNOI
 
Point intersect(Line A, Line B) { // find p(x, y)
	Point res; if (A.b == 0) swap(A, B);
	res.x = (B.c * A.b - A.c * B.b) / (A.a * B.b - B.a * A.b);
	res.y = (-A.c - A.a * res.x) / A.b;
	return res;
} // seem OK
 
Line perpendicular(Point A, Line d) {
	Point n(-d.b, d.a);
	return Line(n.x, n.y, -n.x * A.x - n.y * A.y);
} // tested
 
bool obtuse(Point M, Point A, Point B) { // MAB > 90
	return (M - A).len() + (B - A).len() < (M - B).len();
} // tested
 
double dist(Point M, Point A, Point B) { // dis(M, segment AB)
//	check MBA <= 90 && MAB <= 90
	if (obtuse(M, A, B) || obtuse(M, B, A)) return min(dis(M, A), dis(M, B));
	return dis(M, line(A, B));
} // tested at VNOI
 
bool intersect(Point A, Point B, Point C, Point D) { // segment AB and CD
	int x = sign(cross(C - A, B - A)), y = sign(cross(D - A, B - A));
	int u = sign(cross(A - C, D - C)), v = sign(cross(B - C, D - C));
	if (x == 0 && inside_segment(C, A, B)) return true;
	if (y == 0 && inside_segment(D, A, B)) return true;
	if (u == 0 && inside_segment(A, C, D)) return true;
	if (v == 0 && inside_segment(B, C, D)) return true;
	return (x != y && u != v); 
} // tested at CSES

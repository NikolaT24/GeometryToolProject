/**
* Dolution to course project #3
* Introduction to Programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Nikola Topalov
* @idnumber 1MI0600248
* @compiler VC / g++ / clang++
*
* <Geometry tool>
*
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <string>
#include <limits>
#include <cctype>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>

namespace geometry_tool {

const double EPSILON = 1e-6;
const double PI = 3.141592653589793238462643383279502884;
const int SCREEN_WIDTH = 78;

inline bool isZero(double value) {
    return std::abs(value) < EPSILON;
}

inline bool areEqual(double first, double second) {
    return isZero(first - second);
}

inline bool isLess(double first, double second) {
    return first < second - EPSILON;
}

inline bool isGreater(double first, double second) {
    return first > second + EPSILON;
}

inline double square(double value) {
    return value * value;
}

inline double degreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

inline double radiansToDegrees(double radians) {
    return radians * 180.0 / PI;
}

inline double clampDouble(double value, double low, double high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

inline double safeSqrt(double value) {
    if (value < 0 && value > -EPSILON) return 0;
    return std::sqrt(value);
}

std::string formatDouble(double value, int precision = 6) {
    if (isZero(value)) value = 0;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    std::string text = oss.str();
    while (!text.empty() && text.back() == '0') text.pop_back();
    if (!text.empty() && text.back() == '.') text.pop_back();
    if (text.empty() || text == "-0") text = "0";
    return text;
}

void printRepeated(char ch, int count) {
    for (int i = 0; i < count; ++i) std::cout << ch;
}

void printHorizontalRule(char ch = '-') {
    printRepeated(ch, SCREEN_WIDTH);
    std::cout << "\n";
}

void printCentered(const std::string& text, char fill = ' ') {
    int padding = SCREEN_WIDTH - static_cast<int>(text.size());
    if (padding <= 0) {
        std::cout << text << "\n";
        return;
    }
    int left = padding / 2;
    int right = padding - left;
    printRepeated(fill, left);
    std::cout << text;
    printRepeated(fill, right);
    std::cout << "\n";
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

#ifdef _WIN32
void clearScreen() {
    system("cls");
}
#else
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}
#endif

template <typename T>
T readInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) return value;
        clearBuffer();
        std::cout << "Invalid input. Please try again.\n";
    }
}

int readIntegerInRange(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        int value = readInput<int>(prompt);
        if (value >= minimum && value <= maximum) return value;
        std::cout << "Please enter a number between " << minimum << " and " << maximum << ".\n";
    }
}

char readYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string answer;
        std::cin >> answer;
        if (answer == "Y" || answer == "y") return 'Y';
        if (answer == "N" || answer == "n") return 'N';
        std::cout << "Please answer with Y or N.\n";
    }
}

bool isNameValid(const std::string& name) {
    if (name.empty()) return false;
    for (char ch : name) {
        unsigned char uch = static_cast<unsigned char>(ch);
        if (!std::isalnum(uch) && ch != '_') return false;
    }
    return true;
}

std::string readName(const std::string& prompt) {
    clearBuffer();
    while (true) {
        std::cout << prompt;
        std::string name;
        std::getline(std::cin, name);
        if (isNameValid(name)) return name;
        std::cout << "Please enter a valid name. Use letters, digits, or underscore only.\n";
    }
}

struct Point {
    double x = 0;
    double y = 0;
    std::string name = "";

    Point() = default;
    Point(double px, double py, const std::string& pname = "") : x(px), y(py), name(pname) {}

    std::string toString(bool showName = true) const {
        std::ostringstream oss;
        if (showName && !name.empty()) oss << name;
        oss << "(" << formatDouble(x) << "," << formatDouble(y) << ")";
        return oss.str();
    }

    void read(const std::string& label = "point") {
        std::cout << "Define " << label << ":\n";
        x = readInput<double>("  x-coordinate: ");
        y = readInput<double>("  y-coordinate: ");
        name = readName("  name: ");
        std::cout << "You defined " << toString() << ".\n";
    }
};

struct Vector2D {
    double x = 0;
    double y = 0;

    Vector2D() = default;
    Vector2D(double vx, double vy) : x(vx), y(vy) {}

    double lengthSquared() const { return x * x + y * y; }
    double length() const { return std::sqrt(lengthSquared()); }

    Vector2D normalized() const {
        double len = length();
        if (isZero(len)) return Vector2D(0, 0);
        return Vector2D(x / len, y / len);
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "<" << formatDouble(x) << "," << formatDouble(y) << ">";
        return oss.str();
    }
};

Vector2D operator+(const Vector2D& a, const Vector2D& b) { return Vector2D(a.x + b.x, a.y + b.y); }
Vector2D operator-(const Vector2D& a, const Vector2D& b) { return Vector2D(a.x - b.x, a.y - b.y); }
Vector2D operator*(const Vector2D& a, double k) { return Vector2D(a.x * k, a.y * k); }
Vector2D operator/(const Vector2D& a, double k) { return Vector2D(a.x / k, a.y / k); }

Vector2D vectorFromTo(const Point& a, const Point& b) {
    return Vector2D(b.x - a.x, b.y - a.y);
}

double dotProduct(const Vector2D& a, const Vector2D& b) {
    return a.x * b.x + a.y * b.y;
}

double crossProduct(const Vector2D& a, const Vector2D& b) {
    return a.x * b.y - a.y * b.x;
}

double distanceSquared(const Point& a, const Point& b) {
    return square(a.x - b.x) + square(a.y - b.y);
}

double distance(const Point& a, const Point& b) {
    return std::sqrt(distanceSquared(a, b));
}

Point midpoint(const Point& a, const Point& b) {
    return Point((a.x + b.x) / 2.0, (a.y + b.y) / 2.0, "M");
}

struct Line {
    // General equation: A*x + B*y + C = 0
    double A = 0;
    double B = 1;
    double C = 0;
    std::string name = "";

    Line() = default;
    Line(double a, double b, double c, const std::string& lineName = "") : A(a), B(b), C(c), name(lineName) {}

    static Line fromSlopeIntercept(double slope, double intercept, const std::string& lineName = "") {
        // y = slope*x + intercept -> slope*x - y + intercept = 0
        return Line(slope, -1.0, intercept, lineName);
    }

    static Line vertical(double xValue, const std::string& lineName = "") {
        return Line(1.0, 0.0, -xValue, lineName);
    }

    static Line horizontal(double yValue, const std::string& lineName = "") {
        return Line(0.0, 1.0, -yValue, lineName);
    }

    static Line throughTwoPoints(const Point& p, const Point& q, const std::string& lineName = "") {
        double a = p.y - q.y;
        double b = q.x - p.x;
        double c = p.x * q.y - q.x * p.y;
        return Line(a, b, c, lineName);
    }

    bool isValid() const {
        return !isZero(A) || !isZero(B);
    }

    bool isVertical() const {
        return isZero(B) && !isZero(A);
    }

    bool isHorizontal() const {
        return isZero(A) && !isZero(B);
    }

    bool hasSlope() const {
        return !isZero(B);
    }

    double slope() const {
        if (isZero(B)) return std::numeric_limits<double>::infinity();
        return -A / B;
    }

    double yIntercept() const {
        if (isZero(B)) return std::numeric_limits<double>::quiet_NaN();
        return -C / B;
    }

    double xValueForVertical() const {
        if (!isVertical()) return std::numeric_limits<double>::quiet_NaN();
        return -C / A;
    }

    double valueAt(double x) const {
        if (isZero(B)) return std::numeric_limits<double>::quiet_NaN();
        return (-A * x - C) / B;
    }

    double signedValueAt(const Point& p) const {
        return A * p.x + B * p.y + C;
    }

    bool contains(const Point& p) const {
        return isZero(signedValueAt(p));
    }

    double distanceTo(const Point& p) const {
        return std::abs(signedValueAt(p)) / std::sqrt(A * A + B * B);
    }

    std::string equation() const {
        std::ostringstream oss;
        if (!name.empty()) oss << "Line \"" << name << "\": ";

        if (isVertical()) {
            oss << "x=" << formatDouble(xValueForVertical());
            return oss.str();
        }

        double m = slope();
        double b = yIntercept();
        oss << "y=";
        if (isZero(m)) {
            oss << formatDouble(b);
            return oss.str();
        }
        if (areEqual(m, 1.0)) oss << "x";
        else if (areEqual(m, -1.0)) oss << "-x";
        else oss << formatDouble(m) << "x";

        if (b > EPSILON) oss << "+" << formatDouble(b);
        else if (b < -EPSILON) oss << formatDouble(b);
        return oss.str();
    }

    std::string generalEquation() const {
        std::ostringstream oss;
        oss << formatDouble(A) << "x";
        if (B >= 0) oss << "+";
        oss << formatDouble(B) << "y";
        if (C >= 0) oss << "+";
        oss << formatDouble(C) << "=0";
        return oss.str();
    }

    void readSlopeIntercept(const std::string& label = "line") {
        std::cout << "Define " << label << " in form y=a*x+b:\n";
        double m = readInput<double>("  slope a: ");
        double b = readInput<double>("  y-intercept b: ");
        name = readName("  name: ");
        *this = Line::fromSlopeIntercept(m, b, name);
        std::cout << equation() << "\n";
    }
};

struct Parabola {
    double a = 1;
    double b = 0;
    double c = 0;
    std::string name = "";

    Parabola() = default;
    Parabola(double pa, double pb, double pc, const std::string& pname = "") : a(pa), b(pb), c(pc), name(pname) {}

    bool isRealParabola() const {
        return !isZero(a);
    }

    double valueAt(double x) const {
        return a * x * x + b * x + c;
    }

    double derivativeAt(double x) const {
        return 2.0 * a * x + b;
    }

    double discriminant() const {
        return b * b - 4.0 * a * c;
    }

    Point vertex() const {
        if (isZero(a)) return Point(0, c, "V");
        double vx = -b / (2.0 * a);
        return Point(vx, valueAt(vx), "V");
    }

    std::string equation() const {
        std::ostringstream oss;
        if (!name.empty()) oss << "Parabola \"" << name << "\": ";
        oss << "y=";
        bool wrote = false;
        auto writeTerm = [&](double coefficient, const std::string& variable, bool allowOne) {
            if (isZero(coefficient)) return;
            if (wrote && coefficient > 0) oss << "+";
            if (allowOne && areEqual(coefficient, 1.0)) oss << variable;
            else if (allowOne && areEqual(coefficient, -1.0)) oss << "-" << variable;
            else oss << formatDouble(coefficient) << variable;
            wrote = true;
        };
        writeTerm(a, "x^2", true);
        writeTerm(b, "x", true);
        if (!isZero(c) || !wrote) {
            if (wrote && c > 0) oss << "+";
            oss << formatDouble(c);
        }
        return oss.str();
    }

    void read(const std::string& label = "parabola") {
        std::cout << "Define " << label << " in form y=a*x^2+b*x+c:\n";
        a = readInput<double>("  a: ");
        b = readInput<double>("  b: ");
        c = readInput<double>("  c: ");
        name = readName("  name: ");
        std::cout << equation() << "\n";
    }
};

struct Triangle {
    Point a;
    Point b;
    Point c;

    Triangle() = default;
    Triangle(const Point& pa, const Point& pb, const Point& pc) : a(pa), b(pb), c(pc) {}

    void read() {
        a.read("first vertex");
        b.read("second vertex");
        c.read("third vertex");
    }

    double signedDoubleArea() const {
        return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    }

    double area() const {
        return std::abs(signedDoubleArea()) / 2.0;
    }

    bool isDegenerate() const {
        return isZero(signedDoubleArea());
    }

    double sideAB() const { return distance(a, b); }
    double sideBC() const { return distance(b, c); }
    double sideCA() const { return distance(c, a); }

    Point centroid() const {
        return Point((a.x + b.x + c.x) / 3.0, (a.y + b.y + c.y) / 3.0, "G");
    }

    std::string typeBySides() const {
        double ab = sideAB();
        double bc = sideBC();
        double ca = sideCA();
        if (areEqual(ab, bc) && areEqual(bc, ca)) return "equilateral";
        if (areEqual(ab, bc) || areEqual(bc, ca) || areEqual(ca, ab)) return "isosceles";
        return "scalene";
    }

    std::string typeByAngles() const {
        std::vector<double> sides = { sideAB(), sideBC(), sideCA() };
        std::sort(sides.begin(), sides.end());
        double lhs = square(sides[0]) + square(sides[1]);
        double rhs = square(sides[2]);
        if (areEqual(lhs, rhs)) return "right";
        if (lhs > rhs) return "acute";
        return "obtuse";
    }
};

bool areParallel(const Line& first, const Line& second) {
    return isZero(first.A * second.B - second.A * first.B);
}

bool arePerpendicular(const Line& first, const Line& second) {
    return isZero(first.A * second.A + first.B * second.B);
}

Line parallelThroughPoint(const Line& line, const Point& point, const std::string& name = "") {
    double c = -(line.A * point.x + line.B * point.y);
    return Line(line.A, line.B, c, name);
}

Line perpendicularThroughPoint(const Line& line, const Point& point, const std::string& name = "") {
    // If line has normal vector (A, B), a perpendicular line has direction parallel to that normal,
    // therefore its normal vector can be (-B, A).
    double a = -line.B;
    double b = line.A;
    double c = -(a * point.x + b * point.y);
    return Line(a, b, c, name);
}

bool intersectionOfLines(const Line& first, const Line& second, Point& result) {
    double det = first.A * second.B - second.A * first.B;
    if (isZero(det)) return false;
    result.x = (first.B * second.C - second.B * first.C) / det;
    result.y = (second.A * first.C - first.A * second.C) / det;
    result.name = "I";
    return true;
}

bool areCollinear(const Point& a, const Point& b, const Point& c) {
    return isZero(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

Line perpendicularBisector(const Point& first, const Point& second, const std::string& name = "") {
    Point mid = midpoint(first, second);
    Line base = Line::throughTwoPoints(first, second);
    return perpendicularThroughPoint(base, mid, name);
}

Line medianFromThirdToFirstSecond(const Point& first, const Point& second, const Point& third, const std::string& name = "") {
    return Line::throughTwoPoints(third, midpoint(first, second), name);
}

Line altitudeFromThirdToFirstSecond(const Point& first, const Point& second, const Point& third, const std::string& name = "") {
    Line base = Line::throughTwoPoints(first, second);
    return perpendicularThroughPoint(base, third, name);
}

Line tangentToParabolaAtPoint(const Parabola& parabola, const Point& point, bool& success) {
    success = false;
    if (!parabola.isRealParabola()) return Line();
    if (!isZero(parabola.valueAt(point.x) - point.y)) return Line();
    success = true;
    double m = parabola.derivativeAt(point.x);
    return Line::fromSlopeIntercept(m, point.y - m * point.x, "tangent");
}

std::vector<Point> intersectLineAndParabola(const Line& line, const Parabola& parabola) {
    std::vector<Point> result;
    if (!parabola.isRealParabola()) {
        Line asLine = Line::fromSlopeIntercept(parabola.b, parabola.c);
        Point intersection;
        if (intersectionOfLines(line, asLine, intersection)) result.push_back(intersection);
        return result;
    }

    if (line.isVertical()) {
        double x = line.xValueForVertical();
        result.push_back(Point(x, parabola.valueAt(x), "P"));
        return result;
    }

    double m = line.slope();
    double n = line.yIntercept();
    double A = parabola.a;
    double B = parabola.b - m;
    double C = parabola.c - n;
    double D = B * B - 4.0 * A * C;

    if (D < -EPSILON) return result;
    if (isZero(D)) {
        double x = -B / (2.0 * A);
        result.push_back(Point(x, line.valueAt(x), "P"));
        return result;
    }

    double rootD = std::sqrt(D);
    double x1 = (-B + rootD) / (2.0 * A);
    double x2 = (-B - rootD) / (2.0 * A);
    result.push_back(Point(x1, line.valueAt(x1), "P1"));
    result.push_back(Point(x2, line.valueAt(x2), "P2"));
    return result;
}

std::vector<Line> tangentsFromXAxisPointToParabola(const Parabola& parabola, const Point& point) {
    std::vector<Line> result;
    if (!isZero(point.y) || !parabola.isRealParabola()) return result;

    double value = parabola.valueAt(point.x);
    if (isZero(value)) {
        bool ok = false;
        Line tangent = tangentToParabolaAtPoint(parabola, point, ok);
        if (ok) result.push_back(tangent);
        return result;
    }

    double discriminant = square(parabola.a * point.x) + parabola.a * parabola.b * point.x + parabola.a * parabola.c;
    if (discriminant < -EPSILON) return result;

    double root = safeSqrt(discriminant);
    double tx1 = (parabola.a * point.x - root) / parabola.a;
    double tx2 = (parabola.a * point.x + root) / parabola.a;

    Point t1(tx1, parabola.valueAt(tx1), "T1");
    Point t2(tx2, parabola.valueAt(tx2), "T2");

    bool ok1 = false;
    bool ok2 = false;
    Line l1 = tangentToParabolaAtPoint(parabola, t1, ok1);
    Line l2 = tangentToParabolaAtPoint(parabola, t2, ok2);

    if (ok1) result.push_back(l1);
    if (ok2 && !areParallel(l1, l2)) result.push_back(l2);
    return result;
}

std::string getLineEquation(double slope, double intercept, const std::string& name = "") {
    return Line::fromSlopeIntercept(slope, intercept, name).equation();
}

bool isOnLine(double a, double b, double x1, double y1) {
    return Line::fromSlopeIntercept(a, b).contains(Point(x1, y1));
}

std::string parLineThroughPoint(double a, double b, double x1, double y1) {
    Line l = Line::fromSlopeIntercept(a, b);
    return parallelThroughPoint(l, Point(x1, y1)).equation();
}

std::string perpLineThroughPoint(double a, double b, double x1, double y1) {
    Line l = Line::fromSlopeIntercept(a, b);
    Point p(x1, y1);
    return perpendicularThroughPoint(l, p).equation();
}

std::string intersectionOfLines(double a, double b, double p, double q) {
    Line first = Line::fromSlopeIntercept(a, b);
    Line second = Line::fromSlopeIntercept(p, q);
    Point result;
    if (!intersectionOfLines(first, second, result)) return "Given lines are parallel.";
    return "Functions intersect at " + result.toString(false) + ".";
}

bool isTriangleIsosceles(double x1, double y1, double x2, double y2, double x3, double y3) {
    Point a(x1, y1), b(x2, y2), c(x3, y3);
    Triangle t(a, b, c);
    return t.typeBySides() == "isosceles" || t.typeBySides() == "equilateral";
}

std::string eqPerpBisector(double x1, double y1, double x2, double y2) {
    return perpendicularBisector(Point(x1, y1), Point(x2, y2)).equation();
}

bool areCollinear(double x1, double y1, double x2, double y2, double x3, double y3) {
    return areCollinear(Point(x1, y1), Point(x2, y2), Point(x3, y3));
}

std::string eqMedian(double x1, double y1, double x2, double y2, double x3, double y3) {
    Point p1(x1, y1), p2(x2, y2), p3(x3, y3);
    if (areCollinear(p1, p2, p3)) return "The points you entered are collinear.";
    return medianFromThirdToFirstSecond(p1, p2, p3).equation();
}

std::string eqAltitude(double x1, double y1, double x2, double y2, double x3, double y3) {
    Point p1(x1, y1), p2(x2, y2), p3(x3, y3);
    if (areCollinear(p1, p2, p3)) return "The points you entered are collinear.";
    return altitudeFromThirdToFirstSecond(p1, p2, p3).equation();
}

std::string tangentToParAtPoint(double a, double b, double c, double x1, double y1) {
    bool ok = false;
    Line tangent = tangentToParabolaAtPoint(Parabola(a, b, c), Point(x1, y1), ok);
    if (!ok) return "The given point does not lie on the parabola";
    return tangent.equation();
}

std::string intersectionOfLineAndPar(double a, double b, double c, double p, double q) {
    std::vector<Point> points = intersectLineAndParabola(Line::fromSlopeIntercept(p, q), Parabola(a, b, c));
    if (points.empty()) return "Given functions do not intersect.";
    std::ostringstream oss;
    if (points.size() == 1) {
        oss << "Functions intersect at " << points[0].toString(false) << ".";
    } else {
        oss << "Functions intersect at " << points[0].toString(false) << " and " << points[1].toString(false) << ".";
    }
    return oss.str();
}

bool doThreeLinesInters(double a, double b, double p, double q, double s, double t) {
    Line l1 = Line::fromSlopeIntercept(a, b);
    Line l2 = Line::fromSlopeIntercept(p, q);
    Line l3 = Line::fromSlopeIntercept(s, t);
    Point i12;
    Point i13;
    if (!intersectionOfLines(l1, l2, i12)) return false;
    if (!intersectionOfLines(l1, l3, i13)) return false;
    return distance(i12, i13) < EPSILON;
}

bool doLinesFormQuadr(double a, double b, double p, double q, double s, double t, double m, double n) {
    Line l1 = Line::fromSlopeIntercept(a, b);
    Line l2 = Line::fromSlopeIntercept(p, q);
    Line l3 = Line::fromSlopeIntercept(s, t);
    Line l4 = Line::fromSlopeIntercept(m, n);

    std::vector<Line> lines = { l1, l2, l3, l4 };
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (areParallel(lines[i], lines[j]) && areEqual(lines[i].yIntercept(), lines[j].yIntercept())) {
                return false;
            }
        }
    }

    // A quadrilateral made from four lines should not have three concurrent lines.
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            for (int k = j + 1; k < 4; ++k) {
                Point firstIntersection;
                Point secondIntersection;
                if (intersectionOfLines(lines[i], lines[j], firstIntersection) &&
                    intersectionOfLines(lines[i], lines[k], secondIntersection) &&
                    distance(firstIntersection, secondIntersection) < EPSILON) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool isParallelogram(double a, double p, double s, double m) {
    return (areEqual(a, p) && areEqual(s, m)) ||
           (areEqual(a, s) && areEqual(p, m)) ||
           (areEqual(a, m) && areEqual(p, s));
}

bool isRectangle(double a, double p, double s, double m) {
    if (!isParallelogram(a, p, s, m)) return false;
    std::vector<double> slopes = { a, p, s, m };
    for (double first : slopes) {
        for (double second : slopes) {
            if (isZero(first * second + 1.0)) return true;
        }
    }
    return false;
}

bool isTrapezoid(double a, double p, double s, double m) {
    int parallelPairs = 0;
    if (areEqual(a, p)) ++parallelPairs;
    if (areEqual(a, s)) ++parallelPairs;
    if (areEqual(a, m)) ++parallelPairs;
    if (areEqual(p, s)) ++parallelPairs;
    if (areEqual(p, m)) ++parallelPairs;
    if (areEqual(s, m)) ++parallelPairs;
    return parallelPairs == 1;
}

void printPointReport(const Point& point) {
    printHorizontalRule();
    std::cout << "Point report\n";
    std::cout << "Name: " << (point.name.empty() ? "unnamed" : point.name) << "\n";
    std::cout << "Coordinates: " << point.toString(false) << "\n";
    std::cout << "Distance from origin: " << formatDouble(distance(Point(0, 0), point)) << "\n";
    printHorizontalRule();
}

void printLineReport(const Line& line) {
    printHorizontalRule();
    std::cout << "Line report\n";
    std::cout << line.equation() << "\n";
    std::cout << "General equation: " << line.generalEquation() << "\n";
    if (line.isVertical()) std::cout << "Line is vertical.\n";
    else std::cout << "Slope: " << formatDouble(line.slope()) << "\n";
    if (line.isHorizontal()) std::cout << "Line is horizontal.\n";
    printHorizontalRule();
}

void printParabolaReport(const Parabola& parabola) {
    printHorizontalRule();
    std::cout << "Parabola report\n";
    std::cout << parabola.equation() << "\n";
    if (!parabola.isRealParabola()) {
        std::cout << "This is not a real parabola because a = 0.\n";
    } else {
        Point v = parabola.vertex();
        std::cout << "Vertex: " << v.toString(false) << "\n";
        std::cout << "Discriminant: " << formatDouble(parabola.discriminant()) << "\n";
        std::cout << "Opens: " << (parabola.a > 0 ? "up" : "down") << "\n";
    }
    printHorizontalRule();
}

void printTriangleReport(const Triangle& triangle) {
    printHorizontalRule();
    std::cout << "Triangle report\n";
    std::cout << "A = " << triangle.a.toString(false) << "\n";
    std::cout << "B = " << triangle.b.toString(false) << "\n";
    std::cout << "C = " << triangle.c.toString(false) << "\n";
    if (triangle.isDegenerate()) {
        std::cout << "The triangle is degenerate because the points are collinear.\n";
    } else {
        std::cout << "Area: " << formatDouble(triangle.area()) << "\n";
        std::cout << "Side AB: " << formatDouble(triangle.sideAB()) << "\n";
        std::cout << "Side BC: " << formatDouble(triangle.sideBC()) << "\n";
        std::cout << "Side CA: " << formatDouble(triangle.sideCA()) << "\n";
        std::cout << "Type by sides: " << triangle.typeBySides() << "\n";
        std::cout << "Type by angles: " << triangle.typeByAngles() << "\n";
        std::cout << "Centroid: " << triangle.centroid().toString(false) << "\n";
    }
    printHorizontalRule();
}

void actionCheckPointOnLine() {
    Line line;
    Point point;
    line.readSlopeIntercept("line");
    point.read("point");
    if (line.contains(point)) std::cout << point.toString() << " lies on " << line.equation() << ".\n";
    else std::cout << point.toString() << " does not lie on " << line.equation() << ".\n";
}

void actionParallelLineThroughPoint() {
    Line line;
    Point point;
    line.readSlopeIntercept("line");
    point.read("point");
    if (line.contains(point)) {
        std::cout << "The given point already lies on the line.\n";
    }
    Line result = parallelThroughPoint(line, point, "parallel_result");
    std::cout << "Parallel line: " << result.equation() << "\n";
}

void actionPerpendicularLineThroughPoint() {
    Line line;
    Point point;
    line.readSlopeIntercept("line");
    point.read("point");
    Line result = perpendicularThroughPoint(line, point, "perpendicular_result");
    std::cout << "Perpendicular line: " << result.equation() << "\n";
}

void actionLineIntersection() {
    Line first;
    Line second;
    first.readSlopeIntercept("first line");
    second.readSlopeIntercept("second line");
    Point result;
    if (intersectionOfLines(first, second, result)) {
        std::cout << "Intersection point: " << result.toString(false) << "\n";
    } else {
        std::cout << "The lines are parallel or identical, so there is no unique intersection point.\n";
    }
}

void actionTriangleLines() {
    Triangle triangle;
    triangle.read();
    printTriangleReport(triangle);
    if (triangle.isDegenerate()) return;

    std::cout << "Medians:\n";
    std::cout << "  from C to AB: " << medianFromThirdToFirstSecond(triangle.a, triangle.b, triangle.c).equation() << "\n";
    std::cout << "  from A to BC: " << medianFromThirdToFirstSecond(triangle.b, triangle.c, triangle.a).equation() << "\n";
    std::cout << "  from B to CA: " << medianFromThirdToFirstSecond(triangle.c, triangle.a, triangle.b).equation() << "\n";

    std::cout << "Altitudes:\n";
    std::cout << "  from C to AB: " << altitudeFromThirdToFirstSecond(triangle.a, triangle.b, triangle.c).equation() << "\n";
    std::cout << "  from A to BC: " << altitudeFromThirdToFirstSecond(triangle.b, triangle.c, triangle.a).equation() << "\n";
    std::cout << "  from B to CA: " << altitudeFromThirdToFirstSecond(triangle.c, triangle.a, triangle.b).equation() << "\n";

    std::cout << "Perpendicular bisectors:\n";
    std::cout << "  of AB: " << perpendicularBisector(triangle.a, triangle.b).equation() << "\n";
    std::cout << "  of BC: " << perpendicularBisector(triangle.b, triangle.c).equation() << "\n";
    std::cout << "  of CA: " << perpendicularBisector(triangle.c, triangle.a).equation() << "\n";
}

void actionTangentsFromXAxisPoint() {
    Point point;
    Parabola parabola;
    point.read("point on x-axis");
    parabola.read();
    if (!isZero(point.y)) {
        std::cout << "The given point does not lie on the x-axis.\n";
        return;
    }
    std::vector<Line> tangents = tangentsFromXAxisPointToParabola(parabola, point);
    if (tangents.empty()) {
        std::cout << "There are no tangent lines from this point to the given parabola.\n";
        return;
    }
    std::cout << "Tangent lines:\n";
    for (std::size_t i = 0; i < tangents.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << tangents[i].equation() << "\n";
    }
}

void actionLineParabolaIntersection() {
    Line line;
    Parabola parabola;
    line.readSlopeIntercept("line");
    parabola.read();
    std::vector<Point> points = intersectLineAndParabola(line, parabola);
    if (points.empty()) {
        std::cout << "The line and parabola do not intersect.\n";
        return;
    }
    std::cout << "Intersection points:\n";
    for (const Point& point : points) {
        std::cout << "  " << point.toString(false) << "\n";
    }
}

void actionQuadrilateralType() {
    Line l1, l2, l3, l4;
    l1.readSlopeIntercept("first line");
    l2.readSlopeIntercept("second line");
    l3.readSlopeIntercept("third line");
    l4.readSlopeIntercept("fourth line");

    double a = l1.slope(), p = l2.slope(), s = l3.slope(), m = l4.slope();
    double b = l1.yIntercept(), q = l2.yIntercept(), t = l3.yIntercept(), n = l4.yIntercept();

    if (!doLinesFormQuadr(a, b, p, q, s, t, m, n)) {
        std::cout << "Given lines do not form a quadrilateral.\n";
        return;
    }

    if (isParallelogram(a, p, s, m)) {
        if (isRectangle(a, p, s, m)) std::cout << "Given lines form a rectangle.\n";
        else std::cout << "Given lines form a parallelogram.\n";
    } else if (isTrapezoid(a, p, s, m)) {
        std::cout << "Given lines form a trapezoid.\n";
    } else {
        std::cout << "Given lines form a general quadrilateral.\n";
    }
}

void actionDistancePointLine() {
    Line line;
    Point point;
    line.readSlopeIntercept("line");
    point.read("point");
    std::cout << "Distance from " << point.toString() << " to " << line.equation() << " is "
              << formatDouble(line.distanceTo(point)) << ".\n";
}

void actionLineThroughTwoPoints() {
    Point first;
    Point second;
    first.read("first point");
    second.read("second point");
    if (distance(first, second) < EPSILON) {
        std::cout << "The two points are identical. Infinitely many lines pass through them.\n";
        return;
    }
    Line line = Line::throughTwoPoints(first, second, "through_points");
    std::cout << "Line through the two points: " << line.equation() << "\n";
}

void actionTriangleClassification() {
    Triangle triangle;
    triangle.read();
    printTriangleReport(triangle);
}

void actionParabolaReport() {
    Parabola parabola;
    parabola.read();
    printParabolaReport(parabola);
}

void actionTangentAtParabolaPoint() {
    Parabola parabola;
    Point point;
    parabola.read();
    point.read("point on parabola");
    bool ok = false;
    Line tangent = tangentToParabolaAtPoint(parabola, point, ok);
    if (!ok) {
        std::cout << "The point does not lie on the parabola, or the function is not a parabola.\n";
        return;
    }
    std::cout << "Tangent line: " << tangent.equation() << "\n";
}

void printStartMessage() {
    printHorizontalRule('=');
    printCentered("Geometry Tool", ' ');
    printHorizontalRule('=');
    std::cout << "You can choose one of the following operations:\n\n";
    std::cout << "  1. Check whether a point lies on a given line\n";
    std::cout << "  2. Find a line through a point parallel to a given line\n";
    std::cout << "  3. Find a line through a point perpendicular to a given line\n";
    std::cout << "  4. Find the intersection point of two lines\n";
    std::cout << "  5. Find altitudes, medians and perpendicular bisectors of a triangle\n";
    std::cout << "  6. Find tangent lines to a parabola from a point on the x-axis\n";
    std::cout << "  7. Find intersection points of a parabola and a line\n";
    std::cout << "  8. Find type of quadrilateral given four lines\n";
    std::cout << "  9. Find distance from point to line\n";
    std::cout << " 10. Build a line through two points\n";
    std::cout << " 11. Classify triangle and show report\n";
    std::cout << " 12. Show parabola report\n";
    std::cout << " 13. Tangent to parabola at a given point\n";
    std::cout << "  0. Exit\n\n";
    std::cout << "Note: Main line input uses slope-intercept form y=a*x+b.\n";
    printHorizontalRule();
}

using MenuAction = std::function<void()>;

struct MenuItem {
    int id;
    std::string title;
    MenuAction action;
};

std::vector<MenuItem> createMenuItems() {
    return {
        {1,  "Point on line", actionCheckPointOnLine},
        {2,  "Parallel line", actionParallelLineThroughPoint},
        {3,  "Perpendicular line", actionPerpendicularLineThroughPoint},
        {4,  "Line intersection", actionLineIntersection},
        {5,  "Triangle special lines", actionTriangleLines},
        {6,  "Tangents from x-axis point", actionTangentsFromXAxisPoint},
        {7,  "Line and parabola intersection", actionLineParabolaIntersection},
        {8,  "Quadrilateral type", actionQuadrilateralType},
        {9,  "Point-line distance", actionDistancePointLine},
        {10, "Line through two points", actionLineThroughTwoPoints},
        {11, "Triangle classification", actionTriangleClassification},
        {12, "Parabola report", actionParabolaReport},
        {13, "Tangent at parabola point", actionTangentAtParabolaPoint}
    };
}

void executeGeometryTool() {
    std::cout << "Welcome to the expanded Geometry Tool program!\n";
    char proceed = readYesNo("Would you like to proceed? Y/N: ");
    if (proceed == 'N') {
        std::cout << "Thank you for visiting the program.\n";
        return;
    }

    std::vector<MenuItem> menu = createMenuItems();

    while (true) {
        clearScreen();
        printStartMessage();
        int choice = readIntegerInRange("Enter your choice: ", 0, 13);
        if (choice == 0) break;

        clearScreen();
        auto it = std::find_if(menu.begin(), menu.end(), [choice](const MenuItem& item) {
            return item.id == choice;
        });

        if (it != menu.end()) {
            printCentered(it->title, ' ');
            printHorizontalRule();
            it->action();
        } else {
            std::cout << "Invalid menu choice.\n";
        }

        char again = readYesNo("\nWould you like to run another operation? Y/N: ");
        if (again == 'N') break;
    }

    clearScreen();
    std::cout << "Thank you for using the Geometry Tool.\n";
}

void assertMessage(bool condition, const std::string& message) {
    std::cout << (condition ? "[OK] " : "[FAIL] ") << message << "\n";
}

void runTinySelfTestSuite() {
    Line l1 = Line::fromSlopeIntercept(1, 0);
    Line l2 = Line::fromSlopeIntercept(-1, 2);
    Point intersection;
    bool hasIntersection = intersectionOfLines(l1, l2, intersection);
    assertMessage(hasIntersection, "Two non-parallel lines intersect.");
    assertMessage(areEqual(intersection.x, 1.0) && areEqual(intersection.y, 1.0), "Intersection is (1,1).");

    Point a(0, 0), b(2, 0), c(1, 2);
    Triangle triangle(a, b, c);
    assertMessage(!triangle.isDegenerate(), "Triangle is non-degenerate.");
    assertMessage(triangle.typeBySides() == "isosceles", "Triangle is isosceles.");

    Parabola parabola(1, 0, 0);
    Line horizontal = Line::fromSlopeIntercept(0, 1);
    std::vector<Point> points = intersectLineAndParabola(horizontal, parabola);
    assertMessage(points.size() == 2, "Line y=1 intersects y=x^2 twice.");
}

int main() {
    geometry_tool::executeGeometryTool();
    return 0;
}

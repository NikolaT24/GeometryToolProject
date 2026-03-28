/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Nikola Topalov
* @idnumber 1MI0600248
* @compiler VC
*
* <Geometry tool>
*
*/

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <limits>
#include <cctype>

const double EPSILON = 1e-6;

inline bool isZero(double d) {
    return std::abs(d) < EPSILON;
}

inline bool areEqual(double a, double b) {
    return isZero(a - b);
}

template <typename T>
T readInput(const std::string& prompt) {
    T val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please try again.\n";
    }
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool isNameValid(const std::string& name) {
    if (name.empty()) return false;
    for (char c : name) {
        if (!std::isalnum(c) && c != '_') return false;
    }
    return true;
}

std::string getLineEquation(double a, double b, const std::string& name = "") {
    std::ostringstream oss;
    if (!name.empty()) {
        oss << "Your line \"" << name << "\" is defined as: ";
    }
    
    if (isZero(a)) {
        oss << "y=" << b;
        return oss.str();
    }
    
    oss << "y=";
    if (areEqual(a, 1.0)) oss << "x";
    else if (areEqual(a, -1.0)) oss << "-x";
    else oss << a << "x";

    if (b > EPSILON) oss << "+" << b;
    else if (b < -EPSILON) oss << b; 
    
    return oss.str();
}

struct Point {
    double xCoord = 0;
    double yCoord = 0;
    std::string pointName = "";

    void showInfoPoint() {
        xCoord = readInput<double>("Input a number for the x-coordinate: ");
        yCoord = readInput<double>("Input a number for the y-coordinate: ");
        
        clearBuffer();
        while (true) {
            std::cout << "Enter a name for your point: ";
            std::getline(std::cin, pointName);
            if (isNameValid(pointName)) break;
            std::cout << "Please enter a valid name.\n";
        }
        std::cout << "You defined your point as: " << pointName << "(" << xCoord << "," << yCoord << ").\n";
    }
};

struct Line {
    double slope = 0;
    double yInter = 0;
    std::string lineName = "";

    void showInfoLine() {
        slope = readInput<double>("Input a number for the slope: ");
        yInter = readInput<double>("Input a number for the y-intercept: ");
        
        clearBuffer();
        while (true) {
            std::cout << "Enter a name for your line: ";
            std::getline(std::cin, lineName);
            if (isNameValid(lineName)) break;
            std::cout << "Please enter a valid name for your line.\n";
        }
        std::cout << getLineEquation(slope, yInter, lineName) << "\n";
    }
};

bool isOnLine(double a, double b, double x1, double y1) {
    return isZero(a * x1 + b - y1);
}

std::string parLineThroughPoint(double a, double b, double x1, double y1) {
    double yIntercept = y1 - a * x1;
    return getLineEquation(a, yIntercept);
}

std::string perpLineThroughPoint(double a, double b, double x1, double y1) {
    if (isOnLine(a, b, x1, y1)) {
        if (isZero(a)) {
            std::ostringstream oss;
            oss << "x=" << x1;
            return oss.str();
        }
        double slope = -1.0 / a;
        return getLineEquation(slope, y1 - slope * x1);
    }
    return "Given point does not lie on your line.";
}

std::string intersectionOfLines(double a, double b, double p, double q) {
    if (areEqual(a, p)) return "Given lines are parallel.";
    double intersectX = (q - b) / (a - p);
    double intersectY = p * intersectX + q;
    std::ostringstream oss;
    oss << "Functions intersect at (" << intersectX << "," << intersectY << ").";
    return oss.str();
}

bool isTriangleIsosceles(double x1, double y1, double x2, double y2, double x3, double y3) {
    double lenSq1 = std::pow(x3 - x1, 2) + std::pow(y3 - y1, 2);
    double lenSq2 = std::pow(x3 - x2, 2) + std::pow(y3 - y2, 2);
    return areEqual(std::sqrt(lenSq1), std::sqrt(lenSq2));
}

std::string eqPerpBisector(double x1, double y1, double x2, double y2) {
    if (areEqual(x1, x2)) {
        std::ostringstream oss;
        oss << "y=" << (y1 + y2) / 2.0;
        return oss.str();
    }
    if (areEqual(y1, y2)) {
        std::ostringstream oss;
        oss << "x=" << (x1 + x2) / 2.0;
        return oss.str();
    }
    
    double slope = -(x2 - x1) / (y2 - y1);
    double midX = (x1 + x2) / 2.0;
    double midY = (y1 + y2) / 2.0;
    return getLineEquation(slope, midY - slope * midX);
}

bool areCollinear(double x1, double y1, double x2, double y2, double x3, double y3) {
    return isZero(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)); 
}

std::string eqMedian(double x1, double y1, double x2, double y2, double x3, double y3) {
    if (areCollinear(x1, y1, x2, y2, x3, y3)) return "The points you entered are collinear.";
    
    double midX = (x1 + x2) / 2.0;
    double midY = (y1 + y2) / 2.0;

    if (areEqual(x3, midX)) {
        std::ostringstream oss;
        oss << "x=" << x3;
        return oss.str();
    }
    
    double slope = (y3 - midY) / (x3 - midX);
    return getLineEquation(slope, y3 - slope * x3);
}

std::string eqAltitude(double x1, double y1, double x2, double y2, double x3, double y3) {
    if (areCollinear(x1, y1, x2, y2, x3, y3)) return "The points you entered are collinear.";
    
    if (areEqual(y1, y2)) {
        std::ostringstream oss;
        oss << "x=" << x3;
        return oss.str();
    }
    if (areEqual(x1, x2)) {
        std::ostringstream oss;
        oss << "y=" << y3;
        return oss.str();
    }
    
    double slope = -(x2 - x1) / (y2 - y1);
    return getLineEquation(slope, y3 - slope * x3);
}

std::string tangentToParAtPoint(double a, double b, double c, double x1, double y1) {
    if (!isZero(a * x1 * x1 + b * x1 + c - y1)) return "The given point does not lie on the parabola";
    
    double slope = 2.0 * a * x1 + b;
    return getLineEquation(slope, y1 - slope * x1);
}

void tangentToPar(double a, double b, double c, double x1, double y1) {
    if (!isZero(y1)) {
        std::cout << "The given point does not lie on the x-axis\n";
        return;
    }
    if (isZero(a)) {
        std::cout << "The given function is not a parabola.\n";
        return;
    }

    double parVal = a * std::pow(x1, 2) + b * x1 + c;
    if (isZero(parVal)) {
        std::cout << tangentToParAtPoint(a, b, c, x1, y1) << "\n";
        return;
    }

    double discr = std::pow(a * x1, 2) + a * b * x1 + a * c;
    if (discr < -EPSILON) {
        std::cout << "The point you entered is located between the roots of the parabola and therefore there are no tangent lines.\n";
        return;
    }

    double sqrtDiscr = std::sqrt(discr);
    double tx1 = (a * x1 - sqrtDiscr) / a;
    double ty1 = a * tx1 * tx1 + b * tx1 + c;
    
    double tx2 = (a * x1 + sqrtDiscr) / a;
    double ty2 = a * tx2 * tx2 + b * tx2 + c;

    double slope1 = 2.0 * a * tx1 + b;
    double slope2 = 2.0 * a * tx2 + b;

    std::cout << getLineEquation(slope1, ty1 - tx1 * slope1) << "\n";
    std::cout << getLineEquation(slope2, ty2 - tx2 * slope2) << "\n";
}

std::string intersectionOfLineAndPar(double a, double b, double c, double p, double q) {
    std::ostringstream os;
    if (isZero(a)) {
        if (areEqual(b, p)) return "Given functions do not intersect.";
        os << "x=" << (q - c) / (b - p);
        return os.str();
    }

    double discriminant = std::pow(b - p, 2) - 4.0 * a * (c - q);
    
    if (discriminant > EPSILON) {
        double sqrtDiscr = std::sqrt(discriminant);
        double sol1 = (p - b + sqrtDiscr) / (2.0 * a);
        double sol2 = (p - b - sqrtDiscr) / (2.0 * a);
        os << "Functions intersect at (" << sol1 << "," << p * sol1 + q << ") and ("
           << sol2 << "," << p * sol2 + q << ").";
    } else if (isZero(discriminant)) {
        double sol = (p - b) / (2.0 * a);
        os << "Functions intersect at (" << sol << "," << p * sol + q << ").";
    } else {
        os << "Given functions do not intersect.";
    }
    return os.str();
}

bool doThreeLinesInters(double a, double b, double p, double q, double s, double t) {
    return isZero((q - b) * (p - s) - (a - p) * (t - q));
}

bool doLinesFormQuadr(double a, double b, double p, double q, double s, double t, double m, double n) {
    if (areEqual(a, p) || areEqual(a, s) || areEqual(a, m) || areEqual(p, s) || areEqual(p, m) || areEqual(s, m)) return false;
    
    if (doThreeLinesInters(a, b, p, q, s, t) || doThreeLinesInters(a, b, p, q, m, n) ||
        doThreeLinesInters(p, q, s, t, m, n) || doThreeLinesInters(a, b, m, n, s, t))
        return false;
        
    return true;
}

bool isParallelogram(double a, double p, double s, double m) {
    return (areEqual(a, p) && areEqual(s, m)) || (areEqual(a, s) && areEqual(p, m)) || (areEqual(p, s) && areEqual(a, m));
}

bool isRectangle(double a, double p, double s, double m) {
    if (!isParallelogram(a, p, s, m)) return false;
    return isZero(a * m + 1) || isZero(a * p + 1) || isZero(p * s + 1) || 
           isZero(s * m + 1) || isZero(a * s + 1) || isZero(p * m + 1);
}

bool isTrapezoid(double a, double p, double s, double m) {
    return (areEqual(a, s) && !areEqual(m, p)) || (areEqual(a, m) && !areEqual(s, p)) ||
           (areEqual(a, p) && !areEqual(s, m)) || (areEqual(m, p) && !areEqual(a, s)) ||
           (areEqual(s, p) && !areEqual(a, m)) || (areEqual(s, m) && !areEqual(a, p));
}

void printStartMessage() {
    std::cout << std::string(30, ' ') << "--------========Geometry Tool========--------\n";
    std::cout << "You can:\n\n";
    std::cout << (char)254 << " Check whether a point lies on a given line; (1)\n\n";
    std::cout << (char)254 << " Find line that passes through a given point and is parallel to a given line; (2)\n\n";
    std::cout << (char)254 << " Find line that passes through a given point and is perpendicular to a given line; (3)\n\n";
    std::cout << (char)254 << " Find intersection point of two given lines; (4)\n\n";
    std::cout << (char)254 << " Find equations of the altitudes, medians and perpendicular bisectors of a triangle; (5)\n\n";
    std::cout << (char)254 << " Find equation of tangent line to a parabola through a point from the x-axis; (6)\n\n";
    std::cout << (char)254 << " Find the intersection points of parabola and line; (7)\n\n";
    std::cout << (char)254 << " Find type of quadrilateral given four lines; (8)\n\n";
    std::cout << "Note: Lines are in slope-intercept form (y=ax+b). Enter a number between 1 and 8 to get started: ";
}

void executeGeometryTool() {
    std::cout << "Welcome to my GeometryTool program! Would you like to proceed? Y/N: ";
    std::string ans;
    std::cin >> ans;

    while (ans == "y" || ans == "Y") {
        #ifdef _WIN32
            system("cls");
        #endif
        printStartMessage();
        
        int choice = readInput<int>("");
        
        #ifdef _WIN32
            system("cls");
        #endif

        switch (choice) {
            case 1: {
                Line l; Point p; l.showInfoLine(); std::cout << "\n"; p.showInfoPoint();
                if (isOnLine(l.slope, l.yInter, p.xCoord, p.yCoord)) std::cout << p.pointName << " lies on " << l.lineName << ".\n";
                else std::cout << p.pointName << " does not lie on \"" << l.lineName << "\".\n";
                break;
            }
            case 2: {
                Line l; Point p; l.showInfoLine(); std::cout << "\n"; p.showInfoPoint();
                if (isOnLine(l.slope, l.yInter, p.xCoord, p.yCoord)) std::cout << "Given point lies on the line.\n";
                else std::cout << "Parallel line: " << parLineThroughPoint(l.slope, l.yInter, p.xCoord, p.yCoord) << "\n";
                break;
            }
            case 3: {
                Line l; Point p; l.showInfoLine(); std::cout << "\n"; p.showInfoPoint();
                std::cout << perpLineThroughPoint(l.slope, l.yInter, p.xCoord, p.yCoord) << "\n";
                break;
            }
            case 4: {
                Line l1, l2; l1.showInfoLine(); std::cout << "\nDefine second line (y=px+q):\n"; l2.showInfoLine();
                std::cout << intersectionOfLines(l1.slope, l1.yInter, l2.slope, l2.yInter) << "\n";
                break;
            }
            case 5: {
                Point p1, p2, p3; p1.showInfoPoint(); p2.showInfoPoint(); p3.showInfoPoint();
                if (areCollinear(p1.xCoord, p1.yCoord, p2.xCoord, p2.yCoord, p3.xCoord, p3.yCoord)) {
                    std::cout << "The points you entered are collinear.\n";
                } else {
                    std::cout << "\nMedians:\n" << eqMedian(p1.xCoord, p1.yCoord, p2.xCoord, p2.yCoord, p3.xCoord, p3.yCoord) << "\n"
                              << eqMedian(p2.xCoord, p2.yCoord, p3.xCoord, p3.yCoord, p1.xCoord, p1.yCoord) << "\n"
                              << eqMedian(p3.xCoord, p3.yCoord, p1.xCoord, p1.yCoord, p2.xCoord, p2.yCoord) << "\n";
                    std::cout << "Altitudes:\n" << eqAltitude(p1.xCoord, p1.yCoord, p2.xCoord, p2.yCoord, p3.xCoord, p3.yCoord) << "\n"
                              << eqAltitude(p2.xCoord, p2.yCoord, p3.xCoord, p3.yCoord, p1.xCoord, p1.yCoord) << "\n"
                              << eqAltitude(p3.xCoord, p3.yCoord, p1.xCoord, p1.yCoord, p2.xCoord, p2.yCoord) << "\n";
                    std::cout << "Perpendicular Bisectors:\n" << eqPerpBisector(p1.xCoord, p1.yCoord, p2.xCoord, p2.yCoord) << "\n"
                              << eqPerpBisector(p1.xCoord, p1.yCoord, p3.xCoord, p3.yCoord) << "\n"
                              << eqPerpBisector(p2.xCoord, p2.yCoord, p3.xCoord, p3.yCoord) << "\n";
                }
                break;
            }
            case 6: {
                Point p; p.showInfoPoint();
                double a = readInput<double>("Define parabola (ax^2+bx+c)\na: ");
                double b = readInput<double>("b: ");
                double c = readInput<double>("c: ");
                tangentToPar(a, b, c, p.xCoord, p.yCoord);
                break;
            }
            case 7: {
                Line l; l.showInfoLine();
                double m = readInput<double>("Define parabola (mx^2+nx+p)\nm: ");
                double n = readInput<double>("n: ");
                double p = readInput<double>("p: ");
                std::cout << intersectionOfLineAndPar(m, n, p, l.slope, l.yInter) << "\n";
                break;
            }
            case 8: {
                Line l1, l2, l3, l4;
                l1.showInfoLine(); l2.showInfoLine(); l3.showInfoLine(); l4.showInfoLine();
                if (doLinesFormQuadr(l1.slope, l1.yInter, l2.slope, l2.yInter, l3.slope, l3.yInter, l4.slope, l4.yInter)) {
                    if (isParallelogram(l1.slope, l2.slope, l3.slope, l4.slope)) {
                        if (isRectangle(l1.slope, l2.slope, l3.slope, l4.slope)) std::cout << "Given lines form a rectangle.\n";
                        else std::cout << "Given lines form a parallelogram.\n";
                    } else if (isTrapezoid(l1.slope, l2.slope, l3.slope, l4.slope)) {
                        std::cout << "Given lines form a trapezoid.\n";
                    } else {
                        std::cout << "Given lines form a general quadrilateral.\n";
                    }
                } else {
                    std::cout << "Given lines do not form a quadrilateral.\n";
                }
                break;
            }
            default:
                std::cout << "Invalid input. Must be between 1 and 8.\n";
                break;
        }
        
        std::cout << "\nWould you like to run the program again? Y/N: ";
        std::cin >> ans;
    }
    
    #ifdef _WIN32
        system("cls");
    #endif
    std::cout << "Thank you for using my program.\n";
}

int main() {
    executeGeometryTool();
    return 0;
}

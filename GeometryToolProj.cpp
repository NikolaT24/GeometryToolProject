#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <cstring>

const std::size_t MAX_SIZE = 64; //maximum name length of points and lines

const double EPSILON = 1e-6;

//function to compare double values
double myFabs(double num) {
	return num - 0 > EPSILON ? num : -num;
}

//function to improve the outcome of the equation of a line
std::string stylizeLine(double a, double b) {
	std::ostringstream oss;
	if (myFabs(a) < EPSILON) {
		oss << "y=" << b;
		return oss.str();
	}
	else if (myFabs(a + 1.0) < EPSILON) {
		if (myFabs(b) < EPSILON)
			return "y=-x";
		if (b > 0) {
			oss << "y=" << "-x+" << b;
			return oss.str();
		}
		else {
			oss << "y=" << "-x" << b;
			return oss.str();
		}
	}
	else if (myFabs(a - 1.0) < EPSILON) {
		if (b > 0) {
			oss << "y=" << "x+" << b;
			return oss.str();
		}
		else if (myFabs(b) < EPSILON)
			return "y=x";
		else {
			oss << "y=" << "x" << b;
			return oss.str();
		}
	}
	else {
		if (b > 0) {
			oss << "y=" << a << "x+" << b;
			return oss.str();
		}
		else if (myFabs(b) < EPSILON) {
			oss << "y=" << a << "x";
			return oss.str();
		}
		else {
			oss << "y=" << a << "x" << b;
			return oss.str();
		}
	}
}

//function to improve the outcome of the equation of a line that you can give a name to
std::string stylizeLineWithName(double a, double b, char name[MAX_SIZE]) {
	std::ostringstream oss;
	if (myFabs(a) < EPSILON) {
		oss << "Your line " << '\"' << name << '\"' << " is defined as: " << "y=" << b;
		return oss.str();
	}
	else if (myFabs(a + 1.0) < EPSILON) {
		if (myFabs(b) < EPSILON) {
			oss << "Your line " << '\"' << name << '\"' << " is defined as: " << "y=-x";
			return oss.str();
		}
		else if (b > 0) {
			oss << "Your line " << '\"' << name << '\"' << " is defined as: " << "y=" << "-x+" << b;
			return oss.str();
		}
		else {
			oss << "Your line " << '\"' << name << '\"' << " is defined as: " << "y=" << "-x" << b;
			return oss.str();
		}
	}
	else if (myFabs(a - 1.0) < EPSILON) {
		if (b > 0) {
			oss << "Your line " << '\"' << name << '\"' << " is defined as : " << "y=" << "x+" << b;
			return oss.str();
		}
		else if (myFabs(b) < EPSILON) {
			oss << "Your line " << '\"' << name << '\"' << " is defined as: y=x";
			return oss.str();
		}
		else {
			oss << "Your line " << '\"' << name << '\"' << " is defined as: " << "y=" << "x" << b;
			return oss.str();
		}
	}
	else {
		if (b > 0) {
			oss << "Your line " << '\"' << name << '\"' << " is defined as: " << "y=" << a << "x+" << b;
			return oss.str();
		}
		else if (myFabs(b) < EPSILON) {
			oss << "Your line " << '\"' << name << '\"' << " is defined as: " << "y=" << a << "x";
			return oss.str();
		}
		else {
			oss << "Your line " << '\"' << name << '\"' << " is defined as: " << "y=" << a << "x" << b;
			return oss.str();
		}
	}
}

//checks whether point (x1,y1) lies on y=ax+b
bool isOnLine(double a, double b, double x1, double y1) {
	if (myFabs(a * x1 + b - y1) < EPSILON)
		return true;
	else
		return false;
}

std::string parLineThroughPoint(double a, double b, double x1, double y1) {
	double slope = a;
	double yIntercept = y1 - slope * x1;
	std::ostringstream oss;
	if (myFabs(a) < EPSILON) {
		oss << "y=" << y1;
		return oss.str();
	}
	return stylizeLine(slope, yIntercept);
}

std::string perpLineThroughPoint(double a, double b, double x1, double y1) {
	double slope = -1.0 / a;
	double yIntercept = y1 - slope * x1;
	std::ostringstream oss;
	if (myFabs(y1 - a * x1 - b) < EPSILON) {
		if (myFabs(a) < EPSILON) {
			oss << "x=" << x1;
			return oss.str();
		}
		else
			return stylizeLine(slope, yIntercept);
	}
	else
		return "Given point does not lie on your line.";
}

//function to find the solutions to the equation ax+b=px+q
std::string intersectionOfLines(double a, double b, double p, double q) {
	double intersect = (q - b) / (a - p);
	std::ostringstream oss;
	if (myFabs(a - b) < EPSILON)
		return "Given lines are parallel.";
	else {
		oss << "Functions intersect at (" << intersect << "," << p * intersect + q << ").";
		return oss.str();
	}
}

bool isTriangleIsosceles(double x1, double y1, double x2, double y2, double x3, double y3) {
	//checking whether vectors (x3-x1,y3-y1) and (x3-x2,y3-y2) have the same length
	double firstSideLen = std::sqrt(std::pow((x3 - x1), 2) + std::pow((y3 - y1), 2));
	double secondSideLen = std::sqrt(std::pow((x3 - x2), 2) + std::pow((y3 - y2), 2));
	if (myFabs(firstSideLen - secondSideLen) < EPSILON)
		return true;
	return false;
}

std::string eqPerpBisector(double x1, double y1, double x2, double y2) {
	double slope = (x1 - x2) / (y2 - y1);
	double yIntercept = 0.5 * (y1 + y2) - (slope) * 0.5 * (x1 + x2);
	std::ostringstream oss;
	if (myFabs(x1 - x2) < EPSILON) { //case when given line is parallel to the x-axis
		oss << "y=" << (y1 + y2) / 2.0;
		return oss.str();
	}
	if (myFabs(y1 - y2) < EPSILON) { //case when given line is parallel to the y-axis
		oss << "x=" << (x1 + x2) / 2.0;
		return oss.str();
	}
	else
		return stylizeLine(slope, yIntercept);
}

//function to check whether three points are collinear
bool areCollinear(double x1, double y1, double x2, double y2, double x3, double y3) {
	double slope = (y3 - y1) / (x3 - x1);
	double yIntercept = y3 - slope * x3;
	if (myFabs(slope * x2 + y3 - x3 * slope - y2) < EPSILON || (myFabs(x3 - x1) < EPSILON && myFabs(x2 - x1) < EPSILON))
		return true;
	return false;
}

std::string eqMedian(double x1, double y1, double x2, double y2, double x3, double y3) {
	double slope = (2.0 * y3 - y1 - y2) / (2.0 * x3 - x1 - x2);
	double yIntercept = y3 - slope * x3;
	if (!areCollinear(x1, y1, x2, y2, x3, y3)) {
		if (myFabs(2.0 * x3 - x1 - x2) < EPSILON) {
			std::ostringstream oss;
			oss << "x=" << x3;
			return oss.str();
		}
		else if (isTriangleIsosceles(x1, y1, x2, y2, x3, y3))
			return eqPerpBisector(x1, y1, x2, y2);
		else
			return stylizeLine(slope, yIntercept);
	}
	else
		return "The points you entered are collinear.";
}

std::string eqAltitude(double x1, double y1, double x2, double y2, double x3, double y3) {
	double slope = (x1 - x2) / (y2 - y1);
	double yIntercept = y3 - slope * x3;
	std::ostringstream oss;
	if (!areCollinear(x1, y1, x2, y2, x3, y3)) {
		if (myFabs(x1 - x2) < EPSILON) {
			oss << "y=" << (y1 + y2) / 2.0;
			return oss.str();
		}
		if (myFabs(y1 - y2) < EPSILON) {
			oss << "x=" << (x1 + x2) / 2.0;
			return oss.str();
		}
		if (isTriangleIsosceles(x1, y1, x2, y2, x3, y3))
			return eqPerpBisector(x1, y1, x2, y2);
		else
			return stylizeLine(slope, yIntercept);
	}
	else
		return "The points you entered are collinear.";
}

bool isNameValid(char* name) {
	while (*name) {
		bool isSymValid = false;
		if ((*name >= 'a' && *name <= 'z') || (*name >= 'A' && *name <= 'Z') || (*name >= '0' && *name <= '9') || *name == '_')
			isSymValid = true;
		if (!isSymValid)
			return false;
		name++;
	}
	return true;
}

void ignoreLine() {
	std::cin.clear();
	std::cin.ignore();
}

struct Point {
	double xCoord = 0;
	double yCoord = 0;
	char pointName[MAX_SIZE] = {};
	void getPointX() {
		std::cout << "Input a number for the x-coordinate: ";
		std::cin >> xCoord;
		while (std::cin.fail()) {
			ignoreLine();
			std::cout << "Please enter a valid number: ";
			std::cin >> xCoord;
		}
	}
	void getPointY() {
		std::cout << "Input a number for the y-coordinate: ";
		std::cin >> yCoord;
		while (std::cin.fail()) {
			ignoreLine();
			std::cout << "Please enter a valid number: ";
			std::cin >> yCoord;
		}
	}
	void getPointName() {
		std::cin.ignore();
		std::cout << "Enter a name for your point: ";
		std::cin.getline(pointName, MAX_SIZE);
		while (!isNameValid(pointName)) {
			std::cout << "Please enter a valid name: ";
			std::cin >> pointName;
		}
		std::cout << "You defined your point as: " << pointName << "(" << xCoord << "," << yCoord << "). ";
	}
	void showInfoPoint() {
		getPointX();
		getPointY();
		getPointName();
	}
};

//displays the equation of tangent line to a parabola through a point from the parabola
std::string tangentToParAtPoint(double a, double b, double c, double x1, double y1) {
	double slope = 2.0 * a * x1 + b;
	double yIntercept = y1 - 2.0 * a * x1 * x1 - b * x1;
	if (myFabs(a * x1 * x1 + b * x1 + c - y1) < EPSILON)
		return stylizeLine(slope, yIntercept);
	else
		return "The given point does not lie on the parabola";
}

bool isOnXAxis(double x, double y) {
	if (myFabs(y) < EPSILON)
		return true;
	return false;
}

//displays equation(s) of tangent line(s) to a parabola through a point from the x-axis
void tangentToPar(double a, double b, double c, double x1, double y1) {
	double discr = std::pow(a, 2) * std::pow(x1, 2) + a * b * x1 + c; //discriminant of obtained quadratic
	double tangentPointX1 = (a * x1 - std::sqrt(discr)) / a;
	double tangentPointY1 = -2.0 * x1 * (std::sqrt(discr) - b) - b * std::sqrt(discr) / a + 2.0 * a * std::pow(x1, 2) + 2.0 * c;
	double tangentPointX2 = (a * x1 + std::sqrt(discr)) / a;
	double tangentPointY2 = 2.0 * x1 * (std::sqrt(discr) + b) + b * std::sqrt(discr) / a + 2.0 * a * std::pow(x1, 2) + 2.0 * c;
	double slope1 = 2.0 * a * tangentPointX1 + b;
	double yIntercept1 = tangentPointY1 - tangentPointX1 * slope1;
	double slope2 = 2.0 * a * tangentPointX2 + b;
	double yIntercept2 = tangentPointY2 - tangentPointX2 * slope2;
	if (isOnXAxis(x1, y1)) {
		if (myFabs(a * std::pow(x1, 2) + b * x1 + c) < EPSILON) //case when x1 is a root of the equation ax^2+bx+c=0
			std::cout << tangentToParAtPoint(a, b, c, x1, y1);
		else {
			if (std::pow(a, 2) * std::pow(x1, 2) + a * b * x1 + a * c < 0) //case when x1 lies between the roots of the parabola
				std::cout << "The point you entered is located between the roots of the parabola and therefore there are no tangent lines.";
			else if (myFabs(a) < EPSILON)
				std::cout << "The given function is not a parabola.";
			else {
				std::cout << stylizeLine(slope1, yIntercept1) << std::endl;
				std::cout << stylizeLine(slope2, yIntercept2);
			}
		}
	}
	else
		std::cout << "The given point does not lie on the x-axis";
}

//function to find the solutions of the equation ax^2+bx+c=px+q
std::string intersectionOfLineAndPar(double a, double b, double c, double p, double q) {
	std::ostringstream os;
	double discriminant = std::sqrt(std::pow(b - p, 2) - 4.0 * a * (c - q));
	double firstSol = 0.5 * (p - b + discriminant) / a;
	double secondSol = 0.5 * (p - b - discriminant) / a;
	double linearSol = (q - c) / (b - p); // unique solution when a = 0
	double zeroDiscrSol = 0.5 * (p - b) / a; // unique solution when the discriminant is zero
	if (myFabs(a) < EPSILON) {
		if (myFabs(b - p) < EPSILON)
			return "Given functions do not intersect.";
		else {
			os << "x=" << linearSol;
			return os.str();
		}
	}
	else {
		if (discriminant > 0) {
			os << "Functions intersect at (" << firstSol << "," << p * firstSol + q << ") and ("
				<< secondSol << "," << p * secondSol + q << ").";
			return os.str();
		}
		else if (myFabs(discriminant) < EPSILON) {
			os << "Functions intersect at (" << zeroDiscrSol << "," << p * zeroDiscrSol + q << ").";
			return os.str();
		}
		else
			return "Given functions do not intersect.";
	}
}

bool areLinesParallel(double a, double p) {
	if (myFabs(a - p) < EPSILON)
		return true;
	return false;
}

double intersOfLinesX(double a, double b, double p, double q) {
	if (areLinesParallel(a, p))
		return 0;
	else
		return (q - b) / (a - p);
}

double intersOfLinesY(double a, double b, double p, double q) {
	if (areLinesParallel(a, p))
		return 0;
	else
		return a * (q - b) / (a - p) + b;
}

bool doThreeLinesInters(double a, double b, double p, double q, double s, double t) {
	if (myFabs((q - b) * (p - s) - (a - p) * (t - q)) < EPSILON)
		return true;
	else
		return false;
}

bool doLinesFormQuadr(double a, double b, double p, double q, double s, double t, double m, double n) {
	if (((areLinesParallel(m, s) && areLinesParallel(m, p)) ||
		(areLinesParallel(a, m) && areLinesParallel(a, p)) ||
		(areLinesParallel(a, p) && areLinesParallel(a, s))) &&
		doThreeLinesInters(a, b, p, q, s, t) || doThreeLinesInters(a, b, p, q, m, n) ||
		doThreeLinesInters(p, q, s, t, m, n) || doThreeLinesInters(a, b, m, n, s, t))
		return false;
	return true;
}

bool isParallelogram(double a, double b, double p, double q, double s, double t, double m, double n) {
	if ((myFabs(a - p) < EPSILON && myFabs(s - m) < EPSILON) ||
		(myFabs(a - s) < EPSILON && myFabs(p - m) < EPSILON) ||
		(myFabs(p - s) < EPSILON && myFabs(a - m) < EPSILON))
		return true;
	else
		return false;
}

bool isRectangle(double a, double b, double p, double q, double s, double t, double m, double n) {
	if (isParallelogram(a, b, p, q, s, t, m, n)) {
		if (myFabs(a * m + 1) < EPSILON || myFabs(a * p + 1) < EPSILON || myFabs(p * s + 1) < EPSILON ||
			myFabs(s * m + 1) < EPSILON || myFabs(a * s + 1) < EPSILON || myFabs(p * m + 1) < EPSILON)
			return true;
		return false;
	}
	else
		return false;
}

bool isTrapezoid(double a, double b, double p, double q, double s, double t, double m, double n) {
	if ((myFabs(a - s) < EPSILON && !(myFabs(m - p) < EPSILON)) ||
		(myFabs(a - m) < EPSILON && !(myFabs(s - p) < EPSILON)) ||
		(myFabs(a - p) < EPSILON && !(myFabs(s - m) < EPSILON)) ||
		(myFabs(m - p) < EPSILON && !(myFabs(a - s) < EPSILON)) ||
		(myFabs(s - p) < EPSILON && !(myFabs(a - m) < EPSILON)) ||
		(myFabs(s - m) < EPSILON && !(myFabs(a - p) < EPSILON)))
		return true;
	else
		return false;
}

void printStartMessage() {
	std::cout << "You can:" << std::endl;
	std::cout << std::endl;
	std::cout << (char)254 << " Check whether a point lies on a given line; (1)\n";
	std::cout << std::endl;
	std::cout << (char)254 << " Find line that passes through a given point and is parallel to a given line; (2)\n";
	std::cout << std::endl;
	std::cout << (char)254 << " Find line that passes through a given point and is perpendicular to a given line; (3)\n";
	std::cout << std::endl;
	std::cout << (char)254 << " Find intersection point of two given lines; (4)\n";
	std::cout << std::endl;
	std::cout << (char)254 << " Find equations of the altitudes, medians and perpendicular bisectors of a triangle given the coordinates of its vertices; (5)\n";
	std::cout << std::endl;
	std::cout << (char)254 << " Find equation of tangent line to a parabola through a point from the x-axis; (6)\n";
	std::cout << std::endl;
	std::cout << (char)254 << " Find the intersection points of parabola and line; (7)\n";
	std::cout << std::endl;
	std::cout << (char)254 << " Find type of quadrilateral given four lines; (8)\n";
	std::cout << std::endl;
	std::cout << "You can also give names to the lines and points you define. Note that the lines are in slope-intercept form (y=ax+b). Enter a number between 1 and 8 to get started: ";
}

class Line {
public:
	double slope = 0;
	double yInter = 0;
	char lineName[MAX_SIZE] = {};
	void getLineSlope() {
		std::cout << "Input a number for the slope: ";
		std::cin >> slope;
		while (std::cin.fail()) {
			ignoreLine();
			std::cout << "Please enter a valid number: ";
			std::cin >> slope;
		}
	}
	void getLineYInter() {
		std::cout << "Input a number for the y-intercept: ";
		std::cin >> yInter;
		while (std::cin.fail()) {
			ignoreLine();
			std::cout << "Please enter a valid number: ";
			std::cin >> yInter;
		}
	}
	void getLineName() {
		std::cin.ignore();
		std::cout << "Enter a name for your line: ";
		std::cin.getline(lineName, MAX_SIZE);
		while (!isNameValid(lineName)) {
			std::cout << "Please enter a valid name for your line: ";
			std::cin >> lineName;
		}
	}
	void showInfoLine() {
		getLineSlope();
		getLineYInter();
		getLineName();
		std::cout << stylizeLineWithName(slope, yInter, lineName);
	}
};

//function for (1) from the menu
void printLine() {
	Line yourLine;
	Point yourPoint;
	yourLine.showInfoLine();
	std::cout << std::endl;
	yourPoint.showInfoPoint();
	if (isOnLine(yourLine.slope, yourLine.yInter, yourPoint.xCoord, yourPoint.yCoord))
		std::cout << yourPoint.pointName << " lies on " << yourLine.lineName << ".";
	else
		std::cout << yourPoint.pointName << " does not lie on \"" << yourLine.lineName << "\".";
}

//function for (2) from the menu
void printParLine() {
	Line yourLine;
	Point yourPoint;
	std::cout << "Define your line. ";
	yourLine.showInfoLine();
	std::cout << std::endl;
	std::cout << "Define your point. ";
	yourPoint.showInfoPoint();
	if (isOnLine(yourLine.slope, yourLine.yInter, yourPoint.xCoord, yourPoint.yCoord))
		std::cout << "Given point lies on the line.";
	else {
		std::cout << "The equation of a parallel line to \"" << yourLine.lineName << "\" through " << yourPoint.pointName <<
			" is " << parLineThroughPoint(yourLine.slope, yourLine.yInter, yourPoint.xCoord, yourPoint.yCoord) << ".";
	}
}

//function for (3) from the menu
void printPerpLine() {
	Line yourLine;
	Point yourPoint;
	yourLine.showInfoLine();
	std::cout << std::endl;
	yourPoint.showInfoPoint();
	if (isOnLine(yourLine.slope, yourLine.yInter, yourPoint.xCoord, yourPoint.yCoord))
		std::cout << "The equation of a perpendicular line to \"" << yourLine.lineName << "\" that passes through " << yourPoint.pointName <<
		" is " << perpLineThroughPoint(yourLine.slope, yourLine.yInter, yourPoint.xCoord, yourPoint.yCoord) << ".";
	else
		std::cout << "Given point does not lie on your line.";
}

//function for (4) from the menu
void printLineInters() {
	Line firstLine, secondLine;
	firstLine.showInfoLine();
	std::cout << std::endl;
	std::cout << "Define your second line y=px+q." << std::endl;
	std::cout << "Input a number for \"p\": ";
	std::cin >> secondLine.slope;
	std::cout << "Input a number for \"q\": ";
	std::cin >> secondLine.yInter;
	std::cin.ignore();
	std::cout << "Enter a name for your line: ";
	std::cin.getline(secondLine.lineName, MAX_SIZE);
	std::cout << stylizeLineWithName(secondLine.slope, secondLine.yInter, secondLine.lineName) << ". ";
	std::cout << intersectionOfLines(firstLine.slope, firstLine.yInter, secondLine.slope, secondLine.yInter);
}

//function for (5) from the menu
void printTriangleObj() {
	Point fiVer, seVer, thVer; //short for "vertice"
	std::cout << "Define the first vertice of your triangle. ";
	fiVer.showInfoPoint();
	std::cout << "Define the second vertice of your triangle. ";
	seVer.showInfoPoint();
	std::cout << "Define the third vertice of your triangle. ";
	thVer.showInfoPoint();
	system("cls");
	if (areCollinear(fiVer.xCoord, fiVer.yCoord, seVer.xCoord, seVer.yCoord, thVer.xCoord, thVer.yCoord))
		std::cout << "The points you entered are collinear.";
	else {
		std::cout << "You defined your triangle with vertices " << fiVer.pointName << "(" << fiVer.xCoord << "," << fiVer.yCoord << "), " <<
			seVer.pointName << "(" << seVer.xCoord << "," << seVer.yCoord << ") and " << thVer.pointName << "(" << thVer.xCoord << "," <<
			thVer.yCoord << ")." << "\n";
		std::cout << "The equations of the medians of your triangle are" << "\n";
		std::cout << eqMedian(fiVer.xCoord, fiVer.yCoord, seVer.xCoord, seVer.yCoord, thVer.xCoord, thVer.yCoord) << "\n";
		std::cout << eqMedian(seVer.xCoord, seVer.yCoord, thVer.xCoord, thVer.yCoord, fiVer.xCoord, fiVer.yCoord) << "\n";
		std::cout << eqMedian(thVer.xCoord, thVer.yCoord, fiVer.xCoord, fiVer.yCoord, seVer.xCoord, seVer.yCoord) << "\n";
		std::cout << "The equations of the altitudes of your triangle are" << "\n";
		std::cout << eqAltitude(fiVer.xCoord, fiVer.yCoord, seVer.xCoord, seVer.yCoord, thVer.xCoord, thVer.yCoord) << "\n";
		std::cout << eqAltitude(seVer.xCoord, seVer.yCoord, thVer.xCoord, thVer.yCoord, fiVer.xCoord, fiVer.yCoord) << "\n";
		std::cout << eqAltitude(thVer.xCoord, thVer.yCoord, fiVer.xCoord, fiVer.yCoord, seVer.xCoord, seVer.yCoord) << "\n";
		std::cout << "The equations of the perpendicular bisectors of your triangle are" << "\n";
		std::cout << eqPerpBisector(fiVer.xCoord, fiVer.yCoord, seVer.xCoord, seVer.yCoord) << "\n";
		std::cout << eqPerpBisector(fiVer.xCoord, fiVer.yCoord, thVer.xCoord, thVer.yCoord) << "\n";
		std::cout << eqPerpBisector(seVer.xCoord, seVer.yCoord, thVer.xCoord, thVer.yCoord) << "\n";
	}
}

//function for (6) from the menu
void printTangent() {
	double a, b, c;
	Point yourPoint;
	yourPoint.showInfoPoint();
	std::cout << "Define your parabola (ax^2+bx+c). Input a value for \"a\": ";
	std::cin >> a;
	while (std::cin.fail()) {
		ignoreLine();
		std::cout << "Please enter a valid number: ";
		std::cin >> a;
	}
	std::cout << "Input a value for \"b\": ";
	std::cin >> b;
	while (std::cin.fail()) {
		ignoreLine();
		std::cout << "Please enter a valid number: ";
		std::cin >> b;
	}
	std::cout << "Input a value for \"c\": ";
	std::cin >> c;
	while (std::cin.fail()) {
		ignoreLine();
		std::cout << "Please enter a valid number: ";
		std::cin >> c;
	}
	std::cout << "The tangent lines to the given parabola through " << yourPoint.pointName << " are:" << std::endl;
	tangentToPar(a, b, c, yourPoint.xCoord, yourPoint.yCoord);
}

//function for (7) from the menu
void findSolution() {
	double m, n, p;
	Line yourLine;
	yourLine.showInfoLine();
	std::cout << ". Define your parabola (mx^2+nx+p). Input a value for \"m\": ";
	std::cin >> m;
	while (std::cin.fail()) {
		ignoreLine();
		std::cout << "Please enter a valid number: ";
		std::cin >> m;
	}
	std::cout << "Input a value for \"n\": ";
	std::cin >> n;
	while (std::cin.fail()) {
		ignoreLine();
		std::cout << "Please enter a valid number: ";
		std::cin >> n;
	}
	std::cout << "Input a value for \"p\": ";
	std::cin >> p;
	while (std::cin.fail()) {
		ignoreLine();
		std::cout << "Please enter a valid number: ";
		std::cin >> p;
	}
	std::cout << intersectionOfLineAndPar(m, n, p, yourLine.slope, yourLine.yInter);
}

//function for (8) from the menu
void determineQuadr() {
	Line l1, l2, l3, l4;
	std::cout << "Define your first line. ";
	l1.showInfoLine();
	std::cout << ". Define your second line. ";
	l2.showInfoLine();
	std::cout << ". Define your third line. ";
	l3.showInfoLine();
	std::cout << ". Define your fourth line. ";
	l4.showInfoLine();
	std::cout << std::endl;
	if (doLinesFormQuadr(l1.slope, l1.yInter, l2.slope, l2.yInter, l3.slope, l3.yInter, l4.slope, l4.yInter)) {
		if (isParallelogram(l1.slope, l1.yInter, l2.slope, l2.yInter, l3.slope, l3.yInter, l4.slope, l4.yInter)) {
			if (isRectangle(l1.slope, l1.yInter, l2.slope, l2.yInter, l3.slope, l3.yInter, l4.slope, l4.yInter))
				std::cout << "Given lines form a rectangle.";
			else
				std::cout << "Given lines form a parallelogram.";
		}
		else {
			if (isTrapezoid(l1.slope, l1.yInter, l2.slope, l2.yInter, l3.slope, l3.yInter, l4.slope, l4.yInter))
				std::cout << "Given lines form a trapezoid.";
		}
	}
	else
		std::cout << "Given lines do not form a quadrilateral.";
}

//function to help stylize the menu
void printSpace() {
	for (int i = 0; i <= 30; i++) {
		std::cout << " ";
	}
}

void executeGeometryTool() {
start:
	printSpace();
	std::cout << "--------========Geometry Tool========--------" << std::endl;
	std::cout << "Welcome to my GeometryTool program! This is a math tool for analytic geometry. Would you like to proceed? Y/N: ";
	std::string startAns = " ";
	std::cin >> startAns;
	if (startAns == "y" || startAns == "Y") {
		while (startAns == "y" || startAns == "Y") {
			system("cls");
			printStartMessage();
			int numChoice = 0;
			std::cin >> numChoice;
			system("cls");
			switch (numChoice) {
			case 1: printLine();
				break;
			case 2: printParLine();
				break;
			case 3: printPerpLine();
				break;
			case 4: printLineInters();
				break;
			case 5: printTriangleObj();
				break;
			case 6: printTangent();
				break;
			case 7: findSolution();
				break;
			case 8: determineQuadr();
				break;
			default: std::cout << "Invalid input. The input must be between 1 and 8. ";
				break;
			}
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "Would you like to run the program again? Y/N: ";
			std::cin >> startAns;
		}
	}
	else if (startAns == "N" || startAns == "n") {
		system("cls");
		std::cout << "Thank you for using my program.";
	}
	else {
		system("cls");
		std::cout << "Invalid input. Would you like to run the program again? Y/N: ";
		std::string invInputAns = " ";
		std::cin >> invInputAns;
		if (invInputAns == "y" || invInputAns == "Y") {
			system("cls");
			goto start;
		}
		else {
			system("cls");
			std::cout << "Thank you for using my program.";
		}
	}
}

int main() {
	executeGeometryTool();
	return 0;
}
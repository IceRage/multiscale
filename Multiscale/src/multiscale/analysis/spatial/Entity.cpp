#include "multiscale/analysis/spatial/Entity.hpp"
#include "multiscale/util/StringManipulator.hpp"
#include "multiscale/util/Geometry2D.hpp"

using namespace multiscale::analysis;


Entity::Entity(double pileUpDegree, double area, const Point &centre) {
    if (!areValid(pileUpDegree, area, centre))
        throw ERR_INPUT;

    this->pileUpDegree = pileUpDegree;
    this->area = area;
    this->centre = centre;
}

Entity::~Entity() {}

double Entity::getPileUpDegree() const {
    return pileUpDegree;
}

double Entity::getArea() const {
    return area;
}

Point Entity::getCentre() const {
    return centre;
}

string Entity::toString() {
    return StringManipulator::toString<double>(pileUpDegree) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.x) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.y);
}

double Entity::distanceTo(const DataPoint &point) {
    if (typeid(this) != typeid(point))
        throw ERR_DISTANCE;

    return Geometry2D::distanceBtwPoints(this->centre, ((Entity)point).centre);
}

bool Entity::areValid(double pileUpDegree, double area, const Point &centre) {
    return (
        (pileUpDegree > 0) &&
        (area > 0) &&
        ((centre.x > 0) && (centre.y >0))
    );
}

#include "multiscale/analysis/spatial/Cluster.hpp"
#include "multiscale/util/Geometry2D.hpp"
#include "multiscale/util/StringManipulator.hpp"

using namespace multiscale::analysis;


Cluster::Cluster() {
    initialise();
}

Cluster::~Cluster() {}

void Cluster::addEntity(const Entity &entity) {
    entities.push_back(entity);

    updateFlag = true;
}

double Cluster::getClusterednessDegree() const {
    updateMeasuresIfRequired();

    return clusterednessDegree;
}

double Cluster::getPileUpDegree() const {
    updateMeasuresIfRequired();

    return pileUpDegree;
}

double Cluster::getArea() const {
    updateMeasuresIfRequired();

    return area;
}

Shape2D Cluster::getShape() const {
    updateMeasuresIfRequired();

    return shape;
}

Point Cluster::getCentre() const {
    updateMeasuresIfRequired();

    return centre;
}

vector<Entity> Cluster::getEntities() const {
    return entities;
}

string Cluster::toString() {
    return StringManipulator::toString<double>(clusterednessDegree) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(pileUpDegree) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(area) + OUTPUT_SEPARATOR +
           shapeAsString() + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.x) + OUTPUT_SEPARATOR +
           StringManipulator::toString<double>(centre.y);
}

void Cluster::initialise() {
    this->clusterednessDegree = 0;
    this->pileUpDegree = 0;
    this->area = 0;

    this->isTriangularProbability = 0;
    this->isRectangularProbability = 0;
    this->isCircularProbability = 0;

    this->minAreaEnclosingCircleRadius = 0;

    this->shape = Shape2D::Undefined;

    minAreaEnclosingTriangle.clear();
    entities.clear();

    updateFlag = true;
}

vector<Point> Cluster::getEntitiesCentrePoints() {
    vector<Point> centrePoints;

    for (const Entity& entity : entities) {
        centrePoints.push_back(entity.getCentre());
    }

    return centrePoints;
}

void Cluster::updateMeasuresIfRequired() {
    if (updateFlag) {
        updateMeasures();

        updateFlag = false;
    }
}

void Cluster::updateMeasures() {
    if (entities.size() > 0) {
        updatePileUpDegree();
        updateArea();
        updateClusterednessDegree();
        updateShape();
        updateCentrePoint();
    }
}

void Cluster::updateClusterednessDegree() {
    clusterednessDegree = 0;

    for (const Entity &e1 : entities) {
        double avgDistance = 0;

        for (const Entity &e2 : entities) {
            avgDistance += e1.distanceTo(e2);
        }

        clusterednessDegree += avgDistance / (entities.size() - 1);
    }

    clusterednessDegree /= (entities.size());
}

void Cluster::updatePileUpDegree() {
    pileUpDegree = 0;

    for (const Entity &entity : entities) {
        pileUpDegree += entity.getPileUpDegree();
    }

    pileUpDegree /= (entities.size());
}

void Cluster::updateArea() {
    area = 0;

    for (const Entity &entity : entities) {
        area += entity.getArea();
    }

    area /= (entities.size());
}

void Cluster::updateShape() {
    triangularProbability = isTriangularProbability();
    rectangularProbability = isRectangularProbability();
    circularProbability = isCircularProbability();

    if (triangularProbability < rectangularProbability) {
        if (rectangularProbability > circularProbability) {
            shape = Shape2D::Rectangle;
        } else {
            shape = Shape2D::Circle;
        }
    } else {
        if (triangularProbability > circularProbability) {
            shape = Shape2D::Triangle;
        } else {
            shape = Shape2D::Circle;
        }
    }
}

void Cluster::updateCentrePoint() {
    centre *= 0;

    for (const Entity &entity : entities) {
        centre += entity.getCentre();
    }

    centre.x /= entities.size();
    centre.y /= entities.size();
}

double Cluster::isTriangularProbability() {
    // TODO: Unimplemented method
    return 1E-10;
}

double Cluster::isRectangularProbability() {
    vector<Point> entitiesCentrePoints = getEntitiesCentrePoints();

    minAreaEnclosingRect = minAreaRect(entitiesCentrePoints);

    // Compute the area of the minimum area enclosing rectangle
    double rectArea = minAreaEnclosingRect.size.height * minAreaEnclosingRect.size.width;

    return (rectArea == 0) ? 0
                           : (area / rectArea);
}

double Cluster::isCircularProbability() {
    vector<Point> entitiesCentrePoints = getEntitiesCentrePoints();

    minEnclosingCircle(entitiesCentrePoints, minAreaEnclosingCircleCentre, minAreaEnclosingCircleRadius);

    // Compute the area of the minimum area enclosing circle
    double circleArea = PI * minAreaEnclosingCircleRadius * minAreaEnclosingCircleRadius;

    return (circleArea == 0) ? 0
                             : (area / circleArea);
}

string Cluster::shapeAsString() {
    switch (shape) {
        case Shape2D::Triangle:
            return STR_TRIANGLE;
            break;

        case Shape2D::Rectangle:
            return STR_RECTANGLE;
            break;

        case Shape2D::Circle:
            return STR_CIRCLE;
            break;

        default:
            throw ERR_UNDEFINED_SHAPE;
            break;
    }
}

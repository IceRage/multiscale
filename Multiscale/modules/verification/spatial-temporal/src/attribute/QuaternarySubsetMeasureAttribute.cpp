#include "multiscale/verification/spatial-temporal/attribute/QuaternarySubsetMeasureAttribute.hpp"

using namespace multiscale::verification;


QuaternarySubsetMeasureType QuaternarySubsetMeasureAttribute::evaluate() const {
    return quaternarySubsetMeasureType;
}

//! Overload the output stream operator for the enumeration
std::ostream& multiscale::verification::operator<<(std::ostream& out, const QuaternarySubsetMeasureType &quaternarySubsetMeasureType) {
    switch (quaternarySubsetMeasureType) {
        case QuaternarySubsetMeasureType::Covar:
            out << "covar";
            break;

        default:
            out << "undefined";
    }

    return out;
}

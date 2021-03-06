#ifndef TEMPORALNUMERICCOLLETIONATTRIBUTE_HPP
#define TEMPORALNUMERICCOLLETIONATTRIBUTE_HPP

#include "multiscale/verification/spatial-temporal/attribute/TemporalNumericMeasureCollectionAttribute.hpp"

#include <boost/fusion/include/adapt_struct.hpp>


namespace multiscale {

    namespace verification {

        // Forward declaration of classes
        class ChangeTemporalNumericCollectionAttribute;
        class HomogeneousHomogeneousTimeSeriesAttribute;
        class TimeSeriesTimeSeriesComponentAttribute;


        //! Variant for the temporal numeric collection attribute
        typedef boost::variant<
            TemporalNumericMeasureCollectionAttribute,
            boost::recursive_wrapper<ChangeTemporalNumericCollectionAttribute>,
            boost::recursive_wrapper<TimeSeriesTimeSeriesComponentAttribute>,
            boost::recursive_wrapper<HomogeneousHomogeneousTimeSeriesAttribute>
        > TemporalNumericCollectionType;


        //! Class for representing a temporal numeric collection attribute
        class TemporalNumericCollectionAttribute {

            public:

                TemporalNumericCollectionType temporalNumericCollection;  /*!< The temporal numeric collection */

        };

    };

};


BOOST_FUSION_ADAPT_STRUCT(
    multiscale::verification::TemporalNumericCollectionAttribute,
    (multiscale::verification::TemporalNumericCollectionType, temporalNumericCollection)
)


#endif

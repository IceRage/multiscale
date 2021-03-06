#ifndef SYMBOLTABLESAUTOGENERATED_HPP
#define SYMBOLTABLESAUTOGENERATED_HPP

/******************************************************************************
 *
 * WARNING! AUTO-GENERATED FILE.
 *
 * PLEASE DO NOT UPDATE THIS FILE MANUALLY. 
 * USE THE PYTHON GENERATOR SCRIPTS FOR ANY MODIFICATIONS.
 *
 *****************************************************************************/
 
#include "multiscale/verification/spatial-temporal/attribute/SpatialMeasureAttribute.hpp"
#include "multiscale/verification/spatial-temporal/attribute/SubsetSpecificAttribute.hpp"

#include <boost/spirit/include/qi_symbols.hpp>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace qi = boost::spirit::qi;


        //! Symbol table and parser for the spatial measure type
        struct SpatialMeasureTypeParser : qi::symbols<char, multiscale::verification::SpatialMeasureType> {

            SpatialMeasureTypeParser() {
                add
                    ("clusteredness"       , SpatialMeasureType::Clusteredness)
                    ("density"             , SpatialMeasureType::Density)
                    ("area"                , SpatialMeasureType::Area)
                    ("perimeter"           , SpatialMeasureType::Perimeter)
                    ("distanceFromOrigin"  , SpatialMeasureType::DistanceFromOrigin)
                    ("angle"               , SpatialMeasureType::Angle)
                    ("triangleMeasure"     , SpatialMeasureType::TriangleMeasure)
                    ("rectangleMeasure"    , SpatialMeasureType::RectangleMeasure)
                    ("circleMeasure"       , SpatialMeasureType::CircleMeasure)
                    ("centroidX"           , SpatialMeasureType::CentroidX)
                    ("centroidY"           , SpatialMeasureType::CentroidY)
                ;
            }

        };

        //! Symbol table and parser for a specific subset type
        struct SubsetSpecificTypeParser : qi::symbols<char, multiscale::verification::SubsetSpecificType> {

            SubsetSpecificTypeParser() {
                add
                    ("clusters" , SubsetSpecificType::Clusters)
                    ("regions"  , SubsetSpecificType::Regions)
                ;
            }

        };

    };

};


#endif
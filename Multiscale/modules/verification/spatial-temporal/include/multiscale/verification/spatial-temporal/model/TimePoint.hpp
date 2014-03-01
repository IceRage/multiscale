#ifndef TIMEPOINT_HPP
#define TIMEPOINT_HPP

#include "multiscale/verification/spatial-temporal/model/Cluster.hpp"
#include "multiscale/verification/spatial-temporal/model/Region.hpp"

#include <limits>
#include <map>
#include <set>
#include <string>


namespace multiscale {

    namespace verification {

        //! Enumeration for representing the considered spatial entity type(s)
        enum class ConsideredSpatialEntityType : int {
            All,        /*!< All */
            Clusters,   /*!< Clusters */
            Regions     /*!< Regions */
        };

        //! Enumeration for representing the set operation type(s)
        enum class SetOperationType : int {
            Difference,     /*!< Set difference */
            Intersection,   /*!< Set intersection */
            Union           /*!< Set union */
        };


        //! Class for representing a timepoint
        class TimePoint {

            private:

                unsigned long value;   /*!< The value of the timepoint within a simulation/experiment */

                std::set<Cluster>  clusters;     /*!< The set of clusters */
                std::set<Region>   regions;      /*!< The set of regions */

                std::map<std::string, double>   numericStateVariables;      /*!< The associative map for storing numeric state variables */

                ConsideredSpatialEntityType consideredSpatialEntityType;    /*!< The considered spatial entity type */

            public:

                TimePoint(unsigned long value = std::numeric_limits<unsigned long>::max());
                TimePoint(const TimePoint &timePoint);
                ~TimePoint();

                //! Get the value of the timepoint
                unsigned long getValue() const;

                //! Set the value of the timepoint
                /*!
                 * \param value The value of the timepoint
                 */
                void setValue(unsigned long value);

                //! Get the considered spatial entity type
                ConsideredSpatialEntityType getConsideredSpatialEntityType();

                //! Set the considered spatial entity type
                /*!
                 * \param consideredSpatialEntityType   The considered type of the spatial entities
                 */
                void setConsideredSpatialEntityType(const ConsideredSpatialEntityType &consideredSpatialEntityType);

                //! Add a cluster to the list of clusters
                /*!
                 * \param cluster The cluster to be added
                 */
                void addCluster(const Cluster &cluster);

                //! Add a region to the list of regions
                /*!
                 * \param region The region to be added
                 */
                void addRegion(const Region &region);

                //! Add a numeric state variable to the map
                /*!
                 * If a numeric state variable with the same name exists then the value
                 * of the existing numeric state variable will be replaced by the provided
                 * new value.
                 *
                 * \param name  The name of the numeric state variable
                 * \param value The value of the numeric state variable
                 */
                void addNumericStateVariable(const std::string &name, double value);

                //! Check if the numeric state variable with the given name exists
                /*!
                 * \param name The name of the numeric state variable
                 */
                bool existsNumericStateVariable(const std::string &name);

                //! Get the set of clusters
                std::set<Cluster> getClusters() const;

                //! Get the set of regions
                std::set<Region> getRegions() const;

                //! Get the value of the numeric state variable with the given name if it exists and throw an exception otherwise
                /*!
                 * \param name The name of the numeric state variable
                 */
                double getNumericStateVariable(const std::string &name) const;

                //! Compute the difference of this timepoint and the given timepoint
                /*! Compute the difference of this timepoint and the given timepoint by taking into account
                 *  the value of consideredSpatialEntityType
                 *
                 * \param timePoint The given timepoint
                 */
                void timePointDifference(const TimePoint &timePoint);

                //! Compute the intersection of this timepoint and the given timepoint
                /*! Compute the intersection of this timepoint and the given timepoint by taking into account
                 *  the value of consideredSpatialEntityType
                 *
                 * \param timePoint The given timepoint
                 */
                void timePointIntersection(const TimePoint &timePoint);

                //! Compute the union of this timepoint and the given timepoint
                /*! Compute the union of this timepoint and the given timepoint by taking into account
                 *  the value of consideredSpatialEntityType
                 *
                 * \param timePoint The given timepoint
                 */
                void timePointUnion(const TimePoint &timePoint);

                //! Remove the cluster from the given position
                /*!
                 * \param position  The position of the cluster to be removed
                 */
                void removeCluster(const std::set<Cluster>::iterator &position);

                //! Remove the region from the given position
                /*!
                 * \param position  The position of the region to be removed
                 */
                void removeRegion(const std::set<Region>::iterator &position);

            private:

                //! Compute the given set operation of this timepoint and the given timepoint considering the given set operation type
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                void timePointSetOperation(const TimePoint &timePoint, const SetOperationType &setOperationType);

                //! Compute the given set operation of this timepoint and the given timepoint considering all spatial entities
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                void timePointSetOperationAll(const TimePoint &timePoint, const SetOperationType &setOperationType);

                //! Compute the given set operation of this timepoint and the given timepoint considering clusters
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                void timePointSetOperationClusters(const TimePoint &timePoint, const SetOperationType &setOperationType);

                //! Compute the given set operation of this timepoint and the given timepoint considering regions
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                void timePointSetOperationRegions(const TimePoint &timePoint, const SetOperationType &setOperationType);

                //! Compute the given set operation of this set of clusters and the one provided by the given timepoint
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                std::set<Cluster> clustersSetOperation(const TimePoint &timePoint, const SetOperationType &setOperationType);

                //! Compute the given set operation of this set of regions and the one provided by the given timepoint
                /*!
                 * \param timePoint         The given timepoint
                 * \param setOperationType  The considered set operation type
                 */
                std::set<Region> regionsSetOperation(const TimePoint &timePoint, const SetOperationType &setOperationType);


                // Constants
                static const std::string ERR_GET_NUMERIC_STATE_VARIABLE_PREFIX;
                static const std::string ERR_GET_NUMERIC_STATE_VARIABLE_SUFFIX;

        };

    };

};

#endif

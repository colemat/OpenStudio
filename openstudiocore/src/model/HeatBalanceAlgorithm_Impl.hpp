/**********************************************************************
 *  Copyright (c) 2008-2014, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef MODEL_HEATBALANCEALGORITHM_IMPL_HPP
#define MODEL_HEATBALANCEALGORITHM_IMPL_HPP

#include "ModelAPI.hpp"
#include "ModelObject_Impl.hpp"

#include <utilities/units/Quantity.hpp>
#include <utilities/units/OSOptionalQuantity.hpp>

namespace openstudio {
namespace model {

namespace detail {

  /** HeatBalanceAlgorithm_Impl is a ModelObject_Impl that is the implementation class for HeatBalanceAlgorithm.*/
  class MODEL_API HeatBalanceAlgorithm_Impl : public ModelObject_Impl {
    Q_OBJECT;

    Q_PROPERTY(std::string algorithm READ algorithm WRITE setAlgorithm RESET resetAlgorithm);
    Q_PROPERTY(bool isAlgorithmDefaulted READ isAlgorithmDefaulted);
    Q_PROPERTY(std::vector<std::string> algorithmValues READ algorithmValues);

    Q_PROPERTY(double surfaceTemperatureUpperLimit READ surfaceTemperatureUpperLimit WRITE setSurfaceTemperatureUpperLimit RESET resetSurfaceTemperatureUpperLimit);
    Q_PROPERTY(openstudio::Quantity surfaceTemperatureUpperLimit_SI READ surfaceTemperatureUpperLimit_SI WRITE setSurfaceTemperatureUpperLimit RESET resetSurfaceTemperatureUpperLimit);
    Q_PROPERTY(openstudio::Quantity surfaceTemperatureUpperLimit_IP READ surfaceTemperatureUpperLimit_IP WRITE setSurfaceTemperatureUpperLimit RESET resetSurfaceTemperatureUpperLimit);
    Q_PROPERTY(bool isSurfaceTemperatureUpperLimitDefaulted READ isSurfaceTemperatureUpperLimitDefaulted);

    Q_PROPERTY(double minimumSurfaceConvectionHeatTransferCoefficientValue READ minimumSurfaceConvectionHeatTransferCoefficientValue WRITE setMinimumSurfaceConvectionHeatTransferCoefficientValue RESET resetMinimumSurfaceConvectionHeatTransferCoefficientValue);
    Q_PROPERTY(openstudio::Quantity minimumSurfaceConvectionHeatTransferCoefficientValue_SI READ minimumSurfaceConvectionHeatTransferCoefficientValue_SI WRITE setMinimumSurfaceConvectionHeatTransferCoefficientValue RESET resetMinimumSurfaceConvectionHeatTransferCoefficientValue);
    Q_PROPERTY(openstudio::Quantity minimumSurfaceConvectionHeatTransferCoefficientValue_IP READ minimumSurfaceConvectionHeatTransferCoefficientValue_IP WRITE setMinimumSurfaceConvectionHeatTransferCoefficientValue RESET resetMinimumSurfaceConvectionHeatTransferCoefficientValue);
    Q_PROPERTY(bool isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted READ isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted);

    Q_PROPERTY(double maximumSurfaceConvectionHeatTransferCoefficientValue READ maximumSurfaceConvectionHeatTransferCoefficientValue WRITE setMaximumSurfaceConvectionHeatTransferCoefficientValue RESET resetMaximumSurfaceConvectionHeatTransferCoefficientValue);
    Q_PROPERTY(openstudio::Quantity maximumSurfaceConvectionHeatTransferCoefficientValue_SI READ maximumSurfaceConvectionHeatTransferCoefficientValue_SI WRITE setMaximumSurfaceConvectionHeatTransferCoefficientValue RESET resetMaximumSurfaceConvectionHeatTransferCoefficientValue);
    Q_PROPERTY(openstudio::Quantity maximumSurfaceConvectionHeatTransferCoefficientValue_IP READ maximumSurfaceConvectionHeatTransferCoefficientValue_IP WRITE setMaximumSurfaceConvectionHeatTransferCoefficientValue RESET resetMaximumSurfaceConvectionHeatTransferCoefficientValue);
    Q_PROPERTY(bool isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted READ isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted);

    // TODO: Add relationships for objects related to this one, but not pointed to by the underlying data.
    //       Such relationships can be generated by the GenerateRelationships.rb script.
   public:
    /** @name Constructors and Destructors */
    //@{

    // constructor
    HeatBalanceAlgorithm_Impl(const IdfObject& idfObject,
                              Model_Impl* model,
                              bool keepHandle);

    // construct from workspace
    HeatBalanceAlgorithm_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                              Model_Impl* model,
                              bool keepHandle);

    // clone copy constructor
    HeatBalanceAlgorithm_Impl(const HeatBalanceAlgorithm_Impl& other,
                              Model_Impl* model,
                              bool keepHandle);

    // virtual destructor
    virtual ~HeatBalanceAlgorithm_Impl() {}

    // return the parent object in the hierarchy
    virtual boost::optional<ParentObject> parent() const;

    // set the parent, child may have to call methods on the parent
    virtual bool setParent(ParentObject& newParent);

    //@}

    /** @name Virtual Methods */
    //@{

    // Get all output variable names that could be associated with this object.
    virtual const std::vector<std::string>& outputVariableNames() const;

    virtual IddObjectType iddObjectType() const;

    //@}
    /** @name Getters */
    //@{

    std::string algorithm() const;

    bool isAlgorithmDefaulted() const;

    double surfaceTemperatureUpperLimit() const;

    Quantity getSurfaceTemperatureUpperLimit(bool returnIP=false) const;

    bool isSurfaceTemperatureUpperLimitDefaulted() const;

    double minimumSurfaceConvectionHeatTransferCoefficientValue() const;

    Quantity getMinimumSurfaceConvectionHeatTransferCoefficientValue(bool returnIP=false) const;

    bool isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const;

    double maximumSurfaceConvectionHeatTransferCoefficientValue() const;

    Quantity getMaximumSurfaceConvectionHeatTransferCoefficientValue(bool returnIP=false) const;

    bool isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const;

    //@}
    /** @name Setters */
    //@{

    bool setAlgorithm(std::string algorithm);

    void resetAlgorithm();

    bool setSurfaceTemperatureUpperLimit(double surfaceTemperatureUpperLimit);

    bool setSurfaceTemperatureUpperLimit(const Quantity& surfaceTemperatureUpperLimit);

    void resetSurfaceTemperatureUpperLimit();

    bool setMinimumSurfaceConvectionHeatTransferCoefficientValue(double minimumSurfaceConvectionHeatTransferCoefficientValue);

    bool setMinimumSurfaceConvectionHeatTransferCoefficientValue(const Quantity& minimumSurfaceConvectionHeatTransferCoefficientValue);

    void resetMinimumSurfaceConvectionHeatTransferCoefficientValue();

    bool setMaximumSurfaceConvectionHeatTransferCoefficientValue(double maximumSurfaceConvectionHeatTransferCoefficientValue);

    bool setMaximumSurfaceConvectionHeatTransferCoefficientValue(const Quantity& maximumSurfaceConvectionHeatTransferCoefficientValue);

    void resetMaximumSurfaceConvectionHeatTransferCoefficientValue();

    //@}
    /** @name Other */
    //@{

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.HeatBalanceAlgorithm");

    std::vector<std::string> algorithmValues() const;
    openstudio::Quantity surfaceTemperatureUpperLimit_SI() const;
    openstudio::Quantity surfaceTemperatureUpperLimit_IP() const;
    openstudio::Quantity minimumSurfaceConvectionHeatTransferCoefficientValue_SI() const;
    openstudio::Quantity minimumSurfaceConvectionHeatTransferCoefficientValue_IP() const;
    openstudio::Quantity maximumSurfaceConvectionHeatTransferCoefficientValue_SI() const;
    openstudio::Quantity maximumSurfaceConvectionHeatTransferCoefficientValue_IP() const;
  };

} // detail

} // model
} // openstudio

#endif // MODEL_HEATBALANCEALGORITHM_IMPL_HPP


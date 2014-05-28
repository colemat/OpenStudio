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

#ifndef RADIANCE_FORWARDTRANSLATOR_HPP
#define RADIANCE_FORWARDTRANSLATOR_HPP

#include "RadianceAPI.hpp"

#include "../model/Model.hpp"
#include "../model/Surface.hpp"
#include "../model/SubSurface.hpp"
#include "../model/ShadingSurface.hpp"
#include "../model/InteriorPartitionSurface.hpp"
#include "../model/Luminaire.hpp"
#include "../model/DaylightingControl.hpp"
#include "../model/IlluminanceMap.hpp"
#include "../model/GlareSensor.hpp"

#include "../utilities/geometry/Point3d.hpp"
#include "../utilities/geometry/Vector3d.hpp"

#include "../utilities/core/Logger.hpp"
#include "../utilities/core/StringStreamLogSink.hpp"

namespace openstudio {
namespace radiance {

  /* Translates OpenStudio Building Model to Radiance simulation input.
  */
  class RADIANCE_API ForwardTranslator{
  public:

    ForwardTranslator();

    /** Translates a Model to radiance format in directory outPath
     */
    std::vector<openstudio::path> translateModel(const openstudio::path& outPath, const openstudio::model::Model& model);

    /** Get warning messages generated by the last translation.
     */
    std::vector<LogMessage> warnings() const;

    /** Get error messages generated by the last translation.
     */
    std::vector<LogMessage> errors() const;

    // for now just implement some functionality and let the Ruby script
    // be the main driver

    /// subtract subsurfaces from surface polygon and return
    /// resulting polygons as vector of Point3dVector, these vertices
    /// will be in absolute coodinates
    static openstudio::Point3dVector getPolygon(const openstudio::model::Surface& surface);

    /// convert subsurface vertices to absolute coodinates
    static openstudio::Point3dVector getPolygon(const openstudio::model::SubSurface& subSurface);

    /// convert shading surface vertices to absolute coodinates
    static openstudio::Point3dVector getPolygon(const openstudio::model::ShadingSurface& shadingSurface);

    /// convert interior partition surface vertices to absolute coodinates
    static openstudio::Point3dVector getPolygon(const openstudio::model::InteriorPartitionSurface& interiorPartitionSurface);

    /// convert luminaire to absolute coodinates
    static openstudio::Point3dVector getPolygon(const openstudio::model::Luminaire& luminaire);

    /// get daylighting control reference point
    static openstudio::Point3d getReferencePoint(const openstudio::model::DaylightingControl& control);
    
    /// get sensor vector
    static openstudio::Vector3d getSensorVector(const openstudio::model::DaylightingControl& control);
    
    /// get view vectors, number is determined by the Number of Daylighting Views parameter
    static openstudio::Vector3dVector getViewVectors(const openstudio::model::DaylightingControl& control);

    /// get glare sensor view vectors, number is determined by the Number of Glare View Vectors parameter
    static openstudio::Vector3dVector getViewVectors(const openstudio::model::GlareSensor& sensor);

   /// get sensor vector
    static openstudio::Vector3d getSensorVector(const openstudio::model::GlareSensor& sensor);
    
     /// get glare sensor reference point
    static openstudio::Point3d getReferencePoint(const openstudio::model::GlareSensor& sensor);

    /// get output illuminance map reference points
    static openstudio::Point3dVector getReferencePoints(const openstudio::model::IlluminanceMap& IlluminanceMap);

    /// get sensor vector, this is the same for all points
    static openstudio::Vector3d getSensorVector(const openstudio::model::IlluminanceMap& IlluminanceMap);

  private:
      static double PI() { return 3.14159265358979323; }
      openstudio::model::Model m_model;

      // create materials library for model, shared for all Spaces
      std::set<std::string> m_radMaterials;
      std::set<std::string> m_radMaterialsDC;

      // materials list for rtcontrib
      std::set<std::string> m_radDCmats;

      // scene files
      std::vector<openstudio::path> m_radSceneFiles;

      // create space geometry, hashes of space name to file contents
      std::map<std::string, std::string> m_radSpaces;
      std::map<std::string, std::string> m_radSensors;
      std::map<std::string, std::string> m_radGlareSensors;
      std::map<std::string, std::string> m_radMaps;
      std::map<std::string, openstudio::Handle> m_radMapHandles;
      std::map<std::string, std::string> m_radViewPoints;
      std::map<std::string, std::string> m_radApertures;

      std::vector<std::string> aperture_headings;

      void siteShadingSurfaceGroups(const openstudio::path &t_radDir, 
          const std::vector<openstudio::model::ShadingSurfaceGroup> &t_radShadingSurfaceGroups,
          std::vector<openstudio::path> &t_outpaths);

      void buildingShadingSurfaceGroups(const openstudio::path &t_radDir, 
          const std::vector<openstudio::model::ShadingSurfaceGroup> &t_radShadingSurfaceGroups,
          std::vector<openstudio::path> &t_outpaths);

      void buildingSpaces(const openstudio::path &t_radDir, 
          const std::vector<openstudio::model::Space> &t_spaces,
          std::vector<openstudio::path> &t_outpaths);
    
    StringStreamLogSink m_logSink;

    REGISTER_LOGGER("openstudio.radiance.ForwardTranslator");

  };

} // radiance
} // openstudio

#endif // RADIANCE_FORWARDTRANSLATOR_HPP

/** @file
    @brief Header

    @date 2015

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

// Copyright 2015 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_DisplayConfiguration_h_GUID_E976C3C5_C76D_4781_6930_A133E598D5B1
#define INCLUDED_DisplayConfiguration_h_GUID_E976C3C5_C76D_4781_6930_A133E598D5B1

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <string>
#include <iostream>
#include <exception>
#include <vector>

namespace osvr {
namespace client {
    class DisplayConfigurationParseException : public std::exception {
      public:
        DisplayConfigurationParseException(const std::string &message)
            : std::exception(), m_message(message) {
            // do nothing
        }

        const char *what() const override { return m_message.c_str(); }

      private:
        const std::string m_message;
    };

    class DisplayConfiguration {
      public:
        enum DisplayMode {
            HORIZONTAL_SIDE_BY_SIDE,
            VERTICAL_SIDE_BY_SIDE,
            FULL_SCREEN
        };

        DisplayConfiguration();
        DisplayConfiguration(const std::string &display_description);

        void parse(const std::string &display_description);

        void print() const;

        /// Read the property information.
        std::string getVendor() const;
        std::string getModel() const;
        std::string getVersion() const;
        std::string getNote() const;
        int getNumDisplays() const;

        int getDisplayTop() const;
        int getDisplayLeft() const;
        int getDisplayWidth() const;
        int getDisplayHeight() const;
        DisplayMode getDisplayMode() const;

        double getVerticalFOV() const;
        double getVerticalFOVRadians() const;
        double getHorizontalFOV() const;
        double getHorizontalFOVRadians() const;
        double getFOVAspectRatio() const;
        double getOverlapPercent() const;

        double getPitchTilt() const;

        double getIPDMeters() const;

        /// Structure holding the information for one eye.
        class EyeInfo {
          public:
            double m_CenterProjX = 0.5;
            double m_CenterProjY = 0.5;
            bool m_rotate180 = false;

            void print() const;
        };

        std::vector<EyeInfo> getEyes() const;

      private:
        struct Resolution {
            int width;
            int height;
            int video_inputs;
            DisplayMode display_mode;
        };

        std::string m_vendor;
        std::string m_model;
        std::string m_version;
        std::string m_note;
        int m_NumDisplays;

        double m_MonocularHorizontalFOV;
        double m_MonocularVerticalFOV;
        double m_OverlapPercent;
        double m_PitchTilt;

        std::vector<Resolution> m_Resolutions;

        /// @name Distortion coefficients
        /// @{
        double k1_red;
        double k1_green;
        double k1_blue;
        /// @}

        // Rendering
        double m_RightRoll;
        double m_LeftRoll;

        // Eyes
        std::vector<EyeInfo> m_eyes;
    };

} // namespace client
} // namespace osvr
#endif // INCLUDED_DisplayConfiguration_h_GUID_E976C3C5_C76D_4781_6930_A133E598D5B1

/* -*- C++ -*-
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2025 Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//---------------------------------------------------------------------------
#ifndef analyzerinfoH
#define analyzerinfoH
//---------------------------------------------------------------------------

#include "config.h"

#include <cstddef>
#include <fstream>
#include <list>
#include <string>

class ErrorMessage;
struct FileSettings;

namespace tinyxml2 {
    class XMLDocument;
};

/// @addtogroup Core
/// @{

/**
 * @brief Analyzer information
 *
 * Store various analysis information:
 * - checksum
 * - error messages
 * - whole program analysis data
 *
 * The information can be used for various purposes. It allows:
 * - 'make' - only analyze TUs that are changed and generate full report
 * - should be possible to add distributed analysis later
 * - multi-threaded whole program analysis
 */
class CPPCHECKLIB AnalyzerInformation {
public:
    friend class TestAnalyzerInformation;

    ~AnalyzerInformation();

    static std::string getFilesTxt(const std::list<std::string> &sourcefiles, const std::string &userDefines, const std::list<FileSettings> &fileSettings);

    static void writeFilesTxt(const std::string &buildDir, const std::list<std::string> &sourcefiles, const std::string &userDefines, const std::list<FileSettings> &fileSettings);

    /** Close current TU.analyzerinfo file */
    void close();
    bool analyzeFile(const std::string &buildDir, const std::string &sourcefile, const std::string &cfg, int fileIndex, std::size_t hash, std::list<ErrorMessage> &errors);
    void reportErr(const ErrorMessage &msg);
    void setFileInfo(const std::string &check, const std::string &fileInfo);
    static std::string getAnalyzerInfoFile(const std::string &buildDir, const std::string &sourcefile, const std::string &cfg, int fileIndex);

    static const char sep = ':';

    class CPPCHECKLIB Info {
    public:
        bool parse(const std::string& filesTxtLine);
        std::string afile;
        std::string cfg;
        int fileIndex = 0;
        std::string sourceFile;
    };

protected:
    static std::string getAnalyzerInfoFileFromFilesTxt(std::istream& filesTxt, const std::string &sourcefile, const std::string &cfg, int fileIndex);

private:
    static bool skipAnalysis(const tinyxml2::XMLDocument &analyzerInfoDoc, std::size_t hash, std::list<ErrorMessage> &errors);

    std::ofstream mOutputStream;
    std::string mAnalyzerInfoFile;
};

/// @}
//---------------------------------------------------------------------------
#endif // analyzerinfoH

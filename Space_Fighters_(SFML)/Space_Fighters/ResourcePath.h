//
// Keeps asset paths working from common launch locations: IDE build folders,
// the project folder, and the repository root.
//

#ifndef SFML_PROJECTS_CS3A_RESOURCEPATH_H
#define SFML_PROJECTS_CS3A_RESOURCEPATH_H

#include <fstream>
#include <string>

namespace ResourcePath
{
    inline bool fileExists(const std::string& path)
    {
        std::ifstream file(path.c_str());
        return file.good();
    }

    inline std::string resolve(const std::string& relativePath)
    {
        const std::string candidates[] = {
            relativePath,
            "../" + relativePath,
            "../../" + relativePath,
            "Space_Fighters/" + relativePath,
            "../Space_Fighters/" + relativePath,
            "../../Space_Fighters/" + relativePath,
            "Space_Fighters_(SFML)/Space_Fighters/" + relativePath,
            "../Space_Fighters_(SFML)/Space_Fighters/" + relativePath
        };

        for(const std::string& candidate : candidates)
        {
            if(fileExists(candidate))
            {
                return candidate;
            }
        }

        return relativePath;
    }
}

#endif //SFML_PROJECTS_CS3A_RESOURCEPATH_H

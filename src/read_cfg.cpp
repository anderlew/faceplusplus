/*                                                                              
 * Copyright (C) 2013 Deepin, Inc.                                                 
 *               2013 Zhai Xiang                                                   
 *                                                                              
 * Author:     Zhai Xiang <zhaixiang@linuxdeepin.com>                           
 * Maintainer: Zhai Xiang <zhaixiang@linuxdeepin.com>                           
 *                                                                              
 * This program is free software: you can redistribute it and/or modify         
 * it under the terms of the GNU General Public License as published by         
 * the Free Software Foundation, either version 3 of the License, or            
 * any later version.                                                           
 *                                                                              
 * This program is distributed in the hope that it will be useful,              
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
 * GNU General Public License for more details.                                 
 *                                                                              
 * You should have received a copy of the GNU General Public License            
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        
 */

#include <iostream>
#include <fstream>
#include <algorithm>

#include "read_cfg.h"

namespace fpp 
{

static std::map<std::string, std::string> m_options;

static void m_parse(std::ifstream & cfgfile)
{
    std::string line;
    std::string id, eq, value;
    size_t pos;

    while (std::getline(cfgfile, line))
    {
        if (line[0] == '#') 
            continue;

        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        if ((pos = line.find("#")) != std::string::npos) 
            line = line.substr(0, pos);

        if ((pos = line.find("=")) == std::string::npos)
            continue;

        id = line.substr(0, pos);
        value = line.substr(pos + 1, line.size() - pos);

        m_options[id] = value;
    }
}

std::map<std::string, std::string> get_options(std::string filepath) 
{
    try 
    {
        std::ifstream cfgfile(filepath.c_str());
        m_parse(cfgfile);
    } 
    catch (...) 
    {
        throw std::string("fail to parse cfg file");
    }
    
    return m_options;
}

}

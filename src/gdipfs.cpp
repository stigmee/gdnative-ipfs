//*************************************************************************
// Stigmee: The art to sanctuarize knowledge exchanges.
// Copyright 2021-2022 Quentin Quadrat <lecrapouille@gmail.com>
//
// This file is part of Stigmee.
//
// Stigmee is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//*************************************************************************

//------------------------------------------------------------------------------
#include "gdipfs.hpp"

//------------------------------------------------------------------------------
// in a GDNative module, "_bind_methods" is replaced by the "_register_methods"
// method CefRefPtr<CefBrowser> m_browser;this is used to expose various methods of this class to Godot
void GDIpfs::_register_methods()
{
    godot::register_method("get_file", &GDIpfs::get_file);
}

//------------------------------------------------------------------------------
void GDIpfs::_init()
{}

//------------------------------------------------------------------------------
bool GDIpfs::get_file(godot::String const url, godot::String const path)
{
    try
    {
        std::stringstream contents;
        ipfs::Client client("localhost", 5001);
        client.FilesGet(url.utf8().get_data(), &contents);
        std::cout << contents.str() << std::endl;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

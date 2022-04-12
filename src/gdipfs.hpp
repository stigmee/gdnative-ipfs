//*************************************************************************
// Stigmee: The art to sanctuarize knowledge exchanges.
// Copyright 2021-2022 Alain Duron <duron.alain@gmail.com>
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

#ifndef STIGMEE_GDIPFS_HPP
#  define STIGMEE_GDIPFS_HPP

#  if !defined(_WIN32)
#    pragma GCC diagnostic push
#      pragma GCC diagnostic ignored "-Wold-style-cast"
#      pragma GCC diagnostic ignored "-Wparentheses"
#      pragma GCC diagnostic ignored "-Wunused-parameter"
#      pragma GCC diagnostic ignored "-Wconversion"
#      pragma GCC diagnostic ignored "-Wsign-conversion"
#      pragma GCC diagnostic ignored "-Wfloat-conversion"
#      pragma GCC diagnostic ignored "-Wfloat-equal"
#      pragma GCC diagnostic ignored "-Wpedantic"
#      pragma GCC diagnostic ignored "-Wshadow"
#      if defined(__clang__)
#        pragma clang diagnostic push
#        pragma clang diagnostic ignored "-Wcast-align"
#        pragma clang diagnostic ignored "-Wcast-align"
#        pragma clang diagnostic ignored "-Wundef"
#        pragma clang diagnostic ignored "-Wshadow-field"
#        pragma clang diagnostic ignored "-Wcast-qual"
#      endif
#  endif

// Godot
#  include "Godot.hpp"
#  include "GDScript.hpp"
#  include "Node.hpp"

// IPFS lib
#  include "ipfs/client.h"

// ****************************************************************************
//! \brief
// ****************************************************************************
class GDIpfs : public godot::Node
{
public: // Godot interfaces

    // -------------------------------------------------------------------------
    //! \brief Our initializer called by Godot.
    // -------------------------------------------------------------------------
    void _init();

    // -------------------------------------------------------------------------
    //! \brief Static function that Godot will call to find out which methods
    //! can be called on our NativeScript and which properties it exposes.
    // -------------------------------------------------------------------------
    static void _register_methods();

    // -------------------------------------------------------------------------
    //! \brief Godot stuff
    // -------------------------------------------------------------------------
    GODOT_CLASS(GDIpfs, godot::Node);

public:

    bool get_file(godot::String const url, godot::String const path);
};

#  if !defined(_WIN32)
#      if defined(__clang__)
#        pragma clang diagnostic pop
#      endif
#    pragma GCC diagnostic pop
#  endif

#endif // STIGMEE_GDIPFS_HPP

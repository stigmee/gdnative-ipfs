#!python
###############################################################################
## Stigmee: The art to sanctuarize knowledge exchanges.
## Copyright 2021-2022 Quentin Quadrat <lecrapouille@gmail.com>
##
## This file is part of Stigmee.
##
## Stigmee is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
###############################################################################

import os

# We let SCons build its default ENV as it includes OS-specific things which we don't
# want to have to pull in manually.
# Then we prepend PATH to make it take precedence, while preserving SCons' own entries.
custom_tools = ["default"]
env = Environment(tools=custom_tools)
env.PrependENVPath("PATH", os.getenv("PATH"))
env.PrependENVPath("PKG_CONFIG_PATH", os.getenv("PKG_CONFIG_PATH"))
if "TERM" in os.environ:  # Used for colored output.
    env["ENV"]["TERM"] = os.environ["TERM"]
opts = Variables([], ARGUMENTS)

# Define our options
platforms = ['windows', 'x11', 'linux', 'linuxbsd', 'macos', 'osx']
archis = ['x86_64', 'arm64']

# Define our options
opts.Add(EnumVariable('target', 'Compilation target', '', ['d', 'debug', 'r', 'release']))
opts.Add(EnumVariable('platform', 'Compilation platform', '', platforms + ['']))
opts.Add(EnumVariable('arch', 'Platform architecture', 'x86_64', ['x86_64', 'arm64']))
opts.Add(BoolVariable('use_llvm', 'Use the LLVM / Clang compiler', 'no'))
opts.Add(PathVariable('workspace', 'The path of Stigmee workspace', '', PathVariable.PathAccept))
opts.Add(PathVariable('godot_version', 'The Godot version installed in workspace', '3.4.2-stable', PathVariable.PathAccept))

# Updates the environment with the option variables.
opts.Update(env)

# Process some arguments.
# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags
if env['use_llvm'] or env['platform'] == 'osx':
    env['CC'] = 'clang'
    env['CXX'] = 'clang++'

# Process platform arguments. Here we use the same names as GDNative.
platform = env['platform']
if platform == 'macos':
    platform = 'osx'
elif platform in ('x11', 'linuxbsd'):
    platform = 'linux'
elif platform == 'bsd':
    platform = 'freebsd'
if platform == '':
    print('No valid target platform selected.')
    quit()

# X86 or ARM
archi = env['arch']
arch_ext = archi
if archi == 'x86_64':
    if platform != 'osx':
        arch_ext = '64'

# Check if the Stigmee workspace is known
workspace = env['workspace']
packages = workspace + '/packages'
if workspace == '':
    print('You shall define the path of the Stigmee workspace.')
    print('Please pass the content your environement variable WORKSPACE_STIGMEE')
    quit();
if not os.path.isdir(workspace):
    print('The argument workspace ' + workspace + ' path is invalid')
    print('Please pass the content your environement variable WORKSPACE_STIGMEE')
    quit();

# Check if Godot exists
godot_api_path = workspace + '/godot/' + env['godot_version'] + '/cpp'
if not os.path.isdir(godot_api_path):
    print('The Godot path ' + godot_api_path + ' is invalid.')
    print('Please pass the content your environement variable WORKSPACE_STIGMEE')
    quit();

# Compile either in release or debug mode
compile_mode = env['target']
if compile_mode == 'd':
    compile_mode = 'debug'
elif compile_mode == 'r':
    compile_mode = 'release'

# Compile CEF either in 'Release' or 'Debug' mode
cef_compile_mode = compile_mode.capitalize()

# The godot library we want to create
target_path = workspace + '/stigmee/build'
target_library = 'libgdipfs'

# Platform specific compilation
if platform == 'osx':
    env.Append(CXXFLAGS=['--std=c++17'])
    env.Append(LINKFLAGS=['-arch', archi])
    env.Append(CCFLAGS=['-arch', archi])
    if compile_mode == 'debug':
        env.Append(CCFLAGS=['-g', '-O2'])
    else:
        env.Append(CCFLAGS=['-g', '-O3'])
    env.Append(CCFLAGS=['-fPIC'])
    env.Append(CXXFLAGS=['-DCEF_USE_SANDBOX', '-DNDEBUG',
                         '-DWRAPPING_CEF_SHARED', '-D__STDC_CONSTANT_MACROS',
                         '-D__STDC_FORMAT_MACROS'])

elif platform == 'linux':
    env.Append(CXXFLAGS=['--std=c++17'])
    if compile_mode == 'debug':
        env.Append(CCFLAGS=['-g3', '-Og'])
    else:
        env.Append(CCFLAGS=['-g', '-O3'])
    env.Append(CCFLAGS=['-fPIC'])
    env.Append(CXXFLAGS=['-DCEF_USE_SANDBOX', '-DNDEBUG', '-D_FILE_OFFSET_BITS=64',
                         '-D__STDC_CONSTANT_MACROS', '-D__STDC_FORMAT_MACROS'])

elif platform == 'windows':
    # This makes sure to keep the session environment variables on windows,
    # that way you can run scons in a vs 2017 prompt and it will find all the required tools
    env.Append(ENV=os.environ)
    env.Append(CPPDEFINES=['WIN32', '_WIN32', '_WINDOWS', '_CRT_SECURE_NO_WARNINGS'])
    env.Append(CCFLAGS=['-W3', '-GR'])
    env.Append(CXXFLAGS='/std:c++17')
    if compile_mode == 'debug':
        env.Append(CPPDEFINES=['_DEBUG'])
        env.Append(CCFLAGS=['-EHsc', '-MDd', '-ZI'])
        env.Append(LINKFLAGS=['-DEBUG'])
    else:
        env.Append(CPPDEFINES=['NDEBUG'])
        env.Append(CCFLAGS=['-O2', '-EHsc', '-MD'])

# Unix compilation flags
if platform == 'linux' or platform == 'osx':
    # gcc/clang compilation flags
    env.Append(CXXFLAGS=['-Wall', '-Wextra', '-Wuninitialized', '-Wundef',
                         '-Wunused', '-Wunused-result', '-Wunused-parameter',
                         '-Wtype-limits', '-Wcast-align', '-Wcast-qual',
                         '-Wconversion', '-Wfloat-equal', '-Wpointer-arith',
                         '-Wswitch-enum', '-Wpacked', '-Wold-style-cast',
                         '-Wdeprecated', '-Wvariadic-macros', '-Wvla',
                         '-Wsign-conversion'])

    # clang specific flags
    if env['use_llvm']:
        env.Append(CXXFLAGS=['-Wused-but-marked-unused', '-Wzero-length-array',
                             '-Wunused-member-function', '-Wvector-conversion',
                             '-Wunused-getter-return-value', '-Wthread-safety',
                             '-Wunneeded-member-function', '-Wshadow-all',
                             '-Wunused-exception-parameter',
                             '-Wunneeded-internal-declaration',
                             '-Wunreachable-code-aggressive',
                             '-Wsuper-class-method-mismatch',
                             '-Werror=implicit-function-declaration',
                             '-Wtautological-compare'])

# Pathes of Godot header files
env.Append(CPPPATH=['.',
                    godot_api_path + '/godot-headers',
                    godot_api_path + '/include',
                    godot_api_path + '/include/core',
                    godot_api_path + '/include/gen'])

# Godot library that is linked against our library
libgodot = 'libgodot-cpp.' + platform + '.' + compile_mode + '.' + arch_ext
env.Append(LIBS=[libgodot], LIBPATH=[godot_api_path + '/bin'])

# System libraries
env.Append(LIBS=['curl'])

# Pathes header files of our module
env.Append(CPPPATH = [packages + '/ipfs/include', packages + '/json/include'])

# Compile the library
sources = [packages + '/ipfs/src/http/transport-curl.cc',
           packages + '/ipfs/src/client.cc',
           'src/gdipfs.cpp', 'src/gdlibrary.cpp']
library = env.SharedLibrary(target=target_path + '/' + target_library, source=sources)
Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))

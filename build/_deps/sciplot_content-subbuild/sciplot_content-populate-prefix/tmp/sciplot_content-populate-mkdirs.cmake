# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-src")
  file(MAKE_DIRECTORY "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-src")
endif()
file(MAKE_DIRECTORY
  "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-build"
  "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix"
  "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/tmp"
  "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src/sciplot_content-populate-stamp"
  "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src"
  "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src/sciplot_content-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src/sciplot_content-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/taufikrendi/Documents/distertasi/openfhe-development/ownscript/build/_deps/sciplot_content-subbuild/sciplot_content-populate-prefix/src/sciplot_content-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

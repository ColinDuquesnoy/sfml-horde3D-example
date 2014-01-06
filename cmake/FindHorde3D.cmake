# - Try to find a Horde3D installation
# Once done, this will define
#
#  Horde3D_FOUND - system has Horde3D
#  Horde3D_INCLUDE_DIRS - the Horde3D and Horde3DUtils include directories
#  Horde3D_LIBRARIES - link these to use Horde3D and Horde3DUtils
#------------------------------------------------------------------------------


#------------------------------------------------------------------------------
# Find Horde3D Includes
#------------------------------------------------------------------------------

find_path(HORDE3D_INCLUDE_DIR Horde3D.h
			PATHS
				/usr/include
				/usr/local/include
				${CMAKE_SOURCE_DIR}/deps
			PATH_SUFFIXES
				horde3d
				Horde3D.framework/Headers
)
if(HORDE3D_INCLUDE_DIR)
	message (STATUS "Found Horde3D includes: " ${HORDE3D_INCLUDE_DIR})
	set(Horde3D_INCLUDE_DIRS ${HORDE3D_INCLUDE_DIR})
else()
	message(FATAL_ERROR "Horde3D includes not found.")
endif()

#------------------------------------------------------------------------------

find_path(HORDE3DUTILS_INCLUDE_DIR Horde3DUtils.h
			PATHS
				/usr/include
				/usr/local/include
				${CMAKE_SOURCE_DIR}/deps
			PATH_SUFFIXES
				horde3d
				Horde3DUtils.framework/Headers
)

if(HORDE3DUTILS_INCLUDE_DIR)
	message (STATUS "Found Horde3DUtils includes: " ${HORDE3DUTILS_INCLUDE_DIR})
	set(Horde3D_INCLUDE_DIRS ${Horde3D_INCLUDE_DIRS} ${HORDE3DUTILS_INCLUDE_DIR})
else()
	message(FATAL_ERROR "Horde3DUtils includes not found.")
endif()

#------------------------------------------------------------------------------
# Find Horde3D Libraries
#------------------------------------------------------------------------------

find_library(HORDE3D_LIBRARY Horde3D
			PATHS
				/usr/lib
				/usr/local/lib
				${CMAKE_SOURCE_DIR}/deps
			PATH_SUFFIXES
				horde3d
				Horde3D.framework
)
if(HORDE3D_LIBRARY)
	message (STATUS "Found Horde3D lib: " ${HORDE3D_LIBRARY})
	set(Horde3D_LIBRARIES ${HORDE3D_LIBRARY})
else()
	message(FATAL_ERROR "Horde3D lib not found.")
endif()

#------------------------------------------------------------------------------

find_library(HORDE3DUTILS_LIBRARY Horde3DUtils
			PATHS
				/usr/lib
				/usr/local/lib
				${CMAKE_SOURCE_DIR}/deps
			PATH_SUFFIXES
				horde3d
				Horde3DUtils.framework
)
if(HORDE3DUTILS_LIBRARY)
	message (STATUS "Found Horde3DUtils lib: " ${HORDE3DUTILS_LIBRARY})
	set(Horde3D_LIBRARIES ${Horde3D_LIBRARIES} ${HORDE3DUTILS_LIBRARY})
else()
	message(FATAL_ERROR "Horde3DUtils lib not found.")
endif()

#------------------------------------------------------------------------------

# If we get here, we know everything's found.
set(Horde3D_FOUND TRUE)

#------------------------------------------------------------------------------



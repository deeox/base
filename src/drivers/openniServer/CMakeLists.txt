#SET( DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../Deps) # Directorio donde se encuentran las dependencias
#include(${DEPS_DIR}/openni2/CMakeLists.txt)
#include(${DEPS_DIR}/nite2/CMakeLists.txt)

IF(OPENNI2_LIB)
	#check for the path openni libs
	


	SET( SOURCE_FILES
			openniServer.cpp
			OpenNiServerLib/myprogeo
			OpenNiServerLib/ConcurrentDevice
			OpenNiServerLib/OpenCVConverter
			OpenNiServerLib/OpenNIDeviceListener
			OpenNiServerLib/RGBCamera
			OpenNiServerLib/DepthCamera
			OpenNiServerLib/PointCloudServer
			OpenNiServerLib/RGBDServer
			)
    add_definitions(-DGLADE_DIR="${gladedir}")

	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-rpath ./" ) # Opciones para el compilador

    include_directories(
        ${INTERFACES_CPP_DIR}
        ${LIBS_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/cameras
		${NITE2_INC}
		${ZLIB_INCLUDE_DIRS}
       ${easyiceconfig_INCLUDE_DIRS}
	)

	link_directories(
		${easyiceconfig_LIBRARY_DIRS}
	)


    add_executable (openniServer ${SOURCE_FILES})
	#copy openni libs to local path
	if (NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/OpenNI2)
		file (COPY ${OPENNI2_LIB} DESTINATION .)
		file (COPY ${OPENNI2_LIB_PATH}/OpenNI2 DESTINATION .)
		
	endif()


	if  ( NITE2_LIB )
		set_property ( SOURCE openniServer.cpp
			PROPERTY COMPILE_DEFINITIONS WITH_NITE2=1
		)
		#copy nite libs to local path
		if (NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/NiTE2)
			message ("--CMake will install local NiTE2 lib and Driver")
			file (COPY ${NITE2_LIB}/libNiTE2.so DESTINATION .)
			file (COPY ${NITE2_LIB}/NiTE2 DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
		endif()
	
		TARGET_LINK_LIBRARIES(openniServer
	        ${CMAKE_THREAD_LIBS_INIT}
			${CMAKE_THREAD_LIBS_INIT}
			${easyiceconfig_LIBRARIES} 
	        ${ZeroCIce_LIBRARIES}
	        ${OpenCV_LIBRARIES}
	        ${OpenCVGUI_LIBRARIES} 
	        ${gsl_LIBRARIES}
			logger
			ns
	        jderobotutil
	        geometry
	        colorspacesmm
	        JderobotInterfaces
			${OPENNI2_LIB}
			${NITE2_LIB}/libNiTE2.so
			${Boost_LIBRARIES}
	        ${LIBXML2_LIBRARIES}
	        ${ZLIB_LIBRARIES}
		)
	else()
		TARGET_LINK_LIBRARIES(openniServer
	        ${CMAKE_THREAD_LIBS_INIT}
			${easyiceconfig_LIBRARIES} 
			${ZeroCIce_LIBRARIES}
			${OpenCV_LIBRARIES}
	        ${OpenCVGUI_LIBRARIES}
			${gsl_LIBRARIES}
	        jderobotutil
	        geometry
	        colorspacesmm
	        JderobotInterfaces
			logger
			ns
			${OPENNI2_LIB}		    
	        ${Boost_LIBRARIES}
	        ${LIBXML2_LIBRARIES}
	        ${ZLIB_LIBRARIES}
	        ${OPENSSL_LIBRARIES}
			${GLOG_LIBRARIES}
		)
	endif()

	INSTALL(TARGETS openniServer
          DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/
          COMPONENT openniServer
    )

	FILE(GLOB_RECURSE CFG_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cfg)
	INSTALL (FILES ${CFG_FILES} 
		DESTINATION ${CMAKE_INSTALL_PREFIX}/share/jderobot/conf 
		COMPONENT openniServer
	)
ENDIF()


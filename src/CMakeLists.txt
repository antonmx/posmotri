
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)
include_directories(
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5Xml_INCLUDE_DIRS}
  ${Qt5OpenGL_INCLUDE_DIRS}
  ${Qt5Network_INCLUDE_DIRS}
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

find_package(OpenGL)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(QGLViewer REQUIRED)
include_directories(${QGLVIEWER_INCLUDE_DIR})

set (NETCDF_CXX "YES")
find_package(NetCDF REQUIRED)
include_directories(${NETCDF_INCLUDES})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})


qt5_wrap_ui(ui_directionvectorwidget.h directionvectorwidget.h)


add_executable(posmotri
  boundingbox.cpp
  blendshaderfactory.cpp
  brickinformation.cpp
  bricks.cpp
  brickswidget.cpp
  camerapathnode.cpp
  captions.cpp
  captiondialog.cpp
  captiongrabber.cpp
  captionobject.cpp
  classes.cpp
  colorbar.cpp
  colorbargrabber.cpp
  colorbarobject.cpp
  clipinformation.cpp
  clipplane.cpp
  clipobject.cpp
  clipgrabber.cpp
  coloreditor.cpp
  crops.cpp
  cropobject.cpp
  cropgrabber.cpp
  cropshaderfactory.cpp
  dcolordialog.cpp
  dcolorwheel.cpp
  doublespinboxdelegate.cpp
  dialogs.cpp
  directionvectorwidget.cpp
  drawhiresvolume.cpp
  drawlowresvolume.cpp
  fileslistdialog.cpp
  geometryobjects.cpp
  geoshaderfactory.cpp
  glewinitialisation.cpp
  global.cpp
  glowshaderfactory.cpp
  gradienteditor.cpp
  gradienteditorwidget.cpp
  grids.cpp
  gridgrabber.cpp
  gridobject.cpp
  hitpoints.cpp
  hitpointgrabber.cpp
  keyframe.cpp
  keyframeeditor.cpp
  keyframeinformation.cpp
  lightinginformation.cpp
  lightingwidget.cpp
  load2volumes.cpp
  load3volumes.cpp
  load4volumes.cpp
  main.cpp
  mainwindow.cpp
  mainwindowui.cpp
  matrix.cpp
  messagedisplayer.cpp
  mymanipulatedframe.cpp
  networkinformation.cpp
  networks.cpp
  networkgrabber.cpp
  networkobject.cpp
  opacityeditor.cpp
  paintball.cpp
  propertyeditor.cpp
  pathobject.cpp
  pathgrabber.cpp
  paths.cpp
  pathgroups.cpp
  pathgroupobject.cpp
  pathgroupgrabber.cpp
  pathshaderfactory.cpp
  ply.c
  pluginthread.cpp
  preferenceswidget.cpp
  profileviewer.cpp
  prunehandler.cpp
  pruneshaderfactory.cpp
  rawvolume.cpp
  saveimageseqdialog.cpp
  savemoviedialog.cpp
  scalebar.cpp
  scalebargrabber.cpp
  scalebarobject.cpp
  shaderfactory.cpp
  shaderfactory2.cpp
  shaderfactoryrgb.cpp
  splineeditor.cpp
  splineeditorwidget.cpp
  splineinformation.cpp
  splinetransferfunction.cpp
  staticfunctions.cpp
  tagcoloreditor.cpp
  tearshaderfactory.cpp
  tick.cpp
  transferfunctioncontainer.cpp
  transferfunctioneditorwidget.cpp
  transferfunctionmanager.cpp
  trisetinformation.cpp
  trisets.cpp
  trisetgrabber.cpp
  trisetobject.cpp
  viewer.cpp
  viewinformation.cpp
  viewseditor.cpp
  volume.cpp
  volumebase.cpp
  volumeinformation.cpp
  volumeinformationwidget.cpp
  volumefilemanager.cpp
  volumesingle.cpp
  volumergbbase.cpp
  volumergb.cpp
  xmlheaderfunctions.cpp
  remaphistogramline.cpp
  remaphistogramwidget.cpp
  itksegmentation.cpp
  lighthandler.cpp
  lightshaderfactory.cpp
  gilights.cpp
  gilightgrabber.cpp
  gilightobject.cpp
  gilightinfo.cpp
  gilightobjectinfo.cpp
)

target_link_libraries(posmotri
  ${QGLVIEWER_LIBRARIES}
  ${Qt5OpenGL_LIBRARIES}
  ${Qt5Xml_LIBRARIES}
  ${Qt5Network_LIBRARIES}
  ${NETCDF_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${GLUT_LIBRARIES}
  ${OPENGL_LIBRARIES}
)


install(TARGETS posmotri RUNTIME DESTINATION bin)


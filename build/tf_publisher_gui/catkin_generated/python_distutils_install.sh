#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/ias/Desktop/thesis/code/ros_camera/src/tf_publisher_gui"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/ias/Desktop/thesis/code/ros_camera/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/ias/Desktop/thesis/code/ros_camera/install/lib/python3/dist-packages:/home/ias/Desktop/thesis/code/ros_camera/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/ias/Desktop/thesis/code/ros_camera/build" \
    "/usr/bin/python3" \
    "/home/ias/Desktop/thesis/code/ros_camera/src/tf_publisher_gui/setup.py" \
     \
    build --build-base "/home/ias/Desktop/thesis/code/ros_camera/build/tf_publisher_gui" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/ias/Desktop/thesis/code/ros_camera/install" --install-scripts="/home/ias/Desktop/thesis/code/ros_camera/install/bin"

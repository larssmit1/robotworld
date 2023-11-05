This is an extra README which contains some extra information about the implementation of the assignment.


Building and Running the software
---------------------------------

**Building:**
Building the software works in the same way as the original software.

**Running:**
When it comes to running the software I would recommend, however, to navigate to the scripts folder and use "bash run.sh" 
to run the software. When not doing this there might be issues when it comes to finding the config files. This can be
solved by changing the paths in "ConfigReader.cpp" and rebuilding the software, but is not recommended.


Configs
-------

There are currently 2 configuration files, both these files can be found in the "config" folder. Of these files
"config.txt" contains general configurations for the entire program. "worldconfig.txt" contains the layout of the
different worlds which can be populated in the program.

Both these config files are read by the ConfigReader in the software. I have chosen to make a parser for these
files myself to prevent other students from having to install a separate library, which can create issues with
running the code if this is not done properly. The disadvantage of this, however, is that this parser is
less stable compared to most libraries. As long as the layout is followed, everything works properly, but be
carefull when making major changes in these config files.

### config.txt

When it comes to the "config.txt" I would recommend to simply change values and not change anything else. All options
are present in the config so adding options is unnecesary. 

The config file is parsed by taking the first part before a space and checking if this corresponds to a value and
afterwards taking the second part seperated by a space and assigning this second part as the value if this is
possible. Everything after the first two parts seperated by spaces should be ignored.

**Options:**
    * "stddev_compass:" -> The standard deviation of the compass.
    * "stddev_odometer:" -> The standard deviation of the odometer.
    * "stddev_lidar:" -> The standard deviation of the lidar.
    * "beamangle_lidar:" -> The angle between the beams of the lidar.
    * "beamlength_lidar:" -> The length of the beams of the lidar.
    * "x_spacing_robot:" -> Extra spacing when it comes to width, which the robot keeps when calculating a path.
    * "y_spacing_robot:" -> Extra spacing when it comes to height, which the robot keeps when calculating a path.
    * "max_particle_diff:" -> The maximum difference a particle can have compared to the lidar to have a chance to reappear.
    * "min_particle_chance:" -> The minimum chance a particle which is similar to the measurement has to reappear.
    * "particle_range:" -> The maximum range a particle can be from the previoussly determined position of the robot, to be considered valid.

### worldconfig.txt

I would recommend to mostly just change values in worldconfig.txt as well. But it can be usefull to add an extra world in this file.
To do this simply copy one of the other worlds and change the values. Don't forget to seperate the worlds with whitelines and
add a whiteline at the end.

"worldconfig.txt" works similar to "config.txt" but has the added options to add worlds and walls are read in groups.
First off all coordinates need to be written as "x,y" without spaces. Every world in this file needs to be seperated
by a whiteline. After the last world there also needs to be a whiteline, for the last world to be saved properly.
Walls will be read untill this is closed with a "}" at a seperate line. Don't forget the closing bracket because
it will ignore all other values.

**Options:**
    "name:" -> The name of the world.
    "robot:" -> The location of the robot in the world.
    "goal:" -> The location of the goal in the world.
    "walls{" -> The locations of the walls in the world. (this option needs to be close with a } at a seperate line)


GUI
---

Below I've described the options which have been added for this assignment to the GUI.

**Options:**
    "Draw Lidar" -> When checked draws the beams of the lidar.
    "Draw Particles" -> When checked draws the particles of the particle filter.
    "Draw Kalman route" -> When checked draws the path the robot has driven according to the kalmanfilter.
    "Draw particle filter route" -> When checked draws the path the robot has driven according to the particlefilter.
    "World" -> Select the world which you want to load using the populate button.
    "RobotDriveMode" -> Select the drive mode the robot uses to follow the path. (Default is the original, Kalman filter mode uses the kalmanfilter positions to drive around)

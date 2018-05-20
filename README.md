# Model Predictive Control
## Abstract
Based on the vehicle kinematic model's predictive result, optimizing the control performance. The pid control is not enough for high speed control. The another problem of PID control doesn't have capability to handle the latency. So in high speed vehicle , latency is very critical vehicle control and vehicle safety.

## Introduction
### Data explain
1. Udacity simulator provides trajectory reference points in [x,y] format with map coordinate.
2. (Udacity simulator also provides) vehicle's position in [x,y] format in map coordinate is also provided.what's more, vehicle's velocity, steering angle, yaw angle and acceleration are provied.

### Algorithm strategy.(MPC.cpp)
1. Initialize the interval of predicted trajectory and sample time.
2. Since IPOPT solver needs vector input, data index is initialized with size_t.
3. define the FG_eval for IPOPT solver.
 - FG_eval class is used for making the vector to feed to IPOPT solver.
 - Define the cost function (copy and paste from udacity keep in mind lesson). No additional cost function is added.
4. Based on the number of variance , define length of variance and constraints
5. Define the variance lowerbound and upperbound by using the index of variance.(defined in FG_eval)
 - Acceleration boudary is [-1,1] <= means max deceleration and max acceleration.
 - Steering value boundary is [-25,25] <= for vehicle stability.
 
### Algorithm strategy.(MPC.cpp)
1. For convinient, PI and bound parameters are added.

### Algorithm strategy.(main.cpp)
This file content can be divide into 2 parts. 
1. Mapping reference trajectory's points [x,y] into vehicle coordinate. 
 - In kidnapped vehicle project, fixed axis transformation was used. In this project, reference trajectory's [x,y] needs to be transformed into vehicle coordinate. The reason why transfrom reference points into vehicle coordinate is that vehicle needs ref trajectory points to calculate cte and epsi in next time step.
2. Feeding the (next time step) predicted vehicle position and other states into mpc.Solve function. Then mpc.Solve feeds state into IPOPT solver and executes online optimization. Then IPOPT calculates the coefficient of polynominal which calculated as the smallest cost function. Then [steering andle, acceleration] can be extract from 'solution' <= As udacity guide.
 - Vehicle only use the first value of [steering andle, acceleration] in fg
 
## Simulation Results.
1. Vehicle can run the track with good performance in velocity of 70km/h.
![MPC_corner1](https://github.com/Fred159/CarND-MPC-Project/blob/master/mpc_corner1.png)
![MPC_corner2](https://github.com/Fred159/CarND-MPC-Project/blob/master/mpc_corner2.png)
![MPC_corner3](https://github.com/Fred159/CarND-MPC-Project/blob/master/mpc_corner3_1.png)

2. Vehicle performance was not good enough run with 90~120 km/h.

## Conclution
MPC based on the (kinematic model in this project) model, handle the latency of system. And based on the cost function, additional constraints are also can be added. MPC is better than PID controll in high speed vehicle. 

## Appendix
### Environment 
1. Docker windows toolbox
2. github online code editor
3. Visual Studio 2017

### References
1. Udacity class
2. darienmt
3. mvirgo
4. sebastian-sampayo
5. NikolasEnt

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# CarND-Controls-MPC
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `install-mac.sh` or `install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.

* **Ipopt and CppAD:** Please refer to [this document](https://github.com/udacity/CarND-MPC-Project/blob/master/install_Ipopt_CppAD.md) for installation instructions.
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page). This is already part of the repo so you shouldn't have to worry about it.
* Simulator. You can download these from the [releases tab](https://github.com/udacity/self-driving-car-sim/releases).
* Not a dependency but read the [DATA.md](./DATA.md) for a description of the data sent back from the simulator.


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./mpc`.

## Tips

1. It's recommended to test the MPC on basic examples to see if your implementation behaves as desired. One possible example
is the vehicle starting offset of a straight line (reference). If the MPC implementation is correct, after some number of timesteps
(not too many) it should find and track the reference line.
2. The `lake_track_waypoints.csv` file has the waypoints of the lake track. You could use this to fit polynomials and points and see of how well your model tracks curve. NOTE: This file might be not completely in sync with the simulator so your solution should NOT depend on it.
3. For visualization this C++ [matplotlib wrapper](https://github.com/lava/matplotlib-cpp) could be helpful.)
4.  Tips for setting up your environment are available [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)
5. **VM Latency:** Some students have reported differences in behavior using VM's ostensibly a result of latency.  Please let us know if issues arise as a result of a VM environment.

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/b1ff3be0-c904-438e-aad3-2b5379f0e0c3/concepts/1a2255a0-e23c-44cf-8d41-39b8a3c8264a)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

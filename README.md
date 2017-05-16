# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Project Instructions and Rubric

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.
## PID Controller Overview

| Component | Description |
| --------- | ----------- |
| Proportional \(P\) | Steers proportional to the cross track error.  The car steers harder the larger the cross track error.  With proportional control alone, the car tends to repeatedly overshoot the center line. |
| Integral (I) | The integral component serves to offset possible bias in steering.  An example of this could be wind force that pushes the car away from the center line. |
| Derivative (D) | Temporal derivative of the cross track error.  The derivative component smooths the oscillation or overshooting effect of the proportional component by adding resistance as the car approaches the center line.  With too little resistance, and the car still oscillates, but too much resistance causes the car to take too long to adjust to center. |

### Underdamped (Resistance Too Low)

In this video, the derivative term is too small, and the car oscillates heavily.

[Underdamped Video](https://youtu.be/9VdKtL6c-eg)

### Overdamped (Resistance Too High)

In this video, I've derivative term high enough where the controller is overdamped, and the car is taking a long time to adjust to center.

[Overdamped Video](https://www.youtube.com/watch?v=fxbpE9z046g)

## Parameter Tuning

Parameters were initially obtained through the Twiddle algorithm.  The algorithm can be found in `src/twiddle.cpp`, and has designed so that it works well within the simulated environment.  In particular, a `cycle_` variable is used to keep track which part of the flow the current trial is using.  For example, a cycle of `UP` indicates that we are running a trial with `Dp` added to the base parameter value.

### Initial Parameter Values

|  | P | I | D |
| -- | -- | -- | -- |
| p | 0 | 0 | 0 |
| Dp | 0.1 | 0.1 | 0.1 |

### Twiddle Tuned Values

Note: Final value for integral term is zero because there is no steering bias in the simulated environment.

|  | P | I | D |
| -- | -- | -- | -- |
| p | .65672 | 0 | 8.99679 |

## Manual Tuning

It seems that after twiddle tuning the parameters are stuck in a local minimum and the algorithm car is not able to complete the entire track without touching the edges.  Manual tuning actually turned out to be much more effective.

First I started with the proportional gain, adjusting until the car oscillated enough where it oscillated, but not wildly.  Next, slowly I adjusted to the derivative gain, dampening the effects of the proportional component until the car no longer oscillated heavily.  After dampening the oscillation I adjusted the proportional term again slightly so that the car could make the sharpest turns.  The integral term is kept at zero.

### Manual Tuned Values

|  | P | I | D |
| -- | -- | -- | -- |
| p | .16 | 0 | 2 |

## Final Video

[Final Video](https://www.youtube.com/watch?v=c-n_zz25-IA)


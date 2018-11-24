# CAHRR

[![Build Status](https://travis-ci.com/SkyZH/CAHRR.svg?branch=master)](https://travis-ci.com/SkyZH/CAHRR)

Chi's Advanced Hurricane Robot Runtime

This framework can be embedded into any system. For example, [Hurricane](https://github.com/SkyZH/Hurricane), the robot control system for SJTU RoboMaster Competition.

## Usage

Refer to [Tests](https://github.com/SkyZH/CAHRR/tree/master/test).

## Structure

### System

CAHRR defines a variety of systems being widely used in robot control systems.

* CAN System (CANSystem.h) - control CAN devices
* Chassis System (ChassisSystem.h) - control chassis
* Debug System (DebugSystem.h) - transmit debug information
* IMU System (IMUSystem.h) - read gyro data from IMU
* Remote System (RemoteSystem.h) - read user control value from joystick or other devices
* Ultrasonic System (UltrasonicSystem.h) - use ultrasonic sensor to measure distance

You can either extend these classes or build your own system based on these specifications.

### Accumulator and Utils

* Average Accumulator (AvgAccumulator.h) - feed the accumulator some data and get the average
* Delta Accumulator (DeltaAccumulator.h) - feed the accumulator current value and get delta from last value
* PID Rate Accumulator (PIDAccumulator.h) - PID rate control
* PID Displacement Accumulator (PIDAccumulator.h) - PID displacement control, usually used with rate accumulator
* Ramp Accumulator (RampAccumulator.h) - feed the accumulator target value and get a value not to far from previous
* Rotate Accumulator (RotateAccumulator.h) - usually used with motors with feedback of position and provide precise position control
* clamp (utils.h) - clamp value
* cycle_err (utils.h) - get continous error
* map_range (utils.h) - map a range of value to another range

### Tasks

Task is the core idea of CAHRR. All of your stuff should be fit in task to provide asynchronous control of all systems.

Each task is made up of (Task.h):

* `initialize()` - called on the start of the task
* `destroy()` - called at the end of the task
* `isEnd()` - a function which returns a boolean value, indicating if this task has been ended. Note that if the task is not wrapped in a task container supporting automated scheduling of tasks, this value is ignored.
* `update()` - called at each update cycle

And then there are automated task containers:

* TimedTask - Task will end if timeout is triggered. You should implement your own `time()` function based on the system you're using.
* SwitchTask - Take two tasks as parameters. If `selected` is false, it will execute the first task. Otherwise the second task is executed.
* ConditionSwitchTask - Take two tasks as parameters. You should implement member function `when()`. If `when()` returns true, it will start the second task, otherwise it will start the first task.
* AutoSwitchTask - Take two tasks as parameters. If one task ends, start another. If both tasks end, this task ends.
* TriggeredSwitchTask - Take two tasks as parameters. You should implement your own `trigger()`. It is like a push button. If you push the button, the light goes on. Another push turns off the light. `trigger()` returns a signal like this. If it is triggered, TriggeredSwitchTask will switch to another task. By default the first task is executed.
* ParallelTask - Take a vector of `Task*` as parameter. All tasks are being executed.
* SequentialTask - Take a vector of `Task*` as parameter. Tasks will be executed one by one if the previous one ends. If cycle is on, first task will be executed after last task ends. If cycle is off, all tasks will end and sequential task ends.

If you have any further questions, please submit a issue or refer to unit tests of these modules.

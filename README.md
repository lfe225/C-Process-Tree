# C++ Process Tree
This project was completed as part of my coursework for CSE 109 Systems Software.

## Project Overview

The **C++ Process Tree** project is designed to display the hierarchical structure of processes running on a Linux system using a recursive search method. This application generates a textual representation of the process tree, where sibling processes are aligned at the same level of indentation, and child processes are indented by four hyphens ("----") from their parent.

## Features

- Generates a clear, hierarchical output of processes.
- Handles cases where there is no singular origin parent process, returning specific error codes:
  - Return code 98 if no singular origin parent exists.
  - Return code 99 if there is no origin parent process with a PPID of 0.
- Uses a `Process` class to encapsulate process information, including PID, PPID, Name, and State.

## Class Design

The `Process` class is designed to hold essential details about each process, including:

- **PID**: Process ID
- **PPID**: Parent Process ID
- **Name**: Name of the process
- **State**: Current state of the process

This class utilizes encapsulation, with private members and public setter/getter functions for data manipulation. The output operator has been overloaded to facilitate easy display of process details.

## Requirements

To run this project, you must have remote access to the SunLab machines, which are part of Lehigh's CSE Department's public computer labs. Ensure you are connected via SSH to the appropriate machine.

## Sample Output

The program produces output similar to the following format:

```bash
$> psTree /home/merle/109/inClassPrograms/proc3
systemd (1,sleeping)
----NetworkManager (1616,sleeping)
--------gmain (1623,sleeping)    
--------gdbus (1624,sleeping)
----sshd (1635,running)
--------sshd (1383882,sleeping)
------------sshd (1383942,sleeping)
----------------bash (1383952,sleeping)
--------------------sleep (1385681,stopped)
--------------------psTree (1385685,running)
--------------------a.out (1473880,zombie)
----crond (3657,sleeping)


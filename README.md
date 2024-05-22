### Operating Systems Project

## OPTIMIZING RUNWAY ALLOCATION

#### Introduction
This project is a client-server application designed to function as an aircraft scheduling system, it aims to enable multiple airlines to connect to a central Air Traffic Controller server. The system facilitates efficient scheduling of flights based on predefined rules, ensuring optimal utilization of airport resources and minimizing delays.

#### Problem Statement
Runway allocation is crucial for the smooth operation of air travel and cargo transfer. Inefficient scheduling can lead to increased turnaround times, operational delays, and even airport shutdowns. The challenges include:
1. Inefficient runway allocation.
2. Increased turnaround times and operational delays.
3. Difficulty in prioritizing aircraft for landing and takeoff.
4. Lack of an ageing mechanism to prevent indefinite delays.

The solution requires advanced algorithms for real-time optimization and dynamic priority assignment based on critical factors, along with an ageing mechanism, to ensure timely operations.

#### Project Overview
The System is designed to manage real-time scheduling of flights with the following key features:
1. Multiple Simultaneous Requests: Allows multiple airlines to connect and request runway access simultaneously.
2. Multi-Level Queue Scheduling: Implements Priority and First-Come-First-Serve (FCFS) scheduling algorithms.
3. Aging: Ensures indefinite delays are avoided by assigning higher priority to older requests.
4. Reducing Turnaround Times: Gives landing priority to reduce turnaround times.
5. Optimal Resource Utilization: Ensures efficient allocation of a single runway resource.

#### Prerequisites
To run this project, the following prerequisites are required:
1. Development Environment: Linux operating system with GCC compiler installed.
2. Programming Language: C.
3. Networking: Understanding of socket programming in C.
4. Libraries: pthread library for threading, necessary for server-side concurrency.


 #### Methodology
 ###### Client Side
- Establish a socket connection to the server.
- Prompt for and send flight details.
- Receive and display updates from the server until the operation is complete.

###### Server Side
- Handle client connections and flight details.
- Manage flight queues with a runway handler thread.
- Utilize mutex locks for thread-safe operations.
- Provide real-time updates to clients.

 #### Implementation
 ###### Client Side
- Establishes connection, prompts for flight details, sends data, and handles updates.

 ###### Server Side
- Manages flight queues, prioritizes operations, handles runway assignments, and provides feedback to clients.

#### Future Work
Future enhancements could include:
1. Multi-Runway Support: To handle increased air traffic efficiently.
2. User Interface Improvements: To offer more interactive and informative client feedback.
3. Integration with External Systems: To incorporate data from weather forecasts and air traffic control systems for better decision-making.

#### Conclusion
The project successfully demonstrates a client-server architecture for efficient flight scheduling. Utilizing multi-level queue scheduling with aging, it addresses the primary challenges in runway allocation and prioritization, ensuring optimal airport operations.

#### References
1. William Stallings, Operating Systems - Internals and Design Principles, Prentice Hall, 5th Edition, 2004.
2. Maurice Bach, The Design of the Unix Operating System, PHI, 1986.
3. Neil Mathew and Richard Stones, Beginning Linux Programming, 4th Edition.
4. Graham Glass and King Abels, Unix for Programmers and Users – A Complete Guide, PHI, 1993.
5. Sumitabha Das, Unix Concepts and Applications, McGraw Hill, 4th Edition, 2015.
6. Neil Matthew and Richard Stones, Beginning Linux Programming, 3rd Edition, Wiley, 1999.
7. A. Silberschatz, P. B. Galvin and G. Gagne, Operating System Concepts, Wiley, 8th Edition, 2014.
8. Darryl Gove, Multicore Application Programming for Windows, Linux, and Oracle Solaris, Addison Wesley, 2011.
9. W. R. Stevens, UNIX Network Programming-Volume II (IPC), PHI, 1998.

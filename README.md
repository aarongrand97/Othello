# Othello
This game takes a pre-made othello game UI, and adapts the computer player decision making process to a minimax algorithm. The decision making code is written in C++, and integrated into the Python UI using Boost libraries.

Compilation of the project is done using CMake, using an example provided by François Lanusse at https://flanusse.net/interfacing-c++-with-python.html.

To create the project, navigate to the build folder in terminal, before running the following commands:

  cmake ..
  
  make othellolib
  
  
If Boost is not already installed, it will be downloaded and configured in the build folder.

The programme can then be run like any other Python programme.

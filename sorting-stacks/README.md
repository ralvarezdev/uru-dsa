# Sorting Stacks
This repository contains the source code of an algorithm to sort N stacks with N values considering stacks limitations for removing nodes (can only pop first node), developed by:

## Developers
Ramón Álvarez <a href="https://github.com/ralvarezdev">(ralvarezdev)</a>.

## Programming Languages
Only C++.

## Installation

<ol>
<li>Clone this repository to your local machine using the following command: 

```git clone https://github.com/ralvarezdev/uru-dsa```
</li>

<li>Change your Current Working Directory to where the repository was cloned</li>

<li>Move to 'sorting-stacks' directory</li>

<li>There are two ways to compile the program: </li>

<ol>
<li>With <strong>G++</strong> (you must have installed <strong>MinGW Compiler</strong>). Use the following command:

<details>
<summary>Command for Windows</summary>

```g++ -o bin\SortingStacks.exe src\main.cpp src\lib\namespaces.h src\lib\algorithm\modHanoi.h src\lib\algorithm\modHanoi.cpp src\lib\terminal\ansiEsc.h src\lib\terminal\ansiEsc.cpp src\lib\terminal\input.cpp src\lib\terminal\input.h```

</details>

<details>
<summary>Command for Linux</summary>

```g++ -o bin/SortingStacks.exe src/main.cpp src/lib/namespaces.h src/lib/algorithm/modHanoi.h src/lib/algorithm/modHanoi.cpp src/lib/terminal/ansiEsc.h src/lib/terminal/ansiEsc.cpp src/lib/terminal/input.cpp src/lib/terminal/input.h```

</details></li>

<li>With <strong>CMake</strong> (you must have installed <strong>CMake and Make</strong>). First, get to the <code>bin</code> folder. Use the following command

<details>
<summary>Command for Windows</summary>

```cmake -S ..\ -G "MinGW Makefiles" -B .\ && make```

</details>

<details>
<summary>Command for Linux</summary>

```cmake -S ../ -G "MinGW Makefiles" -B ./ && make```

</details></li></ol>

<li>Run the program by clicking <code>SortingStacks.exe</code>.</li></ol>

<strong>For a better user experience, resize the terminal window to Fullscreen Mode</strong>

## View it on Action

<a href="https://www.instagram.com/p/C3detnXPmqM/">Sorting 6 Stacks with 6 Nodes Each</a>

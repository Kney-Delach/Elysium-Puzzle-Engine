<a name="Elysium-Puzzle-Engine"></a>
<p align="center"><img width=100% src="Resources/Images/Elysium_Logo_2.png?raw=true"></p>

[![trello_1](https://img.shields.io/badge/Trello-brightgreen)](https://trello.com/b/vNEURvxs/csc8501-cw-part-1)
[![trello_2](https://img.shields.io/badge/Trello-darkgreen)](https://trello.com/b/ZXmtjMhK/csc8501-cw-part-2)
![date](https://img.shields.io/badge/Build%20Date-21.10.19-informational) <!---IsComplete.CourseworkSection.BranchNo.BranchIteration-->
![version](https://img.shields.io/badge/Engine%20Version-0.1.3.5-FD175C)
![unreleased](https://img.shields.io/badge/Branch%20Features-9-orange)

<a name="about"></a>
## About
This engine is being created with the purpose of simulating combinatorical strategies for variations of the 15-Puzzle problem in C++.

<a name="list-of-features"></a>
## List of Features
[active]:https://img.shields.io/badge/-Active-success
[depreciated]:https://img.shields.io/badge/-Depreciated-inactive
[updating]:https://img.shields.io/badge/-Updating-purple
[passing]:https://img.shields.io/badge/-Passing-success
[outdated]:https://img.shields.io/badge/-Outdated-blue
[dev]:https://img.shields.io/badge/-Unreleased-important

[version-1.0.0]:https://img.shields.io/badge/Ver.-1.0.0-ff69b4
[version-1.0.1]:https://img.shields.io/badge/Ver.-1.0.1-ff69b4
[version-1.0.2]:https://img.shields.io/badge/Ver.-1.0.2-ff69b4
[version-1.0.3]:https://img.shields.io/badge/Ver.-1.0.3-ff69b4
[version-1.0.4]:https://img.shields.io/badge/Ver.-1.0.4-ff69b4
[version-1.0.5]:https://img.shields.io/badge/Ver.-1.0.5-ff69b4
[version-dev]:https://img.shields.io/badge/Ver.-dev-important


|**Name**|**Description**|**Version**|**Tests**|**Status**|
|:------:|:-------------:|:---------:|:-------:|:--------:|
|[User Interface Design]()|A loop prompting user input.|![dev][version-dev]|![In Development][passing]|![Active][active]|
|[Puzzle Console Output]()|Multiple valid puzzle configurations can be formatted and streamed to the console.|![dev][version-dev]|![In Development][passing]|![Active][active]|
|[Random Configuration Generation]()|Up to 20,000 valid puzzle configurations can be generated.|![dev][version-dev]|![In Development][dev]|![Active][active]|
|[Writing Configurations To Files]()|Possible to write configurations created directly into a file.|![dev][version-dev]|![In Development][dev]|![Active][active]|
|[Reading Configurations From Files]()|Possible to read configuration files in order to process configurations further.|![dev][version-dev]|![In Development][dev]|![Active][active]|
|[Writing Solution Data To Files]()|Possible to write correctly formatted solution files.|![dev][version-dev]|![In Development][dev]|![Active][active]|
|[Puzzle Analysis for Continous Rows/Columns]()|It will be possible to analyse a puzzle configuration for the total number of continuous rows / columns + reverse.|![dev][version-dev]|![In Development][dev]|![Updating][updating]|
|[Read/Write NxN Configurations]()|Writing and Reading files containing arbitrarily sized puzzles is now possible.|![dev][version-dev]|![In Development][passing]|![Updating][active]|
|[Solution File for Arbitrary Sized Partials]()|It is possible to create a solution file that contains any of the (N^2-1)  partials. |![dev][version-dev]|![In Development][passing]|![Updating][active]|

<a name="references"></a>
## References

<a name="puzzle-research"></a>
#### Puzzle Research

- Research Papers
  - [Ya. Perelman 1988 - Fun with Maths and Physics](https://www.cut-the-knot.org/pythagoras/history15.shtml)
  - [Aaron F. Archer - A Modern Treatment of the 15 Puzzle](http://www.cs.cmu.edu/afs/cs/academic/class/15859-f01/www/notes/15-puzzle.pdf)
  - [Ratner & Warmuth - Finding a Shortest Solution for the NxN Extension of the 15-Puzzle](https://www.aaai.org/Papers/AAAI/1986/AAAI86-027.pdf)
  - [Ratner & Warmuth - The (n^2 -1)-Puzzle and Related Relocation Problems](https://www.sciencedirect.com/science/article/pii/S0747717108800016)
- Blogs
  - [Kevin Gong](http://kevingong.com/Math/SixteenPuzzle.html)
  - [Neos](https://neos-guide.org/content/15puzzle)
  - [Math-Stackexchange - What is the parity of a permutation in the 15 puzzle](https://math.stackexchange.com/questions/635188/what-is-the-parity-of-permutation-in-the-15-puzzle)
  - [UBC Math](http://www.math.ubc.ca/~cass/courses/m308-02b/projects/grant/fifteen.html)
  - [Wolfram-Math-World](http://mathworld.wolfram.com/15Puzzle.html)
- Wikipedia 
  - [The 15 Puzzle](https://en.wikipedia.org/wiki/15_puzzle) 
  - [Parity of a Permutation](https://en.wikipedia.org/wiki/Parity_of_a_permutation)
  - [Mathematical Invariance](https://en.wikipedia.org/wiki/Invariant_(mathematics))
- Finite Set Theory 
  - [Finite Sets](https://en.wikipedia.org/wiki/Finite_set)
  - [Alternating Groups](https://en.wikipedia.org/wiki/Alternating_group)
  - [Even Permutations (Parity)](https://en.wikipedia.org/wiki/Parity_of_a_permutation)
  - [Cardinality of a Set](https://en.wikipedia.org/wiki/Cardinality)
<a name="optimization-research"></a>
#### Optimization Research 
- [Bit twiddling hacks](https://graphics.stanford.edu/~seander/bithacks.html)
- [Aggregate magic algorithms](http://aggregate.org/MAGIC/)
- [Real-Time-Mantra](http://www.eventhelix.com/realtimemantra/)
- [Agner](https://www.agner.org/)
- [Optimizing Software in C++](https://www.agner.org/optimize/optimizing_cpp.pdf)

<a name="c-plus-plus"></a>
#### C++
- [C++ Reference](https://en.cppreference.com/w/)
- [Stackoverflow](https://stackoverflow.com/)
- [Cplusplus](http://www.cplusplus.com/forum/windows/)
- [Isocpp](https://isocpp.org/std/forums)
- [C++ Patterns ](https://cpppatterns.com/)
<a name="build-config"></a>
#### Build Configuration
[Premake](https://premake.github.io/) is the build system tools used for this repository, I prefer it to [CMake](https://cmake.org/) as I have experience with [Lua](https://www.lua.org/), and have used this framework previously.

<a name="unit-testing"></a>
#### Testing Framework
[GoogleTest](https://github.com/google/googletest) is the Testing framework used for this repository. The main advantages of using this framework is that it is portable, reusable and based on the [xUnit](https://en.wikipedia.org/wiki/XUnit) architecture.
- [Primer](https://github.com/google/googletest/blob/master/googletest/docs/primer.md)

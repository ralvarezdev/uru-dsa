# uru-dsa

**Note:** This repository is archived and read-only.

Projects from the Data Structures and Algorithms college course (URU): C++ console programs, each with its own CMake project.

## Projects

- **`binary-tree`** — binary tree and binary search tree terminal program
- **`college-test1`**, **`college-test2`** — course tests; the first reads linked-list style chains from `src/data/part1.txt` and `part2.txt`, the second is an emergency queue fed from `src/data/unknown.txt`
- **`dungeons-without-dragons`** — dungeons graph with a terminal UI
- **`grades-system`** — student grades backed by `src/data/students.csv`
- **`matriarchy-tree`** — family tree loaded from `src/data/matriarchy.csv`
- **`requests-system-1queue`** — priority queue of requests from `src/data/requests.csv`
- **`sorting-stacks`** — sorts N stacks of N values with a modified Tower of Hanoi approach where only the first node can be popped; it has its own `README.md`

Shared helpers live in `src/lib/` (`terminal/ansiEsc`, `terminal/input`, `terminal/cols`, `namespaces.h`). `submodules/udemy-dsa-cpp` is a git submodule pointing to [ralvarezdev/udemy-dsa-cpp](https://github.com/ralvarezdev/udemy-dsa-cpp).

## Building

```bash
git clone --recurse-submodules https://github.com/ralvarezdev/uru-dsa
cd uru-dsa/grades-system
cmake -S . -B build
cmake --build build
```

Programs that read data files change directory to `src/data` at startup, so run them from within the repository layout.

## License

GNU General Public License v3.0 (see `LICENSE`).

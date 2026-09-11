# HPC-Lab
# Running OpenMP C Programs on Linux

## Prerequisites

Install GCC (includes OpenMP support):

```bash
# Debian / Ubuntu
sudo apt update && sudo apt install build-essential

# Fedora / RHEL
sudo dnf install gcc

# Arch
sudo pacman -S gcc
```

Verify OpenMP is available:

```bash
echo | cpp -fopenmp -dM | grep -i openmp
```

If it prints a line like `#define _OPENMP 201511`, you're good.

## Creating the source file from the terminal

Create a folder for your work and open a new `.c` file in an editor:

```bash
mkdir -p omp-programs
cd omp-programs
nano hello.c
```

In `nano`: type or paste your code, then press `Ctrl+O` → `Enter` to save and `Ctrl+X` to exit.

Other editors:

```bash
vim hello.c      # press i to insert, Esc then :wq to save and quit
gedit hello.c    # GUI editor, if available
code hello.c     # VS Code, if installed
```

Alternatively, write the file directly without an editor:

```bash
cat > hello.c << 'EOF'
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        printf("Hello from thread %d of %d\n",
               omp_get_thread_num(), omp_get_num_threads());
    }
    return 0;
}
EOF
```

Check the file was written:

```bash
cat hello.c
```

## Writing a program

Every OpenMP program needs `#include <omp.h>` and at least one `#pragma omp` directive. Minimal example (`hello.c`):

```c
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        printf("Hello from thread %d of %d\n",
               omp_get_thread_num(), omp_get_num_threads());
    }
    return 0;
}
```

## Compiling

```bash
gcc -fopenmp <source>.c -o <output>
```

Example:

```bash
gcc -fopenmp hello.c -o hello
```

The `-fopenmp` flag is mandatory. Without it, all `#pragma omp` lines are silently ignored and `omp_*` functions fail to link.

Useful extra flags:

| Flag        | Purpose                              |
|-------------|--------------------------------------|
| `-Wall`     | Show all warnings                    |
| `-O2`       | Enable optimizations                 |
| `-lm`       | Link the math library (if using `math.h`) |

## Running

```bash
./<output>
```

Example:

```bash
./hello
```

## Controlling the number of threads

Set the `OMP_NUM_THREADS` environment variable before running:

```bash
OMP_NUM_THREADS=4 ./hello
```

Or export it for the whole session:

```bash
export OMP_NUM_THREADS=8
./hello
```

Inside the code you can also use `num_threads(N)` on a directive or call `omp_set_num_threads(N)`. Code-level settings override the environment variable.

## One-liner: compile and run

```bash
gcc -fopenmp prog.c -o prog && ./prog
```

## Common errors

| Error | Cause / Fix |
|-------|-------------|
| `undefined reference to 'omp_get_thread_num'` | Missing `-fopenmp` |
| `omp.h: No such file or directory` | GCC/OpenMP not installed, or wrong compiler |
| Program runs on a single thread | Missing `-fopenmp`, or `OMP_NUM_THREADS=1` |
| Output order changes between runs | Normal — threads run concurrently |

## Notes

- Thread output order is nondeterministic; don't rely on it.
- Use `omp_get_wtime()` to measure elapsed time for performance comparisons.
- Compile with `clang -fopenmp` if you prefer Clang (may need `libomp-dev` installed).

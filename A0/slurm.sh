#!/bin/bash

####### PLANEX SPECIFIC - DO NOT EDIT THIS SECTION
#SBATCH --clusters=faculty
#SBATCH --partition=planex
#SBATCH --qos=planex
#SBATCH --account=cse570f21
#SBATCH --exclusive
#SBATCH --mem=64000
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr

####### CUSTOMIZE THIS SECTION FOR YOUR JOB
#SBATCH --job-name="changeme"
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --time=00:35:00

# your app invocation should follow
# ...

module load intel/20.2

make clean

make

OMP_NUM_THREADS=1 ./a0 50000 10000
OMP_NUM_THREADS=2 ./a0 50000 10000
OMP_NUM_THREADS=4 ./a0 50000 10000
OMP_NUM_THREADS=8 ./a0 50000 10000
OMP_NUM_THREADS=16 ./a0 50000 10000
OMP_NUM_THREADS=32 ./a0 50000 10000

echo 

OMP_NUM_THREADS=1 ./a0 100000 10000
OMP_NUM_THREADS=2 ./a0 100000 10000
OMP_NUM_THREADS=4 ./a0 100000 10000
OMP_NUM_THREADS=8 ./a0 100000 10000
OMP_NUM_THREADS=16 ./a0 100000 10000
OMP_NUM_THREADS=32 ./a0 100000 10000

make clean

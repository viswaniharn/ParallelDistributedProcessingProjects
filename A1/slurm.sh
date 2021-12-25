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
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=10
#SBATCH --time=00:15:00

module load intel-mpi/2019.5
module load gcc/10.2.0-sse

# if using Intel MPI add need this
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so

make clean

make

srun --mpi=pmi2 ./a1 1000000000
srun --mpi=pmi2 ./a1 10000000000

make clean
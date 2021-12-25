#!/bin/bash

#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr
#SBATCH --job-name="changeme"
#SBATCH --gres=gpu:tesla_v100-pcie-16gb:1
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:10:00

module load gcc/6.3.0
module load cuda

make clean

make

./a3 100000 0.001
./a3 200000 0.001
./a3 400000 0.001
./a3 800000 0.001
./a3 1600000 0.001
./a3 3200000 0.001
./a3 6400000 0.001

make clean
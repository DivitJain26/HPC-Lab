#!/bin/bash
#
# Experiment 2: SLURM batch job script - prints job ID and hostname
#
# Submit:     sbatch myjob.sh
# Check:      squeue -u $USER
# See output: cat out_<jobid>.txt
#
#SBATCH --job-name=test
#SBATCH --output=out_%j.txt
echo "Hello from SLURM job $SLURM_JOB_ID"
hostname
sleep 30

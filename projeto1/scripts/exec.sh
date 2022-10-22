scp -r 'include' pg50393@s7edu2.di.uminho.pt:/home/pg50393/projetos/projeto1/

scp -r 'src' pg50393@s7edu2.di.uminho.pt:/home/pg50393/projetos/projeto1/

scp -r 'Makefile' pg50393@s7edu2.di.uminho.pt:/home/pg50393/projetos/projeto1

ssh pg50393@s7edu2.di.uminho.pt "cd /home/pg50393/projetos/projeto1/;
module load gcc/7.2.0;
make clean;
make;
srun --partition=cpar perf stat /home/pg50393/projetos/projeto1/bin/k_means"

# System Programming Toolkit in C

This repository contains a complete collection of low-level **system programming utilities written in C**, built around POSIX system calls such as  
**fork, execvp, pipe, dup, read, write, open, lseek, wait, kill, signal, time**, and more.  
It provides a modular toolbox for process management, command execution, argument parsing, batch scheduling, directory inspection, file manipulation, redirection handling, and signal-based control.

All functions are grouped into logical components and can be reused independently in larger system-level projects.

---

## 🔧 Command Interpretation & Execution

These functions implement the core of a command-line interpreter:

- **`ligne2Argv(char *ligne)`**  
  Converts a text command into a dynamic `argv` array (tokenization).

- **`afficherArgv(char **argv)`**  
  Displays all arguments cleanly.

- **`argv2Ligne(char **argv)`**  
  Rebuilds a command string from an argument vector.

- **`executer(char **argv, int *pidcom)`**  
  Runs a program, waits for it, returns exit code, and stores its PID.

- **`executerBatch(char **argv)`**  
  Runs a program *without waiting* (asynchronous execution).

- **`miniBash()`**  
  A simple interactive shell that reads, parses, and executes commands.

- **`file2TabArgv(char *file, int *nbarg)`**  
  Loads a file of commands and converts each line into an `argv`.

- **`execFile(char *file)`**  
  Executes commands sequentially from a file.

- **`execFileBatch(char *file)`**  
  Executes all commands in a file *in parallel* and waits for all PIDs.

---

## ⚙️ Structured Parallel Execution

A custom structure describes each launched command:

```c
typedef struct commande {
    int pid;
    int statut;   // -1 not started, 0 finished, 1 running
    int retour;   // exit status
    time_t debut; // start timestamp
    time_t fin;   // end timestamp
    char **argv;  // arguments
} com;
Associated functions:

file2TabCom(char *filename, int *nbcom)
Loads commands and builds a table of com structures.

execFile2(char *file)
Executes commands and produces a detailed runtime report.

execFileBatchCom(char *file)
Executes all commands in parallel and prints a report whenever one ends.

execFileBatchLimite(char *file, int N)
Executes commands in parallel but limits concurrency to N processes, launching new commands as soon as previous ones end.

📂 File & Directory Utilities
Low-level operations implemented using open, read, write, lseek, lockf:

Init()
Creates a binary file with four integers set to 100.

Reserve(int n)
Atomically decrements the n-th integer in the file with file locking.

Ls(char *rep)
Executes and prints the result of ls rep.

LsDansFichier(char *rep, char *fich)
Saves the listing of a directory into a file.

NbFichierPrint(char *rep)
Prints the result of ls rep | wc -l.

NbFichier(char *rep)
Returns the number of files using a programmatic pipeline.

🔥 Enhanced Shell Features
miniBash2()
Adds redirection support (>, <, >>) using dup.

miniBash3()
Extended version for more advanced command handling.

📡 Signal-Driven Programs
affiche(int n, char *msg)
Prints a message every second for n seconds.

affiche2(int n, char *msg)
Similar but handles SIGINT with password validation.

timeout_run(int n, char **cmd)
Runs a program and kills it if it exceeds n seconds.

execFileBatchRapport(char *file)
Parallel execution with status reports every second.

🧪 Utility & Support Functions
com1_puis_com2_et_com3()
Executes one command, then runs two others in parallel.

exo2_signaux()
Multi-process signal demonstration (SIGUSR1 / SIGUSR2).

TEE(char *filename, int append)
Re-implementation of the Unix tee command (write to stdout + file).

Ls2TabChar(char *rep)
Returns directory content as a char ** array.

✔️ Summary
This repository serves as a complete modular toolkit for learning and extending UNIX-style system programming.
Each function is independent, reusable, and based purely on POSIX primitives, making this collection valuable for building shells, schedulers, monitors, execution engines, or any low-level system software requiring fine control over processes, files, directories, and signals.
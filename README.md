# Query System

This project implements a package query system for a logistics delivery network.

## 🧠 Objective

The objective is to implement an efficient search system for a logistics system that contains large volumes of simultaneous packages.
The system enables two types of queries:
1. Package:
   - Given a package ID, it shows the history of events for the package up to the current moment.
2. Client:
   - Given a sender or recipient, it shows the packages that are registered under their name.

## 🛠️ Project Structure

```
├── src/
│   ├── main.cpp                # Main function            
│   ├── Evento.cpp              # Representation of an Event in the system
│   ├── ListaEventos.cpp        # List of Events in the System
│   ├── IndiceClientes.cpp      # Index for client search
│   ├── IndicePacotes.cpp       # Index for package search
│   └── IndiceEventos.cpp       # Index for event search
├── include/                    # Corresponding headers
├── bin/                        # Compiled binaries
├── input.txt                   # Event input file
├── README.md                   # This file
└── Makefile                    # Automated compilation
```

## ▶️ Execution

### Compile
```bash
make
```

### Run
```bash
./bin/tp3.out input.txt
```

> The `input.txt` file should contain the system configuration (logistics parameters, connection matrix and packages to be transported).

## 📊 Experimental Analysis

The simulation was used to investigate the impact of different factors, such as:

- Variation in the number of events
- Number of packages
- Number of clients

### Observed metrics:
- Average search time
- System execution time

Graphs and tables are available in the LaTeX documentation.

## 🔐 Robustness and Engineering

The project applies:
- Defensive programming (null pointer checks, array bounds, file opening failures)
- Dynamic memory release (custom destructors, `delete[]`)
- Input validation and state control

## 🧪 Technologies

- C++11
- Data structures: linked lists, AVL trees
- Tree rebalancing algorithms

## 📘 Documentation

The complete technical documentation was prepared in LaTeX and includes:
- Complexity analysis of main functions
- Robustness strategies
- Experimental analysis with graphs

## 📝 License

This project is for academic and personal use. Feel free to study, modify and expand.
# Parking-Management-System

## Overview

This project implements a parking management system capable of handling multiple parking lots, vehicle entries and exits, and generating billing reports. It uses linked data structures to manage parking lots, vehicles, and their respective records. This was my first project with this level of complexity, introducing me to advanced data structures and algorithms in C.

## Features

- **Parking Lot Management**: Create, list, and remove parking lots with specific capacities and pricing rules.
- **Vehicle Management**: Register vehicle entries and exits, ensuring valid timestamps and license plate formats.
- **Billing Reports**: Calculate and display daily revenue for parking lots.
- **Sorting and Searching**: Sort parking lots and vehicles using merge sort for efficient data handling.
- **Error Handling**: Validate inputs such as dates, times, and license plates.

## Project Structure
```
Parking-Management-System/
├── estruturas.h  # Defines the data structures for the project
├── funcoes.c    # Contains the implementation of all functions
├── funcoes.h    # Function prototypes and auxiliary definitions
└── project.c    # Main file to run the program
```
## How to Build

To compile the project, use the following command:

```bash
gcc -o project project.c [funcoes.c]
```
This will generate an executable named project.

## How to Run
After building the project, run the executable and provide input through the terminal:
`./project`

### Example Usage
1. **Create a Parking Lot:**
`p "Central Park" 50 1.5 2.0 20.0`
Creates a parking lot named "Central Park" with a capacity of 50 vehicles, and specific pricing rules.
2. **Register a Vehicle Entry:**
`e "Central Park" AA-12-BB 2025-04-13 14:30`
Registers a vehicle with license plate `AA-12-BB` entering "Central Park" on April 13, 2025, at 14:30.
3. **Register a Vehicle Exit:**
`s "Central Park" AA-12-BB 2025-04-13 16:00`
Registers the exit of the vehicle and calculates the total cost.
4. **Generate Billing Report:**
`f "Central Park"`
Displays the total revenue for "Central Park".

## Dependencies
- C Standard Library: Includes `<stdio.h>`, `<stdlib.h>`, `<string.h>`, and `<ctype.h>`.

## Key Components
#### Data Structures
- `Carro`: Represents a vehicle with entry details.
- `Parque`: Represents a parking lot with capacity, pricing, and a linked list of vehicles.
- `Registo`: Represents a record of vehicle entries and exits.

#### Functions
Parking Lot Management:
 - `cria_parque`: Creates a new parking lot.
 -`remove_parque`: Removes a parking lot and its associated records.
Vehicle Management:
- `entrada_veiculos`: Registers a vehicle entry.
- `saida_veiculos`: Registers a vehicle exit and calculates the cost.
Billing:
- `faturacao`: Generates a billing report for a parking lot.
Sorting:
- `ordena_lista_carros`: Sorts vehicles or parking lots using merge sort.

## Challenges and Learning
This project was my first experience with complex data structures and algorithms in C. It taught me how to manage linked lists, implement sorting algorithms, and handle real-world constraints like date and time validation.

## Author
Developed by Guilherme Monteiro. For more information, visit [my GitHub profile](https://github.com/Monteir016).

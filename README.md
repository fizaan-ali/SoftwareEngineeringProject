# Software Engineering Project

A comprehensive software engineering project from the 3rd semester BSIT program, applying software engineering principles, object-oriented design, and database integration.

## Overview

This project demonstrates the application of software engineering best practices including:
- Object-oriented programming (OOP) principles
- Software design patterns
- Database integration
- User interface design
- Project documentation
- Version control and collaboration

## Project Description

A C++ application that showcases proper software engineering methodology with comprehensive documentation, UML design, and database-backed functionality.

## Tech Stack

- **Language**: C++
- **Compiler**: GCC/G++ (C++11 standard)
- **Database**: SQLite
- **Documentation**: UML Diagrams, Design Documentation
- **Build System**: Direct g++ compilation

## Repository Structure

```
SoftwareEngineeringProject/
├── Project/
│   ├── main.cpp          # Main application source code
│   └── accounts.db       # SQLite database
├── UML Diagrams/         # Project design diagrams
├── Project Report.pdf    # Comprehensive project documentation
├── README.md             # This file
└── LICENSE               # MIT License
```

## Key Features

### Core Functionality
- User account management
- Database-backed data persistence
- Object-oriented design
- Proper error handling
- User-friendly interface

### Engineering Best Practices
- Clear code organization
- Meaningful variable and function names
- Comprehensive project documentation
- UML design documentation
- Proper separation of concerns

## Compilation

### Prerequisites
- GCC/G++ compiler with C++11 support
- SQLite development libraries

### Install SQLite (if needed)
```bash
# On Ubuntu/Debian
sudo apt-get install libsqlite3-dev

# On macOS
brew install sqlite3
```

### Compile
```bash
g++ -std=c++11 -o main Project/main.cpp -lsqlite3
```

### Compile with strict flags
```bash
g++ -Wall -Wextra -std=c++11 -o main Project/main.cpp -lsqlite3
```

### Run
```bash
./main
```

## Project Documentation

### UML Diagrams
The `UML Diagrams/` folder contains:
- Class diagrams showing object relationships
- Use case diagrams demonstrating user interactions
- Sequence diagrams for process flows
- State diagrams for system states

### Project Report
The `Project Report.pdf` contains:
- Project requirements and objectives
- System design and architecture
- Implementation details
- Testing and validation results
- Lessons learned and conclusions

## Database Schema

The project uses SQLite database (`accounts.db`) for persistent data storage with properly designed tables for account management and related functionality.

### Key Database Features
- Relational schema design
- Proper data types and constraints
- Foreign key relationships
- Efficient indexing

## Code Organization

### Main Components
- **Data Management**: Database operations and queries
- **Business Logic**: Core application functionality
- **User Interface**: Interactive user input and output
- **Utilities**: Helper functions and constants

## Software Engineering Principles Applied

### 1. Object-Oriented Design
- Classes for modeling entities
- Encapsulation of data and behavior
- Inheritance and polymorphism where appropriate

### 2. Design Patterns
- Appropriate use of design patterns
- Separation of concerns
- Modularity and reusability

### 3. Database Design
- Normalized database schema
- Proper use of relationships
- Transaction integrity

### 4. Documentation
- Code comments for clarity
- README documentation
- UML diagrams for architecture
- Project report for stakeholders

### 5. Error Handling
- Input validation
- Exception handling
- Graceful error messages

## Development Process

This project follows a structured development approach:

1. **Requirements Analysis**: Understanding project needs
2. **Design Phase**: Creating UML diagrams and architecture
3. **Implementation**: Writing clean, well-documented code
4. **Testing**: Validating functionality
5. **Documentation**: Recording design decisions and usage

## Testing

To test the application:

1. Compile the source code
2. Run the executable
3. Test various use cases:
   - Account creation
   - Data retrieval
   - Data modification
   - Data deletion
   - Error conditions

## Building for Release

```bash
# Compile with optimizations
g++ -O2 -Wall -Wextra -std=c++11 -o main Project/main.cpp -lsqlite3

# Or with debugging symbols
g++ -g -Wall -Wextra -std=c++11 -o main Project/main.cpp -lsqlite3
```

## Common Compilation Issues

### SQLite linking errors
```bash
# Make sure to link SQLite
g++ -std=c++11 -o main main.cpp -lsqlite3
```

### C++11 features not recognized
```bash
# Explicitly specify C++11 standard
g++ -std=c++11 -o main main.cpp
```

## Learning Outcomes

This project demonstrates:
- ✅ Understanding of software engineering lifecycle
- ✅ Proper OOP design and implementation
- ✅ Database integration with C++
- ✅ Documentation and communication skills
- ✅ Project planning and management
- ✅ Testing and validation

## Future Enhancements

Possible improvements for future versions:
- Web interface using web frameworks
- Advanced database features (stored procedures, views)
- Enhanced user interface
- Additional features and modules
- Performance optimization

## License

MIT License - See LICENSE file for details

## Author

Fizaan Ali  
Government College University, Gujranwala  
BS Information Technology, 3rd Semester

## Instructor Notes

This project was developed as part of the Software Engineering course. It demonstrates the application of software engineering principles learned throughout the semester.

---

**Project Status**: ✅ Complete  
**Grade**: [To be filled by instructor]  
**Submission Date**: [Academic year]


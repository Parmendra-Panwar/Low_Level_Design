# C++ Low Level Design (LLD)
Welcome to my **C++ Low Level Design (LLD)** learning repository.

This repository documents my journey of learning **Low Level Design** from the ground up using **C++**. I first focused on building a strong understanding of the fundamentals.

The learning path begins with **Core C++**, moves through **Object-Oriented Programming**, **UML**, and **SOLID Principles**, and gradually progresses toward **Design Patterns** and **Real-world Low Level Design Projects**.

---

> **Note**
>
> GitHub sorts folders alphabetically, so folders such as **10** may appear before **2**.
> While exploring this repository, please follow the folders in **numerical order** (`0 → 1 → 2 → 3 ...`) instead of GitHub's default ordering.

## full folder structure 

```text
Low_Level_Design
│
├── 0. BasicCpp
├── 1. OOPM
├── 2. UML_Di
├── 3. SOLID (All 5 principles)
├── 4. DocEditProject
│
├── 5. DesignPattern
│   ├── Strategy
│   ├── Factory
│   └── Singleton
│
├── 6. ZomatoClone
│
├── 7. DesignPattern
│   ├── Observer
│   └── Decorator
│
├── 8. NotificationSystem
│
├── 9. DesignPattern
│   ├── Command
│   ├── Adapter
│   └── Facade
│
├── 10. Spotify
│
├── 11. DesignPattern
│   ├── Composite
│   ├── Template Method
│   ├── Proxy
│   ├── Bridge
│   └── Supply Chain Example
│
├── 12. PaymentGateway
├── 13. CoupanManagement
├── 14. InventoryManagement
├── 15. Tinder Clone
│
├── 16. Design Pattern
|   ├── Builder.cpp
|   ├── Iterator.cpp
|   └── Flyweight.cpp
|
├── 17. Splitwise
|
├── 18. Design Pattern
|   └── statePattern.cpp
|
└── 19. Board Games
    ├── tictactoe.cpp
    └── snakeLadder.cpp
```

---

## Foundation of Low Level Design

The first few folders cover the essential concepts required to understand LLD Patterns.

| Folder | Topic | Description |
|--------|-------|-------------|
| 0.0 | Basic C++ | Core C++ concepts required before starting Low Level Design. |
| 1.0 | Object-Oriented Programming | Covers Classes, Objects, Encapsulation, Inheritance, Polymorphism and Abstraction. |
| 2.0 | UML Diagrams | Introduction to UML diagrams used to visualize and communicate software design. |
| 3.0 | SOLID Principles | Five object-oriented design principles for writing maintainable, extensible and scalable software. |

---

## Design Patterns

Design Patterns are reusable solutions to commonly occurring software design problems.

Three major categories of Design Patterns:

---

## Creational Design Patterns

Creational patterns focus on **how objects are created**. Their primary goal is to make object creation flexible while reducing unnecessary coupling between different parts of the application.

| Pattern | Purpose |
|----------|---------|
| Singleton | Ensures that only one instance of a class exists throughout the application. |
| Factory Method | Creates objects without exposing the object creation logic to the client. |
| Builder | Constructs complex objects step by step while separating construction from representation. |

---

## Structural Design Patterns

Structural patterns focus on **how classes and objects are organized** to build larger, flexible software structures.

| Pattern | Purpose |
|----------|---------|
| Adapter | Allows incompatible interfaces to work together without modifying existing code. |
| Bridge | Separates abstraction from implementation so both can evolve independently. |
| Composite | Represents part-whole hierarchies so individual objects and groups can be treated uniformly. |
| Decorator | Adds new functionality to objects dynamically without modifying their original implementation. |
| Facade | Provides a simplified interface to a complex subsystem. |
| Flyweight | Reduces memory usage by sharing common object state between multiple objects. |
| Proxy | Provides a placeholder or surrogate object to control access to another object. |

---

## Behavioral Design Patterns

Behavioral patterns focus on **communication and responsibility between objects**. They define how objects collaborate while keeping the system loosely coupled.

| Pattern | Purpose |
|----------|---------|
| Strategy | Encapsulates interchangeable algorithms and allows them to be selected at runtime. |
| Observer | Defines a one-to-many dependency so that multiple objects receive updates automatically. |
| Command | Encapsulates a request as an object, enabling queuing, logging and undo operations. |
| Template Method | Defines the skeleton of an algorithm while allowing subclasses to customize individual steps. |
| Iterator | Provides a standard way to traverse elements of a collection without exposing its internal structure. |

---

## Low Level Design Projects

After understanding the fundamentals of Object-Oriented Programming and SOLID Principles, I moves toward implementing complete Low Level Design problems.


| Folder | Project | Description |
|--------|---------|-------------|
| 4.0 | Document Editor | A simple document editing system demonstrating the transition from OOP concepts to complete Low Level Design. |
| 6.0 | Zomato | Design of a food delivery platform covering restaurants, menus, ordering workflow and user interactions. |
| 8.0 | Notification System | A flexible notification service supporting multiple notification channels with an extensible architecture. |
| 10.0 | Spotify | Design of a music streaming platform with playlists, users, songs and playback management. |
| 12.0 | Payment Gateway | A payment processing system supporting multiple payment methods through interchangeable implementations. |
| 13.0 | Coupon Management System | Design of a coupon engine capable of validating and applying different coupon strategies. |
| 14.0 | Inventory Management System | Inventory management solution focusing on products, stock management and warehouse operations. |
| 15.0 | Tinder Clone | Simplified matchmaking system demonstrating user management, matching logic and interaction flow. |

Many of the Low Level Design projects in this repository naturally apply the same principles to solve real-world problems.

| Project | Major Concepts |
|---------|----------------|
| Document Editor | Object-Oriented Programming, SOLID Principles, Class Relationships |
| Zomato | Object Composition, Separation of Responsibilities, Extensible Design |
| Notification System | Strategy Pattern, Open/Closed Principle, Dependency Inversion |
| Spotify | Object Relationships, Composition, Scalable Class Design |
| Payment Gateway | Strategy Pattern, Factory Pattern, Runtime Polymorphism |
| Coupon Management System | Strategy Pattern, Business Rule Encapsulation |
| Inventory Management System | Factory Pattern, Encapsulation, Modular Design |
| Tinder Clone | Object Modeling, Association, Business Logic Separation |

> **Note**
>
> A single project may demonstrate multiple Design Patterns and SOLID principles simultaneously. The objective is to understand how these concepts work together in real software rather than studying them in isolation.

---

## Who Is This Repository For?

This repository is intended for:

- Students learning Object-Oriented Programming and Low Level Design
- Developers preparing for Software Development Engineer SDE 1 interviews
- Anyone interested in Design Patterns and Software Architecture

Whether you're starting from scratch or revising before interviews, the repository is designed to provide a structured learning experience.

---

## What i've learned & Path I used And Skills Covered

For the best learning experience, follow the repository in the recommended order.

1. Walk through the Basic C++ section.
2. Learn Object-Oriented Programming concepts.
3. Understand UML Diagrams.
4. Understand the SOLID Principles.
5. Start with basic Document Editor project.
6. Learn each Design Pattern individually along side there related project.
7. Try extending the projects with your own features.

- C++
- Object-Oriented Design
- Low Level Design (LLD)
- Software Design Principles
- Design Patterns
- UML
- Code Reusability
- Clean Architecture
- Modular Design
- Extensible Software Development


Rather than simply reading the code, try implementing each concept on your own before comparing it with the solution provided in the repository.
---

## Future Improvements

This repository is actively evolving. Some planned additions include:

- Remaining GoF Design Patterns
- Additional Low Level Design case studies
- Multithreading and Concurrency examples
- Parking Lot System
- Library Management System
- Elevator System
- Hotel Management System
- Cab Booking System
- Online Shopping System
- Splitwise
- ATM Design
- Chess
- Snake & Ladder
- Logging Framework
- Cache Implementations (LRU, LFU)
- Unit Testing Examples

---

#### Suggestions, improvements and constructive feedback are always welcome.

If you find any issue, have a better approach or want to contribute to the repository, feel free to open an Issue or submit a Pull Request.

---

## Repository Goals

The objective of this repository is not just to implement design patterns.

The focus is on understanding the reasoning behind good software design, writing maintainable code, and learning how real-world software systems are structured.

---

If you found this repository useful, consider giving it a ⭐.
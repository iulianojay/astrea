# Extensibility

Astrea is designed to be highly extensible, allowing users to add custom force models, coordinate frames, propagators, and analysis tools without modifying the core library. This document outlines the extensibility patterns and interfaces that enable customization.

## Extensibility Principles

There are many solutions for extensibility in C++. Astrea's approach is generically based on the following principles:

### **Users don't want to inherit your classes**
In general, just using a 3rd party library is already a burden. Requiring users to directly inherit your type structures, and all the assumptions that come with, can be a cumbersome and exhausting. As such, where extensibility is useful, common, or well-defined, Astrea uses type-erasure and leans on concepts to allow users to implement their own types without needing to inherit from Astrea's type system.

In cases where polymorphism makes sense, and extensibility is less common, Astrea will use minimal inheritance. A key example of this is the `PerturbingForce`. Generally, users won't be writing many of their own forces, they'll just use the ones available in the library. This class also only has a single virtual method, so the runtime overhead is minimal. If many users started writing their own forces, we would consider switching to a type-erased version of the `PerturbingForce` interface as well. A similar case was made for the `EquationsOfMotion`.

### **Compile-time is king**
Extensibility mechanisms should introduce minimal runtime overhead, ensuring that performance-critical applications are not adversely affected. It's easy to design systems of functions that check for properties at runtime and throw errors or try to handle the behavior smoothly. While this tends to be easier for developers, the authors believe that compile-time checks are considerably safer mechanisms for handling bad-behavior. Wherever possible, Astrea tries to lean on concepts, and static type checking mechanisms to ensure performance and accuracy. This makes it easier to avoid throwing errors, safely declare function and class behavior, and make use of the powerful C++ compile-time optimizations.

A benefit of compile-time guarantees is that a lot of information can be optimized away. A runtime object representing a frame, for example, might include the center, the axis, the parent object (probably with lifetime issues), maybe a time system, an offset (or several), etc. Every time you need this, you build out everything it needs or you pass it around, adding a hit to memory and speed, complexity to your code, and constant checks for sanity, correctness, and consistency. In Astrea, all this is done by the compiler as much as possible. 

The result of this style tends to be difficulty for maintainers of the core library. Complex trees of template packs, strange bugs and difficult corner cases, platform-dependent behaviors, and so on. The authors believe this trade-off is worth the price. A performant, compile-time library pays for itself very quickly.

### **Provide examples, not solutions**
Many libraries that receive wide adoption grow beyond the scope of what can be reasonable maintained - a class for every problem, a function for every condition, a structure for every _thing_ a user might want to build, and don't forget the `ThingBuilder`! The authors believe that this decision to expand without boundaries leads to untennable maintainence, massive overhead, and a steadily growing set of unfixable problems. A feature that touches ten others might require ten updates to be fixed. A satellite class defined with good intentions and best practices might end up being the design that restricts the entire library once a spacecraft factory, a spacecraft container, a spacecraft interface, and a spacecraft watcher are all strictly defined and require updates.

With this in mind, Astrea strives for a minimalist approach. Instead of solving all problems and implementing all interfaces, Astrea prefers to define high level interfaces and abstractions that allows users to build out a type system they prefer. As much as possible, extensibility points are defined through type-erased interfaces with a few examples for users to expand on. Astrea is not meant to be a repository for every possible definition of a system of astrodynamic types, but a foundation on which others can build freely.
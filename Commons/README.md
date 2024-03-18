# Arcade-Commons

## Overview

This repository contains the definition of the common interfaces to share for
the Arcade project.

## How to use

### Libraries

A library should export a function with the following prototype :

```cpp
extern "C" arc::ILibrary *entrypoint();
```

It should allocate the `arc::ILibrary` with the `new` operator.

### Games

A game should export a function with the following prototype :

```cpp
extern "C" arc::IGame *entrypoint();
```

It should allocate the `arc::IGame` with the `new` operator.

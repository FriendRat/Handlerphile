# Handlerphile

## A file handler for C++

Handlerphile is a header only library that uses the {r}[Contextual](https://github.com/FriendRat/contextual) context manager to provide a python-like file handler that simplifies the standard mechanisms for safe file management in C++.

## Requirements
This library requires C++17 or greater. It was built and tested on Linux using g++; compatibility with other operating systems and compilers has not been confirmed.

This library also requires the C++ library {r}[Contextual](https://github.com/FriendRat/contextual).

## How to use it

The following is an example codeblock showcasing the use of HandlerFile

```c++
with {
    FileHandler(<filename>, <mode>, <verbose>)(
        [&](auto filehandler){
            ...
        }
    )
}
```

The sigunature of the `FileHandler` class is 
```c++
FileHandler(const std::string filename, std::ios::openmode=std::ios::in | std::ios::out, bool verbose=false);
```
In the above example snippet, the argument `filehandler` (the name is user specified) is a pointer to a struct. It is initialized by the `filename` and `std::ios::openmode` arguments passed to `FileHandler` at initialization. This struct has the following attributes and methods

```c++
struct IData {
    std::fstream file;
    unsigned int length();
    std::string read();
}
```
The file is manipulated through the `file` attribute. The `length` method returns the number of characters in the file and the `read` method returns the entire contents of the file as a string.

The verbose boolean parameter toggles extra logging on and off. 

An example file has been include and can be compiled via `$ make example`.

## Exception handling

FileHandler suppress almost all exceptions and instead issues a warning to `std::cerr`. However, there are two important exceptions. If the file with filename specified cannot be opened for any reason, an exception is thrown. Similarly, FileHandler attempts to close the file stream after the code block has been executed. If it is unable to do this for any reason, an exception is thrown.
